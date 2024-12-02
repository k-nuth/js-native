// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_WALLET_EC_PRIVATE_HPP_
#define KTH_JS_WALLET_EC_PRIVATE_HPP_

#include <node.h>

namespace kth::js_native {

void wallet_ec_private_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_construct_string(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_construct_compressed(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_construct_uncompressed(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_construct_secret(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_encoded(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_secret(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_payment_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_wif_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_compressed(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_to_public(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_private_to_payment_address(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_WALLET_EC_PRIVATE_HPP_
