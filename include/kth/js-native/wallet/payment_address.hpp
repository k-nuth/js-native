// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_WALLET_PAYMENT_ADDRESS_H_
#define KTH_JS_WALLET_PAYMENT_ADDRESS_H_

#include <node.h>

namespace kth::js_native {

void wallet_payment_address_set_cashaddr_prefix(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_encoded_legacy(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_encoded_cashaddr(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_construct_from_string(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_hash20(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_hash32(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_WALLET_PAYMENT_ADDRESS_H_
