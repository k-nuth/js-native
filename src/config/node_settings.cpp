// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/node_settings.h>

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

namespace detail {
v8::Local<v8::Object> config_node_settings_to_js(Isolate* isolate, kth_node_settings const& setts) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, string_to_js(isolate, "syncPeers"), Number::New(isolate, setts.sync_peers));
    setr = res->Set(ctx, string_to_js(isolate, "syncTimeoutSeconds"), Number::New(isolate, setts.sync_timeout_seconds));
    setr = res->Set(ctx, string_to_js(isolate, "blockLatencySeconds"), Number::New(isolate, setts.block_latency_seconds));
    setr = res->Set(ctx, string_to_js(isolate, "refreshTransactions"), Boolean::New(isolate, setts.refresh_transactions != 0));
    setr = res->Set(ctx, string_to_js(isolate, "compactBlocksHighBandwidth"), Boolean::New(isolate, setts.compact_blocks_high_bandwidth != 0));
    return res;
}
}

void config_node_settings_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_node_settings_default function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument network (#1). Required to be IsNumber.");
        return;
    }

    kth_network_t network = network_to_cpp(isolate, args[0]);
    kth_node_settings res = kth_config_node_settings_default(network);
    args.GetReturnValue().Set(detail::config_node_settings_to_js(isolate, res));
}

}  // namespace kth::js_native
