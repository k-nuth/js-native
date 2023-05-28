// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/chain.h>
#include <kth/capi/node.h>
#include <kth/capi/chain/block_list.h>

#include <tuple>

#include <kth/js-native/chain/chain.hpp>
#include <kth/js-native/chain/tools.hpp>
#include <kth/js-native/helper.hpp>

namespace kth::js_native {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Null;
using v8::Number;
using v8::Persistent;
using v8::Function;

using persistent_function_t = v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>>;


struct blockchain_callback_data_t {
    persistent_function_t* callback;
    uv_async_t* async;
    kth_error_code_t error;
    uint64_t height;
    kth_block_list_t incoming;
    kth_block_list_t outgoing;
    bool closing;
    bool unsubscribe;
};

static std::atomic<blockchain_callback_data_t*> global_callback_data{nullptr};

// ---------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------------------

void chain_fetch_last_height_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    // v8::Locker locker(isolate);
	// v8::HandleScope scope(isolate);
    Local<Value> argv[] = { Number::New(isolate, error), Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

// void chain_fetch_last_height(kth_chain_t chain, void* ctx, last_height_fetch_handler_t handler);
void chain_fetch_last_height(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        // throw_exception(isolate, "Wrong number of arguments", v8::NewStringType::kNormal)->ToLocalChecked();
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    auto callback = make_callback(isolate, args[1]);
    kth_chain_async_last_height(chain, callback, chain_fetch_last_height_handler);
}

// ---------------------------------------------------------------------------------------------------------------------------------------

// void chain_fetch_block_height(kth_chain_t chain, void* ctx, kth_hash_t hash, block_height_fetch_handler_t handler);
// int chain_get_block_height(kth_chain_t chain, kth_hash_t hash, uint64_t /*size_t*/* height);
// typedef void (*block_height_fetch_handler_t)(kth_chain_t, void*, int, uint64_t /*size_t*/ h);

void chain_fetch_block_height_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error), Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_block_height(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    kth_hash_t hash = to_native_hash(arr);
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_block_height(chain, callback, hash, chain_fetch_block_height_handler);
}


// // Block Header ---------------------------------------------------------------------

// void chain_fetch_block_header_by_height(kth_chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_header_fetch_handler_t handler);
// int chain_get_block_header_by_height(kth_chain_t chain, uint64_t /*size_t*/ height, kth_header_t* out_header, uint64_t /*size_t*/* out_height);
// typedef void (*block_header_fetch_handler_t)(kth_chain_t, void*, int, kth_header_t header, uint64_t /*size_t*/ h);

void chain_fetch_block_header_by_height_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_header_t header, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error),
                            External::New(isolate, header),
                            Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_block_header_by_height(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    uint64_t height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_block_header_by_height(chain, callback, height, chain_fetch_block_header_by_height_handler);
}

// void chain_fetch_block_header_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, block_header_fetch_handler_t handler);
// int chain_get_block_header_by_hash(kth_chain_t chain, kth_hash_t hash, kth_header_t* out_header, uint64_t /*size_t*/* out_height);
void chain_fetch_block_header_by_hash_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_header_t header, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error),
                            External::New(isolate, header),
                            Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_block_header_by_hash(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    kth_hash_t hash = to_native_hash(arr);
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_block_header_by_hash(chain, callback, hash, chain_fetch_block_header_by_hash_handler);
}

// // Block ---------------------------------------------------------------------
// void chain_fetch_block_by_height(kth_chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_fetch_handler_t handler);
// int chain_get_block_by_height(kth_chain_t chain, uint64_t /*size_t*/ height, kth_block_t* out_block, uint64_t /*size_t*/* out_height);
// typedef void (*block_fetch_handler_t)(kth_chain_t, void*, int, kth_block_t block, uint64_t /*size_t*/ h);

void chain_fetch_block_by_height_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_block_t block, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error),
                            External::New(isolate, block),
                            Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_block_by_height(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsNumber()) {
            throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;

    uint64_t height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_block_by_height(chain, callback, height, chain_fetch_block_by_height_handler);
}


// void chain_fetch_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, block_fetch_handler_t handler);
// int chain_get_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_block_t* out_block, uint64_t /*size_t*/* out_height);
void chain_fetch_block_by_hash_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_block_t block, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error), External::New(isolate, block), Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_block_by_hash(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    kth_hash_t hash = to_native_hash(arr);
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_block_by_hash(chain, callback, hash, chain_fetch_block_by_hash_handler);
}


// // Merkle Block ---------------------------------------------------------------------
// void chain_fetch_merkle_block_by_height(kth_chain_t chain, void* ctx, uint64_t /*size_t*/ height, merkle_block_fetch_handler_t handler);
// int chain_get_merkle_block_by_height(kth_chain_t chain, uint64_t /*size_t*/ height, kth_merkleblock_t* out_block, uint64_t /*size_t*/* out_height);
// typedef void (*merkle_block_fetch_handler_t)(kth_chain_t, void*, int, kth_merkleblock_t block, uint64_t /*size_t*/ h);

void chain_fetch_merkle_block_by_height_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_merkleblock_t merkle_block, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error), External::New(isolate, merkle_block), Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_merkle_block_by_height(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsNumber()) {
            throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;

    uint64_t height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_merkle_block_by_height(chain, callback, height, chain_fetch_merkle_block_by_height_handler);
}


// void chain_fetch_merkle_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, merkle_block_fetch_handler_t handler);
// int chain_get_merkle_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_merkleblock_t* out_merkle_block, uint64_t /*size_t*/* out_height);

void chain_fetch_merkle_block_by_hash_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_merkleblock_t merkle_block, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error), External::New(isolate, merkle_block), Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_merkle_block_by_hash(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    kth_hash_t hash = to_native_hash(arr);
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_merkle_block_by_hash(chain, callback, hash, chain_fetch_merkle_block_by_hash_handler);
}

// // Compact Block ---------------------------------------------------------------------
// void chain_fetch_compact_block_by_height(kth_chain_t chain, void* ctx, uint64_t /*size_t*/ height, compact_block_fetch_handler_t handler);
// int chain_get_compact_block_by_height(kth_chain_t chain, uint64_t /*size_t*/ height, kth_compact_block_t* out_block, uint64_t /*size_t*/* out_height);
// typedef void (*compact_block_fetch_handler_t)(kth_chain_t, void*, int, kth_compact_block_t block, uint64_t /*size_t*/ h);

void chain_fetch_compact_block_by_height_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_compact_block_t compact_block, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error), External::New(isolate, compact_block), Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_compact_block_by_height(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsNumber()) {
            throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;

    uint64_t height = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_compact_block_by_height(chain, callback, height, chain_fetch_compact_block_by_height_handler);
}


// void chain_fetch_compact_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, compact_block_fetch_handler_t handler);
// int chain_get_compact_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_compact_block_t* out_compact_block, uint64_t /*size_t*/* out_height);

void chain_fetch_compact_block_by_hash_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_compact_block_t compact_block, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error), External::New(isolate, compact_block), Number::New(isolate, h) };
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_compact_block_by_hash(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    kth_hash_t hash = to_native_hash(arr);
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_compact_block_by_hash(chain, callback, hash, chain_fetch_compact_block_by_hash_handler);
}


// // Transaction ---------------------------------------------------------------------
// void chain_fetch_transaction(kth_chain_t chain, void* ctx, kth_hash_t hash, int require_confirmed, transaction_fetch_handler_t handler);
// int chain_get_transaction(kth_chain_t chain, kth_hash_t hash, int require_confirmed, kth_transaction_t* out_transaction, uint64_t /*size_t*/* out_height, uint64_t /*size_t*/* out_index);
// typedef void (*transaction_fetch_handler_t)(kth_chain_t, void*, int, kth_transaction_t transaction, uint64_t i, uint64_t h);

void chain_fetch_transaction_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_transaction_t transaction, uint64_t i, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error),
                            External::New(isolate, transaction),
                            Number::New(isolate, i),
                            Number::New(isolate, h)};
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_transaction(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 4) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    if ( ! args[3]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 3");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    kth_hash_t hash = to_native_hash(arr);
    bool require_confirmed = args[2]->BooleanValue(isolate);
    auto callback = make_callback(isolate, args[3]);
    kth_chain_async_transaction(chain, callback, hash, require_confirmed, chain_fetch_transaction_handler);
}

// // Transaction Position ---------------------------------------------------------------------
// void chain_fetch_transaction_position(kth_chain_t chain, void* ctx, kth_hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler);
// int chain_get_transaction_position(kth_chain_t chain, kth_hash_t hash, int require_confirmed, uint64_t /*size_t*/* out_position, uint64_t /*size_t*/* out_height);
// typedef void (*transaction_index_fetch_handler_t)(kth_chain_t, void*, int, uint64_t position, uint64_t height);

void chain_fetch_transaction_position_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, uint64_t i, uint64_t h) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error), Number::New(isolate, i), Number::New(isolate, h)};
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_transaction_position(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 4) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsUint8Array()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsBoolean()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }


    if ( ! args[3]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 3");
        return;
    }

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        throw_exception(isolate, "Wrong arguments, 1, number of bytes");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    kth_hash_t hash = to_native_hash(arr);
    bool require_confirmed = args[2]->BooleanValue(isolate);
    auto callback = make_callback(isolate, args[3]);
    kth_chain_async_transaction_position(chain, callback, hash, require_confirmed, chain_fetch_transaction_position_handler);
}



// // Spend ---------------------------------------------------------------------
// KTH_EXPORT
// void chain_fetch_spend(kth_chain_t chain, void* ctx, kth_outputpoint_t op, spend_fetch_handler_t handler);
// typedef void (*spend_fetch_handler_t)(kth_chain_t, void*, int, kth_inputpoint_t input_point);

void chain_fetch_spend_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_inputpoint_t input_point) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error), External::New(isolate, input_point)};
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_spend(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }


    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;
    void* op_vptr = v8::External::Cast(*args[1])->Value();
    kth_outputpoint_t op = (kth_outputpoint_t)op_vptr;
    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_spend(chain, callback, op, chain_fetch_spend_handler);
}


// // History ---------------------------------------------------------------------
// void chain_fetch_history(kth_chain_t chain, void* ctx, kth_payment_address_t address, uint64_t limit, uint64_t from_height, history_fetch_handler_t handler);
// int chain_get_history(kth_chain_t chain, kth_payment_address_t address, uint64_t limit, uint64_t from_height, kth_history_compact_list_t* out_history);
// typedef void (*history_fetch_handler_t)(kth_chain_t, void*, int, kth_history_compact_list_t history);

void chain_fetch_history_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_history_compact_list_t history) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error), External::New(isolate, history)};
    call_function_and_free(isolate, ctx, argv);
}

void chain_fetch_history(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 5) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    if ( ! args[3]->IsNumber()) {
        throw_exception(isolate, "Wrong arguments, 3");
        return;
    }

    if ( ! args[4]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;

    void* address_vptr = v8::External::Cast(*args[1])->Value();
    kth_payment_address_t address = (kth_payment_address_t)address_vptr;

    uint64_t limit = args[2]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    uint64_t from_height = args[3]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

    auto callback = make_callback(isolate, args[4]);
    kth_chain_async_history(chain, callback, address, limit, from_height, chain_fetch_history_handler);
}


// // Stealth ---------------------------------------------------------------------
// // KTH_EXPORT
// // void chain_fetch_stealth(kth_chain_t chain, void* ctx, kth_binary_t filter, uint64_t from_height, stealth_fetch_handler_t handler);
// // typedef void (*stealth_fetch_handler_t)(kth_chain_t chain, void*, int, kth_stealth_compact_list_t stealth);

// void chain_fetch_stealth_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_stealth_compact_list_t stealth) {
//     auto* isolate = Isolate::GetCurrent();

//     Local<Value> argv[] = { Number::New(isolate, error), External::New(isolate, stealth)};

//     Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

//     Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext(), Null(isolate), argc, argv);

//     callback->Reset();
//     //callback->Dispose();
//     delete callback;
// }

// void chain_fetch_stealth(FunctionCallbackInfo<Value> const& args) {
//     auto* isolate = args.GetIsolate();

//     // kth_chain_t chain, kth_binary_t filter, uint64_t from_height, stealth_fetch_handler_t handler

//     if (args.Length() != 4) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments, 0");
//         return;
//     }

//     if ( ! args[1]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments, 1");
//         return;
//     }

//     if ( ! args[2]->IsNumber()) {
//         throw_exception(isolate, "Wrong arguments, 2");
//         return;
//     }

//     if ( ! args[3]->IsFunction()) {
//         throw_exception(isolate, "Wrong arguments, 2");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_chain_t chain = (kth_chain_t)vptr;

//     void* filter_vptr = v8::External::Cast(*args[1])->Value();
//     kth_binary_t filter = (kth_binary_t)filter_vptr;

//     uint64_t from_height = args[2]->IntegerValue(isolate->GetCurrentContext()).ToChecked();

//     Persistent<Function>* callback = new Persistent<Function>;
//     callback->Reset(isolate, args[3].As<Function>());

//     kth_chain_async_stealth(chain, callback, filter, from_height, chain_fetch_stealth_handler);
// }




// // // Block Locator ---------------------------------------------------------------------

// // void chain_fetch_block_locator(kth_chain_t chain, void* ctx, block_indexes_t heights, block_locator_fetch_handler_t handler);
// // int chain_get_block_locator(kth_chain_t chain, block_indexes_t heights, get_headers_ptr_t* out_headers);
// // typedef void (*block_locator_fetch_handler_t)(kth_chain_t, void*, int, get_headers_ptr_t);

// void chain_fetch_block_locator_handler(kth_chain_t chain, void* ctx, kth_error_code_t error, get_headers_ptr_t headers) {

//     printf("chain_fetch_block_locator_handler - 1\n");
//     printf("chain_fetch_block_locator_handler - error:   %d\n", error);
//     printf("chain_fetch_block_locator_handler - headers:  %p\n", headers);

//     auto* isolate = Isolate::GetCurrent();

//     Local<Value> argv[] = { Number::New(isolate, error), External::New(isolate, headers)};

//     Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

//     Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext(), Null(isolate), argc, argv);

//     callback->Reset();
//     //callback->Dispose();
//     delete callback;
// }

// void chain_fetch_block_locator(FunctionCallbackInfo<Value> const& args) {
//     auto* isolate = args.GetIsolate();


//     // kth_chain_t chain, block_indexes_t heights, block_locator_fetch_handler_t handler)

//     if (args.Length() != 3) {
//         throw_exception(isolate, "Wrong number of arguments");
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments, 0");
//         return;
//     }

//     if ( ! args[1]->IsExternal()) {
//         throw_exception(isolate, "Wrong arguments, 1");
//         return;
//     }

//     if ( ! args[2]->IsFunction()) {
//         throw_exception(isolate, "Wrong arguments, 2");
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     kth_chain_t chain = (kth_chain_t)vptr;

//     void* heights_vptr = v8::External::Cast(*args[1])->Value();
//     block_indexes_t heights = (block_indexes_t)heights_vptr;

//     Persistent<Function>* callback = new Persistent<Function>;
//     callback->Reset(isolate, args[2].As<Function>());

//     kth_chain_async_block_locator(chain, callback, heights, chain_fetch_block_locator_handler);
// }




// // Organizers.
// //-------------------------------------------------------------------------

// void chain_organize_block(kth_chain_t chain, void* ctx, kth_block_t block, result_handler_t handler);
// int chain_organize_block_sync(kth_chain_t chain, kth_block_t block);
// typedef void (*result_handler_t)(kth_chain_t, void*, int);

void chain_organize_block_handler(kth_chain_t chain, void* ctx, kth_error_code_t error) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error)};
    call_function_and_free(isolate, ctx, argv);
}

void chain_organize_block(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    // kth_chain_t chain, kth_block_t block, result_handler_t handler

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;

    void* block_vptr = v8::External::Cast(*args[1])->Value();
    kth_block_t block = (kth_block_t)block_vptr;

    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_organize_block(chain, callback, block, chain_organize_block_handler);
}


// void chain_organize_transaction(kth_chain_t chain, void* ctx, kth_transaction_t transaction, result_handler_t handler);
// int chain_organize_transaction_sync(kth_chain_t chain, kth_transaction_t transaction);
// typedef void (*result_handler_t)(kth_chain_t, void*, int);


void chain_organize_transaction_handler(kth_chain_t chain, void* ctx, kth_error_code_t error) {
    auto* isolate = Isolate::GetCurrent();
    Local<Value> argv[] = { Number::New(isolate, error)};
    call_function_and_free(isolate, ctx, argv);
}

void chain_organize_transaction(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 0");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments, 1");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments, 2");
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    kth_chain_t chain = (kth_chain_t)vptr;

    void* transaction_vptr = v8::External::Cast(*args[1])->Value();
    kth_transaction_t transaction = (kth_transaction_t)transaction_vptr;

    auto callback = make_callback(isolate, args[2]);
    kth_chain_async_organize_transaction(chain, callback, transaction, chain_organize_transaction_handler);
}



// Subscribers.
//-------------------------------------------------------------------------

void free_blockchain_callback_data(blockchain_callback_data_t* callback_data) {
    if (callback_data == nullptr) {
        return;
    }
    callback_data->callback->Reset();
    delete callback_data->callback;
    uv_close(reinterpret_cast<uv_handle_t*>(callback_data->async), [](uv_handle_t* handle) {
        delete reinterpret_cast<uv_async_t*>(handle);
    });
    delete callback_data;
}

kth_bool_t kth_chain_subscribe_blockchain_handler(kth_node_t node, kth_chain_t chain, void* ctx, kth_error_code_t error, uint64_t height, kth_block_list_t incoming, kth_block_list_t outgoing) {
    auto* callback_data = static_cast<blockchain_callback_data_t*>(ctx);
    if (global_callback_data == nullptr) {
        return 0;
    }

    constexpr int service_stopped = 1;
    if (kth_node_stopped(node) != 0 || error == service_stopped) {
        callback_data->closing = true;

        auto* existing_callback_data = global_callback_data.exchange(nullptr);
        if (existing_callback_data != nullptr) {
            free_blockchain_callback_data(existing_callback_data);
        }
        return 0;
    }

    if (callback_data->unsubscribe) {
        auto* existing_callback_data = global_callback_data.exchange(nullptr);
        if (existing_callback_data != nullptr) {
            free_blockchain_callback_data(existing_callback_data);
        }
        return 0;
    }

    callback_data->error = error;
    callback_data->height = height;
    callback_data->incoming = incoming;
    callback_data->outgoing = outgoing;
    callback_data->async->data = callback_data;

    uv_async_send(callback_data->async);

    return 1; // Return 1 to keep the subscription active.
}

void kth_chain_subscribe_blockchain_async_handler(uv_async_t* handle) {
    auto* callback_data = static_cast<blockchain_callback_data_t*>(handle->data);
    if (global_callback_data == nullptr) {
        return;
    }

    auto* isolate = Isolate::GetCurrent();
    auto callback = callback_data->callback;

    v8::HandleScope handle_scope(isolate);

    Local<Value> incomingBlocks;
    if (callback_data->incoming != nullptr) {
        incomingBlocks = External::New(isolate, callback_data->incoming);
    } else {
        incomingBlocks = Null(isolate);
    }

    Local<Value> outgoingBlocks;
    if (callback_data->outgoing != nullptr) {
        outgoingBlocks = External::New(isolate,callback_data->outgoing);
    } else {
        outgoingBlocks = Null(isolate);
    }

    Local<Value> argv[] = {
        Number::New(isolate, callback_data->error),
        Number::New(isolate, callback_data->height),
        incomingBlocks,
        outgoingBlocks
    };

    auto callback_local = Local<Function>::New(isolate, *callback);
    auto maybe_result = callback_local->Call(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 4, argv);

    if (maybe_result.IsEmpty() || ! maybe_result.ToLocalChecked()->IsTrue()) {
        callback_data->unsubscribe = true;
    }

    if (callback_data->incoming != nullptr) {
        kth_chain_block_list_destruct(callback_data->incoming);
        callback_data->incoming = nullptr;
    }

    if (callback_data->outgoing != nullptr) {
        kth_chain_block_list_destruct(callback_data->outgoing);
        callback_data->outgoing = nullptr;
    }

    // // Check if closing flag is set and if so, delete callback_data
    // if (callback_data->closing) {
    //     delete callback_data;
    // }
}

void chain_subscribe_blockchain(FunctionCallbackInfo<Value> const& args) {
    auto* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        throw_exception(isolate, "Wrong number of arguments");
        return;
    }

    if ( ! args[0]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[1]->IsExternal()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    if ( ! args[2]->IsFunction()) {
        throw_exception(isolate, "Wrong arguments");
        return;
    }

    void* node_ptr = v8::External::Cast(*args[0])->Value();
    kth_node_t node = (kth_node_t)node_ptr;

    void* chain_ptr = v8::External::Cast(*args[1])->Value();
    kth_chain_t chain = (kth_chain_t)chain_ptr;

    // Cleanup existing subscription, if any
    auto* existing_callback_data = global_callback_data.exchange(nullptr);
    if (existing_callback_data != nullptr) {
        free_blockchain_callback_data(existing_callback_data);
    }

    auto callback = new persistent_function_t;
    callback->Reset(isolate, args[2].As<v8::Function>());

    auto* async = new uv_async_t;
    uv_async_init(uv_default_loop(), async, kth_chain_subscribe_blockchain_async_handler);

    // Create new subscription context
    auto* callback_data = new blockchain_callback_data_t;
    callback_data->callback = callback;
    callback_data->async = async;
    callback_data->closing = false;
    callback_data->unsubscribe = false;
    global_callback_data = callback_data;

    kth_chain_subscribe_blockchain(node, chain, callback_data, kth_chain_subscribe_blockchain_handler);
}


//---------------------------------------------------------------------------

// KTH_EXPORT
// kth_transaction_t hex_to_tx(char const* tx_hex);


// KTH_EXPORT
// void chain_validate_tx(kth_chain_t chain, void* ctx, kth_transaction_t tx, validate_tx_handler_t handler);


}  // namespace kth::js_native
