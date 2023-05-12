// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/settings.h>

#include <kth/js-native/config/settings.hpp>

#include <kth/js-native/config/blockchain_settings.hpp>
#include <kth/js-native/config/database_settings.hpp>
#include <kth/js-native/config/network_settings.hpp>
#include <kth/js-native/config/node_settings.hpp>
#include <kth/js-native/helper.hpp>

namespace kth::js_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Global;

using v8::Object;
using v8::String;
using v8::Boolean;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Number;
using v8::Persistent;
using v8::Function;
using v8::Uint8Array;
using v8::ArrayBuffer;
namespace detail {
v8::Local<v8::Object> config_settings_to_js(Isolate* isolate, kth_settings const& setts) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, string_to_js(isolate, "node"), detail::config_node_settings_to_js(isolate, setts.node));
    setr = res->Set(ctx, string_to_js(isolate, "chain"), detail::config_blockchain_settings_to_js(isolate, setts.chain));
    setr = res->Set(ctx, string_to_js(isolate, "database"), detail::config_database_settings_to_js(isolate, setts.database));
    setr = res->Set(ctx, string_to_js(isolate, "network"), detail::config_network_settings_to_js(isolate, setts.network));
    return res;
}

kth_settings config_settings_to_cpp(Isolate* isolate, v8::Local<v8::Object> const& setts) {
    auto ctx = isolate->GetCurrentContext();
    kth_settings res;

    res.chain = config_blockchain_settings_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "chain")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());
    res.database = config_database_settings_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "database")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());
    res.network = config_network_settings_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "network")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());
    res.node = config_node_settings_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "node")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());

    return res;
}
}

void config_settings_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_settings_default function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument network (#1). Required to be IsNumber.");
        return;
    }

    kth_network_t network = network_to_cpp(isolate, args[0]);
    kth_settings setts = kth_config_settings_default(network);
    auto obj = detail::config_settings_to_js(isolate, setts);
    args.GetReturnValue().Set(obj);
}

void config_settings_get_from_file(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_settings_get_from_file function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Wrong argument type for argument path (#1). Required to be IsString.");
        return;
    }

    v8::String::Utf8Value path(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());

    kth_settings* settings;
    char* error_message;
    kth_bool_t res = kth_config_settings_get_from_file(*path, &settings, &error_message);

    auto ctx = isolate->GetCurrentContext();
    auto obj = v8::Object::New(isolate);
    auto setr = obj->Set(ctx, string_to_js(isolate, "ok"), Boolean::New(isolate, res != 0));

    if (res == 0) {
        setr = obj->Set(ctx, string_to_js(isolate, "message"), string_to_js(isolate, error_message));
    } else {
        setr = obj->Set(ctx, string_to_js(isolate, "settings"), detail::config_settings_to_js(isolate, *settings));
        kth_config_settings_destruct(settings);
    }
    args.GetReturnValue().Set(obj);
}

// void config_settings_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         throw_exception(isolate, "Wrong number of arguments. config_settings_destruct function requires 1 arguments.");
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong argument type for argument settings (#1). Required to be IsExternal.");
//         return;
//     }

//     void* settings = args[0]->arg_conv_func;
//     kth_config_settings_destruct(settings);
// }

}  // namespace kth::js_native
