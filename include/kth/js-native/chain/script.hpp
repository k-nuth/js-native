// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_JS_CHAIN_SCRIPT_H_
#define KTH_JS_CHAIN_SCRIPT_H_

#include <node.h>

namespace kth::js_native {
// kth_script_t kth_chain_script_construct(uint8_t* encoded, uint64_t n, kth_bool_t prefix);

void chain_script_construct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_is_valid_operations(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_satoshi_content_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_to_string(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_sigops(v8::FunctionCallbackInfo<v8::Value> const& args);
void chain_script_to_data(v8::FunctionCallbackInfo<v8::Value> const& args);

// void chain_script_embedded_sigops(v8::FunctionCallbackInfo<v8::Value> const& args);



// kth_script_t kth_chain_script_construct_default(void);
// kth_script_t kth_chain_script_construct(uint8_t* encoded, uint64_t n, kth_bool_t prefix);
// void kth_chain_script_destruct(kth_script_t script);
// kth_bool_t kth_chain_script_is_valid(kth_script_t script);
// kth_bool_t kth_chain_script_is_valid_operations(kth_script_t script);
// kth_size_t kth_chain_script_satoshi_content_size(kth_script_t script);
// kth_size_t kth_chain_script_serialized_size(kth_script_t script, kth_bool_t prefix);
// char* kth_chain_script_to_string(kth_script_t script, uint32_t active_forks);
// char* kth_chain_script_type(kth_script_t script);
// uint8_t* kth_chain_script_to_data(kth_script_t script, kth_bool_t prefix, kth_size_t* out_size);
// kth_size_t kth_chain_script_sigops(kth_script_t script, kth_bool_t embedded);


}  // namespace kth::js_native

#endif //KTH_JS_CHAIN_SCRIPT_H_
