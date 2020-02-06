#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/c-api/chain/output_point.h>

#include "output_point.h"
#include "tools.h"

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


void kth_chain_output_point_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    output_point_t res = output_point_construct();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void kth_chain_output_point_construct_from_hash_index(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }    

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);

    if (arr->Length() != 32) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1, number of bytes")));
        return;
    }    

    hash_t hash = to_native_hash(arr);
    uint32_t index = args[1]->IntegerValue();

    output_point_t res = output_point_construct_from_hash_index(hash, index);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void kth_chain_output_point_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    output_point_t op = (output_point_t)vptr;

    output_point_destruct(op);
}

void kth_chain_output_point_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    output_point_t op = (output_point_t)vptr;

    hash_t res = output_point_get_hash(op);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    args.GetReturnValue().Set(Uint8Array::New(tmp, 0, 32));
}

void kth_chain_output_point_get_index(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    output_point_t op = (output_point_t)vptr;

    uint32_t res = output_point_get_index(op);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

}  // namespace kth_native
