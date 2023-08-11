// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/network_settings.h>
#include <kth/capi/platform.h>

#include <kth/js-native/config/network_settings.hpp>
#include <kth/js-native/helper.hpp>

namespace kth::js_native {

using v8::Array;
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

namespace detail {

v8::Local<v8::Object> config_endpoint_to_js(Isolate* isolate, kth_endpoint const& endpoint) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, string_to_js(isolate, "scheme"), string_to_js(isolate, endpoint.scheme));
    setr = res->Set(ctx, string_to_js(isolate, "host"), string_to_js(isolate, endpoint.host));
    setr = res->Set(ctx, string_to_js(isolate, "port"), Number::New(isolate, endpoint.port));
    return res;
}

v8::Local<v8::Array> config_endpoints_to_js(Isolate* isolate, kth_endpoint* endpoint, size_t n) {
    auto ctx = isolate->GetCurrentContext();
    v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(n);
    for (size_t i = 0; i < jsArr->Length(); ++i) {
        auto elem = config_endpoint_to_js(isolate, *endpoint);
        auto _ = jsArr->Set(ctx, i, elem);
        ++endpoint;
    }
    return jsArr;
}

v8::Local<v8::Object> config_authority_to_js(Isolate* isolate, kth_authority const& authority) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, string_to_js(isolate, "ip"), string_to_js(isolate, authority.ip));
    setr = res->Set(ctx, string_to_js(isolate, "port"), Number::New(isolate, authority.port));
    return res;
}

v8::Local<v8::Array> config_authorities_to_js(Isolate* isolate, kth_authority* authority, size_t n) {
    auto ctx = isolate->GetCurrentContext();
    v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(n);
    for (size_t i = 0; i < jsArr->Length(); ++i) {
        auto elem = config_authority_to_js(isolate, *authority);
        auto _ = jsArr->Set(ctx, i, elem);
        ++authority;
    }
    return jsArr;
}

v8::Local<v8::Array> config_strings_to_js(Isolate* isolate, char** strs, size_t n) {
    auto ctx = isolate->GetCurrentContext();
    v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(n);
    for (size_t i = 0; i < jsArr->Length(); ++i) {
        auto elem = string_to_js(isolate, *strs);
        auto _ = jsArr->Set(ctx, i, elem);
        ++strs;
    }
    return jsArr;
}

v8::Local<v8::Object> config_network_settings_to_js(Isolate* isolate, kth_network_settings const& setts) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, string_to_js(isolate, "threads"), Number::New(isolate, setts.threads));
    setr = res->Set(ctx, string_to_js(isolate, "protocolMaximum"), Number::New(isolate, setts.protocol_maximum));
    setr = res->Set(ctx, string_to_js(isolate, "protocolMinimum"), Number::New(isolate, setts.protocol_minimum));
    setr = res->Set(ctx, string_to_js(isolate, "services"), Number::New(isolate, setts.services));
    setr = res->Set(ctx, string_to_js(isolate, "invalidServices"), Number::New(isolate, setts.invalid_services));
    setr = res->Set(ctx, string_to_js(isolate, "relayTransactions"), Boolean::New(isolate, setts.relay_transactions != 0));
    setr = res->Set(ctx, string_to_js(isolate, "validateChecksum"), Boolean::New(isolate, setts.validate_checksum != 0));

    setr = res->Set(ctx, string_to_js(isolate, "identifier"), Number::New(isolate, setts.identifier));
    setr = res->Set(ctx, string_to_js(isolate, "inboundPort"), Number::New(isolate, setts.inbound_port));
    setr = res->Set(ctx, string_to_js(isolate, "inboundConnections"), Number::New(isolate, setts.inbound_connections));
    setr = res->Set(ctx, string_to_js(isolate, "outboundConnections"), Number::New(isolate, setts.outbound_connections));
    setr = res->Set(ctx, string_to_js(isolate, "manualAttemptLimit"), Number::New(isolate, setts.manual_attempt_limit));
    setr = res->Set(ctx, string_to_js(isolate, "connectBatchSize"), Number::New(isolate, setts.connect_batch_size));
    setr = res->Set(ctx, string_to_js(isolate, "connectTimeoutSeconds"), Number::New(isolate, setts.connect_timeout_seconds));
    setr = res->Set(ctx, string_to_js(isolate, "channelHandshakeSeconds"), Number::New(isolate, setts.channel_handshake_seconds));
    setr = res->Set(ctx, string_to_js(isolate, "channelHeartbeatMinutes"), Number::New(isolate, setts.channel_heartbeat_minutes));
    setr = res->Set(ctx, string_to_js(isolate, "channelInactivityMinutes"), Number::New(isolate, setts.channel_inactivity_minutes));
    setr = res->Set(ctx, string_to_js(isolate, "channelExpirationMinutes"), Number::New(isolate, setts.channel_expiration_minutes));
    setr = res->Set(ctx, string_to_js(isolate, "channelGerminationSeconds"), Number::New(isolate, setts.channel_germination_seconds));
    setr = res->Set(ctx, string_to_js(isolate, "hostPoolCapacity"), Number::New(isolate, setts.host_pool_capacity));

    setr = res->Set(ctx, string_to_js(isolate, "hostsFile"), string_to_js(isolate, setts.hosts_file));
    setr = res->Set(ctx, string_to_js(isolate, "self"), config_authority_to_js(isolate, setts.self));
    setr = res->Set(ctx, string_to_js(isolate, "blacklist"), config_authorities_to_js(isolate, setts.blacklist, setts.blacklist_count));
    setr = res->Set(ctx, string_to_js(isolate, "peers"), config_endpoints_to_js(isolate, setts.peers, setts.peer_count));
    setr = res->Set(ctx, string_to_js(isolate, "seeds"), config_endpoints_to_js(isolate, setts.seeds, setts.seed_count));

    setr = res->Set(ctx, string_to_js(isolate, "debugFile"), string_to_js(isolate, setts.debug_file));
    setr = res->Set(ctx, string_to_js(isolate, "errorFile"), string_to_js(isolate, setts.error_file));
    setr = res->Set(ctx, string_to_js(isolate, "archiveDirectory"), string_to_js(isolate, setts.archive_directory));

    setr = res->Set(ctx, string_to_js(isolate, "rotationSize"), Number::New(isolate, setts.rotation_size));
    setr = res->Set(ctx, string_to_js(isolate, "minimumFreeSpace"), Number::New(isolate, setts.minimum_free_space));
    setr = res->Set(ctx, string_to_js(isolate, "maximumArchiveSize"), Number::New(isolate, setts.maximum_archive_size));
    setr = res->Set(ctx, string_to_js(isolate, "maximumArchiveFiles"), Number::New(isolate, setts.maximum_archive_files));

    setr = res->Set(ctx, string_to_js(isolate, "statisticsServer"), config_authority_to_js(isolate, setts.statistics_server));

    setr = res->Set(ctx, string_to_js(isolate, "verbose"), Boolean::New(isolate, setts.verbose != 0));
    setr = res->Set(ctx, string_to_js(isolate, "useIpv6"), Boolean::New(isolate, setts.use_ipv6 != 0));

    setr = res->Set(ctx, string_to_js(isolate, "userAgentBlacklist"), config_strings_to_js(isolate, setts.user_agent_blacklist, setts.user_agent_blacklist_count));

    return res;
}

kth_authority config_authority_to_cpp(Isolate* isolate, v8::Local<v8::Object> const& setts) {
    auto ctx = isolate->GetCurrentContext();
    kth_authority res;

    // v8::String::Utf8Value str(isolate, setts->Get(ctx, string_to_js(isolate, "ip")).ToLocalChecked());
    // kth_platform_allocate_and_copy_string_at(&res.ip, 0, *str);

    string_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "ip")).ToLocalChecked()->ToString(ctx).ToLocalChecked(),
        &res.ip);

    res.port = setts->Get(ctx, string_to_js(isolate, "port")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    return res;
}

// kth_authority* config_authorities_to_cpp(Isolate* isolate, Local<Array> const& setts, kth_size_t* out_size) {
kth_authority* config_authorities_to_cpp(Isolate* isolate, Local<Array> const& setts, size_t* out_size) {
    auto const ctx = isolate->GetCurrentContext();
    *out_size = setts->Length();
    kth_authority* res = kth_config_authority_allocate_n(*out_size);
    auto const n = setts->Length();
    kth_authority* it = res;
    for (size_t i = 0; i < n; ++i) {
        *it = config_authority_to_cpp(isolate, setts->Get(ctx, i).ToLocalChecked().As<Object>());
        ++it;
    }
    return res;
}

kth_endpoint config_endpoint_to_cpp(Isolate* isolate, v8::Local<v8::Object> const& setts) {
    auto ctx = isolate->GetCurrentContext();
    kth_endpoint res;
    // v8::String::Utf8Value scheme_str(isolate, setts->Get(ctx, string_to_js(isolate, "scheme")).ToLocalChecked());
    // kth_platform_allocate_and_copy_string_at(&res.scheme, 0, *scheme_str);

    string_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "scheme")).ToLocalChecked()->ToString(ctx).ToLocalChecked(),
        &res.scheme);


    // v8::String::Utf8Value host_str(isolate, setts->Get(ctx, string_to_js(isolate, "host")).ToLocalChecked());
    // kth_platform_allocate_and_copy_string_at(&res.host, 0, *host_str);

    string_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "host")).ToLocalChecked()->ToString(ctx).ToLocalChecked(),
        &res.host);

    res.port = setts->Get(ctx, string_to_js(isolate, "port")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    return res;
}

// kth_endpoint* config_endpoints_to_cpp(Isolate* isolate, Local<Array> const& setts, kth_size_t* out_size) {
kth_endpoint* config_endpoints_to_cpp(Isolate* isolate, Local<Array> const& setts, size_t* out_size) {
    auto const ctx = isolate->GetCurrentContext();
    auto const n = setts->Length();
    *out_size = n;
    kth_endpoint* res = kth_config_endpoint_allocate_n(n);
    kth_endpoint* it = res;
    for (size_t i = 0; i < n; ++i) {
        *it = config_endpoint_to_cpp(isolate, setts->Get(ctx, i).ToLocalChecked().As<Object>());
        ++it;
    }
    return res;
}

// char** config_strings_to_cpp(Isolate* isolate, Local<Array> const& setts, kth_size_t* out_size) {
char** config_strings_to_cpp(Isolate* isolate, Local<Array> const& setts, size_t* out_size) {
    auto const ctx = isolate->GetCurrentContext();
    *out_size = setts->Length();
    char** buffer = kth_platform_allocate_array_of_strings(*out_size);
    // char** it = buffer;
    auto const n = setts->Length();
    for (size_t i = 0; i < n; ++i) {
        v8::String::Utf8Value str(isolate, setts->Get(ctx, i).ToLocalChecked());
        kth_platform_allocate_and_copy_string_at(buffer, i, *str);

        // string_to_cpp(isolate,
        //     setts->Get(ctx, i).ToLocalChecked()->ToString(ctx).ToLocalChecked(),
        //     it);

        // ++it;
    }
    return buffer;
}

kth_network_settings config_network_settings_to_cpp(Isolate* isolate, v8::Local<v8::Object> const& setts) {
    auto ctx = isolate->GetCurrentContext();
    kth_network_settings res;

    res.threads = setts->Get(ctx, string_to_js(isolate, "threads")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.protocol_maximum = setts->Get(ctx, string_to_js(isolate, "protocolMaximum")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.protocol_minimum = setts->Get(ctx, string_to_js(isolate, "protocolMinimum")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.services = setts->Get(ctx, string_to_js(isolate, "services")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.invalid_services = setts->Get(ctx, string_to_js(isolate, "invalidServices")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.relay_transactions = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "relayTransactions")).ToLocalChecked());
    res.validate_checksum = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "validateChecksum")).ToLocalChecked());
    res.identifier = setts->Get(ctx, string_to_js(isolate, "identifier")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.inbound_port = setts->Get(ctx, string_to_js(isolate, "inboundPort")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.inbound_connections = setts->Get(ctx, string_to_js(isolate, "inboundConnections")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.outbound_connections = setts->Get(ctx, string_to_js(isolate, "outboundConnections")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.manual_attempt_limit = setts->Get(ctx, string_to_js(isolate, "manualAttemptLimit")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.connect_batch_size = setts->Get(ctx, string_to_js(isolate, "connectBatchSize")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.connect_timeout_seconds = setts->Get(ctx, string_to_js(isolate, "connectTimeoutSeconds")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.channel_handshake_seconds = setts->Get(ctx, string_to_js(isolate, "channelHandshakeSeconds")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.channel_heartbeat_minutes = setts->Get(ctx, string_to_js(isolate, "channelHeartbeatMinutes")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.channel_inactivity_minutes = setts->Get(ctx, string_to_js(isolate, "channelInactivityMinutes")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.channel_expiration_minutes = setts->Get(ctx, string_to_js(isolate, "channelExpirationMinutes")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.channel_germination_seconds = setts->Get(ctx, string_to_js(isolate, "channelGerminationSeconds")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.host_pool_capacity = setts->Get(ctx, string_to_js(isolate, "hostPoolCapacity")).ToLocalChecked()->IntegerValue(ctx).ToChecked();

    // v8::String::Utf8Value hosts_file_str(isolate, setts->Get(ctx, string_to_js(isolate, "hostsFile")).ToLocalChecked());
    // kth_platform_allocate_and_copy_string_at(&res.hosts_file, 0, *hosts_file_str);
    string_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "hostsFile")).ToLocalChecked()->ToString(ctx).ToLocalChecked(),
        &res.hosts_file);

    res.self = config_authority_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "self")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());

    res.blacklist = config_authorities_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "blacklist")).ToLocalChecked().As<Array>(),
        &res.blacklist_count);

    res.peers = config_endpoints_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "peers")).ToLocalChecked().As<Array>(),
        &res.peer_count);

    res.seeds = config_endpoints_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "seeds")).ToLocalChecked().As<Array>(),
        &res.seed_count);

    // v8::String::Utf8Value debug_file_str(isolate, setts->Get(ctx, string_to_js(isolate, "debugFile")).ToLocalChecked());
    // kth_platform_allocate_and_copy_string_at(&res.debug_file, 0, *debug_file_str);
    string_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "debugFile")).ToLocalChecked()->ToString(ctx).ToLocalChecked(),
        &res.debug_file);

    // v8::String::Utf8Value error_file_str(isolate, setts->Get(ctx, string_to_js(isolate, "errorFile")).ToLocalChecked());
    // kth_platform_allocate_and_copy_string_at(&res.error_file, 0, *error_file_str);
    string_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "errorFile")).ToLocalChecked()->ToString(ctx).ToLocalChecked(),
        &res.error_file);

    // v8::String::Utf8Value archive_directory_str(isolate, setts->Get(ctx, string_to_js(isolate, "archiveDirectory")).ToLocalChecked());
    // kth_platform_allocate_and_copy_string_at(&res.archive_directory, 0, *archive_directory_str);
    string_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "archiveDirectory")).ToLocalChecked()->ToString(ctx).ToLocalChecked(),
        &res.archive_directory);

    res.rotation_size = setts->Get(ctx, string_to_js(isolate, "rotationSize")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.minimum_free_space = setts->Get(ctx, string_to_js(isolate, "minimumFreeSpace")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.maximum_archive_size = setts->Get(ctx, string_to_js(isolate, "maximumArchiveSize")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.maximum_archive_files = setts->Get(ctx, string_to_js(isolate, "maximumArchiveFiles")).ToLocalChecked()->IntegerValue(ctx).ToChecked();

    res.statistics_server = config_authority_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "statisticsServer")).ToLocalChecked()->ToObject(ctx).ToLocalChecked());

    res.verbose = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "verbose")).ToLocalChecked());
    res.use_ipv6 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "useIpv6")).ToLocalChecked());

    res.user_agent_blacklist = config_strings_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "userAgentBlacklist")).ToLocalChecked().As<Array>(),
        &res.user_agent_blacklist_count);

    return res;
}
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

    kth_network_t net = network_to_cpp(isolate, args[0]);
    kth_network_settings res = kth_config_network_settings_default(net);
    args.GetReturnValue().Set(detail::config_network_settings_to_js(isolate, res));
}

}  // namespace kth::js_native
