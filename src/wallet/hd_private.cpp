// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/wallet/hd_private.h>
#include <kth/capi/platform.h>
#include <kth/capi/wallet/primitives.h>

#include <kth/js-native/wallet/hd_private.hpp>
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

void wallet_hd_private_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }
    kth_hd_private_t res = kth_wallet_hd_private_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_private_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type: Uint8Array expected");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    kth_hd_key_t key = to_native_hd_key(arr);
    kth_hd_private_t res = kth_wallet_hd_private_construct(&key);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_private_construct_with_prefix(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type: Uint8Array expected");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type: Number expected");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    kth_hd_key_t key = to_native_hd_key(arr);
    uint32_t prefix = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_hd_private_t res = kth_wallet_hd_private_construct_with_prefix(&key, prefix);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_private_construct_with_prefixes(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type: Uint8Array expected");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type: Number expected");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    kth_hd_key_t key = to_native_hd_key(arr);
    uint64_t prefixes = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_hd_private_t res = kth_wallet_hd_private_construct_with_prefixes(&key, prefixes);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_private_construct_with_seed(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type: Uint8Array expected");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type: Number expected");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
#if (V8_MAJOR_VERSION >= 8)
    uint8_t* seed = (uint8_t*)arr->Buffer()->GetBackingStore()->Data();
#else
    uint8_t* seed = (uint8_t*)arr->Buffer()->GetContents().Data();
#endif

    kth_size_t size = arr->Length();
    uint64_t prefixes = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_hd_private_t res = kth_wallet_hd_private_construct_with_seed(seed, size, prefixes);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_private_construct_string(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Wrong argument type: String expected");
        return;
    }

    v8::String::Utf8Value encoded(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    kth_hd_private_t res = kth_wallet_hd_private_construct_string(*encoded);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_private_construct_string_with_prefix(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Wrong argument type: String expected");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type: Number expected");
        return;
    }

    String::Utf8Value encoded(isolate, args[0]);
    // uint32_t prefix = args[1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
    uint32_t prefix = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_hd_private_t res = kth_wallet_hd_private_construct_string_with_prefix(*encoded, prefix);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_private_construct_string_with_prefixes(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Wrong argument type: String expected");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type: Number expected");
        return;
    }

    String::Utf8Value encoded(isolate, args[0]);
    uint64_t prefixes = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_hd_private_t res = kth_wallet_hd_private_construct_string_with_prefixes(*encoded, prefixes);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_private_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type: External expected");
        return;
    }

    auto obj = (kth_hd_private_t)v8::External::Cast(*args[0])->Value();
    kth_wallet_hd_private_destruct(obj);
}

void wallet_hd_private_encoded(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type: External expected");
        return;
    }

    auto obj = (kth_hd_private_t)v8::External::Cast(*args[0])->Value();
    char* res = kth_wallet_hd_private_encoded(obj);
    args.GetReturnValue().Set(string_to_js(isolate, res));
    kth_platform_free(res);
}

void wallet_hd_private_secret(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type: External expected");
        return;
    }

    auto obj = (kth_hd_private_t)v8::External::Cast(*args[0])->Value();
    kth_ec_secret_t res = kth_wallet_hd_private_secret(obj);
    args.GetReturnValue().Set(ec_secret_to_js(isolate, res));
}

void wallet_hd_private_to_hd_key(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type: External expected");
        return;
    }

    auto obj = (kth_hd_private_t)v8::External::Cast(*args[0])->Value();
    kth_hd_key_t res = kth_wallet_hd_private_to_hd_key(obj);
    args.GetReturnValue().Set(hd_key_to_js(isolate, res));
}

void wallet_hd_private_to_public(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type: External expected");
        return;
    }

    auto obj = (kth_hd_private_t)v8::External::Cast(*args[0])->Value();
    kth_hd_public_t hd_public = kth_wallet_hd_private_to_public(obj);
    args.GetReturnValue().Set(External::New(isolate, hd_public));
}

void wallet_hd_private_derive_private(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type: External expected");
        return;
    }

    if ( ! args[1]->IsUint32()) {
        throw_exception(isolate, "Wrong argument type: Number expected");
        return;
    }

    auto obj = (kth_hd_private_t)v8::External::Cast(*args[0])->Value();
    uint32_t index = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_hd_private_t derived_hd_private = kth_wallet_hd_private_derive_private(obj, index);
    args.GetReturnValue().Set(External::New(isolate, derived_hd_private));
}

void wallet_hd_private_derive_public(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type: External expected");
        return;
    }

    //TODO: should I use IsUint32 or IsNumber?
    if ( ! args[1]->IsUint32()) {
        throw_exception(isolate, "Wrong argument type: Number expected");
        return;
    }

    auto obj = (kth_hd_private_t)v8::External::Cast(*args[0])->Value();
    uint32_t index = args[1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
    kth_hd_public_t derived_hd_public = kth_wallet_hd_private_derive_public(obj, index);
    args.GetReturnValue().Set(External::New(isolate, derived_hd_public));
}

}  // namespace kth::js_native
