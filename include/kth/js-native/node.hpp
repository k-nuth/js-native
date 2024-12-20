// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_NATIVE_NODE_HPP_
#define KTH_JS_NATIVE_NODE_HPP_

#include <node.h>

namespace kth::js_native {

void node_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_init_run_and_wait_for_signal(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_signal_stop(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_get_chain(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_print_thread_id(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_running(v8::FunctionCallbackInfo<v8::Value> const& args);

void node_capi_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_cppapi_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_microarchitecture(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_march_names(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_currency_symbol(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_currency(v8::FunctionCallbackInfo<v8::Value> const& args);
void node_db_type(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_NATIVE_NODE_HPP_
