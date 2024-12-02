// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_TOOLS_H_
#define KTH_JS_CHAIN_TOOLS_H_

#include <node.h>

namespace kth::js_native {

kth_hash_t to_native_hash(v8::Local<v8::Uint8Array> const& arr);
kth_shorthash_t to_native_shorthash(v8::Local<v8::Uint8Array> const& arr);
kth_longhash_t to_native_longhash(v8::Local<v8::Uint8Array> const& arr);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_TOOLS_H_
