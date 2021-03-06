// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/network_settings.h>

#include <kth/js-native/config/network_settings.hpp>
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

v8::Local<v8::Object> config_endpoint_to_js(Isolate* isolate, kth_endpoint const& endpoint) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, to_string(isolate, "scheme"), to_string(isolate, endpoint.scheme));
    setr = res->Set(ctx, to_string(isolate, "host"), to_string(isolate, endpoint.host));
    setr = res->Set(ctx, to_string(isolate, "port"), Number::New(isolate, endpoint.port));
    return res;
}

v8::Local<v8::Array> config_endpoints_to_js(Isolate* isolate, kth_endpoint* endpoint, size_t n) {
    auto ctx = isolate->GetCurrentContext();
    v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(n);
    for (size_t i = 0; i < jsArr->Length(); ++i) {
        auto elem = config_endpoint_to_js(isolate, *endpoint);
        jsArr->Set(ctx, i, elem);
        ++endpoint;
    }
    return jsArr;
}

v8::Local<v8::Object> config_authority_to_js(Isolate* isolate, kth_authority const& authority) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, to_string(isolate, "ip"), to_string(isolate, authority.ip));
    setr = res->Set(ctx, to_string(isolate, "port"), Number::New(isolate, authority.port));
    return res;
}

v8::Local<v8::Array> config_authorities_to_js(Isolate* isolate, kth_authority* authority, size_t n) {
    auto ctx = isolate->GetCurrentContext();
    v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(n);
    for (size_t i = 0; i < jsArr->Length(); ++i) {
        auto elem = config_authority_to_js(isolate, *authority);
        jsArr->Set(ctx, i, elem);
        ++authority;
    }
    return jsArr;
}

v8::Local<v8::Array> config_strings_to_js(Isolate* isolate, char** strs, size_t n) {
    auto ctx = isolate->GetCurrentContext();
    v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(n);
    for (size_t i = 0; i < jsArr->Length(); ++i) {
        auto elem = to_string(isolate, *strs);
        jsArr->Set(ctx, i, elem);
        ++strs;
    }
    return jsArr;
}

v8::Local<v8::Object> config_network_settings_to_js(Isolate* isolate, kth_network_settings const& setts) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, to_string(isolate, "threads"), Number::New(isolate, setts.threads));
    setr = res->Set(ctx, to_string(isolate, "protocolMaximum"), Number::New(isolate, setts.protocol_maximum));
    setr = res->Set(ctx, to_string(isolate, "protocolMinimum"), Number::New(isolate, setts.protocol_minimum));
    setr = res->Set(ctx, to_string(isolate, "services"), Number::New(isolate, setts.services));
    setr = res->Set(ctx, to_string(isolate, "invalidServices"), Number::New(isolate, setts.invalid_services));
    setr = res->Set(ctx, to_string(isolate, "relayTransactions"), Boolean::New(isolate, setts.relay_transactions != 0));
    setr = res->Set(ctx, to_string(isolate, "validateChecksum"), Boolean::New(isolate, setts.validate_checksum != 0));

    setr = res->Set(ctx, to_string(isolate, "identifier"), Number::New(isolate, setts.identifier));
    setr = res->Set(ctx, to_string(isolate, "inboundPort"), Number::New(isolate, setts.inbound_port));
    setr = res->Set(ctx, to_string(isolate, "inboundConnections"), Number::New(isolate, setts.inbound_connections));
    setr = res->Set(ctx, to_string(isolate, "outboundConnections"), Number::New(isolate, setts.outbound_connections));
    setr = res->Set(ctx, to_string(isolate, "manualAttemptLimit"), Number::New(isolate, setts.manual_attempt_limit));
    setr = res->Set(ctx, to_string(isolate, "connectBatchSize"), Number::New(isolate, setts.connect_batch_size));
    setr = res->Set(ctx, to_string(isolate, "connectTimeoutSeconds"), Number::New(isolate, setts.connect_timeout_seconds));
    setr = res->Set(ctx, to_string(isolate, "channelHandshakeSeconds"), Number::New(isolate, setts.channel_handshake_seconds));
    setr = res->Set(ctx, to_string(isolate, "channelHeartbeatMinutes"), Number::New(isolate, setts.channel_heartbeat_minutes));
    setr = res->Set(ctx, to_string(isolate, "channelInactivityMinutes"), Number::New(isolate, setts.channel_inactivity_minutes));
    setr = res->Set(ctx, to_string(isolate, "channelExpirationMinutes"), Number::New(isolate, setts.channel_expiration_minutes));
    setr = res->Set(ctx, to_string(isolate, "channelGerminationSeconds"), Number::New(isolate, setts.channel_germination_seconds));
    setr = res->Set(ctx, to_string(isolate, "hostPoolCapacity"), Number::New(isolate, setts.host_pool_capacity));

    setr = res->Set(ctx, to_string(isolate, "hostsFile"), to_string(isolate, setts.hosts_file));
    setr = res->Set(ctx, to_string(isolate, "self"), config_authority_to_js(isolate, setts.self));
    setr = res->Set(ctx, to_string(isolate, "blacklist"), config_authorities_to_js(isolate, setts.blacklists, setts.blacklist_count));
    setr = res->Set(ctx, to_string(isolate, "peers"), config_endpoints_to_js(isolate, setts.peers, setts.peer_count));
    setr = res->Set(ctx, to_string(isolate, "seeds"), config_endpoints_to_js(isolate, setts.seeds, setts.seed_count));

    setr = res->Set(ctx, to_string(isolate, "debugFile"), to_string(isolate, setts.debug_file));
    setr = res->Set(ctx, to_string(isolate, "errorFile"), to_string(isolate, setts.error_file));
    setr = res->Set(ctx, to_string(isolate, "archiveDirectory"), to_string(isolate, setts.archive_directory));

    setr = res->Set(ctx, to_string(isolate, "rotationSize"), Number::New(isolate, setts.rotation_size));
    setr = res->Set(ctx, to_string(isolate, "minimumFreeSpace"), Number::New(isolate, setts.minimum_free_space));
    setr = res->Set(ctx, to_string(isolate, "maximumArchiveSize"), Number::New(isolate, setts.maximum_archive_size));
    setr = res->Set(ctx, to_string(isolate, "maximumArchiveFiles"), Number::New(isolate, setts.maximum_archive_files));

    setr = res->Set(ctx, to_string(isolate, "statisticsServer"), config_authority_to_js(isolate, setts.statistics_server));

    setr = res->Set(ctx, to_string(isolate, "verbose"), Boolean::New(isolate, setts.verbose != 0));
    setr = res->Set(ctx, to_string(isolate, "useIpv6"), Boolean::New(isolate, setts.use_ipv6 != 0));

    setr = res->Set(ctx, to_string(isolate, "userAgentBlacklist"), config_strings_to_js(isolate, setts.user_agent_blacklist, setts.user_agent_blacklist_count));

    return res;
}

void config_network_settings_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_network_settings_default function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument net (#1). Required to be IsNumber.");
        return;
    }

    kth_network_t net = to_kth_network_t(isolate, args[0]);
    kth_network_settings res = kth_config_network_settings_default(net);
    args.GetReturnValue().Set(config_network_settings_to_js(isolate, res));
}

}  // namespace kth::js_native
