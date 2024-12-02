// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/output.h>
#include <kth/js-native/chain/output.hpp>
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

void chain_output_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_construct_default function requires 0 arguments.");
        return;
    }


    kth_output_t res = kth_chain_output_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_output_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_construct function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument value (#1). Required to be IsNumber.");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument script (#2). Required to be IsExternal.");
        return;
    }

    uint64_t value = args[0]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_script_t script = (kth_script_t)v8::External::Cast(*args[1])->Value();

    kth_output_t res = kth_chain_output_construct(value, script);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_output_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_destruct function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument output (#1). Required to be IsExternal.");
        return;
    }

    kth_output_t output = (kth_output_t)v8::External::Cast(*args[0])->Value();

    kth_chain_output_destruct(output);
}

void chain_output_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_factory_from_data function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type for argument data (#1). Required to be IsUint8Array.");
        return;
    }

    v8::Local<v8::Uint8Array> data_arr = v8::Local<v8::Uint8Array>::Cast(args[0]);

#if (V8_MAJOR_VERSION >= 8)
    uint8_t* data = (uint8_t*)data_arr->Buffer()->GetBackingStore()->Data();
#else
    uint8_t* data = (uint8_t*)data_arr->Buffer()->GetContents().Data();
#endif

    uint64_t n = data_arr->Length();

    kth_output_t res = kth_chain_output_factory_from_data(data, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_output_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_is_valid function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument output (#1). Required to be IsExternal.");
        return;
    }

    kth_output_t output = (kth_output_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_output_is_valid(output);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_output_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_serialized_size function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument output (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument wire (#2). Required to be IsBoolean.");
        return;
    }

    kth_output_t output = (kth_output_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t wire = bool_to_cpp(isolate, args[1]);

    kth_size_t res = kth_chain_output_serialized_size(output, wire);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_output_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_value function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument output (#1). Required to be IsExternal.");
        return;
    }

    kth_output_t output = (kth_output_t)v8::External::Cast(*args[0])->Value();

    uint64_t res = kth_chain_output_value(output);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_output_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_signature_operations function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument output (#1). Required to be IsExternal.");
        return;
    }

    kth_output_t output = (kth_output_t)v8::External::Cast(*args[0])->Value();

    kth_size_t res = kth_chain_output_signature_operations(output);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_output_script(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_script function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument output (#1). Required to be IsExternal.");
        return;
    }

    kth_output_t output = (kth_output_t)v8::External::Cast(*args[0])->Value();

    kth_script_t res = kth_chain_output_script(output);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_output_payment_address(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_payment_address function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument output (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument use_testnet_rules (#2). Required to be IsBoolean.");
        return;
    }

    kth_output_t output = (kth_output_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t use_testnet_rules = bool_to_cpp(isolate, args[1]);

    kth_payment_address_t res = kth_chain_output_payment_address(output, use_testnet_rules);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_output_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_output_to_data function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument output (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument wire (#2). Required to be IsBoolean.");
        return;
    }

    kth_output_t output = (kth_output_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t wire = bool_to_cpp(isolate, args[1]);
    kth_size_t size;

    uint8_t const* res = kth_chain_output_to_data(output, wire, &size);
    args.GetReturnValue().Set(byte_array_to_js(isolate, res, size));
}

}  // namespace kth::js_native
