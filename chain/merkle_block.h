#ifndef KTH_JS_CHAIN_MERKLE_BLOCK_H_
#define KTH_JS_CHAIN_MERKLE_BLOCK_H_

#include <node.h>

namespace kth_native {

void kth_chain_merkle_block_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_merkle_block_get_header(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_merkle_block_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_merkle_block_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_merkle_block_hash_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_merkle_block_total_transaction_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_merkle_block_reset(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth_native

#endif //KTH_JS_CHAIN_MERKLE_BLOCK_H_
