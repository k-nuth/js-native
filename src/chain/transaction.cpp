// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/capi/chain/transaction.h>
#include <kth/js-native/chain/transaction.hpp>
#include <kth/js-native/helper.hpp>

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


void chain_transaction_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    kth_chain_transaction_destruct(tx);
}

void chain_transaction_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    uint32_t res = kth_chain_transaction_version(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

// void chain_transaction_set_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_transaction_t tx = (kth_transaction_t)vptr;

//     kth_chain_transaction_set_version(tx);
// }

void chain_transaction_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    kth_hash_t res = kth_chain_transaction_hash(tx);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    args.GetReturnValue().Set(Uint8Array::New(tmp, 0, 32));
}

void chain_transaction_hash_sighash_type(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    uint32_t sighash_type = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    
    // TODO(fernando): there is a typo in the C-API, fixme: kth_chain_transaction_hash_sighash_type
    kth_hash_t res = kth_chain_transaction_hash_sigkth_hash_type(tx, sighash_type);

    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    args.GetReturnValue().Set(Uint8Array::New(tmp, 0, 32));
}

void chain_transaction_locktime(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    uint32_t res = kth_chain_transaction_locktime(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    bool wire = args[1]->BooleanValue(isolate->GetCurrentContext()).ToChecked();
    uint64_t res = kth_chain_transaction_serialized_size(tx, wire ? 1 : 0);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_fees(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    uint64_t res = kth_chain_transaction_fees(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    uint64_t res = kth_chain_transaction_signature_operations(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    bool bip16_active = args[1]->BooleanValue(isolate->GetCurrentContext()).ToChecked();

    uint64_t res = kth_chain_transaction_signature_operations_bip16_active(tx, bip16_active ? 1 : 0);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_total_input_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    uint64_t res = kth_chain_transaction_total_input_value(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_total_output_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    uint64_t res = kth_chain_transaction_total_output_value(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void chain_transaction_is_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    int res = kth_chain_transaction_is_coinbase(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_null_non_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    int res = kth_chain_transaction_is_null_non_coinbase(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_oversized_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    int res = kth_chain_transaction_is_oversized_coinbase(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_mature(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    uint64_t target_height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    int res = kth_chain_transaction_is_mature(tx, target_height);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_overspent(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    int res = kth_chain_transaction_is_overspent(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    bool include_unconfirmed = args[1]->BooleanValue(isolate->GetCurrentContext()).ToChecked();

    int res = kth_chain_transaction_is_double_spend(tx, include_unconfirmed ? 1 : 0);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_missing_previous_outputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    int res = kth_chain_transaction_is_missing_previous_outputs(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_final(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    uint64_t block_height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    uint32_t kth_block_time = args[2]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    int res = kth_chain_transaction_is_final(tx, block_height, kth_block_time);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_is_locktime_conflict(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    int res = kth_chain_transaction_is_locktime_conflict(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void chain_transaction_outputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    kth_output_list_t res = kth_chain_transaction_outputs(tx);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void chain_transaction_inputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_transaction_t tx = (kth_transaction_t)vptr;

    kth_input_list_t res = kth_chain_transaction_inputs(tx);
    args.GetReturnValue().Set(External::New(isolate, res));
}

}  // namespace kth::js_native
