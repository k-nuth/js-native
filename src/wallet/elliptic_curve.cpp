// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/wallet/elliptic_curve.h>

#include <kth/js-native/wallet/elliptic_curve.hpp>
#include <kth/js-native/helper.hpp>
#include <kth/js-native/wallet/convertions.hpp>

namespace kth::js_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Global;

using v8::Object;
using v8::String;
using v8::Boolean;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Number;
using v8::Persistent;
using v8::Function;
using v8::Uint8Array;
using v8::ArrayBuffer;

void wallet_secret_to_public(v8::FunctionCallbackInfo<v8::Value> const& args) {
    v8::Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsUint8Array()) {
        throw_exception(isolate, "Argument 0 must be a Uint8Array");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[0]);

    if (arr->Length() != KTH_BITCOIN_EC_SECRET_SIZE) {
        throw_exception(isolate, "Wrong arguments, hash length must be 32 bytes");
        return;
    }

    auto secret = to_native_ec_secret(arr);
    kth_ec_compressed_t out;
    kth_bool_t res = kth_wallet_secret_to_public(&out, secret);

    if (res == 0) {
        args.GetReturnValue().SetUndefined();
        return;
    }
    args.GetReturnValue().Set(ec_compressed_to_js(isolate, out));
}


}  // namespace kth::js_native
