#ifndef BITPRIM_JS_CHAIN_PAYMENT_ADDRESS_H_
#define BITPRIM_JS_CHAIN_PAYMENT_ADDRESS_H_

#include <node.h>

namespace bitprim_ns {

void bitprim_chain_payment_address_destruct(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_payment_address_encoded(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_payment_address_version(v8::FunctionCallbackInfo<v8::Value> const& args);
void bitprim_chain_payment_address_construct_from_string(v8::FunctionCallbackInfo<v8::Value> const& args);

}  // namespace bitprim_ns

#endif //BITPRIM_JS_CHAIN_PAYMENT_ADDRESS_H_
