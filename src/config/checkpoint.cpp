// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/config/checkpoint.h>

#include <kth/js-native/config/checkpoint.hpp>
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

void config_checkpoint_allocate_n(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments. config_checkpoint_allocate_n function requires 1 arguments.");
        return;
    }

    if ( ! args[0]->IsNumber()) {
        throw_exception(isolate, "Wrong argument type for argument n (#1). Required to be IsNumber.");
        return;
    }

    kth_size_t n = args[0]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    kth_checkpoint* res = kth_config_checkpoint_allocate_n(n);
    args.GetReturnValue().Set(External::New(isolate, res));
}

}  // namespace kth::js_native
