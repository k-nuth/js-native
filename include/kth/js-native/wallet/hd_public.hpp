// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_WALLET_HD_PUBLIC_HPP_
#define KTH_JS_WALLET_HD_PUBLIC_HPP_

#include <node.h>

namespace kth::js_native {

void wallet_hd_public_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_construct_key(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_construct_key_prefix(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_construct_string(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_construct_string_prefix(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_encoded(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_chain_code(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_lineage(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_point(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_to_hd_key(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_public_derive_public(v8::FunctionCallbackInfo<v8::Value> const& args);


}  // namespace kth::js_native

#endif //KTH_JS_WALLET_HD_PUBLIC_HPP_
