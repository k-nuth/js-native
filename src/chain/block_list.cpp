// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/block_list.h>

#include <kth/js-native/chain/block_list.hpp>
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


void chain_block_list_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    kth_block_list_t res = kth_chain_block_list_construct_default();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_block_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_block_list_t block_list = (kth_block_list_t)vptr;

    kth_chain_block_list_destruct(block_list);
}

void chain_block_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }
    
    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_block_list_t block_list = (kth_block_list_t)vptr;

    void* vptr2 = v8::External::Cast(*args[1])->Value();
    kth_block_t block = (kth_block_t)vptr2;

    kth_chain_block_list_push_back(block_list, block);
}

void chain_block_list_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_block_list_t block_list = (kth_block_list_t)vptr;

    uint64_t res = kth_chain_block_list_count(block_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_block_list_nth(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_block_list_t block_list = (kth_block_list_t)vptr;

    uint64_t n = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_block_t res = kth_chain_block_list_nth(block_list, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

}  // namespace kth::js_native
