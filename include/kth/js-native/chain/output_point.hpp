// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_OUTPUT_POINT_H_
#define KTH_JS_CHAIN_OUTPUT_POINT_H_

#include <node.h>

namespace kth::js_native {

void chain_output_point_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_output_point_construct_from_hash_index(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_output_point_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_output_point_get_hash(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_output_point_get_index(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_OUTPUT_POINT_H_
