// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_OUTPUT_H_
#define KTH_JS_CHAIN_OUTPUT_H_

#include <node.h>

namespace kth::js_native {

void chain_output_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_output_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_output_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_output_value(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_output_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_output_script(v8::FunctionCallbackInfo<v8::Value> const& args);
//void chain_output_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
//void chain_output_get_index(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_OUTPUT_H_
