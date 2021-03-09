// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/input.h>
#include <kth/js-native/chain/input.hpp>
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

void chain_input_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_construct_default function requires 0 arguments.");
        return;
    }


    kth_input_t res = kth_chain_input_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_input_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_construct function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument previous_output (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#2). Required to be IsExternal.");
        return;
    }

    if ( ! args[2]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument sequence (#3). Required to be IsNumber.");
        return;
    }

    kth_outputpoint_t previous_output = (kth_outputpoint_t)v8::External::Cast(*args[0])->Value();
    kth_script_t script = (kth_script_t)v8::External::Cast(*args[1])->Value();
    uint32_t sequence = args[2]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_input_t res = kth_chain_input_construct(previous_output, script, sequence);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_input_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_destruct function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument input (#1). Required to be IsExternal.");
        return;
    }

    kth_input_t input = (kth_input_t)v8::External::Cast(*args[0])->Value();

    kth_chain_input_destruct(input);

}

void chain_input_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_factory_from_data function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type for argument data (#1). Required to be IsUint8Array.");
        return;
    }

    v8::Local<v8::Uint8Array> data_arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    uint8_t* data = (uint8_t*)data_arr->Buffer()->GetContents().Data();
    uint64_t n = data_arr->Length();

    kth_input_t res = kth_chain_input_factory_from_data(data, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_input_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_is_valid function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument input (#1). Required to be IsExternal.");
        return;
    }

    kth_input_t input = (kth_input_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_input_is_valid(input);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_input_is_final(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_is_final function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument input (#1). Required to be IsExternal.");
        return;
    }

    kth_input_t input = (kth_input_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_input_is_final(input);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_input_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_serialized_size function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument input (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument wire (#2). Required to be IsBoolean.");
        return;
    }

    kth_input_t input = (kth_input_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t wire = bool_to_cpp(isolate, args[1]);

    kth_size_t res = kth_chain_input_serialized_size(input, wire);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_input_sequence(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_sequence function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument input (#1). Required to be IsExternal.");
        return;
    }

    kth_input_t input = (kth_input_t)v8::External::Cast(*args[0])->Value();

    uint32_t res = kth_chain_input_sequence(input);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_input_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_signature_operations function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument input (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument bip16_active (#2). Required to be IsBoolean.");
        return;
    }

    kth_input_t input = (kth_input_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t bip16_active = bool_to_cpp(isolate, args[1]);

    kth_size_t res = kth_chain_input_signature_operations(input, bip16_active);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_input_script(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_script function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument input (#1). Required to be IsExternal.");
        return;
    }

    kth_input_t input = (kth_input_t)v8::External::Cast(*args[0])->Value();

    kth_script_t res = kth_chain_input_script(input);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_input_previous_output(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_previous_output function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument input (#1). Required to be IsExternal.");
        return;
    }

    kth_input_t input = (kth_input_t)v8::External::Cast(*args[0])->Value();

    kth_outputpoint_t res = kth_chain_input_previous_output(input);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_input_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_input_to_data function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument input (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument wire (#2). Required to be IsBoolean.");
        return;
    }

    kth_input_t input = (kth_input_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t wire = bool_to_cpp(isolate, args[1]);
    kth_size_t size;

    uint8_t const* res = kth_chain_input_to_data(input, wire, &size);
    args.GetReturnValue().Set(byte_array_to_js(isolate, res, size));
}

}  // namespace kth::js_native
