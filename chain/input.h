#ifndef KTH_JS_CHAIN_INPUT_H_
#define KTH_JS_CHAIN_INPUT_H_

#include <node.h>

namespace kth_native {

void bitprim_chain_input_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_input_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_input_is_final(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_input_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_input_sequence(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_input_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_input_script(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_input_previous_output(v8::FunctionCallbackInfo<v8::Value> const& args);
//void bitprim_chain_input_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
//void bitprim_chain_input_get_index(v8::FunctionCallbackInfo<v8::Value> const& args);


}  // namespace kth_native

#endif //KTH_JS_CHAIN_INPUT_H_
