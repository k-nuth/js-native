// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/wallet/payment_address.h>

#include <kth/js-native/wallet/payment_address.hpp>
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

// void wallet_payment_address_construct_from_string(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_construct_from_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_construct_from_public(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_construct_from_script(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_set_cashaddr_prefix(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_encoded_cashaddr(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_encoded_legacy(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_hash20(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_hash32(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_version(v8::FunctionCallbackInfo<v8::Value> const& args);
// void wallet_payment_address_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);

// kth_payment_address_t kth_wallet_payment_address_construct_from_string(char const* address);
void wallet_payment_address_construct_from_string(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. wallet_payment_address_construct_from_string function requires 1 argument.");
        return;
    }

    if (!args[0]->IsString()) {
        throw_exception(isolate, "Wrong argument type for argument path (#1). Required to be IsString.");
        return;
    }

    v8::String::Utf8Value address(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    kth_payment_address_t res = kth_wallet_payment_address_construct_from_string(*address);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_payment_address_construct_from_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if (!args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if (!args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);

    if (arr->Length() != 20) {
        throw_exception(isolate, "Wrong arguments, hash length must be 20 bytes");
        return;
    }

    kth_shorthash_t hash = to_native_shorthash(arr);
    uint8_t version = static_cast<uint8_t>(args[1]->NumberValue(isolate->GetCurrentContext()).ToChecked());

    kth_payment_address_t res = kth_wallet_payment_address_construct_from_hash(&hash, version);
    args.GetReturnValue().Set(External::New(isolate, res));
}

// void kth_wallet_payment_address_destruct(kth_payment_address_t payment_address);
void wallet_payment_address_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. wallet_payment_address_destruct function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument payment_address (#1). Required to be IsExternal.");
        return;
    }

    kth_payment_address_t payment_address = (kth_payment_address_t)v8::External::Cast(*args[0])->Value();
    kth_wallet_payment_address_destruct(payment_address);
}



// void kth_wallet_payment_address_set_cashaddr_prefix(char const* prefix);
void wallet_payment_address_set_cashaddr_prefix(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. wallet_payment_address_set_cashaddr_prefix function requires 1 argument.");
        return;
    }

    if (!args[0]->IsString()) {
        throw_exception(isolate, "Wrong argument type for argument path (#1). Required to be IsString.");
        return;
    }

    v8::String::Utf8Value prefix(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    kth_wallet_payment_address_set_cashaddr_prefix(*prefix);
}

// char* kth_wallet_payment_address_encoded_cashaddr(kth_payment_address_t payment_address);
void wallet_payment_address_encoded_cashaddr(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. wallet_payment_address_encoded_cashaddr function requires 2 argument.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument payment_address (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument payment_address (#2). Required to be Boolean.");
        return;
    }

    kth_payment_address_t payment_address = (kth_payment_address_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t token_aware = bool_to_cpp(isolate, args[1]);

    char const* res = kth_wallet_payment_address_encoded_cashaddr(payment_address, token_aware);
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void wallet_payment_address_encoded_legacy(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. wallet_payment_address_encoded function requires 1 argument.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument payment_address (#1). Required to be IsExternal.");
        return;
    }

    kth_payment_address_t payment_address = (kth_payment_address_t)v8::External::Cast(*args[0])->Value();

    char const* res = kth_wallet_payment_address_encoded_legacy(payment_address);
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

// kth_shorthash_t kth_wallet_payment_address_hash20(kth_payment_address_t payment_address);
void wallet_payment_address_hash20(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. wallet_payment_address_hash function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument payment_address (#1). Required to be IsExternal.");
        return;
    }

    kth_payment_address_t payment_address = (kth_payment_address_t)v8::External::Cast(*args[0])->Value();

    kth_shorthash_t res = kth_wallet_payment_address_hash20(payment_address);
    args.GetReturnValue().Set(shorthash_to_js(isolate, res));
}

// kth_hash_t kth_wallet_payment_address_hash32(kth_payment_address_t payment_address);
void wallet_payment_address_hash32(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. wallet_payment_address_hash function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument payment_address (#1). Required to be IsExternal.");
        return;
    }

    kth_payment_address_t payment_address = (kth_payment_address_t)v8::External::Cast(*args[0])->Value();

    kth_hash_t res = kth_wallet_payment_address_hash32(payment_address);
    args.GetReturnValue().Set(hash_to_js(isolate, res));
}

// uint8_t kth_wallet_payment_address_version(kth_payment_address_t payment_address);
void wallet_payment_address_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. wallet_payment_address_version function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_payment_address_t payment_address = (kth_payment_address_t)v8::External::Cast(*args[0])->Value();

    uint8_t res = kth_wallet_payment_address_version(payment_address);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

// kth_bool_t kth_wallet_payment_address_is_valid(kth_payment_address_t payment_address);
void wallet_payment_address_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. wallet_payment_address_is_valid function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument payment_address (#1). Required to be IsExternal.");
        return;
    }

    kth_payment_address_t payment_address = (kth_payment_address_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_wallet_payment_address_is_valid(payment_address);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

}  // namespace kth::js_native
