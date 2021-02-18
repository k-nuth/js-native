// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/output.h>
#include <kth/js-native/chain/output.hpp>
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


void chain_output_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_output_t output = (kth_output_t)vptr;

    kth_chain_output_destruct(output);
}

void chain_output_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_output_t output = (kth_output_t)vptr;

    int res = kth_chain_output_is_valid(output);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_output_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_output_t output = (kth_output_t)vptr;

    bool wire = args[1]->BooleanValue(isolate);
    uint64_t res = kth_chain_output_serialized_size(output, wire ? 1 : 0);
    args.GetReturnValue().Set(Number::New(isolate, res));
}


void chain_output_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_output_t output = (kth_output_t)vptr;

    uint64_t res = kth_chain_output_value(output);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_output_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    // if ( ! args[1]->IsBoolean()) {
    //     throw_exception(isolate, "Wrong arguments");
    //     return;
    // }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_output_t output = (kth_output_t)vptr;

    // bool bip16_active = args[1]->BooleanValue(isolate);

    // uint64_t res = kth_chain_output_signature_operations(output, bip16_active ? 1 : 0);
    uint64_t res = kth_chain_output_signature_operations(output);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_output_script(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_output_t output = (kth_output_t)vptr;

    kth_script_t res = kth_chain_output_script(output);
    args.GetReturnValue().Set(External::New(isolate, res));
}


//void chain_output_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
//void chain_output_get_index(v8::FunctionCallbackInfo<v8::Value> const& args);



// void chain_output_is_final(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_output_t output = (kth_output_t)vptr;

//     int res = kth_chain_output_is_final(output);
//     args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
    
// }

// void chain_output_sequence(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_output_t output = (kth_output_t)vptr;

//     uint32_t res = kth_chain_output_sequence(output);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }

// void chain_output_previous_output(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_output_t output = (kth_output_t)vptr;

//     kth_outputpoint_t res = kth_chain_output_previous_output(output);
//     args.GetReturnValue().Set(External::New(isolate, res));
// }


}  // namespace kth::js_native
