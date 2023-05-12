// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_HEADER_H_
#define KTH_JS_CHAIN_HEADER_H_

#include <node.h>

namespace kth::js_native {

void chain_header_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_satoshi_fixed_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_reset(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_to_data(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_set_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_set_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_bits(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_proof_str(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_set_bits(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_set_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_previous_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_merkle(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_header_hash(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_HEADER_H_
