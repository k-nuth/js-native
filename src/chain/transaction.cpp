// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/transaction.h>
#include <kth/js-native/chain/transaction.hpp>
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

void chain_transaction_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_factory_from_data function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#1). Required to be IsNumber.");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type for argument data (#2). Required to be IsUint8Array.");
        return;
    }

    uint32_t version = args[0]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    v8::Local<v8::Uint8Array> data_arr = v8::Local<v8::Uint8Array>::Cast(args[1]);
    uint8_t* data = (uint8_t*)data_arr->Buffer()->GetContents().Data();
    kth_size_t n = data_arr->Length();

    kth_transaction_t res = kth_chain_transaction_factory_from_data(version, data, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_transaction_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_construct_default function requires 0 arguments.");
        return;
    }


    kth_transaction_t res = kth_chain_transaction_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_transaction_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 4) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_construct function requires 4 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#1). Required to be IsNumber.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument locktime (#2). Required to be IsNumber.");
        return;
    }

    if ( ! args[2]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument inputs (#3). Required to be IsExternal.");
        return;
    }

    if ( ! args[3]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument outputs (#4). Required to be IsExternal.");
        return;
    }

    uint32_t version = args[0]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    uint32_t locktime = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_input_list_t inputs = (kth_input_list_t)v8::External::Cast(*args[2])->Value();
    kth_output_list_t outputs = (kth_output_list_t)v8::External::Cast(*args[3])->Value();

    kth_transaction_t res = kth_chain_transaction_construct(version, locktime, inputs, outputs);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_transaction_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_destruct function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_chain_transaction_destruct(transaction);

}

void chain_transaction_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_valid function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_transaction_is_valid(transaction);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_version function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    uint32_t res = kth_chain_transaction_version(transaction);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_set_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_set_version function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#2). Required to be IsNumber.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_chain_transaction_set_version(transaction, version);

}

void chain_transaction_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_hash function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_hash_t res = kth_chain_transaction_hash(transaction);
    args.GetReturnValue().Set(hash_to_js(isolate, res));
}

void chain_transaction_hash_out(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_hash_out function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    kth_hash_t hash;

    kth_chain_transaction_hash_out(transaction, &hash);

}

void chain_transaction_hash_sighash_type(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_hash_sighash_type function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument sighash_type (#2). Required to be IsNumber.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    uint32_t sighash_type = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_hash_t res = kth_chain_transaction_hash_sighash_type(transaction, sighash_type);
    args.GetReturnValue().Set(hash_to_js(isolate, res));
}

void chain_transaction_hash_sighash_type_out(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_hash_sighash_type_out function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument sighash_type (#2). Required to be IsNumber.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    uint32_t sighash_type = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_hash_t hash;

    kth_chain_transaction_hash_sighash_type_out(transaction, sighash_type, &hash);

}

void chain_transaction_locktime(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_locktime function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    uint32_t res = kth_chain_transaction_locktime(transaction);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_serialized_size function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument wire (#2). Required to be IsBoolean.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t wire = bool_to_cpp(isolate, args[1]);

    kth_size_t res = kth_chain_transaction_serialized_size(transaction, wire);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_fees(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_fees function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    uint64_t res = kth_chain_transaction_fees(transaction);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_signature_operations function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_size_t res = kth_chain_transaction_signature_operations(transaction);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_signature_operations_bip16_active function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument bip16_active (#2). Required to be IsBoolean.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t bip16_active = bool_to_cpp(isolate, args[1]);

    kth_size_t res = kth_chain_transaction_signature_operations_bip16_active(transaction, bip16_active);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_total_input_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_total_input_value function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    uint64_t res = kth_chain_transaction_total_input_value(transaction);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_total_output_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_total_output_value function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    uint64_t res = kth_chain_transaction_total_output_value(transaction);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_is_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_coinbase function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_transaction_is_coinbase(transaction);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_null_non_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_null_non_coinbase function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_transaction_is_null_non_coinbase(transaction);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_oversized_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_oversized_coinbase function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_transaction_is_oversized_coinbase(transaction);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_mature(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_mature function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument target_height (#2). Required to be IsNumber.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    kth_size_t target_height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_bool_t res = kth_chain_transaction_is_mature(transaction, target_height);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_overspent(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_overspent function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_transaction_is_overspent(transaction);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_double_spend function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument include_unconfirmed (#2). Required to be IsBoolean.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t include_unconfirmed = bool_to_cpp(isolate, args[1]);

    kth_bool_t res = kth_chain_transaction_is_double_spend(transaction, include_unconfirmed);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_missing_previous_outputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_missing_previous_outputs function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_transaction_is_missing_previous_outputs(transaction);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_final(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_final function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument block_height (#2). Required to be IsNumber.");
        return;
    }

    if ( ! args[2]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument kth_block_time (#3). Required to be IsNumber.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    kth_size_t block_height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    uint32_t kth_block_time = args[2]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_bool_t res = kth_chain_transaction_is_final(transaction, block_height, kth_block_time);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_locktime_conflict(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_is_locktime_conflict function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_transaction_is_locktime_conflict(transaction);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_outputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_outputs function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_output_list_t res = kth_chain_transaction_outputs(transaction);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_transaction_inputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_inputs function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();

    kth_input_list_t res = kth_chain_transaction_inputs(transaction);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_transaction_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_transaction_to_data function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transaction (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument wire (#2). Required to be IsBoolean.");
        return;
    }

    kth_transaction_t transaction = (kth_transaction_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t wire = bool_to_cpp(isolate, args[1]);
    kth_size_t size;

    uint8_t const* res = kth_chain_transaction_to_data(transaction, wire, &size);
    args.GetReturnValue().Set(byte_array_to_js(isolate, res, size));
}

}  // namespace kth::js_native
