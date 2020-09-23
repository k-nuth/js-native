// Copyright (c) 2016-2020 Knuth Project developers.
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
using v8::String;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Number;
using v8::Persistent;
using v8::Function;
using v8::Uint8Array;
using v8::ArrayBuffer;

// // kth_header_t kth_chain_header_factory_from_data(uint32_t version, uint8_t* data, uint64_t n);
// void chain_header_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args) {

// }

// // kth_size_t kth_chain_header_satoshi_fixed_size(uint32_t version);
// void chain_header_satoshi_fixed_size(v8::FunctionCallbackInfo<v8::Value> const& args) {

// }

// // void kth_chain_header_reset(kth_header_t header);
// // void chain_header_reset(v8::FunctionCallbackInfo<v8::Value> const& args) {}

// // kth_size_t kth_chain_header_serialized_size(kth_header_t header, uint32_t version);
// void chain_header_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {

// }

// uint8_t const* kth_chain_header_to_data(kth_header_t header, uint32_t version, kth_size_t* out_size);
void chain_header_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;

    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_size_t size;
    auto data_c = kth_chain_header_to_data(header, version, &size);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, size);
    memcpy(tmp->GetContents().Data(), data_c, size);
    Local<Uint8Array> data = Uint8Array::New(tmp, 0, size);
    args.GetReturnValue().Set(data);
}

// // kth_header_t kth_chain_header_construct_default(void);
// void chain_header_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
// }

// void print_hex(uint8_t const* data, size_t n) {
//     while (n != 0) {
//         printf("%02x", *data);
//         ++data;
//         --n;
//     }
//     printf("\n");
// }

// kth_header_t kth_chain_header_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce);
void chain_header_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 6) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }
    
    if ( ! args[2]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }
    
    if ( ! args[3]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 3");
        return;
    }
    
    if ( ! args[4]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 4");
        return;
    }
    
    if ( ! args[5]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 5");
        return;
    }    

    v8::Local<v8::Uint8Array> previous_block_hash_arr = v8::Local<v8::Uint8Array>::Cast(args[1]);
    if (previous_block_hash_arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }    

    v8::Local<v8::Uint8Array> merkle_arr = v8::Local<v8::Uint8Array>::Cast(args[2]);
    if (merkle_arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 2, number of bytes");
        return;
    }    

    uint32_t version = args[0]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_hash_t previous_block_hash = to_native_hash(previous_block_hash_arr);
    kth_hash_t merkle = to_native_hash(merkle_arr);
    uint32_t timestamp = args[3]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    uint32_t bits = args[4]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    uint32_t nonce = args[5]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    auto res = kth_chain_header_construct(version, previous_block_hash.hash, merkle.hash, timestamp, bits, nonce);
    args.GetReturnValue().Set(External::New(isolate, res));
}

// void kth_chain_header_destruct(kth_header_t header);
void chain_header_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;

    kth_chain_header_destruct(header);
}

// // int kth_chain_header_is_valid(kth_header_t header);
// void chain_header_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {

// }

void chain_header_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;


    uint32_t res = kth_chain_header_version(header);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}

void chain_header_set_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;

    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_chain_header_set_version(header, version);
}

void chain_header_previous_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;


    kth_hash_t res = kth_chain_header_previous_block_hash(header);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

void chain_header_merkle(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;


    kth_hash_t res = kth_chain_header_merkle(header);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

void chain_header_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;

    kth_hash_t res = kth_chain_header_hash(header);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

void chain_header_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;

    uint32_t res = kth_chain_header_timestamp(header);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}

void chain_header_bits(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;

    uint32_t res = kth_chain_header_bits(header);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}

void chain_header_nonce(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_header_t header = (kth_header_t)vptr;

    uint32_t res = kth_chain_header_nonce(header);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}


void chain_header_proof_str(v8::FunctionCallbackInfo<v8::Value> const& args) {
}

// uint32_t kth_chain_header_version(kth_header_t header);
// void kth_chain_header_set_version(kth_header_t header, uint32_t version);
// uint32_t kth_chain_header_timestamp(kth_header_t header);
// void kth_chain_header_set_timestamp(kth_header_t header, uint32_t timestamp);
// uint32_t kth_chain_header_bits(kth_header_t header);
// char const* kth_chain_header_proof_str(kth_header_t header);
// void kth_chain_header_set_bits(kth_header_t header, uint32_t bits);
// uint32_t kth_chain_header_nonce(kth_header_t header);
// void kth_chain_header_set_nonce(kth_header_t header, uint32_t nonce);
// kth_hash_t kth_chain_header_previous_block_hash(kth_header_t header);
// kth_hash_t kth_chain_header_merkle(kth_header_t header);
// kth_hash_t kth_chain_header_hash(kth_header_t header);

// void chain_header_set_version(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_set_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_set_bits(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_header_set_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native
