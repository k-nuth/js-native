// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_HEADER_H_
#define KTH_JS_CHAIN_HEADER_H_

#include <node.h>

namespace kth::js_native {

// void chain_header_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_satoshi_fixed_size(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_reset(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_to_data(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);

// void chain_header_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);

void chain_header_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_bits(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_proof_str(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_previous_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_merkle(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_hash(v8::FunctionCallbackInfo<v8::Value> const& args);

void chain_header_set_version(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_set_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_set_bits(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_set_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);

// void chain_header_previous_block_hash_out(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_merkle_out(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_hash_out(v8::FunctionCallbackInfo<v8::Value> const& args);


// kth_header_t kth_chain_header_factory_from_data(uint32_t version, uint8_t* data, uint64_t n);
// kth_size_t kth_chain_header_satoshi_fixed_size(uint32_t version);
// void kth_chain_header_reset(kth_header_t header);
// kth_size_t kth_chain_header_serialized_size(kth_header_t header, uint32_t version);
// uint8_t const* kth_chain_header_to_data(kth_header_t header, uint32_t version, kth_size_t* out_size);
// kth_header_t kth_chain_header_construct_default(void);
// kth_header_t kth_chain_header_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce);
// void kth_chain_header_destruct(kth_header_t header);
// int kth_chain_header_is_valid(kth_header_t header);
// uint32_t kth_chain_header_version(kth_header_t header);
// void kth_chain_header_set_version(kth_header_t header, uint32_t version);
// uint32_t kth_chain_header_timestamp(kth_header_t header);
// void kth_chain_header_set_timestamp(kth_header_t header, uint32_t timestamp);
// uint32_t kth_chain_header_bits(kth_header_t header);
// char const* kth_chain_header_proof_str(kth_header_t header);
// void kth_chain_header_set_bits(kth_header_t header, uint32_t bits);
// uint32_t kth_chain_header_nonce(kth_header_t header);
// void kth_chain_header_set_nonce(kth_header_t header, uint32_t nonce);
// kth_hash_t kth_chain_header_previous_block_hash(kth_header_t header);
// void kth_chain_header_previous_block_hash_out(kth_header_t header, kth_hash_t* out_previous_block_hash);
// kth_hash_t kth_chain_header_merkle(kth_header_t header);
// void kth_chain_header_merkle_out(kth_header_t header, kth_hash_t* out_merkle);
// kth_hash_t kth_chain_header_hash(kth_header_t header);
// void kth_chain_header_hash_out(kth_header_t header, kth_hash_t* out_hash);


}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_HEADER_H_
