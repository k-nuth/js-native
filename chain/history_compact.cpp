// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/history_compact.h>

#include "history_compact.hpp"

namespace kth_js_native {

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

void chain_history_compact_get_point_kind(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

    uint64_t res = kth_chain_history_compact_get_point_kind(history_compact_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_history_compact_get_point(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

    kth_point_t res = kth_chain_history_compact_get_point(history_compact_list);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_history_compact_get_height(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

    uint64_t res = kth_chain_history_compact_get_height(history_compact_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_history_compact_get_value_or_previous_checksum(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

    uint64_t res = kth_chain_history_compact_get_value_or_previous_checksum(history_compact_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

}  // namespace kth_js_native