// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/wallet/wallet.h>

#include <kth/js-native/wallet/wallet.hpp>
#include <kth/js-native/helper.hpp>
#include <kth/js-native/chain/tools.hpp>
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


void wallet_mnemonics_to_seed(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    auto obj = (kth_string_list_t)v8::External::Cast(*args[0])->Value();

    kth_longhash_t res = kth_wallet_mnemonics_to_seed(obj);
    args.GetReturnValue().Set(longhash_to_js(isolate, res));
}

void wallet_hd_new(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments.");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type for argument seed (#1). Required to be Uint8Array.");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    if (arr->Length() != 64) {
        throw_exception(isolate, "Wrong argument type for argument seed (#2). Required to be 64-byte array.");
        return;
    }
    kth_longhash_t seed = to_native_longhash(arr);

    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_hd_private_t res = kth_wallet_hd_new(seed, version);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_private_to_ec(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument key (#1). Required to be IsExternal.");
        return;
    }

    kth_hd_private_t key = (kth_hd_private_t)v8::External::Cast(*args[0])->Value();
    kth_ec_secret_t res = kth_wallet_hd_private_to_ec(key);
    args.GetReturnValue().Set(ec_secret_to_js(isolate, res));
}

void wallet_ec_to_public(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // Verificar que se tienen el número correcto de argumentos.
    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. kth_wallet_ec_to_public function requires 2 arguments.");
        return;
    }

    // Asegurarse de que se pasa el tipo correcto para "secret".
    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument secret (#1). Required to be IsExternal.");
        return;
    }

    // Asegurarse de que el segundo argumento es un booleano.
    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument uncompressed (#2). Required to be Boolean.");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, secret length must be 32 bytes");
        return;
    }
    kth_ec_secret_t secret = to_native_ec_secret(arr);

    kth_bool_t uncompressed = bool_to_cpp(isolate, args[1]);
    kth_ec_public_t res = kth_wallet_ec_to_public(secret, uncompressed);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_to_address(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. kth_wallet_ec_to_address function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument point (#1). Required to be IsExternal.");
        return;
    }

    //TODO: Use IsUint32() and friends instead of IsNumber() in all the code.
    if ( ! args[1]->IsUint32()) {
        throw_exception(isolate, "Wrong argument type for argument version (#2). Required to be Uint32.");
        return;
    }

    kth_ec_public_t point = (kth_ec_public_t)v8::External::Cast(*args[0])->Value();
    // uint32_t version = args[1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_payment_address_t res = kth_wallet_ec_to_address(point, version);
    args.GetReturnValue().Set(External::New(isolate, res));
}

}  // namespace kth::js_native
