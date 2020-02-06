#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/c-api/chain/stealth_compact_list.h>

#include "stealth_compact_list.hpp"

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

void kth_chain_stealth_compact_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    stealth_compact_list_t stealth_compact_list = (stealth_compact_list_t)vptr;

    stealth_compact_list_destruct(stealth_compact_list);
}

void kth_chain_stealth_compact_list_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    stealth_compact_list_t stealth_compact_list = (stealth_compact_list_t)vptr;

    uint64_t res = stealth_compact_list_count(stealth_compact_list);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_stealth_compact_list_nth(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    
    void* vptr = v8::External::Cast(*args[0])->Value();
    stealth_compact_list_t stealth_compact_list = (stealth_compact_list_t)vptr;

    uint64_t n = args[1]->IntegerValue();

    stealth_compact_t res = stealth_compact_list_nth(stealth_compact_list, n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

// void kth_chain_stealth_compact_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 2) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[1]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }
    
//     void* vptr = v8::External::Cast(*args[0])->Value();
//     stealth_compact_list_t stealth_compact_list = (stealth_compact_list_t)vptr;

//     void* vptr2 = v8::External::Cast(*args[1])->Value();
//     stealth_compact_t stealth_compact = (stealth_compact_t)vptr2;

//     chain_stealth_compact_list_push_back(stealth_compact_list, stealth_compact);
// }


}  // namespace kth_native
