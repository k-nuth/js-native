#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/c-api/chain/header.h>

#include "header.hpp"

namespace kth_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Handle;
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

void kth_chain_header_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    header_t header = (header_t)vptr;

    chain_header_destruct(header);
}

void kth_chain_header_get_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    header_t header = (header_t)vptr;


    uint32_t res = chain_header_version(header);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}

void kth_chain_header_set_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    header_t header = (header_t)vptr;

    uint32_t version = args[1]->IntegerValue();

    chain_header_set_version(header, version);
}

void kth_chain_header_get_previous_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    header_t header = (header_t)vptr;


    hash_t res = chain_header_previous_block_hash(header);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}



// void kth_chain_header_get_merkle(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_merkle(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    header_t header = (header_t)vptr;


    hash_t res = chain_header_merkle(header);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

void kth_chain_header_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    header_t header = (header_t)vptr;


    hash_t res = chain_header_hash(header);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

// void kth_chain_header_get_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    header_t header = (header_t)vptr;

    uint32_t res = chain_header_timestamp(header);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}

// void kth_chain_header_set_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);

// void kth_chain_header_get_bits(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_bits(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    header_t header = (header_t)vptr;

    uint32_t res = chain_header_bits(header);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}



// void kth_chain_header_set_bits(v8::FunctionCallbackInfo<v8::Value> const& args);

// void kth_chain_header_get_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_header_get_nonce(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    header_t header = (header_t)vptr;

    uint32_t res = chain_header_nonce(header);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}



// void kth_chain_header_set_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);




}  // namespace kth_native
