// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/wallet/payment_address.h>
#include <kth/js-native/chain/payment_address.hpp>
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


void wallet_payment_address_construct_from_string(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    v8::String::Utf8Value str(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());

    kth_payment_address_t res = kth_wallet_payment_address_construct_from_string(*str);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_payment_address_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_payment_address_t payment_address = (kth_payment_address_t)vptr;

    kth_wallet_payment_address_destruct(payment_address);
}

void wallet_payment_address_encoded(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_payment_address_t payment_address = (kth_payment_address_t)vptr;

    char const* res = kth_wallet_payment_address_encoded(payment_address);
    args.GetReturnValue().Set(
        String::NewFromUtf8(isolate, res, v8::NewStringType::kNormal).ToLocalChecked()
        );
}

void wallet_payment_address_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_payment_address_t payment_address = (kth_payment_address_t)vptr;

    uint8_t res = kth_wallet_payment_address_version(payment_address);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

}  // namespace kth::js_native
