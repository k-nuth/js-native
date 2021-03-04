// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_NATIVE_HELPER_HPP_
#define KTH_JS_NATIVE_HELPER_HPP_

#include <string>

#include <node.h>
#include <nan.h>

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

struct context_t {
    v8::Persistent<v8::Function>* callback;
    uv_async_t* async;
    void* data;
};

inline
v8::Persistent<v8::Function>* make_callback(v8::Isolate* isolate, v8::Local<v8::Value> const& arg) {
    auto* callback = new v8::Persistent<v8::Function>;
    callback->Reset(isolate, arg.As<v8::Function>());
    return callback;
}

template <typename T> 
inline 
T copy_data_and_free(context_t& context) {
    auto* context_data = static_cast<T*>(context.data);
    T data = *context_data;
    delete context_data;
    return data;
}

inline
v8::Local<v8::String> to_string(v8::Isolate* isolate, char const* str) {
    return v8::String::NewFromUtf8(isolate, str, v8::NewStringType::kNormal).ToLocalChecked();
}

inline
v8::Local<v8::Uint8Array> to_byte_array(v8::Isolate* isolate, uint8_t const* data, kth_size_t size) {
    v8::Local<v8::ArrayBuffer> tmp = v8::ArrayBuffer::New(isolate, size);
    memcpy(tmp->GetContents().Data(), data, size);
    v8::Local<v8::Uint8Array> res = v8::Uint8Array::New(tmp, 0, size);
    return res;
}

inline
v8::Local<v8::Uint8Array> to_hash(v8::Isolate* isolate, kth_hash_t const& hash) {
    return to_byte_array(isolate, hash.hash, 32);
}

inline
v8::Local<v8::Uint8Array> to_shorthash(v8::Isolate* isolate, kth_shorthash_t const& hash) {
    return to_byte_array(isolate, hash.hash, 16);
}

inline
kth_bool_t to_bool(v8::Isolate* isolate, v8::Local<v8::Value> const& x) {
    bool b = x->BooleanValue(isolate);
    // return b ? 1 : 0;
    return b;
}

inline
kth_network_t to_kth_network_t(v8::Isolate* isolate, v8::Local<v8::Value> const& x) {
    auto val = x->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_network_t res = kth_network_t(val);
    return res;
}

}  // namespace kth::js_native

#endif // KTH_JS_NATIVE_HELPER_HPP_
