#ifndef KTH_JS_CHAIN_HISTORY_COMPACT_LIST_H_
#define KTH_JS_CHAIN_HISTORY_COMPACT_LIST_H_

#include <node.h>

namespace kth_native {

void bitprim_chain_history_compact_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_history_compact_list_count(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_history_compact_list_nth(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth_native

#endif //KTH_JS_CHAIN_HISTORY_COMPACT_LIST_H_
