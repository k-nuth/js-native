#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <bitprim/nodecint/chain/history_compact.h>

#include "history_compact.h"

namespace bitprim_ns {

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

void bitprim_chain_history_compact_get_point_kind(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    history_compact_list_t history_compact_list = (history_compact_list_t)vptr;

    uint64_t res = chain_history_compact_get_point_kind(history_compact_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void bitprim_chain_history_compact_get_point(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    history_compact_list_t history_compact_list = (history_compact_list_t)vptr;

    point_t res = chain_history_compact_get_point(history_compact_list);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void bitprim_chain_history_compact_get_height(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    history_compact_list_t history_compact_list = (history_compact_list_t)vptr;

    uint64_t res = chain_history_compact_get_height(history_compact_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void bitprim_chain_history_compact_get_value_or_previous_checksum(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    history_compact_list_t history_compact_list = (history_compact_list_t)vptr;

    uint64_t res = chain_history_compact_get_value_or_previous_checksum(history_compact_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

}  // namespace bitprim_ns
