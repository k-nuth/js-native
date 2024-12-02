// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/string_list.h>
#include <kth/js-native/string_list.hpp>
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


void core_string_list_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    kth_string_list_t res = kth_core_string_list_construct();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void core_string_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    auto obj = (kth_string_list_t)v8::External::Cast(*args[0])->Value();
    kth_core_string_list_destruct(obj);
}

void core_string_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsString()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    auto obj = (kth_string_list_t)v8::External::Cast(*args[0])->Value();
    v8::String::Utf8Value str(isolate, args[1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    kth_core_string_list_push_back(obj, *str);
}

}  // namespace kth::js_native
