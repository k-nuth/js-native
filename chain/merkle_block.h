#ifndef BITPRIM_JS_CHAIN_MERKLE_BLOCK_H_
#define BITPRIM_JS_CHAIN_MERKLE_BLOCK_H_

#include <node.h>

namespace bitprim_ns {

void bitprim_chain_merkle_block_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_merkle_block_get_header(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_merkle_block_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_merkle_block_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);

void bitprim_chain_merkle_block_hash_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_merkle_block_total_transaction_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_merkle_block_reset(v8::FunctionCallbackInfo<v8::Value> const& args);

// void bitprim_chain_merkle_block_is_valid_coinbase_claim(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_is_valid_coinbase_script(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_is_internal_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_is_valid_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_is_distinct_transaction_set(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_transaction_count(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_subsidy(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_fees(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_claim(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_reward(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_generate_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_transaction_nth(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_total_inputs(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_is_extra_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_merkle_block_is_final(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace bitprim_ns

#endif //BITPRIM_JS_CHAIN_MERKLE_BLOCK_H_
