// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_SCRIPT_H_
#define KTH_JS_CHAIN_SCRIPT_H_

#include <node.h>

namespace kth_js_native {

void chain_script_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_is_valid_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_satoshi_content_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_to_string(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_sigops(v8::FunctionCallbackInfo<v8::Value> const& args);
// void chain_script_embedded_sigops(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth_js_native

#endif //KTH_JS_CHAIN_SCRIPT_H_
