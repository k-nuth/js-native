// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// #include <node.h>
#include <nan.h>

#include <kth/capi/node.h>
#include <kth/capi/chain/chain.h>

#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)

#include <kth/js-native/chain/chain.hpp>
#include <kth/js-native/chain/header.hpp>
#include <kth/js-native/chain/block.hpp>
#include <kth/js-native/chain/merkle_block.hpp>
#include <kth/js-native/chain/transaction.hpp>
#include <kth/js-native/chain/input.hpp>
#include <kth/js-native/chain/output.hpp>
#include <kth/js-native/chain/output_point.hpp>
#include <kth/js-native/chain/script.hpp>
#include <kth/js-native/chain/input_list.hpp>
#include <kth/js-native/chain/output_list.hpp>
#include <kth/js-native/chain/transaction_list.hpp>
#include <kth/js-native/chain/block_list.hpp>
#include <kth/js-native/chain/point.hpp>
#include <kth/js-native/chain/history_compact_list.hpp>
#include <kth/js-native/chain/history_compact.hpp>
// #include <kth/js-native/chain/payment_address.hpp>
#include <kth/js-native/chain/stealth_compact.hpp>
#include <kth/js-native/chain/stealth_compact_list.hpp>

#include <kth/js-native/config/authority.hpp>
#include <kth/js-native/config/blockchain_settings.hpp>
#include <kth/js-native/config/checkpoint.hpp>
#include <kth/js-native/config/database_settings.hpp>
#include <kth/js-native/config/endpoint.hpp>
#include <kth/js-native/config/network_settings.hpp>
#include <kth/js-native/config/node_settings.hpp>
#include <kth/js-native/config/settings.hpp>

#include <kth/js-native/wallet/payment_address.hpp>

#include <kth/js-native/node.hpp>
#include <kth/js-native/string_list.hpp>

namespace kth::js_native {

void init(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "node_construct", node_construct);
    NODE_SET_METHOD(exports, "node_init_run_and_wait_for_signal", node_init_run_and_wait_for_signal);
    NODE_SET_METHOD(exports, "node_print_thread_id", node_print_thread_id);
    NODE_SET_METHOD(exports, "node_running", node_running);
    NODE_SET_METHOD(exports, "node_get_chain", node_get_chain);
    NODE_SET_METHOD(exports, "node_destruct", node_destruct);
    NODE_SET_METHOD(exports, "node_signal_stop", node_signal_stop);
    NODE_SET_METHOD(exports, "config_endpoint_allocate_n", config_endpoint_allocate_n);
    NODE_SET_METHOD(exports, "config_checkpoint_allocate_n", config_checkpoint_allocate_n);
    NODE_SET_METHOD(exports, "config_node_settings_default", config_node_settings_default);
    NODE_SET_METHOD(exports, "config_blockchain_settings_default", config_blockchain_settings_default);
    NODE_SET_METHOD(exports, "config_settings_default", config_settings_default);
    NODE_SET_METHOD(exports, "config_settings_get_from_file", config_settings_get_from_file);
    // NODE_SET_METHOD(exports, "config_settings_destruct", config_settings_destruct);
    NODE_SET_METHOD(exports, "config_authority_allocate_n", config_authority_allocate_n);
    NODE_SET_METHOD(exports, "config_database_settings_default", config_database_settings_default);
    NODE_SET_METHOD(exports, "config_network_settings_default", config_network_settings_default);

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

    // chain header
    NODE_SET_METHOD(exports, "chain_header_factory_from_data", chain_header_factory_from_data);
    NODE_SET_METHOD(exports, "chain_header_satoshi_fixed_size", chain_header_satoshi_fixed_size);
    NODE_SET_METHOD(exports, "chain_header_reset", chain_header_reset);
    NODE_SET_METHOD(exports, "chain_header_serialized_size", chain_header_serialized_size);
    NODE_SET_METHOD(exports, "chain_header_to_data", chain_header_to_data);
    NODE_SET_METHOD(exports, "chain_header_construct_default", chain_header_construct_default);
    NODE_SET_METHOD(exports, "chain_header_construct", chain_header_construct);
    NODE_SET_METHOD(exports, "chain_header_destruct", chain_header_destruct);
    NODE_SET_METHOD(exports, "chain_header_is_valid", chain_header_is_valid);
    NODE_SET_METHOD(exports, "chain_header_version", chain_header_version);
    NODE_SET_METHOD(exports, "chain_header_set_version", chain_header_set_version);
    NODE_SET_METHOD(exports, "chain_header_timestamp", chain_header_timestamp);
    NODE_SET_METHOD(exports, "chain_header_set_timestamp", chain_header_set_timestamp);
    NODE_SET_METHOD(exports, "chain_header_bits", chain_header_bits);
    NODE_SET_METHOD(exports, "chain_header_proof_str", chain_header_proof_str);
    NODE_SET_METHOD(exports, "chain_header_set_bits", chain_header_set_bits);
    NODE_SET_METHOD(exports, "chain_header_nonce", chain_header_nonce);
    NODE_SET_METHOD(exports, "chain_header_set_nonce", chain_header_set_nonce);
    NODE_SET_METHOD(exports, "chain_header_previous_block_hash", chain_header_previous_block_hash);
    NODE_SET_METHOD(exports, "chain_header_merkle", chain_header_merkle);
    NODE_SET_METHOD(exports, "chain_header_hash", chain_header_hash);

    NODE_SET_METHOD(exports, "chain_block_construct_default", chain_block_construct_default);
    NODE_SET_METHOD(exports, "chain_block_construct", chain_block_construct);
    NODE_SET_METHOD(exports, "chain_block_factory_from_data", chain_block_factory_from_data);
    NODE_SET_METHOD(exports, "chain_block_destruct", chain_block_destruct);
    NODE_SET_METHOD(exports, "chain_block_is_valid", chain_block_is_valid);
    NODE_SET_METHOD(exports, "chain_block_header", chain_block_header);
    NODE_SET_METHOD(exports, "chain_block_hash", chain_block_hash);
    NODE_SET_METHOD(exports, "chain_block_hash_out", chain_block_hash_out);
    NODE_SET_METHOD(exports, "chain_block_proof_str", chain_block_proof_str);
    NODE_SET_METHOD(exports, "chain_block_transactions", chain_block_transactions);
    NODE_SET_METHOD(exports, "chain_block_serialized_size", chain_block_serialized_size);
    NODE_SET_METHOD(exports, "chain_block_subsidy", chain_block_subsidy);
    NODE_SET_METHOD(exports, "chain_block_fees", chain_block_fees);
    NODE_SET_METHOD(exports, "chain_block_claim", chain_block_claim);
    NODE_SET_METHOD(exports, "chain_block_reward", chain_block_reward);
    NODE_SET_METHOD(exports, "chain_block_generate_merkle_root", chain_block_generate_merkle_root);
    NODE_SET_METHOD(exports, "chain_block_generate_merkle_root_out", chain_block_generate_merkle_root_out);
    NODE_SET_METHOD(exports, "chain_block_signature_operations", chain_block_signature_operations);
    NODE_SET_METHOD(exports, "chain_block_signature_operations_bip16_active", chain_block_signature_operations_bip16_active);
    NODE_SET_METHOD(exports, "chain_block_total_inputs", chain_block_total_inputs);
    NODE_SET_METHOD(exports, "chain_block_is_extra_coinbases", chain_block_is_extra_coinbases);
    NODE_SET_METHOD(exports, "chain_block_is_final", chain_block_is_final);
    NODE_SET_METHOD(exports, "chain_block_is_distinct_transaction_set", chain_block_is_distinct_transaction_set);
    NODE_SET_METHOD(exports, "chain_block_is_valid_coinbase_claim", chain_block_is_valid_coinbase_claim);
    NODE_SET_METHOD(exports, "chain_block_is_valid_coinbase_script", chain_block_is_valid_coinbase_script);
    NODE_SET_METHOD(exports, "chain_block_is_internal_double_spend", chain_block_is_internal_double_spend);
    NODE_SET_METHOD(exports, "chain_block_is_valid_merkle_root", chain_block_is_valid_merkle_root);
    NODE_SET_METHOD(exports, "chain_block_to_data", chain_block_to_data);

    NODE_SET_METHOD(exports, "chain_merkle_block_destruct", chain_merkle_block_destruct);
    NODE_SET_METHOD(exports, "chain_merkle_block_get_header", chain_merkle_block_get_header);
    NODE_SET_METHOD(exports, "chain_merkle_block_serialized_size", chain_merkle_block_serialized_size);
    NODE_SET_METHOD(exports, "chain_merkle_block_is_valid", chain_merkle_block_is_valid);

    NODE_SET_METHOD(exports, "chain_merkle_block_hash_count", chain_merkle_block_hash_count);
    NODE_SET_METHOD(exports, "chain_merkle_block_total_transaction_count", chain_merkle_block_total_transaction_count);
    NODE_SET_METHOD(exports, "chain_merkle_block_reset", chain_merkle_block_reset);

    NODE_SET_METHOD(exports, "chain_transaction_factory_from_data", chain_transaction_factory_from_data);
    NODE_SET_METHOD(exports, "chain_transaction_construct_default", chain_transaction_construct_default);
    NODE_SET_METHOD(exports, "chain_transaction_construct", chain_transaction_construct);
    NODE_SET_METHOD(exports, "chain_transaction_destruct", chain_transaction_destruct);
    NODE_SET_METHOD(exports, "chain_transaction_is_valid", chain_transaction_is_valid);
    NODE_SET_METHOD(exports, "chain_transaction_version", chain_transaction_version);
    NODE_SET_METHOD(exports, "chain_transaction_set_version", chain_transaction_set_version);
    NODE_SET_METHOD(exports, "chain_transaction_hash", chain_transaction_hash);
    NODE_SET_METHOD(exports, "chain_transaction_hash_out", chain_transaction_hash_out);
    NODE_SET_METHOD(exports, "chain_transaction_hash_sighash_type", chain_transaction_hash_sighash_type);
    NODE_SET_METHOD(exports, "chain_transaction_hash_sighash_type_out", chain_transaction_hash_sighash_type_out);
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
    NODE_SET_METHOD(exports, "chain_transaction_to_data", chain_transaction_to_data);

    NODE_SET_METHOD(exports, "chain_input_construct_default", chain_input_construct_default);
    NODE_SET_METHOD(exports, "chain_input_construct", chain_input_construct);
    NODE_SET_METHOD(exports, "chain_input_destruct", chain_input_destruct);
    NODE_SET_METHOD(exports, "chain_input_factory_from_data", chain_input_factory_from_data);
    NODE_SET_METHOD(exports, "chain_input_is_valid", chain_input_is_valid);
    NODE_SET_METHOD(exports, "chain_input_is_final", chain_input_is_final);
    NODE_SET_METHOD(exports, "chain_input_serialized_size", chain_input_serialized_size);
    NODE_SET_METHOD(exports, "chain_input_sequence", chain_input_sequence);
    NODE_SET_METHOD(exports, "chain_input_signature_operations", chain_input_signature_operations);
    NODE_SET_METHOD(exports, "chain_input_script", chain_input_script);
    NODE_SET_METHOD(exports, "chain_input_previous_output", chain_input_previous_output);
    NODE_SET_METHOD(exports, "chain_input_to_data", chain_input_to_data);

    NODE_SET_METHOD(exports, "chain_output_construct_default", chain_output_construct_default);
    NODE_SET_METHOD(exports, "chain_output_construct", chain_output_construct);
    NODE_SET_METHOD(exports, "chain_output_destruct", chain_output_destruct);
    NODE_SET_METHOD(exports, "chain_output_factory_from_data", chain_output_factory_from_data);
    NODE_SET_METHOD(exports, "chain_output_is_valid", chain_output_is_valid);
    NODE_SET_METHOD(exports, "chain_output_serialized_size", chain_output_serialized_size);
    NODE_SET_METHOD(exports, "chain_output_value", chain_output_value);
    NODE_SET_METHOD(exports, "chain_output_signature_operations", chain_output_signature_operations);
    NODE_SET_METHOD(exports, "chain_output_script", chain_output_script);
    NODE_SET_METHOD(exports, "chain_output_payment_address", chain_output_payment_address);
    NODE_SET_METHOD(exports, "chain_output_to_data", chain_output_to_data);

    NODE_SET_METHOD(exports, "chain_output_point_construct", chain_output_point_construct);
    NODE_SET_METHOD(exports, "chain_output_point_construct_from_hash_index", chain_output_point_construct_from_hash_index);
    NODE_SET_METHOD(exports, "chain_output_point_destruct", chain_output_point_destruct);
    NODE_SET_METHOD(exports, "chain_output_point_get_hash", chain_output_point_get_hash);
    NODE_SET_METHOD(exports, "chain_output_point_get_index", chain_output_point_get_index);

    NODE_SET_METHOD(exports, "chain_script_construct_default", chain_script_construct_default);
    NODE_SET_METHOD(exports, "chain_script_construct", chain_script_construct);
    NODE_SET_METHOD(exports, "chain_script_destruct", chain_script_destruct);
    NODE_SET_METHOD(exports, "chain_script_is_valid", chain_script_is_valid);
    NODE_SET_METHOD(exports, "chain_script_is_valid_operations", chain_script_is_valid_operations);
    NODE_SET_METHOD(exports, "chain_script_satoshi_content_size", chain_script_satoshi_content_size);
    NODE_SET_METHOD(exports, "chain_script_serialized_size", chain_script_serialized_size);
    NODE_SET_METHOD(exports, "chain_script_to_string", chain_script_to_string);
    NODE_SET_METHOD(exports, "chain_script_type", chain_script_type);
    NODE_SET_METHOD(exports, "chain_script_to_data", chain_script_to_data);
    NODE_SET_METHOD(exports, "chain_script_sigops", chain_script_sigops);

    NODE_SET_METHOD(exports, "chain_input_list_construct_default", chain_input_list_construct_default);
    NODE_SET_METHOD(exports, "chain_input_list_push_back", chain_input_list_push_back);
    NODE_SET_METHOD(exports, "chain_input_list_destruct", chain_input_list_destruct);
    NODE_SET_METHOD(exports, "chain_input_list_count", chain_input_list_count);
    NODE_SET_METHOD(exports, "chain_input_list_nth", chain_input_list_nth);

    NODE_SET_METHOD(exports, "chain_output_list_construct_default", chain_output_list_construct_default);
    NODE_SET_METHOD(exports, "chain_output_list_push_back", chain_output_list_push_back);
    NODE_SET_METHOD(exports, "chain_output_list_destruct", chain_output_list_destruct);
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

    NODE_SET_METHOD(exports, "chain_stealth_compact_get_ephemeral_public_key_hash", chain_stealth_compact_get_ephemeral_public_key_hash);
    NODE_SET_METHOD(exports, "chain_stealth_compact_get_transaction_hash", chain_stealth_compact_get_transaction_hash);
    NODE_SET_METHOD(exports, "chain_stealth_compact_get_public_key_hash", chain_stealth_compact_get_public_key_hash);

    NODE_SET_METHOD(exports, "chain_stealth_compact_list_destruct", chain_stealth_compact_list_destruct);
    NODE_SET_METHOD(exports, "chain_stealth_compact_list_count", chain_stealth_compact_list_count);
    NODE_SET_METHOD(exports, "chain_stealth_compact_list_nth", chain_stealth_compact_list_nth);

    NODE_SET_METHOD(exports, "wallet_payment_address_set_cashaddr_prefix", wallet_payment_address_set_cashaddr_prefix);
    NODE_SET_METHOD(exports, "wallet_payment_address_encoded_legacy", wallet_payment_address_encoded_legacy);
    NODE_SET_METHOD(exports, "wallet_payment_address_encoded_cashaddr", wallet_payment_address_encoded_cashaddr);
    NODE_SET_METHOD(exports, "wallet_payment_address_construct_from_string", wallet_payment_address_construct_from_string);
    NODE_SET_METHOD(exports, "wallet_payment_address_hash20", wallet_payment_address_hash20);
    NODE_SET_METHOD(exports, "wallet_payment_address_hash32", wallet_payment_address_hash32);
    NODE_SET_METHOD(exports, "wallet_payment_address_version", wallet_payment_address_version);
    NODE_SET_METHOD(exports, "wallet_payment_address_is_valid", wallet_payment_address_is_valid);
    NODE_SET_METHOD(exports, "wallet_payment_address_destruct", wallet_payment_address_destruct);

    NODE_SET_METHOD(exports, "core_string_list_construct", core_string_list_construct);
    NODE_SET_METHOD(exports, "core_string_list_destruct", core_string_list_destruct);
    NODE_SET_METHOD(exports, "core_string_list_push_back", core_string_list_push_back);
}

NODE_MODULE(kth, init)

}  // namespace kth::js_native
