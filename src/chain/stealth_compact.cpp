// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/stealth_compact.h>
#include <kth/js-native/chain/stealth_compact.hpp>
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


void chain_stealth_compact_get_ephemeral_public_key_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_stealth_compact_t stealth_compact = (kth_stealth_compact_t)vptr;

    kth_hash_t res = kth_chain_stealth_compact_get_ephemeral_public_key_hash(stealth_compact);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);

#if (V8_MAJOR_VERSION >= 8)
    memcpy(tmp->GetBackingStore()->Data(), res.hash, 32);
#else
    memcpy(tmp->GetContents().Data(), res.hash, 32);
#endif

    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

void chain_stealth_compact_get_transaction_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_stealth_compact_t stealth_compact = (kth_stealth_compact_t)vptr;

    kth_hash_t res = kth_chain_stealth_compact_get_transaction_hash(stealth_compact);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);

#if (V8_MAJOR_VERSION >= 8)
    memcpy(tmp->GetBackingStore()->Data(), res.hash, 32);
#else
    memcpy(tmp->GetContents().Data(), res.hash, 32);
#endif

    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
    args.GetReturnValue().Set(hash);
}

void chain_stealth_compact_get_public_key_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_stealth_compact_t stealth_compact = (kth_stealth_compact_t)vptr;

    kth_shorthash_t res = kth_chain_stealth_compact_get_public_key_hash(stealth_compact);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 20); //TODO: warning, hardcoded hash size!

#if (V8_MAJOR_VERSION >= 8)
    memcpy(tmp->GetBackingStore()->Data(), res.hash, 20);   //TODO: warning, hardcoded hash size!
#else
    memcpy(tmp->GetContents().Data(), res.hash, 20);        //TODO: warning, hardcoded hash size!
#endif

    Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 20);   //TODO: warning, hardcoded hash size!
    args.GetReturnValue().Set(hash);
}

}  // namespace kth::js_native
