#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/c-api/chain/transaction.h>

#include "transaction.hpp"

namespace kth_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Handle;
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


void kth_chain_transaction_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    chain_transaction_destruct(tx);
}

void kth_chain_transaction_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    uint32_t res = chain_transaction_version(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

// void kth_chain_transaction_set_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     if (args.Length() != 1) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     transaction_t tx = (transaction_t)vptr;

//     chain_transaction_set_version(tx);
// }

void kth_chain_transaction_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    hash_t res = chain_transaction_hash(tx);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    args.GetReturnValue().Set(Uint8Array::New(tmp, 0, 32));
}

void kth_chain_transaction_hash_sighash_type(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    uint32_t sighash_type = args[1]->IntegerValue();
    hash_t res = chain_transaction_hash_sighash_type(tx, sighash_type);
    Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
    memcpy(tmp->GetContents().Data(), res.hash, 32);
    args.GetReturnValue().Set(Uint8Array::New(tmp, 0, 32));
}

void kth_chain_transaction_locktime(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    uint32_t res = chain_transaction_locktime(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_transaction_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    bool wire = args[1]->BooleanValue();
    uint64_t res = chain_transaction_serialized_size(tx, wire ? 1 : 0);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_transaction_fees(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    uint64_t res = chain_transaction_fees(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_transaction_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    uint64_t res = chain_transaction_signature_operations(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_transaction_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    bool bip16_active = args[1]->BooleanValue();

    uint64_t res = chain_transaction_signature_operations_bip16_active(tx, bip16_active ? 1 : 0);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_transaction_total_input_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    uint64_t res = chain_transaction_total_input_value(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_transaction_total_output_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    uint64_t res = chain_transaction_total_output_value(tx);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void kth_chain_transaction_is_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    int res = chain_transaction_is_coinbase(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void kth_chain_transaction_is_null_non_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    int res = chain_transaction_is_null_non_coinbase(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void kth_chain_transaction_is_oversized_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    int res = chain_transaction_is_oversized_coinbase(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void kth_chain_transaction_is_mature(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    uint64_t target_height = args[1]->IntegerValue();

    int res = chain_transaction_is_mature(tx, target_height);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void kth_chain_transaction_is_overspent(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    int res = chain_transaction_is_overspent(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void kth_chain_transaction_is_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsBoolean()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    bool include_unconfirmed = args[1]->BooleanValue();

    int res = chain_transaction_is_double_spend(tx, include_unconfirmed ? 1 : 0);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void kth_chain_transaction_is_missing_previous_outputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    int res = chain_transaction_is_missing_previous_outputs(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void kth_chain_transaction_is_final(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    uint64_t block_height = args[1]->IntegerValue();
    uint32_t block_time = args[2]->IntegerValue();

    int res = chain_transaction_is_final(tx, block_height, block_time);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void kth_chain_transaction_is_locktime_conflict(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    int res = chain_transaction_is_locktime_conflict(tx);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}

void kth_chain_transaction_outputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    output_list_t res = chain_transaction_outputs(tx);
    args.GetReturnValue().Set(External::New(isolate, res));
}

void kth_chain_transaction_inputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    transaction_t tx = (transaction_t)vptr;

    input_list_t res = chain_transaction_inputs(tx);
    args.GetReturnValue().Set(External::New(isolate, res));
}

}  // namespace kth_native
