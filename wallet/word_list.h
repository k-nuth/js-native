#ifndef BITPRIM_JS_WALLET_WORD_LIST_H_
#define BITPRIM_JS_WALLET_WORD_LIST_H_

#include <node.h>

namespace bitprim_ns {

void bitprim_wallet_word_list_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_wallet_word_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_wallet_word_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace bitprim_ns

#endif //BITPRIM_JS_WALLET_WORD_LIST_H_
