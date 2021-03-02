// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/input_list.h>
#include <kth/js-native/chain/input_list.hpp>
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

void chain_input_list_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_list_construct_default function requires 0 arguments.");
        return;
    }


    kth_input_list_t res = kth_chain_input_list_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_input_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_list_push_back function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument list (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument elem (#2). Required to be IsExternal.");
        return;
    }

    kth_input_list_t list = (kth_input_list_t)v8::External::Cast(*args[0])->Value();
    kth_input_t elem = (kth_input_t)v8::External::Cast(*args[1])->Value();

    kth_chain_input_list_push_back(list, elem);
}

void chain_input_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_list_destruct function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument list (#1). Required to be IsExternal.");
        return;
    }

    kth_input_list_t list = (kth_input_list_t)v8::External::Cast(*args[0])->Value();
    kth_chain_input_list_destruct(list);
}

void chain_input_list_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_list_count function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument list (#1). Required to be IsExternal.");
        return;
    }

    kth_input_list_t list = (kth_input_list_t)v8::External::Cast(*args[0])->Value();

    kth_size_t res = kth_chain_input_list_count(list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_input_list_nth(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_list_nth function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument list (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument n (#2). Required to be IsNumber.");
        return;
    }

    kth_input_list_t list = (kth_input_list_t)v8::External::Cast(*args[0])->Value();
    kth_size_t n = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_input_t res = kth_chain_input_list_nth(list, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

}  // namespace kth::js_native
