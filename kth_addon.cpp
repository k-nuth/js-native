// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// #include <node.h>
#include <nan.h>

#include <kth/capi/node.h>
#include <kth/capi/chain/chain.h>

#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)

#include "chain/chain.hpp"
#include "chain/header.hpp"
#include "chain/block.hpp"
#include "chain/merkle_block.hpp"
#include "chain/transaction.hpp"
#include "chain/input.hpp"
#include "chain/output.hpp"
#include "chain/output_point.hpp"
#include "chain/script.hpp"
#include "chain/input_list.hpp"
#include "chain/output_list.hpp"
#include "chain/transaction_list.hpp"
#include "chain/block_list.hpp"
#include "chain/point.hpp"
#include "chain/history_compact_list.hpp"
#include "chain/history_compact.hpp"
#include "chain/payment_address.hpp"
#include "chain/stealth_compact.hpp"
#include "chain/stealth_compact_list.hpp"
#include "wallet/word_list.hpp"

namespace kth_js_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Number;
using v8::Persistent;
using v8::Function;


//void Method(FunctionCallbackInfo<Value> const& args) {
//    Isolate* isolate = args.GetIsolate();
//    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
//}


void node_construct(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsString() ||
         ! (args[1]->IsObject() || args[1]->IsNull()) ||
         ! (args[2]->IsObject() || args[2]->IsNull())
       ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    v8::String::Utf8Value path(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());

    int32_t sout_fd = -1;
    int32_t serr_fd = -1;

    if (! args[1]->IsNull()) {
        auto sout_obj = args[1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        sout_fd = sout_obj->Get(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "fd")).ToLocalChecked()->Int32Value(isolate->GetCurrentContext()).ToChecked();
    }

    if (! args[2]->IsNull()) {
        auto serr_obj = args[2]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        serr_fd = serr_obj->Get(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "fd")).ToLocalChecked()->Int32Value(isolate->GetCurrentContext()).ToChecked();
    }

    kth_bool_t ok;
    char* error_message;
    kth_settings settings = kth_config_settings_get_from_file(*path, &ok, &error_message);

    if ( ! ok) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, error_message)));
        return;
    }

    kth_node_t exec = kth_node_construct_fd(&settings, sout_fd, serr_fd);
    Local<External> ext = External::New(isolate, exec);
    args.GetReturnValue().Set(ext);
}

void node_destruct(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_node_t exec = (kth_node_t)vptr;
    kth_node_destruct(exec);
}


void node_stop(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_node_t exec = (kth_node_t)vptr;
    kth_node_stop(exec);
}


void node_initchain(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_node_t exec = (kth_node_t)vptr;
    int res = kth_node_initchain(exec);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}

//void node_run(FunctionCallbackInfo<Value> const& args) {
//    Isolate* isolate = args.GetIsolate();
//
//    if (args.Length() != 1) {
//        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//        return;
//    }
//
//    if (!args[0]->IsExternal()) {
//        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//        return;
//    }
//
//    void* vptr = v8::External::Cast(*args[0])->Value();
//    kth_node_t exec = (kth_node_t)vptr;
//    int res = kth_node_run(exec);
//
//    Local<Number> num = Number::New(isolate, res);
//    args.GetReturnValue().Set(num);
//}

void node_run_wait(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_node_t exec = (kth_node_t)vptr;
    int res = kth_node_run_wait(exec);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}


void node_get_chain(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_node_t exec = (kth_node_t)vptr;
    kth_chain_t chain = kth_node_get_chain(exec);


    Local<External> ext = External::New(isolate, chain);
    args.GetReturnValue().Set(ext);
}

//-------------------

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "kth_node_construct", node_construct);
    NODE_SET_METHOD(exports, "kth_node_destruct", node_destruct);
    NODE_SET_METHOD(exports, "kth_node_stop", node_stop);
    NODE_SET_METHOD(exports, "kth_node_initchain", node_initchain);
//    NODE_SET_METHOD(exports, "kth_node_run", node_run);
    NODE_SET_METHOD(exports, "kth_node_run_wait", node_run_wait);
    NODE_SET_METHOD(exports, "kth_node_get_chain", node_get_chain);
    
    // NODE_SET_METHOD(exports, "chain_validate_tx", chain_validate_tx);
    // NODE_SET_METHOD(exports, "chain_get_last_height", chain_get_last_height);
    NODE_SET_METHOD(exports, "chain_fetch_last_height", chain_fetch_last_height);
    NODE_SET_METHOD(exports, "chain_fetch_block_height", chain_fetch_block_height);
    NODE_SET_METHOD(exports, "chain_fetch_block_header_by_height", chain_fetch_block_header_by_height);
    NODE_SET_METHOD(exports, "chain_fetch_block_header_by_hash", chain_fetch_block_header_by_hash);
    NODE_SET_METHOD(exports, "chain_fetch_block_by_height", chain_fetch_block_by_height);
    NODE_SET_METHOD(exports, "chain_fetch_block_by_hash", chain_fetch_block_by_hash);
    NODE_SET_METHOD(exports, "chain_fetch_merkle_block_by_height", chain_fetch_merkle_block_by_height);
    NODE_SET_METHOD(exports, "chain_fetch_merkle_block_by_hash", chain_fetch_merkle_block_by_hash);
    // TODO(kth): implement compact blocks.
    // NODE_SET_METHOD(exports, "chain_fetch_compact_block_by_height", chain_fetch_compact_block_by_height);
    // NODE_SET_METHOD(exports, "chain_fetch_compact_block_by_hash", chain_fetch_compact_block_by_hash);
    NODE_SET_METHOD(exports, "chain_fetch_transaction", chain_fetch_transaction);
    NODE_SET_METHOD(exports, "chain_fetch_transaction_position", chain_fetch_transaction_position);
    NODE_SET_METHOD(exports, "chain_fetch_spend", chain_fetch_spend);
    NODE_SET_METHOD(exports, "chain_fetch_history", chain_fetch_history);
    // NODE_SET_METHOD(exports, "chain_fetch_stealth", chain_fetch_stealth);
    // NODE_SET_METHOD(exports, "chain_fetch_block_locator", chain_fetch_block_locator);
    NODE_SET_METHOD(exports, "chain_organize_block", chain_organize_block);
    NODE_SET_METHOD(exports, "chain_organize_transaction", chain_organize_transaction);

    // NODE_SET_METHOD(exports, "chain_subscribe_blockchain", chain_subscribe_blockchain);

    NODE_SET_METHOD(exports, "chain_header_destruct", chain_header_destruct);
    NODE_SET_METHOD(exports, "chain_header_get_version", chain_header_get_version);
    NODE_SET_METHOD(exports, "chain_header_set_version", chain_header_set_version);
    NODE_SET_METHOD(exports, "chain_header_get_previous_block_hash", chain_header_get_previous_block_hash);
    NODE_SET_METHOD(exports, "chain_header_get_merkle", chain_header_get_merkle);
    NODE_SET_METHOD(exports, "chain_header_get_hash", chain_header_get_hash);
    NODE_SET_METHOD(exports, "chain_header_get_timestamp", chain_header_get_timestamp);
    // NODE_SET_METHOD(exports, "chain_header_set_timestamp", chain_header_set_timestamp);
     NODE_SET_METHOD(exports, "chain_header_get_bits", chain_header_get_bits);
    // NODE_SET_METHOD(exports, "chain_header_set_bits", chain_header_set_bits);
     NODE_SET_METHOD(exports, "chain_header_get_nonce", chain_header_get_nonce);
    // NODE_SET_METHOD(exports, "chain_header_set_nonce", chain_header_set_nonce);

    NODE_SET_METHOD(exports, "chain_block_destruct", chain_block_destruct);
    NODE_SET_METHOD(exports, "chain_block_get_header", chain_block_get_header);
    NODE_SET_METHOD(exports, "chain_block_transaction_count", chain_block_transaction_count);
    NODE_SET_METHOD(exports, "chain_block_serialized_size", chain_block_serialized_size);
    NODE_SET_METHOD(exports, "chain_block_subsidy", chain_block_subsidy);
    NODE_SET_METHOD(exports, "chain_block_fees", chain_block_fees);
    NODE_SET_METHOD(exports, "chain_block_claim", chain_block_claim);
    NODE_SET_METHOD(exports, "chain_block_reward", chain_block_reward);
    NODE_SET_METHOD(exports, "chain_block_generate_merkle_root", chain_block_generate_merkle_root);
    NODE_SET_METHOD(exports, "chain_block_hash", chain_block_hash);
    NODE_SET_METHOD(exports, "chain_block_is_valid", chain_block_is_valid);
    NODE_SET_METHOD(exports, "kth_chain_block_transaction_nth", chain_block_transaction_nth);
    NODE_SET_METHOD(exports, "chain_block_signature_operations", chain_block_signature_operations);
    NODE_SET_METHOD(exports, "chain_block_signature_operations_bip16_active", chain_block_signature_operations_bip16_active);
    NODE_SET_METHOD(exports, "kth_chain_block_total_inputs", chain_block_total_inputs);
    NODE_SET_METHOD(exports, "chain_block_is_extra_coinbase", chain_block_is_extra_coinbase);
    NODE_SET_METHOD(exports, "chain_block_is_final", chain_block_is_final);
    NODE_SET_METHOD(exports, "chain_block_is_distinct_transaction_set", chain_block_is_distinct_transaction_set);
    NODE_SET_METHOD(exports, "chain_block_is_valid_coinbase_claim", chain_block_is_valid_coinbase_claim);
    NODE_SET_METHOD(exports, "chain_block_is_valid_coinbase_script", chain_block_is_valid_coinbase_script);
    NODE_SET_METHOD(exports, "chain_block_is_internal_double_spend", chain_block_is_internal_double_spend);
    NODE_SET_METHOD(exports, "chain_block_is_valid_merkle_root", chain_block_is_valid_merkle_root);

    NODE_SET_METHOD(exports, "chain_merkle_block_destruct", chain_merkle_block_destruct);
    NODE_SET_METHOD(exports, "chain_merkle_block_get_header", chain_merkle_block_get_header);
    NODE_SET_METHOD(exports, "chain_merkle_block_serialized_size", chain_merkle_block_serialized_size);
    NODE_SET_METHOD(exports, "chain_merkle_block_is_valid", chain_merkle_block_is_valid);

    NODE_SET_METHOD(exports, "chain_merkle_block_hash_count", chain_merkle_block_hash_count);
    NODE_SET_METHOD(exports, "chain_merkle_block_total_transaction_count", chain_merkle_block_total_transaction_count);
    NODE_SET_METHOD(exports, "chain_merkle_block_reset", chain_merkle_block_reset);

    NODE_SET_METHOD(exports, "chain_transaction_destruct", chain_transaction_destruct);
    NODE_SET_METHOD(exports, "chain_transaction_version", chain_transaction_version);
    // NODE_SET_METHOD(exports, "chain_transaction_set_version", chain_transaction_set_version);
    NODE_SET_METHOD(exports, "chain_transaction_hash", chain_transaction_hash);
    NODE_SET_METHOD(exports, "chain_transaction_hash_sighash_type", chain_transaction_hash_sighash_type);
    NODE_SET_METHOD(exports, "chain_transaction_locktime", chain_transaction_locktime);
    NODE_SET_METHOD(exports, "chain_transaction_serialized_size", chain_transaction_serialized_size);
    NODE_SET_METHOD(exports, "chain_transaction_fees", chain_transaction_fees);
    NODE_SET_METHOD(exports, "chain_transaction_signature_operations", chain_transaction_signature_operations);
    NODE_SET_METHOD(exports, "chain_transaction_signature_operations_bip16_active", chain_transaction_signature_operations_bip16_active);
    NODE_SET_METHOD(exports, "chain_transaction_total_input_value", chain_transaction_total_input_value);
    NODE_SET_METHOD(exports, "chain_transaction_total_output_value", chain_transaction_total_output_value);
    NODE_SET_METHOD(exports, "chain_transaction_is_coinbase", chain_transaction_is_coinbase);
    NODE_SET_METHOD(exports, "chain_transaction_is_null_non_coinbase", chain_transaction_is_null_non_coinbase);
    NODE_SET_METHOD(exports, "chain_transaction_is_oversized_coinbase", chain_transaction_is_oversized_coinbase);
    NODE_SET_METHOD(exports, "chain_transaction_is_mature", chain_transaction_is_mature);
    NODE_SET_METHOD(exports, "chain_transaction_is_overspent", chain_transaction_is_overspent);
    NODE_SET_METHOD(exports, "chain_transaction_is_double_spend", chain_transaction_is_double_spend);
    NODE_SET_METHOD(exports, "chain_transaction_is_missing_previous_outputs", chain_transaction_is_missing_previous_outputs);
    NODE_SET_METHOD(exports, "chain_transaction_is_final", chain_transaction_is_final);
    NODE_SET_METHOD(exports, "chain_transaction_is_locktime_conflict", chain_transaction_is_locktime_conflict);
    NODE_SET_METHOD(exports, "chain_transaction_outputs", chain_transaction_outputs);
    NODE_SET_METHOD(exports, "chain_transaction_inputs", chain_transaction_inputs);

    NODE_SET_METHOD(exports, "chain_input_destruct", chain_input_destruct);
    NODE_SET_METHOD(exports, "chain_input_is_final", chain_input_is_final);
    NODE_SET_METHOD(exports, "chain_input_serialized_size", chain_input_serialized_size);
    NODE_SET_METHOD(exports, "chain_input_sequence", chain_input_sequence);
    NODE_SET_METHOD(exports, "chain_input_signature_operations", chain_input_signature_operations);
    NODE_SET_METHOD(exports, "chain_input_script", chain_input_script);
    NODE_SET_METHOD(exports, "chain_input_previous_output", chain_input_previous_output);

    NODE_SET_METHOD(exports, "chain_output_destruct", chain_output_destruct);
    NODE_SET_METHOD(exports, "chain_output_is_valid", chain_output_is_valid);
    NODE_SET_METHOD(exports, "chain_output_serialized_size", chain_output_serialized_size);
    NODE_SET_METHOD(exports, "chain_output_value", chain_output_value);
    NODE_SET_METHOD(exports, "chain_output_signature_operations", chain_output_signature_operations);
    NODE_SET_METHOD(exports, "chain_output_script", chain_output_script);

    NODE_SET_METHOD(exports, "chain_output_point_construct", chain_output_point_construct);
    NODE_SET_METHOD(exports, "chain_output_point_construct_from_hash_index", chain_output_point_construct_from_hash_index);
    NODE_SET_METHOD(exports, "chain_output_point_destruct", chain_output_point_destruct);
    NODE_SET_METHOD(exports, "chain_output_point_get_hash", chain_output_point_get_hash);
    NODE_SET_METHOD(exports, "chain_output_point_get_index", chain_output_point_get_index);

    NODE_SET_METHOD(exports, "chain_script_destruct", chain_script_destruct);
    NODE_SET_METHOD(exports, "chain_script_is_valid", chain_script_is_valid);
    NODE_SET_METHOD(exports, "chain_script_is_valid_operations", chain_script_is_valid_operations);
    NODE_SET_METHOD(exports, "chain_script_satoshi_content_size", chain_script_satoshi_content_size);
    NODE_SET_METHOD(exports, "chain_script_serialized_size", chain_script_serialized_size);
    NODE_SET_METHOD(exports, "chain_script_to_string", chain_script_to_string);
    NODE_SET_METHOD(exports, "chain_script_sigops", chain_script_sigops);
    // NODE_SET_METHOD(exports, "chain_script_embedded_sigops", chain_script_embedded_sigops);

    NODE_SET_METHOD(exports, "chain_input_list_push_back", chain_input_list_push_back);
    NODE_SET_METHOD(exports, "chain_input_list_count", chain_input_list_count);
    NODE_SET_METHOD(exports, "chain_input_list_nth", chain_input_list_nth);

    NODE_SET_METHOD(exports, "chain_output_list_push_back", chain_output_list_push_back);
    NODE_SET_METHOD(exports, "chain_output_list_count", chain_output_list_count);
    NODE_SET_METHOD(exports, "chain_output_list_nth", chain_output_list_nth);

    NODE_SET_METHOD(exports, "chain_transaction_list_construct_default", chain_transaction_list_construct_default);
    NODE_SET_METHOD(exports, "chain_transaction_list_destruct", chain_transaction_list_destruct);
    NODE_SET_METHOD(exports, "chain_transaction_list_push_back", chain_transaction_list_push_back);
    NODE_SET_METHOD(exports, "chain_transaction_list_count", chain_transaction_list_count);
    NODE_SET_METHOD(exports, "chain_transaction_list_nth", chain_transaction_list_nth);

    NODE_SET_METHOD(exports, "chain_block_list_construct_default", chain_block_list_construct_default);
    NODE_SET_METHOD(exports, "chain_block_list_destruct", chain_block_list_destruct);
    NODE_SET_METHOD(exports, "chain_block_list_push_back", chain_block_list_push_back);
    NODE_SET_METHOD(exports, "chain_block_list_count", chain_block_list_count);
    NODE_SET_METHOD(exports, "chain_block_list_nth", chain_block_list_nth);

    NODE_SET_METHOD(exports, "chain_point_get_hash", chain_point_get_hash);
    NODE_SET_METHOD(exports, "chain_point_is_valid", chain_point_is_valid);
    NODE_SET_METHOD(exports, "chain_point_get_index", chain_point_get_index);
    NODE_SET_METHOD(exports, "chain_point_get_checksum", chain_point_get_checksum);

    NODE_SET_METHOD(exports, "chain_history_compact_list_destruct", chain_history_compact_list_destruct);
    NODE_SET_METHOD(exports, "chain_history_compact_list_count", chain_history_compact_list_count);
    NODE_SET_METHOD(exports, "chain_history_compact_list_nth", chain_history_compact_list_nth);
    
    NODE_SET_METHOD(exports, "chain_history_compact_get_point_kind", chain_history_compact_get_point_kind);
    NODE_SET_METHOD(exports, "chain_history_compact_get_point", chain_history_compact_get_point);
    NODE_SET_METHOD(exports, "chain_history_compact_get_height", chain_history_compact_get_height);
    NODE_SET_METHOD(exports, "chain_history_compact_get_value_or_previous_checksum", chain_history_compact_get_value_or_previous_checksum);

    NODE_SET_METHOD(exports, "wallet_payment_address_destruct", wallet_payment_address_destruct);
    NODE_SET_METHOD(exports, "wallet_payment_address_encoded", wallet_payment_address_encoded);
    NODE_SET_METHOD(exports, "wallet_payment_address_version", wallet_payment_address_version);
    NODE_SET_METHOD(exports, "wallet_payment_address_construct_from_string", wallet_payment_address_construct_from_string);

    NODE_SET_METHOD(exports, "chain_stealth_compact_get_ephemeral_public_key_hash", chain_stealth_compact_get_ephemeral_public_key_hash);
    NODE_SET_METHOD(exports, "chain_stealth_compact_get_transaction_hash", chain_stealth_compact_get_transaction_hash);
    NODE_SET_METHOD(exports, "chain_stealth_compact_get_public_key_hash", chain_stealth_compact_get_public_key_hash);

    NODE_SET_METHOD(exports, "chain_stealth_compact_list_destruct", chain_stealth_compact_list_destruct);
    NODE_SET_METHOD(exports, "chain_stealth_compact_list_count", chain_stealth_compact_list_count);
    NODE_SET_METHOD(exports, "chain_stealth_compact_list_nth", chain_stealth_compact_list_nth);

    NODE_SET_METHOD(exports, "wallet_word_list_construct", wallet_word_list_construct);
    NODE_SET_METHOD(exports, "wallet_word_list_destruct", wallet_word_list_destruct);
    NODE_SET_METHOD(exports, "wallet_word_list_push_back", wallet_word_list_push_back);
}

NODE_MODULE(kth, init)

}  // namespace kth_js_native