// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_WALLET_HD_PRIVATE_HPP_
#define KTH_JS_WALLET_HD_PRIVATE_HPP_

#include <node.h>

namespace kth::js_native {

void wallet_hd_private_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_construct_with_prefix(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_construct_with_prefixes(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_construct_with_seed(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_construct_string(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_construct_string_with_prefix(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_construct_string_with_prefixes(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_encoded(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_secret(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_to_hd_key(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_to_public(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_derive_private(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_derive_public(v8::FunctionCallbackInfo<v8::Value> const& args);


}  // namespace kth::js_native

#endif //KTH_JS_WALLET_HD_PRIVATE_HPP_
