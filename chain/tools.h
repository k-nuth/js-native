#ifndef BITPRIM_JS_CHAIN_TOOLS_H_
#define BITPRIM_JS_CHAIN_TOOLS_H_

#include <node.h>

namespace bitprim_ns {

hash_t to_native_hash(v8::Local<v8::Uint8Array> const& arr);

}  // namespace bitprim_ns

#endif //BITPRIM_JS_CHAIN_TOOLS_H_
