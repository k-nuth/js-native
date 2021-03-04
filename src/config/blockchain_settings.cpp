// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/blockchain_settings.h>

#include <kth/js-native/config/blockchain_settings.hpp>
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

v8::Local<v8::Object> config_blockchain_settings_to_js(Isolate* isolate, kth_blockchain_settings const& setts) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    bool setr = res->Set(ctx, to_string(isolate, "cores"), Number::New(isolate, setts.cores));
    setr = res->Set(ctx, to_string(isolate, "priority"), Boolean::New(isolate, setts.priority != 0));
    return res;

// typedef struct {
//     uint32_t cores;
//     kth_bool_t priority;
//     float byte_fee_satoshis;
//     float sigop_fee_satoshis;
//     uint64_t minimum_output_satoshis;
//     uint32_t notify_limit_hours;
//     uint32_t reorganization_limit;
//     size_t checkpoint_count;
//     kth_checkpoint* checkpoints;
//     kth_bool_t fix_checkpoints;
//     kth_bool_t allow_collisions;
//     kth_bool_t easy_blocks;
//     kth_bool_t retarget;
//     kth_bool_t bip16;
//     kth_bool_t bip30;
//     kth_bool_t bip34;
//     kth_bool_t bip66;
//     kth_bool_t bip65;
//     kth_bool_t bip90;
//     kth_bool_t bip68;
//     kth_bool_t bip112;
//     kth_bool_t bip113;

//     kth_bool_t bch_uahf;
//     kth_bool_t bch_daa_cw144;
//     kth_bool_t bch_pythagoras;
//     kth_bool_t bch_euclid;
//     kth_bool_t bch_pisano;
//     kth_bool_t bch_mersenne;
//     kth_bool_t bch_fermat;      // 2020-May
//     kth_bool_t bch_euler;       // 2020-Nov
//     kth_bool_t bch_gauss;       // 2021-May
//     uint64_t euler_activation_time;
//     uint64_t gauss_activation_time;
//     uint64_t asert_half_life;   //two days
// } kth_blockchain_settings;

}

void config_blockchain_settings_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_blockchain_settings_default function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument net (#1). Required to be IsNumber.");
        return;
    }

    kth_network_t net = to_kth_network_t(isolate, args[0]);

    kth_blockchain_settings res = kth_config_blockchain_settings_default(net);
    // args.GetReturnValue().Set(External::New(isolate, res));
    args.GetReturnValue().Set(config_blockchain_settings_to_js(isolate, res));
}

}  // namespace kth::js_native
