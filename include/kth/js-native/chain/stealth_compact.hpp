// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_STEALTH_COMPACT_H_
#define KTH_JS_CHAIN_STEALTH_COMPACT_H_

#include <node.h>

namespace kth::js_native {

void chain_stealth_compact_get_ephemeral_public_key_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_stealth_compact_get_transaction_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_stealth_compact_get_public_key_hash(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_STEALTH_COMPACT_H_
