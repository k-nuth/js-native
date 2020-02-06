#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/c-api/chain/merkle_block.h>

#include "merkle_block.h"

namespace kth_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Handle;
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

void kth_chain_merkle_block_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    merkle_block_t merkle_block = (merkle_block_t)vptr;

    chain_merkle_block_destruct(merkle_block);
}

void kth_chain_merkle_block_get_header(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    merkle_block_t merkle_block = (merkle_block_t)vptr;

    header_t header = chain_merkle_block_header(merkle_block);

    Local<External> ret = External::New(isolate, header);
    args.GetReturnValue().Set(ret);
    
}

void kth_chain_merkle_block_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    merkle_block_t merkle_block = (merkle_block_t)vptr;

    uint32_t version = args[1]->IntegerValue();

    uint64_t res = chain_merkle_block_serialized_size(merkle_block, version);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_merkle_block_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    merkle_block_t merkle_block = (merkle_block_t)vptr;

    int res = chain_merkle_block_is_valid(merkle_block);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}







void kth_chain_merkle_block_hash_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    merkle_block_t merkle_block = (merkle_block_t)vptr;

    uint64_t res = chain_merkle_block_hash_count(merkle_block);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_merkle_block_total_transaction_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    merkle_block_t merkle_block = (merkle_block_t)vptr;

    uint64_t res = chain_merkle_block_total_transaction_count(merkle_block);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_merkle_block_reset(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    merkle_block_t merkle_block = (merkle_block_t)vptr;
    
    chain_merkle_block_reset(merkle_block);
}

}  // namespace kth_native
