// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_PAYMENT_ADDRESS_H_
#define KTH_JS_CHAIN_PAYMENT_ADDRESS_H_

#include <node.h>

namespace kth::js_native {

void wallet_payment_address_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_encoded(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_payment_address_construct_from_string(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_PAYMENT_ADDRESS_H_
