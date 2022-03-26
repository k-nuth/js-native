// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/block.h>

#include <kth/js-native/chain/block.hpp>
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

void chain_block_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_construct_default function requires 0 arguments.");
        return;
    }


    kth_block_t res = kth_chain_block_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_block_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_construct function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument transactions (#2). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();
    kth_transaction_list_t transactions = (kth_transaction_list_t)v8::External::Cast(*args[1])->Value();

    kth_block_t res = kth_chain_block_construct(header, transactions);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_block_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_factory_from_data function requires 3 arguments.");
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

    kth_block_t res = kth_chain_block_factory_from_data(version, data, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_block_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_destruct function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_chain_block_destruct(block);

}

void chain_block_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_is_valid function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_block_is_valid(block);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_block_header(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_header function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_header_t res = kth_chain_block_header(block);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_hash function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_hash_t res = kth_chain_block_hash(block);
    args.GetReturnValue().Set(hash_to_js(isolate, res));
}

void chain_block_hash_out(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_hash_out function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    kth_hash_t hash;

    kth_chain_block_hash_out(block, &hash);

}

void chain_block_proof_str(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_proof_str function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    char const* res = kth_chain_block_proof_str(block);
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void chain_block_transactions(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_transactions function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_transaction_list_t res = kth_chain_block_transactions(block);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_block_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_serialized_size function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#2). Required to be IsNumber.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_size_t res = kth_chain_block_serialized_size(block, version);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_block_subsidy(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_subsidy function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument height (#1). Required to be IsNumber.");
        return;
    }

    kth_size_t height = args[0]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    uint64_t res = kth_chain_block_subsidy(height);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_block_fees(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_fees function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    uint64_t res = kth_chain_block_fees(block);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_block_claim(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_claim function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    uint64_t res = kth_chain_block_claim(block);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_block_reward(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_reward function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument height (#2). Required to be IsNumber.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    kth_size_t height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    uint64_t res = kth_chain_block_reward(block, height);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_block_generate_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_generate_merkle_root function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_hash_t res = kth_chain_block_generate_merkle_root(block);
    args.GetReturnValue().Set(hash_to_js(isolate, res));
}

void chain_block_generate_merkle_root_out(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_generate_merkle_root_out function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    kth_hash_t merkle;

    kth_chain_block_generate_merkle_root_out(block, &merkle);

}

void chain_block_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_signature_operations function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_size_t res = kth_chain_block_signature_operations(block);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_block_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_signature_operations_bip16_active function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument bip16_active (#2). Required to be IsBoolean.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t bip16_active = bool_to_cpp(isolate, args[1]);

    kth_size_t res = kth_chain_block_signature_operations_bip16_active(block, bip16_active);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_block_total_inputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_total_inputs function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument with_coinbase (#2). Required to be IsBoolean.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t with_coinbase = bool_to_cpp(isolate, args[1]);

    kth_size_t res = kth_chain_block_total_inputs(block, with_coinbase);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_block_is_extra_coinbases(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_is_extra_coinbases function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_block_is_extra_coinbases(block);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_block_is_final(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_is_final function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument height (#2). Required to be IsNumber.");
        return;
    }

    if ( ! args[2]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument kth_block_time (#3). Required to be IsNumber.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    kth_size_t height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    uint32_t kth_block_time = args[2]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_bool_t res = kth_chain_block_is_final(block, height, kth_block_time);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_block_is_distinct_transaction_set(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_is_distinct_transaction_set function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_block_is_distinct_transaction_set(block);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_block_is_valid_coinbase_claim(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_is_valid_coinbase_claim function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument height (#2). Required to be IsNumber.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    kth_size_t height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_bool_t res = kth_chain_block_is_valid_coinbase_claim(block, height);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_block_is_valid_coinbase_script(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_is_valid_coinbase_script function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument height (#2). Required to be IsNumber.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    kth_size_t height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_bool_t res = kth_chain_block_is_valid_coinbase_script(block, height);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_block_is_internal_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_is_internal_double_spend function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_block_is_internal_double_spend(block);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_block_is_valid_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_is_valid_merkle_root function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_block_is_valid_merkle_root(block);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_block_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_block_to_data function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument block (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong argument type for argument wire (#2). Required to be IsBoolean.");
        return;
    }

    kth_block_t block = (kth_block_t)v8::External::Cast(*args[0])->Value();
    kth_bool_t wire = bool_to_cpp(isolate, args[1]);
    kth_size_t size;

    uint8_t const* res = kth_chain_block_to_data(block, wire, &size);
    args.GetReturnValue().Set(byte_array_to_js(isolate, res, size));
}

}  // namespace kth::js_native
