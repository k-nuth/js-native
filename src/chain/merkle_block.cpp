// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/merkle_block.h>
#include <kth/js-native/chain/merkle_block.hpp>
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

void chain_merkle_block_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_merkleblock_t merkle_block = (kth_merkleblock_t)vptr;

    kth_chain_merkle_block_destruct(merkle_block);
}

void chain_merkle_block_get_header(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_merkleblock_t merkle_block = (kth_merkleblock_t)vptr;

    kth_header_t header = kth_chain_merkle_block_header(merkle_block);

    Local<External> ret = External::New(isolate, header);
    args.GetReturnValue().Set(ret);

}

void chain_merkle_block_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_merkleblock_t merkle_block = (kth_merkleblock_t)vptr;

    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    uint64_t res = kth_chain_merkle_block_serialized_size(merkle_block, version);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_merkle_block_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_merkleblock_t merkle_block = (kth_merkleblock_t)vptr;

    int res = kth_chain_merkle_block_is_valid(merkle_block);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}







void chain_merkle_block_hash_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_merkleblock_t merkle_block = (kth_merkleblock_t)vptr;

    uint64_t res = kth_chain_merkle_block_hash_count(merkle_block);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_merkle_block_total_transaction_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_merkleblock_t merkle_block = (kth_merkleblock_t)vptr;

    uint64_t res = kth_chain_merkle_block_total_transaction_count(merkle_block);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_merkle_block_reset(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_merkleblock_t merkle_block = (kth_merkleblock_t)vptr;

    kth_chain_merkle_block_reset(merkle_block);
}

}  // namespace kth::js_native
