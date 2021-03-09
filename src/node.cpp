// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// #include <node.h>
#include <nan.h>

#include <kth/capi/node.h>
#include <kth/capi/chain/chain.h>
#include <kth/js-native/helper.hpp>
#include <kth/js-native/config/settings.hpp>

// #include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)
#include <thread>
#include <iostream>

namespace kth::js_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Number;
using v8::Persistent;
using v8::Function;

static uv_async_t node_init_run_and_wait_for_signal_ah_;

void node_construct(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments, 2 arguments expected");
        return;
    }

    if ( ! args[0]->IsObject()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    kth_settings settings = detail::config_settings_to_cpp(isolate, args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked());

    bool stdout_enabled = args[1]->BooleanValue(isolate);

    kth_node_t node = kth_node_construct(&settings, stdout_enabled);
    Local<External> ext = External::New(isolate, node);
    args.GetReturnValue().Set(ext);
}

// void node_construct(FunctionCallbackInfo<Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 2) {
//         throw_exception(isolate, "Wrong number of arguments, 2 arguments expected");
//         return;
//     }

//     if ( ! args[0]->IsString()) {
//         throw_exception(isolate, "Wrong arguments, 1");
//         return;
//     }

//     if ( ! args[1]->IsBoolean()) {
//         throw_exception(isolate, "Wrong arguments, 2");
//         return;
//     }

//     v8::String::Utf8Value path(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());

//     char* error_message;
//     kth_settings* settings;
//     kth_bool_t ok = kth_config_settings_get_from_file(*path, &settings, &error_message);

//     if ( ! ok) {
//         throw_exception(isolate, error_message);
//         return;
//     }

//     bool stdout_enabled = args[1]->BooleanValue(isolate);

//     kth_node_t node = kth_node_construct(settings, stdout_enabled);
//     Local<External> ext = External::New(isolate, node);
//     args.GetReturnValue().Set(ext);
// }

void node_destruct(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if (!args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_node_t node = (kth_node_t)vptr;
    kth_node_destruct(node);
}

static 
void node_init_run_and_wait_for_signal_handler(uv_async_t* handle) {
    auto* context = static_cast<context_t*>(handle->data);
    auto* isolate = Isolate::GetCurrent();
    auto* callback = context->callback;

    v8::HandleScope handle_scope(isolate); // Added this line.
    int err = copy_data_and_free<int>(*context);
    Local<Value> argv[1] = { Number::New(isolate, err) };
    call_function_and_free(isolate, callback, argv);

    delete context;
    uv_unref((uv_handle_t*)handle);
}

void node_init_run_and_wait_for_signal(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    // std::cout << std::this_thread::get_id() << '\n';
    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_node_t node = (kth_node_t)vptr;

    auto callback = make_callback(isolate, args[1]);

    auto* context = new context_t;
    uv_async_init(uv_default_loop(), &node_init_run_and_wait_for_signal_ah_, node_init_run_and_wait_for_signal_handler);
    context->async = &node_init_run_and_wait_for_signal_ah_;
    context->callback = callback;


    kth_start_modules_t mods = kth_start_modules_all;   //TODO(fernando): this is another parameter.
    std::thread t([node, context, mods]() {
        kth_node_init_run_and_wait_for_signal(node, context, mods, [](kth_node_t node, void* ctx, kth_error_code_t err) {
            auto* context = static_cast<context_t*>(ctx);
            context->data = new int(err);
            context->async->data = context;
            uv_async_send(context->async);
        });
    });
    t.detach();
}

void node_signal_stop(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_node_t node = (kth_node_t)vptr;
    kth_node_signal_stop(node);
}





// void node_initchain(FunctionCallbackInfo<Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if (!args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_node_t node = (kth_node_t)vptr;
//     int res = kth_node_initchain(node);

//     Local<Number> num = Number::New(isolate, res);
//     args.GetReturnValue().Set(num);
// }

// void node_run_wait(FunctionCallbackInfo<Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if (!args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_node_t node = (kth_node_t)vptr;
//     int res = kth_node_run_wait(node);

//     Local<Number> num = Number::New(isolate, res);
//     args.GetReturnValue().Set(num);
// }

// void node_stop(FunctionCallbackInfo<Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if (!args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_node_t node = (kth_node_t)vptr;
//     kth_node_stop(node);
// }



void node_get_chain(FunctionCallbackInfo<Value> const& args) {
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
    kth_node_t node = (kth_node_t)vptr;
    kth_chain_t chain = kth_node_get_chain(node);

    Local<External> ext = External::New(isolate, chain);
    args.GetReturnValue().Set(ext);
}

}  // namespace kth::js_native
