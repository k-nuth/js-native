// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/input.h>
#include <kth/js-native/chain/input.hpp>
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


// kth_input_t kth_chain_input_construct(kth_outputpoint_t previous_output, kth_script_t script, uint32_t sequence);

void chain_input_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 3");
        return;
    }

    kth_outputpoint_t previous_output = (kth_outputpoint_t)v8::External::Cast(*args[0])->Value();
    kth_script_t script = (kth_script_t)v8::External::Cast(*args[1])->Value();
    uint32_t sequence = args[2]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    auto res = kth_chain_input_construct(previous_output, script, sequence);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_input_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_input_t input = (kth_input_t)vptr;

    kth_chain_input_destruct(input);
}

void chain_input_to_data(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_input_t input = (kth_input_t)vptr;

    uint32_t version = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_size_t size;
    auto data_c = kth_chain_input_to_data(input, version, &size);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, size);
    memcpy(tmp->GetContents().Data(), data_c, size);
    Local<Uint8Array> data = Uint8Array::New(tmp, 0, size);
    args.GetReturnValue().Set(data);
}


void chain_input_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_input_t input = (kth_input_t)vptr;

    int res = kth_chain_input_is_valid(input);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_input_is_final(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_input_t input = (kth_input_t)vptr;

    int res = kth_chain_input_is_final(input);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
    
}

void chain_input_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_input_t input = (kth_input_t)vptr;

    bool wire = args[1]->BooleanValue(isolate);
    uint64_t res = kth_chain_input_serialized_size(input, wire ? 1 : 0);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_input_sequence(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_input_t input = (kth_input_t)vptr;

    uint32_t res = kth_chain_input_sequence(input);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_input_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_input_t input = (kth_input_t)vptr;

    bool bip16_active = args[1]->BooleanValue(isolate);

    uint64_t res = kth_chain_input_signature_operations(input, bip16_active ? 1 : 0);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_input_script(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_input_t input = (kth_input_t)vptr;

    kth_script_t res = kth_chain_input_script(input);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_input_previous_output(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    kth_input_t input = (kth_input_t)vptr;

    kth_outputpoint_t res = kth_chain_input_previous_output(input);
    args.GetReturnValue().Set(External::New(isolate, res));
}



//void chain_input_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
//void chain_input_get_index(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native
