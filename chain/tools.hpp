// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_TOOLS_H_
#define KTH_JS_CHAIN_TOOLS_H_

#include <node.h>

namespace kth_native {

hash_t to_native_hash(v8::Local<v8::Uint8Array> const& arr);

}  // namespace kth_native

#endif //KTH_JS_CHAIN_TOOLS_H_
