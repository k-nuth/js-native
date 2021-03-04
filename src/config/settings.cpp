// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/settings.h>

#include <kth/js-native/config/settings.hpp>
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

    kth_network_t network = to_kth_network_t(isolate, args[0]);

    kth_settings res = kth_config_settings_default(network);
    args.GetReturnValue().Set(External::New(isolate, res));
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

    char const* path = to_string(isolate, args[0]);
    kth_settings* settings;
    char* error_message;

    kth_bool_t res = kth_config_settings_get_from_file(path, &settings, &error_message);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void config_settings_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_settings_destruct function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument settings (#1). Required to be IsExternal.");
        return;
    }

    void* settings = args[0]->arg_conv_func;
    kth_config_settings_destruct(settings);
}

}  // namespace kth::js_native
