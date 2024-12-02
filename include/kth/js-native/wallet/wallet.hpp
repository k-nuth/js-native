// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_WALLET_WALLET_HPP_
#define KTH_JS_WALLET_WALLET_HPP_

#include <node.h>

namespace kth::js_native {

void wallet_mnemonics_to_seed(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_new(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_hd_private_to_ec(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_to_public(v8::FunctionCallbackInfo<v8::Value> const& args);
void wallet_ec_to_address(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_WALLET_WALLET_HPP_
