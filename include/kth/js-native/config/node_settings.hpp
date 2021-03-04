// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CONFIG_NODE_SETTINGS_HPP_
#define KTH_JS_CONFIG_NODE_SETTINGS_HPP_

#include <node.h>

namespace kth::js_native {

void config_node_settings_default(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace kth::js_native

#endif //KTH_JS_CONFIG_NODE_SETTINGS_HPP_
