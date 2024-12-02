// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <node.h>

#include <kth/capi/primitives.h>
#include <kth/js-native/chain/tools.hpp>

namespace kth::js_native {

kth_hash_t to_native_hash(v8::Local<v8::Uint8Array> const& arr) {
    //precondition: arr->Length() == 32
    kth_hash_t res;

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

kth_shorthash_t to_native_shorthash(v8::Local<v8::Uint8Array> const& arr) {
    //precondition: arr->Length() == 20
    kth_shorthash_t res;

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

kth_longhash_t to_native_longhash(v8::Local<v8::Uint8Array> const& arr) {
    //precondition: arr->Length() == 64
    kth_longhash_t res;

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

}  // namespace kth::js_native
