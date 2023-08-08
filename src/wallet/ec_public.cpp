// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/wallet/ec_public.h>
#include <kth/capi/platform.h>
#include <kth/capi/wallet/primitives.h>

#include <kth/js-native/wallet/ec_public.hpp>
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


void wallet_ec_public_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    auto res = kth_wallet_ec_public_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_public_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external private object");
        return;
    }

    auto priv = (kth_ec_private_t)v8::External::Cast(*args[0])->Value();
    auto res = kth_wallet_ec_public_construct(priv);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_public_construct_from_decoded(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments: Expected a Uint8Array for decoded data");
        return;
    }

    //TODO: improve this way of getting arrays
    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
#if (V8_MAJOR_VERSION >= 8)
    uint8_t* decoded_data = (uint8_t*)arr->Buffer()->GetBackingStore()->Data();
#else
    uint8_t* decoded_data = (uint8_t*)arr->Buffer()->GetContents().Data();
#endif

    kth_size_t size = arr->Length();
    auto res = kth_wallet_ec_public_construct_from_decoded(decoded_data, size);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_public_construct_from_base16(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Wrong arguments: Expected a base16 string");
        return;
    }

    v8::String::Utf8Value base16(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    auto res = kth_wallet_ec_public_construct_from_base16(*base16);
    args.GetReturnValue().Set(External::New(isolate, res));
}

kth_ec_compressed_t to_native_ec_compressed(v8::Local<v8::Uint8Array> arr) {
    kth_ec_compressed_t point;

#if (V8_MAJOR_VERSION >= 8)
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetBackingStore()->Data();
#else
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetContents().Data();
#endif

    for (uint32_t i = 0; i < arr->Length(); ++i) {
        point.data[i] = native_arr[i];
    }
    return point;
}

void wallet_ec_public_construct_from_point(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments: Expected an Uint8Array for ec_compressed point");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments: Expected a boolean for compression flag");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    kth_ec_compressed_t point = to_native_ec_compressed(arr);
    kth_bool_t compress = args[1]->BooleanValue(isolate);

    auto res = kth_wallet_ec_public_construct_from_point(&point, compress);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void wallet_ec_public_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external ec_public object");
        return;
    }

    auto obj = (kth_ec_public_t)v8::External::Cast(*args[0])->Value();
    kth_wallet_ec_public_destruct(obj);
    // args.GetReturnValue().SetUndefined();
}

void wallet_ec_public_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external ec_public object");
        return;
    }

    auto obj = (kth_ec_public_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t res = kth_wallet_ec_public_is_valid(obj);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void wallet_ec_public_encoded(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external ec_public object");
        return;
    }

    auto obj = (kth_ec_public_t)v8::External::Cast(*args[0])->Value();
    char* res = kth_wallet_ec_public_encoded(obj);
    args.GetReturnValue().Set(string_to_js(isolate, res));
    kth_platform_free(res); //TODO: call kth_platform_free in all the similar places
}

void wallet_ec_public_point(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external ec_public object");
        return;
    }

    auto obj = (kth_ec_public_t)v8::External::Cast(*args[0])->Value();
    auto res = kth_wallet_ec_public_point(obj);
    args.GetReturnValue().Set(ec_compressed_to_js(isolate, res));
}

void wallet_ec_public_compressed(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external ec_public object");
        return;
    }

    auto obj = (kth_ec_public_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t res = kth_wallet_ec_public_compressed(obj);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void wallet_ec_public_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external ec_public object");
        return;
    }

    auto obj = (kth_ec_public_t)v8::External::Cast(*args[0])->Value();
    kth_size_t size;
    uint8_t const* res = kth_wallet_ec_public_to_data(obj, &size);
    args.GetReturnValue().Set(byte_array_to_js(isolate, res, size));
}

void wallet_ec_public_to_uncompressed(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments: Expected an external ec_public object");
        return;
    }

    auto obj = (kth_ec_public_t)v8::External::Cast(*args[0])->Value();
    kth_ec_uncompressed_t out_data;
    kth_bool_t res = kth_wallet_ec_public_to_uncompressed(obj, &out_data);

    if (res == 0) {
        args.GetReturnValue().SetUndefined();
        return;
    }
    args.GetReturnValue().Set(ec_uncompressed_to_js(isolate, out_data));
}

void wallet_ec_public_to_payment_address(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal() || !args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments: Expected an external ec_public object and a number (version)");
        return;
    }

    auto obj = (kth_ec_public_t)v8::External::Cast(*args[0])->Value();
    uint8_t version = static_cast<uint8_t>(args[1]->Int32Value(isolate->GetCurrentContext()).ToChecked());

    auto res = kth_wallet_ec_public_to_payment_address(obj, version);
    args.GetReturnValue().Set(External::New(isolate, res));
}

}  // namespace kth::js_native
