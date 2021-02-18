// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_POINT_H_
#define KTH_JS_CHAIN_POINT_H_

#include <node.h>

namespace kth::js_native {

void chain_point_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_point_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_point_get_index(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_point_get_checksum(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_POINT_H_
