// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_NATIVE_HELPER_HPP_
#define KTH_JS_NATIVE_HELPER_HPP_

#include <string>

#include <node.h>

namespace kth::js_native {

// #if NODE_MAJOR_VERSION >= 14
// #else
// #endif

inline
void throw_exception(v8::Isolate* isolate, std::string const& message) {
    isolate->ThrowException(
        v8::Exception::TypeError(
            v8::String::NewFromUtf8(isolate, message.c_str(), v8::NewStringType::kNormal).ToLocalChecked()));
}

template <typename T, size_t argc> 
void call_function_and_free(v8::Isolate* isolate, void* ctx, T (&argv)[argc]) {
    auto* callback = static_cast<v8::Persistent<v8::Function>*>(ctx);
    auto cb = v8::Local<v8::Function>::New(isolate, *callback);
    cb->Call(isolate->GetCurrentContext(), v8::Null(isolate), argc, argv).ToLocalChecked();
    callback->Reset();
    //callback->Dispose();
    delete callback;
}

inline
v8::Persistent<v8::Function>* make_callback(v8::Isolate* isolate, v8::Local<v8::Value> const& arg) {
    auto* callback = new v8::Persistent<v8::Function>;
    callback->Reset(isolate, arg.As<v8::Function>());
    return callback;
}

}  // namespace kth::js_native

#endif // KTH_JS_NATIVE_HELPER_HPP_
