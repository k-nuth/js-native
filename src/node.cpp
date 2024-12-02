// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// #include <node.h>
#include <nan.h>

#include <kth/capi/node.h>
#include <kth/capi/chain/chain.h>
#include <kth/js-native/helper.hpp>
#include <kth/js-native/config/settings.hpp>

#include <atomic>
#include <thread>

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

std::atomic<bool> running_ = false;
std::atomic<bool> stopped_ = false;

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

void node_destruct(FunctionCallbackInfo<Value> const& args) {
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

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments.");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_node_t node = (kth_node_t)vptr;

    auto callback = make_callback(isolate, args[2]);

    auto* context = new context_t;
    uv_async_init(uv_default_loop(), &node_init_run_and_wait_for_signal_ah_, node_init_run_and_wait_for_signal_handler);
    context->async = &node_init_run_and_wait_for_signal_ah_;
    context->callback = callback;

    kth_start_modules_t mods = start_modules_to_cpp(isolate, args[1]);

    std::thread t([node, context, mods]() {
        kth_node_init_run_and_wait_for_signal(node, context, mods, [](kth_node_t node, void* ctx, kth_error_code_t err) {
            auto* context = static_cast<context_t*>(ctx);
            context->data = new int(err);
            context->async->data = context;
            uv_async_send(context->async);
            running_ = true;
            stopped_ = false;
        });
        stopped_ = true;
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

    while (running_ &&  ! stopped_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void node_running(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    args.GetReturnValue().Set(running_);
}

void node_print_thread_id(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    kth_node_print_thread_id();
}

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

void node_capi_version(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    char const* res = kth_node_capi_version();
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void node_cppapi_version(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    char const* res = kth_node_cppapi_version();
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void node_microarchitecture(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    char const* res = kth_node_microarchitecture();
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void node_march_names(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    char const* res = kth_node_march_names();
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void node_currency_symbol(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    char const* res = kth_node_currency_symbol();
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void node_currency(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    char const* res = kth_node_currency();
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

void node_db_type(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    kth_db_mode_t mode = db_mode_to_cpp(isolate, args[1]);

    char const* res = kth_node_db_type(mode);
    args.GetReturnValue().Set(string_to_js(isolate, res));
}

}  // namespace kth::js_native
