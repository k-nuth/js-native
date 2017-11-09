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

}  // namespace bitprim_ns

#endif //BITPRIM_JS_CHAIN_MERKLE_BLOCK_H_
