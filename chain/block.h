#ifndef KTH_JS_CHAIN_BLOCK_H_
#define KTH_JS_CHAIN_BLOCK_H_

#include <node.h>

namespace kth_native {

void bitprim_chain_block_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_get_header(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_transaction_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_subsidy(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_fees(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_claim(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_reward(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_generate_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_transaction_nth(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_total_inputs(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_is_extra_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_is_final(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_is_distinct_transaction_set(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_is_valid_coinbase_claim(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_is_valid_coinbase_script(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_is_internal_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_block_is_valid_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth_native

#endif //KTH_JS_CHAIN_BLOCK_H_
