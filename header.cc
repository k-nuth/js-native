#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <bitprim/nodecint/chain/header.h>

#include "header.h"

namespace bitprim_ns {

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

void bitprim_chain_header_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
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

void bitprim_chain_header_get_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
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

void bitprim_chain_header_set_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
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

inline
hash_t __to_native_hash_1(v8::Local<v8::ArrayBuffer> const& arr) {
    //precondition: arr->Length() == 32
    hash_t hash;
    uint8_t* native_arr = (uint8_t*)arr->GetContents().Data();
    
    for (uint32_t i = 0; i < arr->ByteLength(); ++i) {
        hash.hash[i] = native_arr[i];
        // printf("0x%02x - 0x%02x\n", native_arr[i], hash.hash[i]);
    }
    return hash;
}

inline
hash_t __to_native_hash_2(v8::Local<v8::Uint8Array> const& arr) {
    //precondition: arr->Length() == 32
    hash_t hash;
    uint8_t* native_arr = (uint8_t*)arr->Buffer()->GetContents().Data();
    
    for (uint32_t i = 0; i < arr->Length(); ++i) {
        hash.hash[i] = native_arr[i];
        // printf("0x%02x - 0x%02x\n", native_arr[i], hash.hash[i]);
    }
    return hash;
}


void bitprim_chain_header_get_previous_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
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

    for (size_t i = 0; i < 32; ++i) {
        printf("0x%02x\n", res.hash[i]);
    }
    printf("---------------------------------------------\n");

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);

    // uint8_t* fffff = (uint8_t*)malloc(32 * sizeof(uint8_t));
    // memcpy(fffff, res.hash, 32);

    
    // for (size_t i = 0; i < 32; ++i) {
    //     printf("0x%02x\n", fffff[i]);
    // }
    // printf("---------------------------------------------\n");


    // Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, fffff, 32);
    // Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, res.hash, 32);
    // Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, res.hash, 32, v8::ArrayBufferCreationMode::kInternalized);


    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);


    args.GetReturnValue().Set(hash);
    // args.GetReturnValue().Set(tmp);
    // args.GetReturnValue().Set(ret);
}



// void bitprim_chain_header_get_merkle(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_header_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
// void bitprim_chain_header_get_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_header_get_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
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

// void bitprim_chain_header_set_timestamp(v8::FunctionCallbackInfo<v8::Value> const& args);

// void bitprim_chain_header_get_bits(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_header_get_bits(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
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



// void bitprim_chain_header_set_bits(v8::FunctionCallbackInfo<v8::Value> const& args);

// void bitprim_chain_header_get_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_header_get_nonce(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
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



// void bitprim_chain_header_set_nonce(v8::FunctionCallbackInfo<v8::Value> const& args);




}  // namespace bitprim_ns
