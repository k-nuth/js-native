// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/wallet/ec_private.h>
#include <kth/capi/platform.h>
#include <kth/capi/wallet/primitives.h>

#include <kth/js-native/wallet/ec_private.hpp>
#include <kth/js-native/helper.hpp>
#include <kth/js-native/wallet/convertions.hpp>

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

void wallet_ec_private_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    kth_ec_private_t res = kth_wallet_ec_private_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_private_construct_string(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    uint8_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    v8::String::Utf8Value wif(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    kth_ec_private_t res = kth_wallet_ec_private_construct_string(*wif, version);
    args.GetReturnValue().Set(External::New(isolate, res));

}

void wallet_ec_private_construct_compressed(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    if (arr->Length() != 38U) {
        throw_exception(isolate, "Wrong arguments, WIF length must be 38 bytes");
        return;
    }

    kth_wif_compressed_t wif_compressed = to_native_wif_compressed(arr);
    uint8_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_ec_private_t res = kth_wallet_ec_private_construct_compressed(&wif_compressed, version);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_private_construct_uncompressed(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments: Expected Uint8Array for WIF Uncompressed");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments: Expected number for version");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    if (arr->Length() != 37) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }

    kth_wif_uncompressed_t wif_uncompressed = to_native_wif_uncompressed(arr);
    uint8_t version = static_cast<uint8_t>(args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked());

    kth_ec_private_t res = kth_wallet_ec_private_construct_uncompressed(&wif_uncompressed, version);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_private_construct_secret(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#0). Required to be IsNumber.");
        return;
    }

    if ( ! args[2]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments: Expected a boolean for compression flag");
        return;
    }


    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, secret length must be 32 bytes");
        return;
    }

    kth_ec_secret_t secret = to_native_ec_secret(arr);
    uint16_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_bool_t compress = bool_to_cpp(isolate, args[2]);
    kth_ec_private_t res = kth_wallet_ec_private_construct_secret(&secret, version, compress);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_private_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    kth_ec_private_t obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    kth_wallet_ec_private_destruct(obj);
}

void wallet_ec_private_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    kth_ec_private_t obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t res = kth_wallet_ec_private_is_valid(obj);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void wallet_ec_private_encoded(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    kth_ec_private_t obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    char* res = kth_wallet_ec_private_encoded(obj);
    args.GetReturnValue().Set(string_to_js(isolate, res));
    kth_platform_free(res);
}

void wallet_ec_private_secret(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    kth_ec_private_t obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    kth_ec_secret_t res = kth_wallet_ec_private_secret(obj);
    args.GetReturnValue().Set(ec_secret_to_js(isolate, res));
}

void wallet_ec_private_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    kth_ec_private_t obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    uint16_t version = kth_wallet_ec_private_version(obj);
    args.GetReturnValue().Set(Number::New(isolate, version));
}

void wallet_ec_private_payment_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    kth_ec_private_t obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    uint8_t payment_version = kth_wallet_ec_private_payment_version(obj);
    args.GetReturnValue().Set(Number::New(isolate, payment_version));
}

void wallet_ec_private_wif_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    kth_ec_private_t obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    uint8_t wif_version = kth_wallet_ec_private_wif_version(obj);
    args.GetReturnValue().Set(Number::New(isolate, wif_version));
}

void wallet_ec_private_compressed(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    kth_ec_private_t obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t res = kth_wallet_ec_private_compressed(obj);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void wallet_ec_private_to_public(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    auto obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    auto res = kth_wallet_ec_private_to_public(obj);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_private_to_payment_address(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    kth_ec_private_t obj = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    auto res = kth_wallet_ec_private_to_payment_address(obj);
    args.GetReturnValue().Set(External::New(isolate, res));
}

}  // namespace kth::js_native
