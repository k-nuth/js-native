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

#if defined(_WIN32)
inline
v8::Local<v8::String> string_to_js(v8::Isolate* isolate, wchar_t const* str) {
    return v8::String::NewFromTwoByte(isolate, reinterpret_cast<uint16_t const*>(str), v8::NewStringType::kNormal).ToLocalChecked();
}
#endif // defined(_WIN32)

inline
v8::Local<v8::String> string_to_js(v8::Isolate* isolate, char const* str) {
    return v8::String::NewFromUtf8(isolate, str, v8::NewStringType::kNormal).ToLocalChecked();
}

#if defined(_WIN32)
inline
wchar_t* string_to_cpp_wide(v8::Isolate* isolate, v8::Local<v8::String> const& js_str, wchar_t** out) {
    v8::String::Value str(isolate, js_str);
    auto n = js_str->Length();
    *out = static_cast<wchar_t*>(malloc(sizeof(wchar_t) * n));
    std::copy_n(*str, n + 1, *out);
    return *out;
}

inline
wchar_t* string_to_cpp(v8::Isolate* isolate, v8::Local<v8::String> const& js_str, wchar_t** out) {
    return string_to_cpp_wide(isolate, js_str, out);
}
#else
inline
char* string_to_cpp(v8::Isolate* isolate, v8::Local<v8::String> const& js_str, char** out) {
    // return v8::String::NewFromUtf8(isolate, str, v8::NewStringType::kNormal).ToLocalChecked();
    // v8::String::Utf8Value str(isolate, setts->Get(ctx, string_to_js(isolate, "directory")).ToLocalChecked());
    // kth_platform_allocate_and_copy_string_at(&res.directory, 0, *str);

    v8::String::Utf8Value str(isolate, js_str);
    auto n = js_str->Length(); //TODO(fernando): Utf8Length() ?
    *out = static_cast<char*>(malloc(sizeof(char) * n));
    std::copy_n(*str, n + 1, *out);
    return *out;
}
#endif // defined(_WIN32)

inline
v8::Local<v8::Uint8Array> byte_array_to_js(v8::Isolate* isolate, uint8_t const* data, kth_size_t size) {
    v8::Local<v8::ArrayBuffer> tmp = v8::ArrayBuffer::New(isolate, size);
    memcpy(tmp->GetContents().Data(), data, size);
    v8::Local<v8::Uint8Array> res = v8::Uint8Array::New(tmp, 0, size);
    return res;
}

inline
v8::Local<v8::Uint8Array> hash_to_js(v8::Isolate* isolate, kth_hash_t const& hash) {
    return byte_array_to_js(isolate, hash.hash, 32);
}

inline
v8::Local<v8::Uint8Array> shorthash_to_js(v8::Isolate* isolate, kth_shorthash_t const& hash) {
    return byte_array_to_js(isolate, hash.hash, 16);
}

inline
kth_bool_t bool_to_cpp(v8::Isolate* isolate, v8::Local<v8::Value> const& x) {
    bool b = x->BooleanValue(isolate);
    // return b ? 1 : 0;
    return b;
}

inline
void byte_array_to_cpp(v8::Isolate* isolate, v8::Local<v8::Uint8Array> const& data, uint8_t* out_data) {
    auto const n = data->Length();
    auto const ctx = isolate->GetCurrentContext();
    for (size_t i = 0; i < n; ++i) {
        *out_data = data->Get(ctx, i).ToLocalChecked()->IntegerValue(ctx).ToChecked();
        ++out_data;
    }
}

inline
kth_hash_t hash_to_cpp(v8::Isolate* isolate, v8::Local<v8::Uint8Array> const& hash_js) {
    kth_hash_t res;
    byte_array_to_cpp(isolate, hash_js, res.hash);
    return res;
}

inline
kth_network_t network_to_cpp(v8::Isolate* isolate, v8::Local<v8::Value> const& x) {
    auto val = x->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_network_t res = kth_network_t(val);
    return res;
}

inline
kth_start_modules_t start_modules_to_cpp(v8::Isolate* isolate, v8::Local<v8::Value> const& x) {
    auto val = x->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    kth_start_modules_t res = kth_start_modules_t(val);
    return res;
}

}  // namespace kth::js_native

#endif // KTH_JS_NATIVE_HELPER_HPP_
