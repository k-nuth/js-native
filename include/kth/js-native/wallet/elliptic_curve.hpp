// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_WALLET_ELLIPTIC_CURVE_HPP
#define KTH_JS_WALLET_ELLIPTIC_CURVE_HPP

#include <node.h>

namespace kth::js_native {

void wallet_secret_to_public(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_WALLET_ELLIPTIC_CURVE_HPP
