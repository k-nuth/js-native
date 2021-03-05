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

v8::Local<v8::Object> config_checkpoint_to_js(Isolate* isolate, kth_checkpoint const* checkpoint) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);

    auto setr = res->Set(ctx, to_string(isolate, "hash"), to_hash(isolate, checkpoint->hash));
    setr = res->Set(ctx, to_string(isolate, "height"), Number::New(isolate, checkpoint->height));

    return res;
}

v8::Local<v8::Array> config_checkpoints_to_js(Isolate* isolate, kth_checkpoint* checkpoint, size_t n) {
    auto ctx = isolate->GetCurrentContext();
    v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(n);
    for (size_t i = 0; i < jsArr->Length(); ++i) {
        auto elem = config_checkpoint_to_js(isolate, checkpoint);
        // double number = vec.at(i);
        // v8::Local<v8::Value> jsElement = Nan::New(number);
        jsArr->Set(ctx, i, elem);
        ++checkpoint;
    }
    return jsArr;
}

v8::Local<v8::Object> config_blockchain_settings_to_js(Isolate* isolate, kth_blockchain_settings const& setts) {
    auto ctx = isolate->GetCurrentContext();
    auto res = v8::Object::New(isolate);
    auto setr = res->Set(ctx, to_string(isolate, "cores"), Number::New(isolate, setts.cores));
    setr = res->Set(ctx, to_string(isolate, "priority"), Boolean::New(isolate, setts.priority != 0));

    setr = res->Set(ctx, to_string(isolate, "bytFeeSatoshis"), Number::New(isolate, setts.byte_fee_satoshis));
    setr = res->Set(ctx, to_string(isolate, "sigopFeeSatoshis"), Number::New(isolate, setts.sigop_fee_satoshis));
    setr = res->Set(ctx, to_string(isolate, "minimumOutputSatoshis"), Number::New(isolate, setts.minimum_output_satoshis));
    setr = res->Set(ctx, to_string(isolate, "notifyLimitHours"), Number::New(isolate, setts.notify_limit_hours));
    setr = res->Set(ctx, to_string(isolate, "reorganizationLimit"), Number::New(isolate, setts.reorganization_limit));
    // setr = res->Set(ctx, to_string(isolate, "checkpointCount"), Number::New(isolate, setts.checkpoint_count));

    // auto chkp = setts.checkpoints;
    // for (size_t i = 0; i < setts.checkpoint_count; ++i) {
    //     ++chkp;
    // }
    


    setr = res->Set(ctx, to_string(isolate, "checkpoints"), config_checkpoints_to_js(isolate, setts.checkpoints, setts.checkpoint_count));

    //TODO(fernando)
//     kth_checkpoint* checkpoints;

    setr = res->Set(ctx, to_string(isolate, "fixCheckpoints"), Boolean::New(isolate, setts.fix_checkpoints != 0));
    setr = res->Set(ctx, to_string(isolate, "allowCollisions"), Boolean::New(isolate, setts.allow_collisions != 0));
    setr = res->Set(ctx, to_string(isolate, "easyBlocks"), Boolean::New(isolate, setts.easy_blocks != 0));
    setr = res->Set(ctx, to_string(isolate, "retarget"), Boolean::New(isolate, setts.retarget != 0));
    setr = res->Set(ctx, to_string(isolate, "bip16"), Boolean::New(isolate, setts.bip16 != 0));
    setr = res->Set(ctx, to_string(isolate, "bip30"), Boolean::New(isolate, setts.bip30 != 0));
    setr = res->Set(ctx, to_string(isolate, "bip34"), Boolean::New(isolate, setts.bip34 != 0));
    setr = res->Set(ctx, to_string(isolate, "bip66"), Boolean::New(isolate, setts.bip66 != 0));
    setr = res->Set(ctx, to_string(isolate, "bip65"), Boolean::New(isolate, setts.bip65 != 0));
    setr = res->Set(ctx, to_string(isolate, "bip90"), Boolean::New(isolate, setts.bip90 != 0));
    setr = res->Set(ctx, to_string(isolate, "bip68"), Boolean::New(isolate, setts.bip68 != 0));
    setr = res->Set(ctx, to_string(isolate, "bip112"), Boolean::New(isolate, setts.bip112 != 0));
    setr = res->Set(ctx, to_string(isolate, "bip113"), Boolean::New(isolate, setts.bip113 != 0));
    setr = res->Set(ctx, to_string(isolate, "bchUahf"), Boolean::New(isolate, setts.bch_uahf != 0));
    setr = res->Set(ctx, to_string(isolate, "bchDaaCw144"), Boolean::New(isolate, setts.bch_daa_cw144 != 0));
    setr = res->Set(ctx, to_string(isolate, "bchPythagoras"), Boolean::New(isolate, setts.bch_pythagoras != 0));
    setr = res->Set(ctx, to_string(isolate, "bchEuclid"), Boolean::New(isolate, setts.bch_euclid != 0));
    setr = res->Set(ctx, to_string(isolate, "bchPisano"), Boolean::New(isolate, setts.bch_pisano != 0));
    setr = res->Set(ctx, to_string(isolate, "bchMersenne"), Boolean::New(isolate, setts.bch_mersenne != 0));
    setr = res->Set(ctx, to_string(isolate, "bchFermat"), Boolean::New(isolate, setts.bch_fermat != 0));
    setr = res->Set(ctx, to_string(isolate, "bchEuler"), Boolean::New(isolate, setts.bch_euler != 0));
    setr = res->Set(ctx, to_string(isolate, "bchGauss"), Boolean::New(isolate, setts.bch_gauss != 0));

    setr = res->Set(ctx, to_string(isolate, "eulerActivationTime"), Number::New(isolate, setts.euler_activation_time));
    setr = res->Set(ctx, to_string(isolate, "gaussActivationTime"), Number::New(isolate, setts.gauss_activation_time));
    setr = res->Set(ctx, to_string(isolate, "asertHalfLife"), Number::New(isolate, setts.asert_half_life));
    return res;
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
