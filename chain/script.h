#ifndef BITPRIM_JS_CHAIN_SCRIPT_H_
#define BITPRIM_JS_CHAIN_SCRIPT_H_

#include <node.h>

namespace bitprim_ns {

void bitprim_chain_script_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_script_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_script_is_valid_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_script_satoshi_content_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_script_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_script_to_string(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_script_sigops(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_script_embedded_sigops(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace bitprim_ns

#endif //BITPRIM_JS_CHAIN_SCRIPT_H_
