// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/database_settings.h>
#include <kth/capi/platform.h>

#include <kth/js-native/config/database_settings.hpp>
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
v8::Local<v8::Object> config_database_settings_to_js(Isolate* isolate, kth_database_settings const& setts) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, string_to_js(isolate, "directory"), string_to_js(isolate, setts.directory));
    setr = res->Set(ctx, string_to_js(isolate, "dbMode"), Number::New(isolate, setts.db_mode));
    setr = res->Set(ctx, string_to_js(isolate, "reorgPoolLimit"), Number::New(isolate, setts.reorg_pool_limit));
    setr = res->Set(ctx, string_to_js(isolate, "dbMaxSize"), Number::New(isolate, setts.db_max_size));
    setr = res->Set(ctx, string_to_js(isolate, "safeMode"), Boolean::New(isolate, setts.safe_mode != 0));
    setr = res->Set(ctx, string_to_js(isolate, "cacheCapacity"), Number::New(isolate, setts.cache_capacity));
    return res;
}

kth_database_settings config_database_settings_to_cpp(Isolate* isolate, v8::Local<v8::Object> const& setts) {
    auto ctx = isolate->GetCurrentContext();
    kth_database_settings res;

    string_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "directory")).ToLocalChecked()->ToString(ctx).ToLocalChecked(),
        &res.directory);

    res.db_mode = db_mode_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "dbMode")).ToLocalChecked());
    res.reorg_pool_limit = setts->Get(ctx, string_to_js(isolate, "reorgPoolLimit")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.db_max_size = setts->Get(ctx, string_to_js(isolate, "dbMaxSize")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.safe_mode = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "safeMode")).ToLocalChecked());
    res.cache_capacity = setts->Get(ctx, string_to_js(isolate, "cacheCapacity")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    return res;
}
}

void config_database_settings_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_database_settings_default function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument net (#1). Required to be IsNumber.");
        return;
    }

    kth_network_t net = network_to_cpp(isolate, args[0]);

    kth_database_settings res = kth_config_database_settings_default(net);
    args.GetReturnValue().Set(detail::config_database_settings_to_js(isolate, res));
}

}  // namespace kth::js_native
