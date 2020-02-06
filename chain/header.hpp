// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_HEADER_H_
#define KTH_JS_CHAIN_HEADER_H_

#include <node.h>

namespace kth_native {

void kth_chain_header_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_set_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_previous_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_merkle(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_set_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_bits(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_set_bits(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_set_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth_native

#endif //KTH_JS_CHAIN_HEADER_H_
