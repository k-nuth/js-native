#ifndef KTH_JS_CHAIN_INPUT_LIST_H_
#define KTH_JS_CHAIN_INPUT_LIST_H_

#include <node.h>

namespace bitprim_ns {

void bitprim_chain_input_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_input_list_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_input_list_nth(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace bitprim_ns

#endif //KTH_JS_CHAIN_INPUT_LIST_H_
