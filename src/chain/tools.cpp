// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <node.h>

#include <kth/capi/primitives.h>
#include <kth/js-native/chain/tools.hpp>

namespace kth::js_native {

kth_hash_t to_native_hash(v8::Local<v8::Uint8Array> const& arr) {
    //precondition: arr->Length() == 32
    kth_hash_t hash;
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetContents().Data();

    for (uint32_t i = 0; i < arr->Length(); ++i) {
        hash.hash[i] = native_arr[i];
    }
    return hash;
}

}  // namespace kth::js_native
