// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/blockchain_settings.h>
#include <kth/capi/config/checkpoint.h>

#include <kth/js-native/config/blockchain_settings.hpp>
#include <kth/js-native/helper.hpp>

namespace kth::js_native {

using v8::Array;
using v8::ArrayBuffer;
using v8::Boolean;
using v8::Exception;
using v8::External;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Global;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Uint8Array;
using v8::Value;

namespace detail {

Local<Object> config_checkpoint_to_js(Isolate* isolate, kth_checkpoint const& checkpoint) {
    auto ctx = isolate->GetCurrentContext();
    auto res = Object::New(isolate);
    auto setr = res->Set(ctx, string_to_js(isolate, "hash"), hash_to_js(isolate, checkpoint.hash));
    setr = res->Set(ctx, string_to_js(isolate, "height"), Number::New(isolate, checkpoint.height));
    return res;
}

Local<Array> config_checkpoints_to_js(Isolate* isolate, kth_checkpoint* checkpoint, size_t n) {
    auto ctx = isolate->GetCurrentContext();
    Local<Array> jsArr = Nan::New<Array>(n);
    for (size_t i = 0; i < jsArr->Length(); ++i) {
        auto elem = config_checkpoint_to_js(isolate, *checkpoint);
        jsArr->Set(ctx, i, elem);
        ++checkpoint;
    }
    return jsArr;
}

Local<Object> config_blockchain_settings_to_js(Isolate* isolate, kth_blockchain_settings const& setts) {
    auto ctx = isolate->GetCurrentContext();
    auto res = Object::New(isolate);
    auto setr = res->Set(ctx, string_to_js(isolate, "cores"), Number::New(isolate, setts.cores));
    setr = res->Set(ctx, string_to_js(isolate, "priority"), Boolean::New(isolate, setts.priority != 0));

    setr = res->Set(ctx, string_to_js(isolate, "byteFeeSatoshis"), Number::New(isolate, setts.byte_fee_satoshis));
    setr = res->Set(ctx, string_to_js(isolate, "sigopFeeSatoshis"), Number::New(isolate, setts.sigop_fee_satoshis));
    setr = res->Set(ctx, string_to_js(isolate, "minimumOutputSatoshis"), Number::New(isolate, setts.minimum_output_satoshis));
    setr = res->Set(ctx, string_to_js(isolate, "notifyLimitHours"), Number::New(isolate, setts.notify_limit_hours));
    setr = res->Set(ctx, string_to_js(isolate, "reorganizationLimit"), Number::New(isolate, setts.reorganization_limit));

    setr = res->Set(ctx, string_to_js(isolate, "checkpoints"), config_checkpoints_to_js(isolate, setts.checkpoints, setts.checkpoint_count));

    setr = res->Set(ctx, string_to_js(isolate, "fixCheckpoints"), Boolean::New(isolate, setts.fix_checkpoints != 0));
    setr = res->Set(ctx, string_to_js(isolate, "allowCollisions"), Boolean::New(isolate, setts.allow_collisions != 0));
    setr = res->Set(ctx, string_to_js(isolate, "easyBlocks"), Boolean::New(isolate, setts.easy_blocks != 0));
    setr = res->Set(ctx, string_to_js(isolate, "retarget"), Boolean::New(isolate, setts.retarget != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bip16"), Boolean::New(isolate, setts.bip16 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bip30"), Boolean::New(isolate, setts.bip30 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bip34"), Boolean::New(isolate, setts.bip34 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bip66"), Boolean::New(isolate, setts.bip66 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bip65"), Boolean::New(isolate, setts.bip65 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bip90"), Boolean::New(isolate, setts.bip90 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bip68"), Boolean::New(isolate, setts.bip68 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bip112"), Boolean::New(isolate, setts.bip112 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bip113"), Boolean::New(isolate, setts.bip113 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bchUahf"), Boolean::New(isolate, setts.bch_uahf != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bchDaaCw144"), Boolean::New(isolate, setts.bch_daa_cw144 != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bchPythagoras"), Boolean::New(isolate, setts.bch_pythagoras != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bchEuclid"), Boolean::New(isolate, setts.bch_euclid != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bchPisano"), Boolean::New(isolate, setts.bch_pisano != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bchMersenne"), Boolean::New(isolate, setts.bch_mersenne != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bchFermat"), Boolean::New(isolate, setts.bch_fermat != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bchEuler"), Boolean::New(isolate, setts.bch_euler != 0));
    setr = res->Set(ctx, string_to_js(isolate, "bchGauss"), Boolean::New(isolate, setts.bch_gauss != 0));
    // setr = res->Set(ctx, string_to_js(isolate, "bchDescartes"), Boolean::New(isolate, setts.bch_descartes != 0));

    setr = res->Set(ctx, string_to_js(isolate, "descartesActivationTime"), Number::New(isolate, setts.descartes_activation_time));
    setr = res->Set(ctx, string_to_js(isolate, "lobachevskiActivationTime"), Number::New(isolate, setts.lobachevski_activation_time));

    setr = res->Set(ctx, string_to_js(isolate, "asertHalfLife"), Number::New(isolate, setts.asert_half_life));
    return res;
}

// bool config_blockchain_validate(Isolate* isolate, Local<Object> const& setts) {
//     auto ctx = isolate->GetCurrentContext();
//     bool valid = setts->Has(ctx, string_to_js(isolate, "cores"));
// }

kth_checkpoint config_checkpoint_to_cpp(Isolate* isolate, Local<Object> const& setts) {
    auto ctx = isolate->GetCurrentContext();
    kth_checkpoint res;
    auto hash_js = setts->Get(ctx, string_to_js(isolate, "hash")).ToLocalChecked().As<Uint8Array>();
    res.hash = hash_to_cpp(isolate, hash_js);
    res.height = setts->Get(ctx, string_to_js(isolate, "height")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    return res;
}

// kth_checkpoint* config_checkpoints_to_cpp(Isolate* isolate, Local<Array> const& setts, size_t* out_size) {
kth_checkpoint* config_checkpoints_to_cpp(Isolate* isolate, Local<Array> const& setts, kth_size_t* out_size) {
    auto const ctx = isolate->GetCurrentContext();
    *out_size = setts->Length();
    kth_checkpoint* res = kth_config_checkpoint_allocate_n(*out_size);
    auto const n = setts->Length();
    kth_checkpoint* it = res;
    for (size_t i = 0; i < n; ++i) {
        *it = config_checkpoint_to_cpp(isolate, setts->Get(ctx, i).ToLocalChecked().As<Object>());
        ++it;
    }
    return res;
}

kth_blockchain_settings config_blockchain_settings_to_cpp(Isolate* isolate, Local<Object> const& setts) {
    auto ctx = isolate->GetCurrentContext();
    kth_blockchain_settings res;

    res.cores = setts->Get(ctx, string_to_js(isolate, "cores")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.priority = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "priority")).ToLocalChecked());
    res.byte_fee_satoshis = setts->Get(ctx, string_to_js(isolate, "byteFeeSatoshis")).ToLocalChecked()->NumberValue(ctx).ToChecked();
    res.sigop_fee_satoshis = setts->Get(ctx, string_to_js(isolate, "sigopFeeSatoshis")).ToLocalChecked()->NumberValue(ctx).ToChecked();

    res.minimum_output_satoshis = setts->Get(ctx, string_to_js(isolate, "minimumOutputSatoshis")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.notify_limit_hours = setts->Get(ctx, string_to_js(isolate, "notifyLimitHours")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.reorganization_limit = setts->Get(ctx, string_to_js(isolate, "reorganizationLimit")).ToLocalChecked()->IntegerValue(ctx).ToChecked();

    res.checkpoints = config_checkpoints_to_cpp(isolate,
        setts->Get(ctx, string_to_js(isolate, "checkpoints")).ToLocalChecked().As<Array>(),
        &res.checkpoint_count);

    res.fix_checkpoints = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "fixCheckpoints")).ToLocalChecked());
    res.allow_collisions = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "allowCollisions")).ToLocalChecked());
    res.easy_blocks = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "easyBlocks")).ToLocalChecked());
    res.retarget = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "retarget")).ToLocalChecked());
    res.bip16 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip16")).ToLocalChecked());
    res.bip30 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip30")).ToLocalChecked());
    res.bip34 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip34")).ToLocalChecked());
    res.bip66 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip66")).ToLocalChecked());
    res.bip65 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip65")).ToLocalChecked());
    res.bip90 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip90")).ToLocalChecked());
    res.bip68 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip68")).ToLocalChecked());
    res.bip112 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip112")).ToLocalChecked());
    res.bip113 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bip113")).ToLocalChecked());
    res.bch_uahf = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchUahf")).ToLocalChecked());
    res.bch_daa_cw144 = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchDaaCw144")).ToLocalChecked());
    res.bch_pythagoras = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchPythagoras")).ToLocalChecked());
    res.bch_euclid = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchEuclid")).ToLocalChecked());
    res.bch_pisano = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchPisano")).ToLocalChecked());
    res.bch_mersenne = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchMersenne")).ToLocalChecked());
    res.bch_fermat = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchFermat")).ToLocalChecked());
    res.bch_euler = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchEuler")).ToLocalChecked());
    res.bch_gauss = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchGauss")).ToLocalChecked());
    // res.bch_descartes = bool_to_cpp(isolate, setts->Get(ctx, string_to_js(isolate, "bchDescartes")).ToLocalChecked());

    res.descartes_activation_time = setts->Get(ctx, string_to_js(isolate, "descartesActivationTime")).ToLocalChecked()->IntegerValue(ctx).ToChecked();
    res.lobachevski_activation_time = setts->Get(ctx, string_to_js(isolate, "lobachevskiActivationTime")).ToLocalChecked()->IntegerValue(ctx).ToChecked();

    res.asert_half_life = setts->Get(ctx, string_to_js(isolate, "asertHalfLife")).ToLocalChecked()->IntegerValue(ctx).ToChecked();

    return res;
}
}

void config_blockchain_settings_default(v8::FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_blockchain_settings_default function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument net (#1). Required to be IsNumber.");
        return;
    }

    kth_network_t net = network_to_cpp(isolate, args[0]);

    kth_blockchain_settings res = kth_config_blockchain_settings_default(net);
    args.GetReturnValue().Set(detail::config_blockchain_settings_to_js(isolate, res));
}

}  // namespace kth::js_native
