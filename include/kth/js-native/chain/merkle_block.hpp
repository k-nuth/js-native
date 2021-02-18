// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_MERKLE_BLOCK_H_
#define KTH_JS_CHAIN_MERKLE_BLOCK_H_

#include <node.h>

namespace kth::js_native {

void chain_merkle_block_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_merkle_block_get_header(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_merkle_block_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_merkle_block_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_merkle_block_hash_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_merkle_block_total_transaction_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_merkle_block_reset(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_MERKLE_BLOCK_H_
