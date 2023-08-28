// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/wallet/hd_public.h>
#include <kth/capi/platform.h>
#include <kth/capi/wallet/primitives.h>

#include <kth/js-native/wallet/hd_public.hpp>
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

void wallet_hd_public_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    kth_hd_public_t res = kth_wallet_hd_public_construct_default();
    args.GetReturnValue().Set(External::New(args.GetIsolate(), res));
}

void wallet_hd_public_construct_key(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Argument 0 must be a Uint8Array");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);

    if (arr->Length() != KTH_HD_KEY_SIZE) {
        throw_exception(isolate, "Wrong arguments, hash length must be 82 bytes");
        return;
    }

    auto key = to_native_hd_key(arr);
    auto res = kth_wallet_hd_public_construct_key(&key);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_public_construct_key_prefix(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Argument 0 must be a Uint8Array");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Argument 1 must be a uint32_t");
        return;
    }

    uint32_t prefix = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    if (arr->Length() != KTH_HD_KEY_SIZE) {
        throw_exception(isolate, "Wrong arguments, hash length must be 82 bytes");
        return;
    }

    auto key = to_native_hd_key(arr);
    auto res = kth_wallet_hd_public_construct_key_prefix(&key, prefix);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_hd_public_construct_string(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Argument 0 must be a string");
        return;
    }
    v8::String::Utf8Value encoded(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    kth_hd_public_t res = kth_wallet_hd_public_construct_string(*encoded);
    args.GetReturnValue().Set(External::New(args.GetIsolate(), res));
}

void wallet_hd_public_construct_string_prefix(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Argument 0 must be a string");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Argument 1 must be a uint32_t");
        return;
    }

    v8::String::Utf8Value encoded(args.GetIsolate(), args[0]->ToString(args.GetIsolate()->GetCurrentContext()).ToLocalChecked());
    uint32_t prefix = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_hd_public_t res = kth_wallet_hd_public_construct_string_prefix(*encoded, prefix);
    args.GetReturnValue().Set(External::New(args.GetIsolate(), res));
}

void wallet_hd_public_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Argument 0 must be an external object");
        return;
    }
    auto obj = (kth_hd_public_t)v8::External::Cast(*args[0])->Value();
    kth_wallet_hd_public_destruct(obj);
    args.GetReturnValue().SetUndefined();
}

void wallet_hd_public_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Argument 0 must be an external object");
        return;
    }
    auto obj = (kth_hd_public_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t res = kth_wallet_hd_public_is_valid(obj);
    args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), res != 0));
}

void wallet_hd_public_encoded(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Argument 0 must be an external object");
        return;
    }

    auto obj = (kth_hd_public_t)v8::External::Cast(*args[0])->Value();
    char* res = kth_wallet_hd_public_encoded(obj);
    args.GetReturnValue().Set(string_to_js(isolate, res));
    kth_platform_free(res);
}

void wallet_hd_public_chain_code(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Argument 0 must be an external object");
        return;
    }

    auto obj = (kth_hd_public_t)v8::External::Cast(*args[0])->Value();
    kth_hd_chain_code_t res = kth_wallet_hd_public_chain_code(obj);
    args.GetReturnValue().Set(hd_chain_code_to_js(isolate, res));
}

void wallet_hd_public_lineage(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Argument 0 must be an external object");
        return;
    }
    auto obj = (kth_hd_public_t)v8::External::Cast(*args[0])->Value();
    kth_hd_lineage_t res = kth_wallet_hd_public_lineage(obj);
    args.GetReturnValue().Set(hd_lineage_to_js(isolate, res));
}

void wallet_hd_public_point(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Argument 0 must be an external object");
        return;
    }
    auto obj = (kth_hd_public_t)v8::External::Cast(*args[0])->Value();
    kth_ec_compressed_t res = kth_wallet_hd_public_point(obj);
    args.GetReturnValue().Set(ec_compressed_to_js(isolate, res));
}

void wallet_hd_public_to_hd_key(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Argument 0 must be an external object");
        return;
    }

    auto obj = (kth_hd_public_t)v8::External::Cast(*args[0])->Value();
    kth_hd_key_t res = kth_wallet_hd_public_to_hd_key(obj);
    args.GetReturnValue().Set(hd_key_to_js(isolate, res));
}

void wallet_hd_public_derive_public(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Arguments must be of the form (external object, uint32)");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Arguments must be of the form (external object, uint32)");
        return;
    }

    auto obj = (kth_hd_public_t)v8::External::Cast(*args[0])->Value();
    uint32_t index = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_hd_public_t res = kth_wallet_hd_public_derive_public(obj, index);
    args.GetReturnValue().Set(External::New(args.GetIsolate(), res));
}

}  // namespace kth::js_native
