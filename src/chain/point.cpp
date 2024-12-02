// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/point.h>
#include <kth/js-native/chain/point.hpp>
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


void chain_point_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_point_t point = (kth_point_t)vptr;


    kth_hash_t res = kth_chain_point_get_hash(point);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);

#if (V8_MAJOR_VERSION >= 8)
    memcpy(tmp->GetBackingStore()->Data(), res.hash, 32);
#else
    memcpy(tmp->GetContents().Data(), res.hash, 32);
#endif

    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

void chain_point_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_point_t point = (kth_point_t)vptr;

    int res = kth_chain_point_is_valid(point);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_point_get_index(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_point_t p = (kth_point_t)vptr;

    uint32_t res = kth_chain_point_get_index(p);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_point_get_checksum(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_point_t p = (kth_point_t)vptr;

    uint64_t res = kth_chain_point_get_checksum(p);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

}  // namespace kth::js_native
