// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_WALLET_WORD_LIST_H_
#define KTH_JS_WALLET_WORD_LIST_H_

#include <node.h>

namespace kth_js_native {

void wallet_word_list_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_word_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_word_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth_js_native

#endif //KTH_JS_WALLET_WORD_LIST_H_
