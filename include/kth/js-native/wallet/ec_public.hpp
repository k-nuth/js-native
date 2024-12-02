// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_WALLET_EC_PUBLIC_HPP_
#define KTH_JS_WALLET_EC_PUBLIC_HPP_

#include <node.h>

namespace kth::js_native {

void wallet_ec_public_construct_default(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_construct_from_decoded(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_construct_from_base16(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_construct_from_point(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_encoded(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_point(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_compressed(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_to_data(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_to_uncompressed(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_public_to_payment_address(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_WALLET_EC_PUBLIC_HPP_
