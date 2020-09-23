// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_INPUT_H_
#define KTH_JS_CHAIN_INPUT_H_

#include <node.h>

namespace kth::js_native {

void chain_input_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_is_final(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_sequence(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_script(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_previous_output(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_input_to_data(v8::FunctionCallbackInfo<v8::Value> const& args);

//void chain_input_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
//void chain_input_get_index(v8::FunctionCallbackInfo<v8::Value> const& args);



// kth_input_t kth_chain_input_construct_default(void);
// kth_input_t kth_chain_input_construct(kth_outputpoint_t previous_output, kth_script_t script, uint32_t sequence);
// void kth_chain_input_destruct(kth_input_t input);
// int kth_chain_input_is_valid(kth_input_t input);
// kth_bool_t kth_chain_input_is_final(kth_input_t input);
// kth_size_t kth_chain_input_serialized_size(kth_input_t input, kth_bool_t wire /* = true*/);
// uint32_t kth_chain_input_sequence(kth_input_t input);
// kth_size_t kth_chain_input_signature_operations(kth_input_t input, kth_bool_t bip16_active);
// kth_script_t kth_chain_input_script(kth_input_t input);
// kth_outputpoint_t kth_chain_input_previous_output(kth_input_t input);
// uint8_t* kth_chain_input_to_data(kth_input_t input, kth_bool_t wire, kth_size_t* out_size);


}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_INPUT_H_
