#ifndef BITPRIM_JS_CHAIN_HISTORY_COMPACT_H_
#define BITPRIM_JS_CHAIN_HISTORY_COMPACT_H_

#include <node.h>

namespace bitprim_ns {

void bitprim_chain_history_compact_get_point_kind(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_history_compact_get_point(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_history_compact_get_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_history_compact_get_value_or_previous_checksum(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace bitprim_ns

#endif //BITPRIM_JS_CHAIN_HISTORY_COMPACT_H_
