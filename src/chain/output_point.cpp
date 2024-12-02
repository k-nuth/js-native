// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/output_point.h>
#include <kth/js-native/chain/output_point.hpp>
#include <kth/js-native/chain/tools.hpp>
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


void chain_output_point_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    kth_outputpoint_t res = kth_chain_output_point_construct();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_output_point_construct_from_hash_index(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);

    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }

    kth_hash_t hash = to_native_hash(arr);
    uint32_t index = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_outputpoint_t res = kth_chain_output_point_construct_from_hash_index(hash, index);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_output_point_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_outputpoint_t op = (kth_outputpoint_t)vptr;

    kth_chain_output_point_destruct(op);
}

void chain_output_point_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_outputpoint_t op = (kth_outputpoint_t)vptr;

    kth_hash_t res = kth_chain_output_point_get_hash(op);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);

#if (V8_MAJOR_VERSION >= 8)
    memcpy(tmp->GetBackingStore()->Data(), res.hash, 32);
#else
    memcpy(tmp->GetContents().Data(), res.hash, 32);
#endif

    args.GetReturnValue().Set(Uint8Array::New(tmp, 0, 32));
}

void chain_output_point_get_index(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_outputpoint_t op = (kth_outputpoint_t)vptr;

    uint32_t res = kth_chain_output_point_get_index(op);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

}  // namespace kth::js_native
