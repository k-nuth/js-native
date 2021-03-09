// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/script.h>
#include <kth/js-native/chain/script.hpp>
#include <kth/js-native/chain/tools.hpp>
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


void chain_script_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_construct_default function requires 0 arguments.");
        return;
    }


    kth_script_t res = kth_chain_script_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_script_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_construct function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type for argument encoded (#1). Required to be IsUint8Array.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument prefix (#2). Required to be IsBoolean.");
        return;
    }

    v8::Local<v8::Uint8Array> encoded_arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    uint8_t* encoded = (uint8_t*)encoded_arr->Buffer()->GetContents().Data();
    kth_size_t n = encoded_arr->Length();
    kth_bool_t prefix = bool_to_cpp(isolate, args[2]);

    kth_script_t res = kth_chain_script_construct(encoded, n, prefix);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_script_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_destruct function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#1). Required to be IsExternal.");
        return;
    }

    kth_script_t script = (kth_script_t)v8::External::Cast(*args[0])->Value();

    kth_chain_script_destruct(script);

}

void chain_script_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_is_valid function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#1). Required to be IsExternal.");
        return;
    }

    kth_script_t script = (kth_script_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_script_is_valid(script);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_script_is_valid_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_is_valid_operations function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#1). Required to be IsExternal.");
        return;
    }

    kth_script_t script = (kth_script_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_script_is_valid_operations(script);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_script_satoshi_content_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_satoshi_content_size function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#1). Required to be IsExternal.");
        return;
    }

    kth_script_t script = (kth_script_t)v8::External::Cast(*args[0])->Value();

    kth_size_t res = kth_chain_script_satoshi_content_size(script);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_script_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_serialized_size function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument prefix (#2). Required to be IsBoolean.");
        return;
    }

    kth_script_t script = (kth_script_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t prefix = bool_to_cpp(isolate, args[1]);

    kth_size_t res = kth_chain_script_serialized_size(script, prefix);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_script_to_string(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_to_string function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument active_forks (#2). Required to be IsNumber.");
        return;
    }

    kth_script_t script = (kth_script_t)v8::External::Cast(*args[0])->Value();
    uint32_t active_forks = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    char const* res = kth_chain_script_to_string(script, active_forks);
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void chain_script_type(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_type function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#1). Required to be IsExternal.");
        return;
    }

    kth_script_t script = (kth_script_t)v8::External::Cast(*args[0])->Value();

    char const* res = kth_chain_script_type(script);
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void chain_script_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_to_data function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument prefix (#2). Required to be IsBoolean.");
        return;
    }

    kth_script_t script = (kth_script_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t prefix = bool_to_cpp(isolate, args[1]);
    kth_size_t size;

    uint8_t const* res = kth_chain_script_to_data(script, prefix, &size);
    args.GetReturnValue().Set(byte_array_to_js(isolate, res, size));
}

void chain_script_sigops(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_script_sigops function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument embedded (#2). Required to be IsBoolean.");
        return;
    }

    kth_script_t script = (kth_script_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t embedded = bool_to_cpp(isolate, args[1]);

    kth_size_t res = kth_chain_script_sigops(script, embedded);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

}  // namespace kth::js_native
