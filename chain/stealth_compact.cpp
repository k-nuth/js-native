#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/c-api/chain/stealth_compact.h>

#include "stealth_compact.hpp"

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


void kth_chain_stealth_compact_get_ephemeral_public_key_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    stealth_compact_t stealth_compact = (stealth_compact_t)vptr;

    hash_t res = stealth_compact_get_ephemeral_public_key_hash(stealth_compact);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

void kth_chain_stealth_compact_get_transaction_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    stealth_compact_t stealth_compact = (stealth_compact_t)vptr;

    hash_t res = stealth_compact_get_transaction_hash(stealth_compact);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

void kth_chain_stealth_compact_get_public_key_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    stealth_compact_t stealth_compact = (stealth_compact_t)vptr;

    short_hash_t res = stealth_compact_get_public_key_hash(stealth_compact);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 20); //TODO: warning, hardcoded hash size!
    memcpy(tmp->GetContents().Data(), res.hash, 20);        //TODO: warning, hardcoded hash size!
    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 20);   //TODO: warning, hardcoded hash size!
    args.GetReturnValue().Set(hash);
}

}  // namespace kth_native
