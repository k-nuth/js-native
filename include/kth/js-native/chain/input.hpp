// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_INPUT_H_
#define KTH_JS_CHAIN_INPUT_H_

#include <node.h>

namespace kth::js_native {

void chain_input_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_factory_from_data(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_is_final(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_sequence(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_script(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_previous_output(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_to_data(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_INPUT_H_
