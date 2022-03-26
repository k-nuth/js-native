// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_CHAIN_HPP_
#define KTH_JS_CHAIN_CHAIN_HPP_

#include <node.h>

namespace kth::js_native {

void chain_fetch_last_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_block_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_block_header_by_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_block_header_by_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_block_by_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_block_by_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_merkle_block_by_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_merkle_block_by_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_compact_block_by_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_compact_block_by_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_transaction(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_transaction_position(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_spend(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_fetch_history(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_fetch_stealth(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_organize_block(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_organize_transaction(v8::FunctionCallbackInfo<v8::Value> const& args);

// void chain_subscribe_blockchain(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_CHAIN_HPP_
