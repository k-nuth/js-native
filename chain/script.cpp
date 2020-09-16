// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/script.h>

#include "script.hpp"
#include "tools.hpp"

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


void chain_script_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    kth_chain_script_destruct(script);
}

void chain_script_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    int res = kth_chain_script_is_valid(script);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_script_is_valid_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    int res = kth_chain_script_is_valid_operations(script);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_script_satoshi_content_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    uint64_t res = kth_chain_script_satoshi_content_size(script);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_script_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_script_t script = (kth_script_t)vptr;

    bool prefix = args[1]->BooleanValue(isolate->GetCurrentContext()).ToChecked();

    uint64_t res = kth_chain_script_serialized_size(script, prefix);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_script_to_string(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    uint32_t active_forks = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    char const* res = kth_chain_script_to_string(script, active_forks);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, res)); // NewFromOneByte 
}

void chain_script_sigops(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }    


    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_script_t script = (kth_script_t)vptr;

    bool embedded = args[1]->BooleanValue(isolate->GetCurrentContext()).ToChecked();

    uint64_t res = kth_chain_script_sigops(script, embedded);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

// void chain_script_embedded_sigops(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     kth_script_t script = (kth_script_t)vptr;

//     void* vptr2 = v8::External::Cast(*args[1])->Value();
//     kth_script_t prevout_script = (kth_script_t)vptr2;

//     uint64_t res = kth_chain_script_embedded_sigops(script, prevout_script);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }

}  // namespace kth_js_native
