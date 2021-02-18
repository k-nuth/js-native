// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_TRANSACTION_H_
#define KTH_JS_CHAIN_TRANSACTION_H_

#include <node.h>

namespace kth::js_native {

void chain_transaction_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_version(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_transaction_set_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_hash_sighash_type(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_locktime(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_fees(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_total_input_value(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_total_output_value(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_is_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_is_null_non_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_is_oversized_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_is_mature(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_is_overspent(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_is_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_is_missing_previous_outputs(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_is_final(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_is_locktime_conflict(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_outputs(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_transaction_inputs(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_TRANSACTION_H_
