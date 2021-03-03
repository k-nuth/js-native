// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_BLOCK_H_
#define KTH_JS_CHAIN_BLOCK_H_

#include <node.h>

namespace kth::js_native {

void chain_block_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_header(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_hash_out(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_proof_str(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_transactions(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_subsidy(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_fees(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_claim(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_reward(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_generate_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_generate_merkle_root_out(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_total_inputs(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_is_extra_coinbases(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_is_final(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_is_distinct_transaction_set(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_is_valid_coinbase_claim(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_is_valid_coinbase_script(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_is_internal_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_is_valid_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_block_to_data(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_BLOCK_H_
