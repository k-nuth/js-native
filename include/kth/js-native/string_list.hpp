// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CORE_STRING_LIST_HPP_
#define KTH_JS_CORE_STRING_LIST_HPP_

#include <node.h>

namespace kth::js_native {

void core_string_list_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void core_string_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void core_string_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CORE_STRING_LIST_HPP_
