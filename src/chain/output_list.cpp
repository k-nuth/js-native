// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/output_list.h>
#include <kth/js-native/chain/output_list.hpp>
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


void chain_output_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_output_list_t output_list = (kth_output_list_t)vptr;

    void* vptr2 = v8::External::Cast(*args[1])->Value();
    kth_output_t output = (kth_output_t)vptr2;

    kth_chain_output_list_push_back(output_list, output);
}

void chain_output_list_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_output_list_t output_list = (kth_output_list_t)vptr;

    uint64_t res = kth_chain_output_list_count(output_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_output_list_nth(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_output_list_t output_list = (kth_output_list_t)vptr;

    uint64_t n = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_output_t res = kth_chain_output_list_nth(output_list, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

}  // namespace kth::js_native
