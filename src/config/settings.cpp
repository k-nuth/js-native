// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/settings.h>

#include <kth/js-native/config/settings.hpp>

#include <kth/js-native/config/blockchain_settings.hpp>
#include <kth/js-native/config/database_settings.hpp>
#include <kth/js-native/config/network_settings.hpp>
#include <kth/js-native/config/node_settings.hpp>
#include <kth/js-native/helper.hpp>

namespace kth::js_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Global;

using v8::Object;
using v8::String;
using v8::Boolean;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Number;
using v8::Persistent;
using v8::Function;
using v8::Uint8Array;
using v8::ArrayBuffer;



// typedef struct {
//     kth_node_settings node;
//     kth_blockchain_settings chain;
//     kth_database_settings database;
//     kth_network_settings network;
// } kth_settings;

    // auto ctx = isolate->GetCurrentContext();
    // auto res = v8::Object::New(isolate);
    // auto setr = res->Set(ctx, string_to_js(isolate, "node"), detail::config_node_settings_to_js(isolate, setts.node));
    // setr = res->Set(ctx, string_to_js(isolate, "chain"), detail::config_blockchain_settings_to_js(isolate, setts.chain));
    // setr = res->Set(ctx, string_to_js(isolate, "database"), detail::config_database_settings_to_js(isolate, setts.database));
    // setr = res->Set(ctx, string_to_js(isolate, "network"), detail::config_network_settings_to_js(isolate, setts.network));


namespace detail {
v8::Local<v8::Object> config_settings_to_js(Isolate* isolate, kth_settings const& setts) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, string_to_js(isolate, "node"), detail::config_node_settings_to_js(isolate, setts.node));
    setr = res->Set(ctx, string_to_js(isolate, "chain"), detail::config_blockchain_settings_to_js(isolate, setts.chain));
    setr = res->Set(ctx, string_to_js(isolate, "database"), detail::config_database_settings_to_js(isolate, setts.database));
    setr = res->Set(ctx, string_to_js(isolate, "network"), detail::config_network_settings_to_js(isolate, setts.network));
    return res;
}

kth_settings config_settings_to_cpp(Isolate* isolate, v8::Local<v8::Object> const& setts) {
    auto ctx = isolate->GetCurrentContext();
    kth_settings res;

    printf("config_settings_to_cpp 1\n");
    res.chain = config_blockchain_settings_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "chain")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());
    printf("config_settings_to_cpp 2\n");
    res.database = config_database_settings_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "database")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());
    printf("config_settings_to_cpp 3\n");
    res.network = config_network_settings_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "network")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());
    printf("config_settings_to_cpp 4\n");
    res.node = config_node_settings_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "node")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());
    printf("config_settings_to_cpp 5\n");




    // printf("res.chain.cores:              %d\n", res.chain.cores);
    // printf("res.chain.priority:           %d\n", res.chain.priority);
    // printf("res.chain.byte_fee_satoshis:  %f\n", res.chain.byte_fee_satoshis);
    // printf("res.chain.sigop_fee_satoshis: %f\n", res.chain.sigop_fee_satoshis);

    // printf("res.chain.minimum_output_satoshis: %d\n", res.chain.minimum_output_satoshis);
    // printf("res.chain.notify_limit_hours:      %d\n", res.chain.notify_limit_hours);
    // printf("res.chain.reorganization_limit:    %d\n", res.chain.reorganization_limit);
    // printf("res.chain.checkpoint_count:        %d\n", res.chain.checkpoint_count);
    // printf("res.chain.checkpoints[0].height:   %zu\n", res.chain.checkpoints[0].height);
    // printf("res.chain.checkpoints[1].height:   %zu\n", res.chain.checkpoints[1].height);
    // printf("res.chain.checkpoints[2].height:   %zu\n", res.chain.checkpoints[2].height);
    // printf("res.chain.checkpoints[3].height:   %zu\n", res.chain.checkpoints[3].height);
    // printf("res.chain.checkpoints[4].height:   %zu\n", res.chain.checkpoints[4].height);

    // // // kth_checkpoint* checkpoints;

    // // res.fix_checkpoints = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "fixCheckpoints")).ToLocalChecked());
    // // res.allow_collisions = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "allowCollisions")).ToLocalChecked());
    // // res.easy_blocks = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "easyBlocks")).ToLocalChecked());
    // // res.retarget = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "retarget")).ToLocalChecked());
    // // res.bip16 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip16")).ToLocalChecked());
    // // res.bip30 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip30")).ToLocalChecked());
    // // res.bip34 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip34")).ToLocalChecked());
    // // res.bip66 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip66")).ToLocalChecked());
    // // res.bip65 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip65")).ToLocalChecked());
    // // res.bip90 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip90")).ToLocalChecked());
    // // res.bip68 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip68")).ToLocalChecked());
    // // res.bip112 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip112")).ToLocalChecked());
    // // res.bip113 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip113")).ToLocalChecked());
    // // res.bch_uahf = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchUahf")).ToLocalChecked());
    // // res.bch_daa_cw144 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchDaaCw144")).ToLocalChecked());
    // // res.bch_pythagoras = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchPythagoras")).ToLocalChecked());
    // // res.bch_euclid = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchEuclid")).ToLocalChecked());
    // // res.bch_pisano = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchPisano")).ToLocalChecked());
    // // res.bch_mersenne = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchMersenne")).ToLocalChecked());
    // // res.bch_fermat = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchFermat")).ToLocalChecked());
    // // res.bch_euler = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchEuler")).ToLocalChecked());
    // // res.bch_gauss = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchGauss")).ToLocalChecked());
    // // res.euler_activation_time = setts->Get(ctx, string_to_js(isolate, "eulerActivationTime")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    // // res.gauss_activation_time = setts->Get(ctx, string_to_js(isolate, "gaussActivationTime")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    // // res.asert_half_life = setts->Get(ctx, string_to_js(isolate, "asertHalfLife")).ToLocalChecked()->IntegerValue(ctx).ToChecked();


    // printf("res.database.directory:           %s\n", res.database.directory);
    // printf("res.database.flush_writes:        %d\n", res.database.flush_writes);
    // printf("res.database.file_growth_rate:    %d\n", res.database.file_growth_rate);
    // printf("res.database.index_start_height:  %d\n", res.database.index_start_height);
    // printf("res.database.reorg_pool_limit:    %d\n", res.database.reorg_pool_limit);
    // printf("res.database.db_max_size:         %zu\n", res.database.db_max_size);
    // printf("res.database.safe_mode:           %d\n", res.database.safe_mode);
    // printf("res.database.cache_capacity:      %d\n", res.database.cache_capacity);

    // printf("--------------------------------------------------------------------------------\n");

    // printf("res.network.threads:                     %d\n", res.network.threads);
    // printf("res.network.protocol_maximum:            %d\n", res.network.protocol_maximum);
    // printf("res.network.protocol_minimum:            %d\n", res.network.protocol_minimum);
    // printf("res.network.services:                    %d\n", res.network.services);
    // printf("res.network.invalid_services:            %d\n", res.network.invalid_services);

    // printf("res.network.relay_transactions:          %d\n", res.network.relay_transactions);
    // printf("res.network.validate_checksum:           %d\n", res.network.validate_checksum);
    // printf("res.network.identifier:                  %zu\n", res.network.identifier);
    // printf("res.network.inbound_port:                %d\n", res.network.inbound_port);
    // printf("res.network.inbound_connections:         %d\n", res.network.inbound_connections);

    // printf("res.network.outbound_connections:        %d\n", res.network.outbound_connections);
    // printf("res.network.manual_attempt_limit:        %d\n", res.network.manual_attempt_limit);
    // printf("res.network.connect_batch_size:          %d\n", res.network.connect_batch_size);
    // printf("res.network.connect_timeout_seconds:     %d\n", res.network.connect_timeout_seconds);
    // printf("res.network.channel_handshake_seconds:   %d\n", res.network.channel_handshake_seconds);

    // printf("res.network.channel_heartbeat_minutes:   %d\n", res.network.channel_heartbeat_minutes);
    // printf("res.network.channel_inactivity_minutes:  %d\n", res.network.channel_inactivity_minutes);
    // printf("res.network.channel_expiration_minutes:  %d\n", res.network.channel_expiration_minutes);
    // printf("res.network.channel_germination_seconds: %d\n", res.network.channel_germination_seconds);
    // printf("res.network.host_pool_capacity:          %d\n", res.network.host_pool_capacity);

    // printf("res.network.hosts_file:           %s\n", res.network.hosts_file);

    // printf("res.network.self.ip:   %s\n", res.network.self.ip);
    // printf("res.network.self.port: %d\n", res.network.self.port);


    // printf("res.network.blacklist_count:      %d\n", res.network.blacklist_count);
    // // printf("res.network.blacklist[0].ip:     %s\n", res.network.blacklist[0].ip);
    // // printf("res.network.blacklist[0].port:   %d\n", res.network.blacklist[0].port);

    // printf("res.network.peer_count:      %d\n", res.network.peer_count);

    // printf("res.network.seed_count:      %d\n", res.network.seed_count);
    // printf("res.network.seeds[0].scheme: %s\n", res.network.seeds[0].scheme);
    // printf("res.network.seeds[0].host:   %s\n", res.network.seeds[0].host);
    // printf("res.network.seeds[0].port:   %d\n", res.network.seeds[0].port);


    // printf("res.network.debug_file:           %s\n", res.network.debug_file);
    // printf("res.network.error_file:           %s\n", res.network.error_file);
    // printf("res.network.archive_directory:    %s\n", res.network.archive_directory);


    // printf("res.network.rotation_size:         %d\n", res.network.rotation_size);
    // printf("res.network.minimum_free_space:    %d\n", res.network.minimum_free_space);
    // printf("res.network.maximum_archive_size:  %d\n", res.network.maximum_archive_size);
    // printf("res.network.maximum_archive_files: %d\n", res.network.maximum_archive_files);


    // printf("res.network.statistics_server.ip:   %s\n", res.network.statistics_server.ip);
    // printf("res.network.statistics_server.port: %d\n", res.network.statistics_server.port);

    // printf("res.network.verbose:   %d\n", res.network.verbose);
    // printf("res.network.use_ipv6:  %d\n", res.network.use_ipv6);

    // printf("res.network.user_agent_blacklist_count: %d\n", res.network.user_agent_blacklist_count);
    // printf("res.network.user_agent_blacklist[0]:    %s\n", res.network.user_agent_blacklist[0]);

    // printf("--------------------------------------------------------------------------------\n");

    // printf("res.node.sync_peers: %d\n", res.node.sync_peers);
    // printf("res.node.sync_timeout_seconds: %d\n", res.node.sync_timeout_seconds);
    // printf("res.node.block_latency_seconds: %d\n", res.node.block_latency_seconds);
    // printf("res.node.refresh_transactions: %d\n", res.node.refresh_transactions);
    // printf("res.node.compact_blocks_high_bandwidth: %d\n", res.node.compact_blocks_high_bandwidth);

    return res;
}
}

void config_settings_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_settings_default function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument network (#1). Required to be IsNumber.");
        return;
    }

    kth_network_t network = network_to_cpp(isolate, args[0]);
    kth_settings setts = kth_config_settings_default(network);
    auto obj = detail::config_settings_to_js(isolate, setts);
    args.GetReturnValue().Set(obj);
}

void config_settings_get_from_file(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_settings_get_from_file function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsString()) {
        throw_exception(isolate, "Wrong argument type for argument path (#1). Required to be IsString.");
        return;
    }

    v8::String::Utf8Value path(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());

    kth_settings* settings;
    char* error_message;
    kth_bool_t res = kth_config_settings_get_from_file(*path, &settings, &error_message);

    auto ctx = isolate->GetCurrentContext();
    auto obj = v8::Object::New(isolate);
    auto setr = obj->Set(ctx, string_to_js(isolate, "ok"), Boolean::New(isolate, res != 0));

    if (res == 0) {
        setr = obj->Set(ctx, string_to_js(isolate, "message"), string_to_js(isolate, error_message));
    } else {
        setr = obj->Set(ctx, string_to_js(isolate, "settings"), detail::config_settings_to_js(isolate, *settings));
        kth_config_settings_destruct(settings);
    }
    args.GetReturnValue().Set(obj);
}

// void config_settings_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         throw_exception(isolate, "Wrong number of arguments. config_settings_destruct function requires 1 arguments.");
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong argument type for argument settings (#1). Required to be IsExternal.");
//         return;
//     }

//     void* settings = args[0]->arg_conv_func;
//     kth_config_settings_destruct(settings);
// }

}  // namespace kth::js_native
