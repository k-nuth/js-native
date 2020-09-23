// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/script.h>
#include <kth/js-native/chain/script.hpp>
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


// kth_script_t kth_chain_script_construct(uint8_t* encoded, uint64_t n, kth_bool_t prefix);
void chain_script_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }
   
    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }
    
    if ( ! args[2]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }
    
    v8::Local<v8::Uint8Array> encoded_arr = v8::Local<v8::Uint8Array>::Cast(args[0]);
    uint8_t* encoded = (uint8_t*)encoded_arr->Buffer()->GetContents().Data();
    uint64_t n = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    bool prefix = args[2]->BooleanValue(isolate);

    auto res = kth_chain_script_construct(encoded, n, prefix);
    args.GetReturnValue().Set(External::New(isolate, res));    
}

void chain_script_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    kth_chain_script_destruct(script);
}

void chain_script_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    int res = kth_chain_script_is_valid(script);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_script_is_valid_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    int res = kth_chain_script_is_valid_operations(script);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_script_satoshi_content_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    uint64_t res = kth_chain_script_satoshi_content_size(script);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_script_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_script_t script = (kth_script_t)vptr;

    bool prefix = args[1]->BooleanValue(isolate);

    uint64_t res = kth_chain_script_serialized_size(script, prefix);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_script_to_string(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_script_t script = (kth_script_t)vptr;

    uint32_t active_forks = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    char const* res = kth_chain_script_to_string(script, active_forks);
    args.GetReturnValue().Set(
        String::NewFromUtf8(isolate, res, v8::NewStringType::kNormal).ToLocalChecked()
        ); // NewFromOneByte 
}

void chain_script_sigops(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }    


    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_script_t script = (kth_script_t)vptr;

    bool embedded = args[1]->BooleanValue(isolate);

    uint64_t res = kth_chain_script_sigops(script, embedded);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_script_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_script_t script = (kth_script_t)vptr;

    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_size_t size;
    auto data_c = kth_chain_script_to_data(script, version, &size);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, size);
    memcpy(tmp->GetContents().Data(), data_c, size);
    Local<Uint8Array> data = Uint8Array::New(tmp, 0, size);
    args.GetReturnValue().Set(data);
}

// void chain_script_embedded_sigops(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     kth_script_t script = (kth_script_t)vptr;

//     void* vptr2 = v8::External::Cast(*args[1])->Value();
//     kth_script_t prevout_script = (kth_script_t)vptr2;

//     uint64_t res = kth_chain_script_embedded_sigops(script, prevout_script);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }

}  // namespace kth::js_native
