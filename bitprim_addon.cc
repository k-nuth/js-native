// #include <node.h>
#include <nan.h>

#include <knuth/nodecint/executor_c.h>
#include <knuth/nodecint/chain/chain.h>

#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)

#include "chain/chain.h"
#include "chain/header.h"
#include "chain/block.h"
#include "chain/merkle_block.h"
#include "chain/transaction.h"
#include "chain/input.h"
#include "chain/output.h"
#include "chain/output_point.h"
#include "chain/script.h"
#include "chain/input_list.h"
#include "chain/output_list.h"
#include "chain/transaction_list.h"
#include "chain/block_list.h"
#include "chain/point.h"
#include "chain/history_compact_list.h"
#include "chain/history_compact.h"
#include "chain/payment_address.h"
#include "chain/stealth_compact.h"
#include "chain/stealth_compact_list.h"
#include "wallet/word_list.h"

namespace bitprim_ns {

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


void bitprim_executor_construct(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

//    printf("args[0]->IsString(): %d\n", args[0]->IsString());
//    printf("args[1]->IsObject(): %d\n", args[1]->IsObject());
//    printf("args[2]->IsObject(): %d\n", args[2]->IsObject());

//    printf("args[1]->IsObject(): %d\n", args[1]->IsObject());
//    printf("args[2]->IsObject(): %d\n", args[2]->IsObject());
//    printf("args[1]->IsNull():   %d\n", args[1]->IsNull());
//    printf("args[2]->IsNull():   %d\n", args[2]->IsNull());

    if ( ! args[0]->IsString() ||
         ! (args[1]->IsObject() || args[1]->IsNull()) ||
         ! (args[2]->IsObject() || args[2]->IsNull())
       ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    v8::String::Utf8Value path(args[0]->ToString());


    int32_t sout_fd = -1;
    int32_t serr_fd = -1;

    if (! args[1]->IsNull()) {
        auto sout_obj = args[1]->ToObject();
        sout_fd = sout_obj->Get(String::NewFromUtf8(isolate, "fd"))->Int32Value();
    }

    if (! args[2]->IsNull()) {
        auto serr_obj = args[2]->ToObject();
        serr_fd = serr_obj->Get(String::NewFromUtf8(isolate, "fd"))->Int32Value();
    }

//    printf("path:    %s\n", *path);
//    printf("sout_fd: %d\n", sout_fd);
//    printf("serr_fd: %d\n", serr_fd);

    executor_t exec = executor_construct_fd(*path, sout_fd, serr_fd);
//    printf("bitprim_executor_construct - exec: 0x%" PRIXPTR "\n", (uintptr_t)exec);

    Local<External> ext = External::New(isolate, exec);
//    printf("xxxxx 4\n");
    args.GetReturnValue().Set(ext);
//    printf("xxxxx 5\n");
}

void bitprim_executor_destruct(FunctionCallbackInfo<Value> const& args) {
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
    executor_t exec = (executor_t)vptr;
    executor_destruct(exec);
}


void bitprim_executor_stop(FunctionCallbackInfo<Value> const& args) {
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
    executor_t exec = (executor_t)vptr;
    executor_stop(exec);
}


void bitprim_executor_initchain(FunctionCallbackInfo<Value> const& args) {
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
    executor_t exec = (executor_t)vptr;
    int res = executor_initchain(exec);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}

//void bitprim_executor_run(FunctionCallbackInfo<Value> const& args) {
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
//    executor_t exec = (executor_t)vptr;
//    int res = executor_run(exec);
//
//    Local<Number> num = Number::New(isolate, res);
//    args.GetReturnValue().Set(num);
//}

void bitprim_executor_run_wait(FunctionCallbackInfo<Value> const& args) {
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
    executor_t exec = (executor_t)vptr;
    int res = executor_run_wait(exec);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}


void bitprim_executor_get_chain(FunctionCallbackInfo<Value> const& args) {
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
    executor_t exec = (executor_t)vptr;
    chain_t chain = executor_get_chain(exec);


    Local<External> ext = External::New(isolate, chain);
    args.GetReturnValue().Set(ext);
}

//-------------------

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "executor_construct", bitprim_executor_construct);
    NODE_SET_METHOD(exports, "executor_destruct", bitprim_executor_destruct);
    NODE_SET_METHOD(exports, "executor_stop", bitprim_executor_stop);
    NODE_SET_METHOD(exports, "executor_initchain", bitprim_executor_initchain);
//    NODE_SET_METHOD(exports, "executor_run", bitprim_executor_run);
    NODE_SET_METHOD(exports, "executor_run_wait", bitprim_executor_run_wait);
    NODE_SET_METHOD(exports, "executor_get_chain", bitprim_executor_get_chain);
    
    // NODE_SET_METHOD(exports, "chain_validate_tx", bitprim_chain_validate_tx);
    // NODE_SET_METHOD(exports, "chain_get_last_height", bitprim_chain_get_last_height);
    NODE_SET_METHOD(exports, "chain_fetch_last_height", bitprim_chain_fetch_last_height);
    NODE_SET_METHOD(exports, "chain_fetch_block_height", bitprim_chain_fetch_block_height);
    NODE_SET_METHOD(exports, "chain_fetch_block_header_by_height", bitprim_chain_fetch_block_header_by_height);
    NODE_SET_METHOD(exports, "chain_fetch_block_header_by_hash", bitprim_chain_fetch_block_header_by_hash);
    NODE_SET_METHOD(exports, "chain_fetch_block_by_height", bitprim_chain_fetch_block_by_height);
    NODE_SET_METHOD(exports, "chain_fetch_block_by_hash", bitprim_chain_fetch_block_by_hash);
    NODE_SET_METHOD(exports, "chain_fetch_merkle_block_by_height", bitprim_chain_fetch_merkle_block_by_height);
    NODE_SET_METHOD(exports, "chain_fetch_merkle_block_by_hash", bitprim_chain_fetch_merkle_block_by_hash);
    // TODO(kth): implement compact blocks.
    // NODE_SET_METHOD(exports, "chain_fetch_compact_block_by_height", bitprim_chain_fetch_compact_block_by_height);
    // NODE_SET_METHOD(exports, "chain_fetch_compact_block_by_hash", bitprim_chain_fetch_compact_block_by_hash);
    NODE_SET_METHOD(exports, "chain_fetch_transaction", bitprim_chain_fetch_transaction);
    NODE_SET_METHOD(exports, "chain_fetch_transaction_position", bitprim_chain_fetch_transaction_position);
    NODE_SET_METHOD(exports, "chain_fetch_spend", bitprim_chain_fetch_spend);
    NODE_SET_METHOD(exports, "chain_fetch_history", bitprim_chain_fetch_history);
    NODE_SET_METHOD(exports, "chain_fetch_stealth", bitprim_chain_fetch_stealth);
    // NODE_SET_METHOD(exports, "chain_fetch_block_locator", bitprim_chain_fetch_block_locator);
    NODE_SET_METHOD(exports, "chain_organize_block", bitprim_chain_organize_block);
    NODE_SET_METHOD(exports, "chain_organize_transaction", bitprim_chain_organize_transaction);


    NODE_SET_METHOD(exports, "chain_subscribe_blockchain", bitprim_chain_subscribe_blockchain);


    NODE_SET_METHOD(exports, "chain_header_destruct", bitprim_chain_header_destruct);
    NODE_SET_METHOD(exports, "chain_header_get_version", bitprim_chain_header_get_version);
    NODE_SET_METHOD(exports, "chain_header_set_version", bitprim_chain_header_set_version);
    NODE_SET_METHOD(exports, "chain_header_get_previous_block_hash", bitprim_chain_header_get_previous_block_hash);
    NODE_SET_METHOD(exports, "chain_header_get_merkle", bitprim_chain_header_get_merkle);
    NODE_SET_METHOD(exports, "chain_header_get_hash", bitprim_chain_header_get_hash);
    NODE_SET_METHOD(exports, "chain_header_get_timestamp", bitprim_chain_header_get_timestamp);
    // NODE_SET_METHOD(exports, "chain_header_set_timestamp", bitprim_chain_header_set_timestamp);
     NODE_SET_METHOD(exports, "chain_header_get_bits", bitprim_chain_header_get_bits);
    // NODE_SET_METHOD(exports, "chain_header_set_bits", bitprim_chain_header_set_bits);
     NODE_SET_METHOD(exports, "chain_header_get_nonce", bitprim_chain_header_get_nonce);
    // NODE_SET_METHOD(exports, "chain_header_set_nonce", bitprim_chain_header_set_nonce);

    NODE_SET_METHOD(exports, "chain_block_destruct", bitprim_chain_block_destruct);
    NODE_SET_METHOD(exports, "chain_block_get_header", bitprim_chain_block_get_header);
    NODE_SET_METHOD(exports, "chain_block_transaction_count", bitprim_chain_block_transaction_count);
    NODE_SET_METHOD(exports, "chain_block_serialized_size", bitprim_chain_block_serialized_size);
    NODE_SET_METHOD(exports, "chain_block_subsidy", bitprim_chain_block_subsidy);
    NODE_SET_METHOD(exports, "chain_block_fees", bitprim_chain_block_fees);
    NODE_SET_METHOD(exports, "chain_block_claim", bitprim_chain_block_claim);
    NODE_SET_METHOD(exports, "chain_block_reward", bitprim_chain_block_reward);
    NODE_SET_METHOD(exports, "chain_block_generate_merkle_root", bitprim_chain_block_generate_merkle_root);
    NODE_SET_METHOD(exports, "chain_block_hash", bitprim_chain_block_hash);
    NODE_SET_METHOD(exports, "chain_block_is_valid", bitprim_chain_block_is_valid);
    NODE_SET_METHOD(exports, "chain_block_transaction_nth", bitprim_chain_block_transaction_nth);
    NODE_SET_METHOD(exports, "chain_block_signature_operations", bitprim_chain_block_signature_operations);
    NODE_SET_METHOD(exports, "chain_block_signature_operations_bip16_active", bitprim_chain_block_signature_operations_bip16_active);
    NODE_SET_METHOD(exports, "chain_block_total_inputs", bitprim_chain_block_total_inputs);
    NODE_SET_METHOD(exports, "chain_block_is_extra_coinbase", bitprim_chain_block_is_extra_coinbase);
    NODE_SET_METHOD(exports, "chain_block_is_final", bitprim_chain_block_is_final);
    NODE_SET_METHOD(exports, "chain_block_is_distinct_transaction_set", bitprim_chain_block_is_distinct_transaction_set);
    NODE_SET_METHOD(exports, "chain_block_is_valid_coinbase_claim", bitprim_chain_block_is_valid_coinbase_claim);
    NODE_SET_METHOD(exports, "chain_block_is_valid_coinbase_script", bitprim_chain_block_is_valid_coinbase_script);
    NODE_SET_METHOD(exports, "chain_block_is_internal_double_spend", bitprim_chain_block_is_internal_double_spend);
    NODE_SET_METHOD(exports, "chain_block_is_valid_merkle_root", bitprim_chain_block_is_valid_merkle_root);

    NODE_SET_METHOD(exports, "chain_merkle_block_destruct", bitprim_chain_merkle_block_destruct);
    NODE_SET_METHOD(exports, "chain_merkle_block_get_header", bitprim_chain_merkle_block_get_header);
    NODE_SET_METHOD(exports, "chain_merkle_block_serialized_size", bitprim_chain_merkle_block_serialized_size);
    NODE_SET_METHOD(exports, "chain_merkle_block_is_valid", bitprim_chain_merkle_block_is_valid);

    NODE_SET_METHOD(exports, "chain_merkle_block_hash_count", bitprim_chain_merkle_block_hash_count);
    NODE_SET_METHOD(exports, "chain_merkle_block_total_transaction_count", bitprim_chain_merkle_block_total_transaction_count);
    NODE_SET_METHOD(exports, "chain_merkle_block_reset", bitprim_chain_merkle_block_reset);

    NODE_SET_METHOD(exports, "chain_transaction_destruct", bitprim_chain_transaction_destruct);
    NODE_SET_METHOD(exports, "chain_transaction_version", bitprim_chain_transaction_version);
    // NODE_SET_METHOD(exports, "chain_transaction_set_version", bitprim_chain_transaction_set_version);
    NODE_SET_METHOD(exports, "chain_transaction_hash", bitprim_chain_transaction_hash);
    NODE_SET_METHOD(exports, "chain_transaction_hash_sighash_type", bitprim_chain_transaction_hash_sighash_type);
    NODE_SET_METHOD(exports, "chain_transaction_locktime", bitprim_chain_transaction_locktime);
    NODE_SET_METHOD(exports, "chain_transaction_serialized_size", bitprim_chain_transaction_serialized_size);
    NODE_SET_METHOD(exports, "chain_transaction_fees", bitprim_chain_transaction_fees);
    NODE_SET_METHOD(exports, "chain_transaction_signature_operations", bitprim_chain_transaction_signature_operations);
    NODE_SET_METHOD(exports, "chain_transaction_signature_operations_bip16_active", bitprim_chain_transaction_signature_operations_bip16_active);
    NODE_SET_METHOD(exports, "chain_transaction_total_input_value", bitprim_chain_transaction_total_input_value);
    NODE_SET_METHOD(exports, "chain_transaction_total_output_value", bitprim_chain_transaction_total_output_value);
    NODE_SET_METHOD(exports, "chain_transaction_is_coinbase", bitprim_chain_transaction_is_coinbase);
    NODE_SET_METHOD(exports, "chain_transaction_is_null_non_coinbase", bitprim_chain_transaction_is_null_non_coinbase);
    NODE_SET_METHOD(exports, "chain_transaction_is_oversized_coinbase", bitprim_chain_transaction_is_oversized_coinbase);
    NODE_SET_METHOD(exports, "chain_transaction_is_mature", bitprim_chain_transaction_is_mature);
    NODE_SET_METHOD(exports, "chain_transaction_is_overspent", bitprim_chain_transaction_is_overspent);
    NODE_SET_METHOD(exports, "chain_transaction_is_double_spend", bitprim_chain_transaction_is_double_spend);
    NODE_SET_METHOD(exports, "chain_transaction_is_missing_previous_outputs", bitprim_chain_transaction_is_missing_previous_outputs);
    NODE_SET_METHOD(exports, "chain_transaction_is_final", bitprim_chain_transaction_is_final);
    NODE_SET_METHOD(exports, "chain_transaction_is_locktime_conflict", bitprim_chain_transaction_is_locktime_conflict);
    NODE_SET_METHOD(exports, "chain_transaction_outputs", bitprim_chain_transaction_outputs);
    NODE_SET_METHOD(exports, "chain_transaction_inputs", bitprim_chain_transaction_inputs);

    NODE_SET_METHOD(exports, "chain_input_destruct", bitprim_chain_input_destruct);
    NODE_SET_METHOD(exports, "chain_input_is_final", bitprim_chain_input_is_final);
    NODE_SET_METHOD(exports, "chain_input_serialized_size", bitprim_chain_input_serialized_size);
    NODE_SET_METHOD(exports, "chain_input_sequence", bitprim_chain_input_sequence);
    NODE_SET_METHOD(exports, "chain_input_signature_operations", bitprim_chain_input_signature_operations);
    NODE_SET_METHOD(exports, "chain_input_script", bitprim_chain_input_script);
    NODE_SET_METHOD(exports, "chain_input_previous_output", bitprim_chain_input_previous_output);

    NODE_SET_METHOD(exports, "chain_output_destruct", bitprim_chain_output_destruct);
    NODE_SET_METHOD(exports, "chain_output_is_valid", bitprim_chain_output_is_valid);
    NODE_SET_METHOD(exports, "chain_output_serialized_size", bitprim_chain_output_serialized_size);
    NODE_SET_METHOD(exports, "chain_output_value", bitprim_chain_output_value);
    NODE_SET_METHOD(exports, "chain_output_signature_operations", bitprim_chain_output_signature_operations);
    NODE_SET_METHOD(exports, "chain_output_script", bitprim_chain_output_script);

    NODE_SET_METHOD(exports, "chain_output_point_construct", bitprim_chain_output_point_construct);
    NODE_SET_METHOD(exports, "chain_output_point_construct_from_hash_index", bitprim_chain_output_point_construct_from_hash_index);
    NODE_SET_METHOD(exports, "chain_output_point_destruct", bitprim_chain_output_point_destruct);
    NODE_SET_METHOD(exports, "chain_output_point_get_hash", bitprim_chain_output_point_get_hash);
    NODE_SET_METHOD(exports, "chain_output_point_get_index", bitprim_chain_output_point_get_index);

    NODE_SET_METHOD(exports, "chain_script_destruct", bitprim_chain_script_destruct);
    NODE_SET_METHOD(exports, "chain_script_is_valid", bitprim_chain_script_is_valid);
    NODE_SET_METHOD(exports, "chain_script_is_valid_operations", bitprim_chain_script_is_valid_operations);
    NODE_SET_METHOD(exports, "chain_script_satoshi_content_size", bitprim_chain_script_satoshi_content_size);
    NODE_SET_METHOD(exports, "chain_script_serialized_size", bitprim_chain_script_serialized_size);
    NODE_SET_METHOD(exports, "chain_script_to_string", bitprim_chain_script_to_string);
    NODE_SET_METHOD(exports, "chain_script_sigops", bitprim_chain_script_sigops);
    NODE_SET_METHOD(exports, "chain_script_embedded_sigops", bitprim_chain_script_embedded_sigops);

    NODE_SET_METHOD(exports, "chain_input_list_push_back", bitprim_chain_input_list_push_back);
    NODE_SET_METHOD(exports, "chain_input_list_count", bitprim_chain_input_list_count);
    NODE_SET_METHOD(exports, "chain_input_list_nth", bitprim_chain_input_list_nth);

    NODE_SET_METHOD(exports, "chain_output_list_push_back", bitprim_chain_output_list_push_back);
    NODE_SET_METHOD(exports, "chain_output_list_count", bitprim_chain_output_list_count);
    NODE_SET_METHOD(exports, "chain_output_list_nth", bitprim_chain_output_list_nth);

    NODE_SET_METHOD(exports, "chain_transaction_list_construct_default", bitprim_chain_transaction_list_construct_default);
    NODE_SET_METHOD(exports, "chain_transaction_list_destruct", bitprim_chain_transaction_list_destruct);
    NODE_SET_METHOD(exports, "chain_transaction_list_push_back", bitprim_chain_transaction_list_push_back);
    NODE_SET_METHOD(exports, "chain_transaction_list_count", bitprim_chain_transaction_list_count);
    NODE_SET_METHOD(exports, "chain_transaction_list_nth", bitprim_chain_transaction_list_nth);

    NODE_SET_METHOD(exports, "chain_block_list_construct_default", bitprim_chain_block_list_construct_default);
    NODE_SET_METHOD(exports, "chain_block_list_destruct", bitprim_chain_block_list_destruct);
    NODE_SET_METHOD(exports, "chain_block_list_push_back", bitprim_chain_block_list_push_back);
    NODE_SET_METHOD(exports, "chain_block_list_count", bitprim_chain_block_list_count);
    NODE_SET_METHOD(exports, "chain_block_list_nth", bitprim_chain_block_list_nth);

    NODE_SET_METHOD(exports, "chain_point_get_hash", bitprim_chain_point_get_hash);
    NODE_SET_METHOD(exports, "chain_point_is_valid", bitprim_chain_point_is_valid);
    NODE_SET_METHOD(exports, "chain_point_get_index", bitprim_chain_point_get_index);
    NODE_SET_METHOD(exports, "chain_point_get_checksum", bitprim_chain_point_get_checksum);

    NODE_SET_METHOD(exports, "chain_history_compact_list_destruct", bitprim_chain_history_compact_list_destruct);
    NODE_SET_METHOD(exports, "chain_history_compact_list_count", bitprim_chain_history_compact_list_count);
    NODE_SET_METHOD(exports, "chain_history_compact_list_nth", bitprim_chain_history_compact_list_nth);
    
    NODE_SET_METHOD(exports, "chain_history_compact_get_point_kind", bitprim_chain_history_compact_get_point_kind);
    NODE_SET_METHOD(exports, "chain_history_compact_get_point", bitprim_chain_history_compact_get_point);
    NODE_SET_METHOD(exports, "chain_history_compact_get_height", bitprim_chain_history_compact_get_height);
    NODE_SET_METHOD(exports, "chain_history_compact_get_value_or_previous_checksum", bitprim_chain_history_compact_get_value_or_previous_checksum);

    NODE_SET_METHOD(exports, "chain_payment_address_destruct", bitprim_chain_payment_address_destruct);
    NODE_SET_METHOD(exports, "chain_payment_address_encoded", bitprim_chain_payment_address_encoded);
    NODE_SET_METHOD(exports, "chain_payment_address_version", bitprim_chain_payment_address_version);
    NODE_SET_METHOD(exports, "chain_payment_address_construct_from_string", bitprim_chain_payment_address_construct_from_string);

    NODE_SET_METHOD(exports, "chain_stealth_compact_get_ephemeral_public_key_hash", bitprim_chain_stealth_compact_get_ephemeral_public_key_hash);
    NODE_SET_METHOD(exports, "chain_stealth_compact_get_transaction_hash", bitprim_chain_stealth_compact_get_transaction_hash);
    NODE_SET_METHOD(exports, "chain_stealth_compact_get_public_key_hash", bitprim_chain_stealth_compact_get_public_key_hash);

    NODE_SET_METHOD(exports, "chain_stealth_compact_list_destruct", bitprim_chain_stealth_compact_list_destruct);
    NODE_SET_METHOD(exports, "chain_stealth_compact_list_count", bitprim_chain_stealth_compact_list_count);
    NODE_SET_METHOD(exports, "chain_stealth_compact_list_nth", bitprim_chain_stealth_compact_list_nth);

    NODE_SET_METHOD(exports, "wallet_word_list_construct", bitprim_wallet_word_list_construct);
    NODE_SET_METHOD(exports, "wallet_word_list_destruct", bitprim_wallet_word_list_destruct);
    NODE_SET_METHOD(exports, "wallet_word_list_push_back", bitprim_wallet_word_list_push_back);
}

NODE_MODULE(bitprim, init)

}  // namespace bitprim_ns
