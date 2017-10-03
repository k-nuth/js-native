#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <bitprim/nodecint/chain/transaction.h>

#include "transaction.h"

namespace bitprim_ns {

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


void bitprim_chain_transaction_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


// void bitprim_chain_transaction_set_version(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

void bitprim_chain_transaction_hash_sighash_type(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_locktime(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    uint64_t res = chain_transaction_serialized_size(tx, wire != 0);
    args.GetReturnValue().Set(Number::New(isolate, res));
}

void bitprim_chain_transaction_fees(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

void bitprim_chain_transaction_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

    uint64_t res = chain_transaction_signature_operations_bip16_active(tx, bip16_active);
    args.GetReturnValue().Set(Number::New(isolate, res));
}


void bitprim_chain_transaction_total_input_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_total_output_value(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_is_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

void bitprim_chain_transaction_is_null_non_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

void bitprim_chain_transaction_is_oversized_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

void bitprim_chain_transaction_is_mature(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

void bitprim_chain_transaction_is_overspent(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_is_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

    int res = chain_transaction_is_double_spend(tx, include_unconfirmed != 0);
    args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
}


void bitprim_chain_transaction_is_missing_previous_outputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_is_final(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_is_locktime_conflict(v8::FunctionCallbackInfo<v8::Value> const& args) {
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

void bitprim_chain_transaction_outputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
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


void bitprim_chain_transaction_inputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
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




// -----------------------------------------------

// void bitprim_chain_block_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     chain_block_destruct(block);
// }

// void bitprim_chain_block_get_header(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     header_t header = chain_block_header(block);

//     Local<External> ret = External::New(isolate, header);
//     args.GetReturnValue().Set(ret);
    
// }

// void bitprim_chain_block_transaction_count(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     // Check the number of arguments passed.
//     if (args.Length() != 1) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     block_t block = (block_t)vptr;

//     uint64_t tx_count = chain_block_transaction_count(block);
//     args.GetReturnValue().Set(Number::New(isolate, tx_count));
// }

// void bitprim_chain_block_serialized_size(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     if (args.Length() != 2) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[1]->IsNumber()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     block_t block = (block_t)vptr;

//     uint32_t version = args[1]->IntegerValue();

//     uint64_t res = chain_block_serialized_size(block, version);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }

// // C++ static
// void bitprim_chain_block_subsidy(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     if (args.Length() != 1) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsNumber()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     uint64_t height = args[0]->IntegerValue();
    
//     uint64_t res = chain_block_subsidy(height);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }

// void bitprim_chain_block_fees(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     uint64_t res = chain_block_fees(block);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }

// void bitprim_chain_block_claim(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     uint64_t res = chain_block_claim(block);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }

// void bitprim_chain_block_reward(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     if (args.Length() != 2) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[1]->IsNumber()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     block_t block = (block_t)vptr;

//     uint64_t height = args[1]->IntegerValue();

//     uint64_t res = chain_block_reward(block, height);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }

// void bitprim_chain_block_generate_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     hash_t res = chain_block_generate_merkle_root(block);
//     Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
//     memcpy(tmp->GetContents().Data(), res.hash, 32);
//     Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
//     args.GetReturnValue().Set(hash);
// }

// void bitprim_chain_block_hash(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     hash_t res = chain_block_hash(block);
//     Local<ArrayBuffer> tmp = ArrayBuffer::New(isolate, 32);
//     memcpy(tmp->GetContents().Data(), res.hash, 32);
//     Local<Uint8Array> hash = Uint8Array::New(tmp, 0, 32);
//     args.GetReturnValue().Set(hash);

// }

// void bitprim_chain_block_is_valid(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     int res = chain_block_is_valid(block);
//     args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
// }


// void bitprim_chain_block_transaction_nth(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     if (args.Length() != 2) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[1]->IsNumber()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     block_t block = (block_t)vptr;

//     uint64_t n = args[1]->IntegerValue();
    
//     transaction_t res = chain_block_transaction_nth(block, n);
//     args.GetReturnValue().Set(External::New(isolate, res));
// }


// void bitprim_chain_block_signature_operations(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     uint64_t res = chain_block_signature_operations(block);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }



// void bitprim_chain_block_signature_operations_bip16_active(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     if (args.Length() != 2) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[1]->IsBoolean()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     block_t block = (block_t)vptr;

//     bool bip16_active = args[1]->BooleanValue();
    
//     uint64_t res = chain_block_signature_operations_bip16_active(block, bip16_active ? 1 : 0);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }


// void bitprim_chain_block_total_inputs(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     if (args.Length() != 2) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[1]->IsBoolean()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }
    
//     void* vptr = v8::External::Cast(*args[0])->Value();
//     block_t block = (block_t)vptr;

//     bool with_coinbase = args[1]->BooleanValue();

//     uint64_t res = chain_block_total_inputs(block, with_coinbase ? 1 : 0);
//     args.GetReturnValue().Set(Number::New(isolate, res));
// }


// void bitprim_chain_block_is_extra_coinbase(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     int res = chain_block_is_extra_coinbases(block);
//     args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
// }

// void bitprim_chain_block_is_final(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     if (args.Length() != 3) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[1]->IsNumber()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[2]->IsNumber()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     block_t block = (block_t)vptr;

//     uint64_t height = args[1]->IntegerValue();
//     uint32_t block_time = args[2]->IntegerValue();

//     int res = chain_block_is_final(block, height, block_time);
//     args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
// }


// void bitprim_chain_block_is_distinct_transaction_set(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     int res = chain_block_is_distinct_transaction_set(block);
//     args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
// }


// void bitprim_chain_block_is_valid_coinbase_claim(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     if (args.Length() != 2) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[1]->IsNumber()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     block_t block = (block_t)vptr;

//     uint64_t height = args[1]->IntegerValue();
    
//     int res = chain_block_is_valid_coinbase_claim(block, height);
//     args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
// }


// void bitprim_chain_block_is_valid_coinbase_script(v8::FunctionCallbackInfo<v8::Value> const& args) {
//     Isolate* isolate = args.GetIsolate();
    
//     if (args.Length() != 2) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     if ( ! args[1]->IsNumber()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     block_t block = (block_t)vptr;

//     uint64_t height = args[1]->IntegerValue();
    
//     int res = chain_block_is_valid_coinbase_script(block, height);
//     args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
// }


// void bitprim_chain_block_is_internal_double_spend(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     int res = chain_block_is_internal_double_spend(block);
//     args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
// }


// void bitprim_chain_block_is_valid_merkle_root(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
//     block_t block = (block_t)vptr;

//     int res = chain_block_is_valid_merkle_root(block);
//     args.GetReturnValue().Set(Boolean::New(isolate, res != 0));
// }

}  // namespace bitprim_ns
