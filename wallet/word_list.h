#ifndef KTH_JS_WALLET_WORD_LIST_H_
#define KTH_JS_WALLET_WORD_LIST_H_

#include <node.h>

namespace kth_native {

void bitprim_wallet_word_list_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_wallet_word_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_wallet_word_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth_native

#endif //KTH_JS_WALLET_WORD_LIST_H_
