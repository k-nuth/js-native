// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/stealth_compact_list.h>
#include <kth/js-native/chain/stealth_compact_list.hpp>
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

void chain_stealth_compact_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_stealth_compact_list_t stealth_compact_list = (kth_stealth_compact_list_t)vptr;

    kth_chain_stealth_compact_list_destruct(stealth_compact_list);
}

void chain_stealth_compact_list_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_stealth_compact_list_t stealth_compact_list = (kth_stealth_compact_list_t)vptr;

    uint64_t res = kth_chain_stealth_compact_list_count(stealth_compact_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_stealth_compact_list_nth(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_stealth_compact_list_t stealth_compact_list = (kth_stealth_compact_list_t)vptr;

    uint64_t n = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_stealth_compact_t res = kth_chain_stealth_compact_list_nth(stealth_compact_list, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

// void chain_stealth_compact_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 2) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments");
//         return;
//     }

//     if ( ! args[1]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_stealth_compact_list_t stealth_compact_list = (kth_stealth_compact_list_t)vptr;

//     void* vptr2 = v8::External::Cast(*args[1])->Value();
//     kth_stealth_compact_t stealth_compact = (kth_stealth_compact_t)vptr2;

//     kth_chain_stealth_compact_list_push_back(stealth_compact_list, stealth_compact);
// }


}  // namespace kth::js_native
