// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_TOOLS_H_
#define KTH_JS_CHAIN_TOOLS_H_

#include <node.h>

namespace kth::js_native {

kth_hash_t to_native_hash(v8::Local<v8::Uint8Array> const& arr);
kth_shorthash_t to_native_shorthash(v8::Local<v8::Uint8Array> arr);
kth_wif_compressed_t to_native_wif_compressed(v8::Local<v8::Uint8Array> arr);
kth_wif_uncompressed_t to_native_wif_uncompressed(v8::Local<v8::Uint8Array> arr);
kth_ec_secret_t to_native_ec_secret(v8::Local<v8::Uint8Array> arr);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_TOOLS_H_
