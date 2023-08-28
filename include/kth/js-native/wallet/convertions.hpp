// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_NATIVE_WALLET_CONVERTIONS_HPP_
#define KTH_JS_NATIVE_WALLET_CONVERTIONS_HPP_

#include <iostream>
#include <string>

#include <node.h>
#include <nan.h>

#include <kth/capi/wallet/hd_lineage.h>

namespace kth::js_native {

inline
v8::Local<v8::Uint8Array> ec_secret_to_js(v8::Isolate* isolate, kth_ec_secret_t const& x) {
    return byte_array_to_js(isolate, x.hash, KTH_BITCOIN_EC_SECRET_SIZE);
}

inline
v8::Local<v8::Uint8Array> hd_key_to_js(v8::Isolate* isolate, kth_hd_key_t const& x) {
    return byte_array_to_js(isolate, x.data, KTH_HD_KEY_SIZE);
}

inline
v8::Local<v8::Uint8Array> ec_compressed_to_js(v8::Isolate* isolate, kth_ec_compressed_t const& x) {
    return byte_array_to_js(isolate, x.data, KTH_EC_COMPRESSED_SIZE);
}

inline
v8::Local<v8::Uint8Array> ec_uncompressed_to_js(v8::Isolate* isolate, kth_ec_uncompressed_t const& x) {
    return byte_array_to_js(isolate, x.data, KTH_BITCOIN_EC_UNCOMPRESSED_SIZE);
}

inline
v8::Local<v8::Uint8Array> hd_chain_code_to_js(v8::Isolate* isolate, kth_hd_chain_code_t const& x) {
    return byte_array_to_js(isolate, x.data, KTH_HD_CHAIN_CODE_SIZE);
}

inline
v8::Local<v8::Object> hd_lineage_to_js(v8::Isolate* isolate, kth_hd_lineage const& x) {
    auto ctx = isolate->GetCurrentContext();
    v8::Local<v8::Object> res = v8::Object::New(isolate);
    res->Set(ctx, string_to_js(isolate, "prefixes"), v8::BigInt::NewFromUnsigned(isolate, x.prefixes));
    res->Set(ctx, string_to_js(isolate, "depth"), v8::Number::New(isolate, x.depth));
    res->Set(ctx, string_to_js(isolate, "parent_fingerprint"), v8::Number::New(isolate, x.parent_fingerprint));
    res->Set(ctx, string_to_js(isolate, "child_number"), v8::Number::New(isolate, x.child_number));
    return res;
}

inline
kth_hd_key_t to_native_hd_key(v8::Local<v8::Uint8Array> const& arr) {
    //precondition: arr->Length() == KTH_HD_KEY_SIZE
    kth_hd_key_t res;

#if (V8_MAJOR_VERSION >= 8)
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetBackingStore()->Data();
#else
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetContents().Data();
#endif

    for (uint32_t i = 0; i < arr->Length(); ++i) {
        res.data[i] = native_arr[i];
    }
    return res;
}

inline
kth_ec_secret_t to_native_ec_secret(v8::Local<v8::Uint8Array> const& arr) {
    //precondition: arr->Length() == 32
    kth_ec_secret_t res;

#if (V8_MAJOR_VERSION >= 8)
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetBackingStore()->Data();
#else
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetContents().Data();
#endif

    for (uint32_t i = 0; i < arr->Length(); ++i) {
        res.hash[i] = native_arr[i];
    }
    return res;
}

inline
kth_wif_compressed_t to_native_wif_compressed(v8::Local<v8::Uint8Array> arr) {
    //precondition: arr->Length() == 38
    kth_wif_compressed_t res;

#if (V8_MAJOR_VERSION >= 8)
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetBackingStore()->Data();
#else
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetContents().Data();
#endif

    for (uint32_t i = 0; i < arr->Length(); ++i) {
        res.data[i] = native_arr[i];
    }
    return res;
}

inline
kth_wif_uncompressed_t to_native_wif_uncompressed(v8::Local<v8::Uint8Array> arr) {
    //precondition: arr->Length() == 37
    kth_wif_uncompressed_t res;

#if (V8_MAJOR_VERSION >= 8)
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetBackingStore()->Data();
#else
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetContents().Data();
#endif

    for (uint32_t i = 0; i < arr->Length(); ++i) {
        res.data[i] = native_arr[i];
    }
    return res;
}

}  // namespace kth::js_native

#endif // KTH_JS_NATIVE_WALLET_CONVERTIONS_HPP_
