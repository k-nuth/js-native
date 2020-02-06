#ifndef KTH_JS_CHAIN_TOOLS_H_
#define KTH_JS_CHAIN_TOOLS_H_

#include <node.h>

namespace kth_native {

hash_t to_native_hash(v8::Local<v8::Uint8Array> const& arr);

}  // namespace kth_native

#endif //KTH_JS_CHAIN_TOOLS_H_
