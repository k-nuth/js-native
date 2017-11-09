#ifndef BITPRIM_JS_CHAIN_CHAIN_H_
#define BITPRIM_JS_CHAIN_CHAIN_H_

#include <node.h>

namespace bitprim_ns {

void bitprim_chain_fetch_last_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_block_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_block_header_by_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_block_header_by_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_block_by_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_block_by_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_merkle_block_by_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_merkle_block_by_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_compact_block_by_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_compact_block_by_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_transaction(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_transaction_position(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_spend(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_history(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_fetch_stealth(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_organize_block(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_organize_transaction(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace bitprim_ns

#endif //BITPRIM_JS_CHAIN_CHAIN_H_
