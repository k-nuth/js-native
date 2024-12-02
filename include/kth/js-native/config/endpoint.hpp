// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CONFIG_ENDPOINT_HPP_
#define KTH_JS_CONFIG_ENDPOINT_HPP_

#include <node.h>

namespace kth::js_native {

void config_endpoint_allocate_n(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CONFIG_ENDPOINT_HPP_
