// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/header.h>
#include <kth/js-native/chain/header.hpp>
#include <kth/js-native/chain/tools.hpp>
#include <kth/js-native/helper.hpp>

namespace kth::js_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Global;

using v8::Object;
using v8::Boolean;
using v8::String;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Number;
using v8::Persistent;
using v8::Function;
using v8::Uint8Array;
using v8::ArrayBuffer;

void chain_header_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_factory_from_data function requires 3 arguments.");
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

    kth_header_t res = kth_chain_header_factory_from_data(version, data, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_header_satoshi_fixed_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_satoshi_fixed_size function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#1). Required to be IsNumber.");
        return;
    }

    uint32_t version = args[0]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_size_t res = kth_chain_header_satoshi_fixed_size(version);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_header_reset(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_reset function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    kth_chain_header_reset(header);

}

void chain_header_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_serialized_size function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#2). Required to be IsNumber.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();
    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_size_t res = kth_chain_header_serialized_size(header, version);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_header_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_to_data function requires 3 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#2). Required to be IsNumber.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();
    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_size_t size;

    uint8_t const* res = kth_chain_header_to_data(header, version, &size);
    args.GetReturnValue().Set(byte_array_to_js(isolate, res, size));
}

void chain_header_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_construct_default function requires 0 arguments.");
        return;
    }


    kth_header_t res = kth_chain_header_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_header_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 6) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_construct function requires 6 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#1). Required to be IsNumber.");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type for argument previous_block_hash (#2). Required to be IsUint8Array.");
        return;
    }

    v8::Local<v8::Uint8Array> previous_block_hash_arr = v8::Local<v8::Uint8Array>::Cast(args[1]);
    if (previous_block_hash_arr->Length() != 32) {
        throw_exception(isolate, "Wrong argument type for argument previous_block_hash (#2). Required to be 32-byte array.");
        return;
    }

    if ( ! args[2]->IsUint8Array()) {
        throw_exception(isolate, "Wrong argument type for argument merkle (#3). Required to be IsUint8Array.");
        return;
    }

    v8::Local<v8::Uint8Array> merkle_arr = v8::Local<v8::Uint8Array>::Cast(args[2]);
    if (merkle_arr->Length() != 32) {
        throw_exception(isolate, "Wrong argument type for argument merkle (#3). Required to be 32-byte array.");
        return;
    }

    if ( ! args[3]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument timestamp (#4). Required to be IsNumber.");
        return;
    }

    if ( ! args[4]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument bits (#5). Required to be IsNumber.");
        return;
    }

    if ( ! args[5]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument nonce (#6). Required to be IsNumber.");
        return;
    }

    uint32_t version = args[0]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_hash_t previous_block_hash = to_native_hash(previous_block_hash_arr);
    kth_hash_t merkle = to_native_hash(merkle_arr);
    uint32_t timestamp = args[3]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    uint32_t bits = args[4]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    uint32_t nonce = args[5]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_header_t res = kth_chain_header_construct(version, previous_block_hash.hash, merkle.hash, timestamp, bits, nonce);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_header_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_destruct function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    kth_chain_header_destruct(header);

}

void chain_header_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_is_valid function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    kth_bool_t res = kth_chain_header_is_valid(header);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_header_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_version function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    uint32_t res = kth_chain_header_version(header);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_header_set_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_set_version function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument version (#2). Required to be IsNumber.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();
    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_chain_header_set_version(header, version);

}

void chain_header_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_timestamp function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    uint32_t res = kth_chain_header_timestamp(header);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_header_set_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_set_timestamp function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument timestamp (#2). Required to be IsNumber.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();
    uint32_t timestamp = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_chain_header_set_timestamp(header, timestamp);

}

void chain_header_bits(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_bits function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    uint32_t res = kth_chain_header_bits(header);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_header_proof_str(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_proof_str function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    char const* res = kth_chain_header_proof_str(header);
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void chain_header_set_bits(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_set_bits function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument bits (#2). Required to be IsNumber.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();
    uint32_t bits = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_chain_header_set_bits(header, bits);

}

void chain_header_nonce(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_nonce function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    uint32_t res = kth_chain_header_nonce(header);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_header_set_nonce(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_set_nonce function requires 2 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument nonce (#2). Required to be IsNumber.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();
    uint32_t nonce = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_chain_header_set_nonce(header, nonce);

}

void chain_header_previous_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_previous_block_hash function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    kth_hash_t res = kth_chain_header_previous_block_hash(header);
    args.GetReturnValue().Set(hash_to_js(isolate, res));
}

void chain_header_merkle(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_merkle function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    kth_hash_t res = kth_chain_header_merkle(header);
    args.GetReturnValue().Set(hash_to_js(isolate, res));
}

void chain_header_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. chain_header_hash function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong argument type for argument header (#1). Required to be IsExternal.");
        return;
    }

    kth_header_t header = (kth_header_t)v8::External::Cast(*args[0])->Value();

    kth_hash_t res = kth_chain_header_hash(header);
    args.GetReturnValue().Set(hash_to_js(isolate, res));
}

}  // namespace kth::js_native
