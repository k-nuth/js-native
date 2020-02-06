// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_HISTORY_COMPACT_H_
#define KTH_JS_CHAIN_HISTORY_COMPACT_H_

#include <node.h>

namespace kth_native {

void kth_chain_history_compact_get_point_kind(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_history_compact_get_point(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_history_compact_get_height(v8::FunctionCallbackInfo<v8::Value> const& args);
void kth_chain_history_compact_get_value_or_previous_checksum(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth_native

#endif //KTH_JS_CHAIN_HISTORY_COMPACT_H_
