#ifndef BITPRIM_JS_CHAIN_HISTORY_COMPACT_LIST_H_
#define BITPRIM_JS_CHAIN_HISTORY_COMPACT_LIST_H_

#include <node.h>

namespace bitprim_ns {

void bitprim_chain_history_compact_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_history_compact_list_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_history_compact_list_nth(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace bitprim_ns

#endif //BITPRIM_JS_CHAIN_HISTORY_COMPACT_LIST_H_
