#include <node.h>

#include <bitprim/nodecint/executor_c.h>
#include <bitprim/nodecint/chain/chain.h>

#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)

namespace bitprim_ns {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Number;
using v8::Persistent;
using v8::Function;

//void Method(FunctionCallbackInfo<Value> const& args) {
//    Isolate* isolate = args.GetIsolate();
//    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
//}


void bitprim_executor_construct(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

//    printf("args[0]->IsString(): %d\n", args[0]->IsString());
//    printf("args[1]->IsObject(): %d\n", args[1]->IsObject());
//    printf("args[2]->IsObject(): %d\n", args[2]->IsObject());

//    printf("args[1]->IsObject(): %d\n", args[1]->IsObject());
//    printf("args[2]->IsObject(): %d\n", args[2]->IsObject());
//    printf("args[1]->IsNull():   %d\n", args[1]->IsNull());
//    printf("args[2]->IsNull():   %d\n", args[2]->IsNull());

    if ( ! args[0]->IsString() ||
         ! (args[1]->IsObject() || args[1]->IsNull()) ||
         ! (args[2]->IsObject() || args[2]->IsNull())
       ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    v8::String::Utf8Value path(args[0]->ToString());


    int32_t sout_fd = -1;
    int32_t serr_fd = -1;

    if (! args[1]->IsNull()) {
        auto sout_obj = args[1]->ToObject();
        sout_fd = sout_obj->Get(String::NewFromUtf8(isolate, "fd"))->Int32Value();
    }

    if (! args[2]->IsNull()) {
        auto serr_obj = args[2]->ToObject();
        serr_fd = serr_obj->Get(String::NewFromUtf8(isolate, "fd"))->Int32Value();
    }

//    printf("path:    %s\n", *path);
//    printf("sout_fd: %d\n", sout_fd);
//    printf("serr_fd: %d\n", serr_fd);

    executor_t exec = executor_construct_fd(*path, sout_fd, serr_fd);
//    printf("bitprim_executor_construct - exec: 0x%" PRIXPTR "\n", (uintptr_t)exec);

    Local<External> ext = External::New(isolate, exec);
//    printf("xxxxx 4\n");
    args.GetReturnValue().Set(ext);
//    printf("xxxxx 5\n");
}

void bitprim_executor_destruct(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    executor_t exec = (executor_t)vptr;
    executor_destruct(exec);
}


void bitprim_executor_stop(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    executor_t exec = (executor_t)vptr;
    executor_stop(exec);
}


void bitprim_executor_initchain(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    executor_t exec = (executor_t)vptr;
    int res = executor_initchain(exec);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}

//void bitprim_executor_run(const FunctionCallbackInfo<Value>& args) {
//    Isolate* isolate = args.GetIsolate();
//
//    // Check the number of arguments passed.
//    if (args.Length() != 1) {
//        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//        return;
//    }
//
//    if (!args[0]->IsExternal()) {
//        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//        return;
//    }
//
//    void* vptr = v8::External::Cast(*args[0])->Value();
//    executor_t exec = (executor_t)vptr;
//    int res = executor_run(exec);
//
//    Local<Number> num = Number::New(isolate, res);
//    args.GetReturnValue().Set(num);
//}

void bitprim_executor_run_wait(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    executor_t exec = (executor_t)vptr;
    int res = executor_run_wait(exec);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}


void bitprim_executor_get_chain(FunctionCallbackInfo<Value> const& args) {
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
    executor_t exec = (executor_t)vptr;
    chain_t chain = executor_get_chain(exec);


    Local<External> ext = External::New(isolate, chain);
    args.GetReturnValue().Set(ext);
}


// ---------------------------------------------

void chain_fetch_last_height_handler(chain_t chain, void* ctx, int error, uint64_t h) {
    Isolate* isolate = Isolate::GetCurrent();

    // printf("chain_fetch_last_height_handler - 1\n");
    // printf("chain_fetch_last_height_handler - error:   %d\n", error);
    // printf("chain_fetch_last_height_handler - h:       %d\n", h);

    unsigned int const argc = 2;
    Local<Value> argv[argc] = { Number::New(isolate, error), Number::New(isolate, h) };

    // printf("chain_fetch_last_height_handler - 2n");

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    // printf("chain_fetch_last_height_handler - 3\n");

    callback->Reset();

    // printf("chain_fetch_last_height_handler - 4\n");

    delete callback;

    // printf("chain_fetch_last_height_handler - 5\n");
}

// void chain_fetch_last_height(chain_t chain, void* ctx, last_height_fetch_handler_t handler);
void bitprim_chain_fetch_last_height(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[1].As<Function>());

    chain_fetch_last_height(chain, callback, chain_fetch_last_height_handler);
}


// void bitprim_chain_get_last_height(const FunctionCallbackInfo<Value>& args) {
//     Isolate* isolate = args.GetIsolate();

//     // Check the number of arguments passed.
//     if (args.Length() != 1) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if (!args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     chain_t chain = (chain_t)vptr;
//     size_t height;
//     int res = chain_get_last_height(chain, &height);

//     Local<Number> num = Number::New(isolate, height);
//     args.GetReturnValue().Set(num);
// }
// ---------------------------------------------




// BITPRIM_EXPORT
// void chain_fetch_last_height(chain_t chain, void* ctx, last_height_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_last_height(chain_t chain, uint64_t /*size_t*/* height);







// ---------------------------------------------

// void chain_fetch_block_height(chain_t chain, void* ctx, hash_t hash, block_height_fetch_handler_t handler);
// int chain_get_block_height(chain_t chain, hash_t hash, uint64_t /*size_t*/* height);
// typedef void (*block_height_fetch_handler_t)(chain_t, void*, int, uint64_t /*size_t*/ h);

void chain_fetch_block_height_handler(chain_t chain, void* ctx, int error, uint64_t h) {
    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 2;
    Local<Value> argv[argc] = { Number::New(isolate, error), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    delete callback;
}

void bitprim_chain_fetch_block_height(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    
    // if ( ! args[1]->IsString()) {
    if ( ! args[1]->IsUint8Array()) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;


    // v8::String::Utf8Value tx_hex(args[1]->ToString());

    v8::Local<v8::Array> arr = v8::Local<v8::Array>::Cast(args[1]);
    uint32_t arr_length = arr->Length();
    // v8::String::Utf8Value key(arr->Get(0));
    // v8::String::Utf8Value value(arr->Get(1));

    for (uint32_t i = 0; i < arr_length; ++i) {
        v8::Local<v8::Value> element = arr->Get(i);
    }

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_block_height(chain, callback, chain_fetch_block_height_handler);
}







// // Block Header ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_block_header_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_header_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_block_header_by_height(chain_t chain, uint64_t /*size_t*/ height, header_t* out_header, uint64_t /*size_t*/* out_height);

// BITPRIM_EXPORT
// void chain_fetch_block_header_by_hash(chain_t chain, void* ctx, hash_t hash, block_header_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_block_header_by_hash(chain_t chain, hash_t hash, header_t* out_header, uint64_t /*size_t*/* out_height);


// // Block ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_block_by_height(chain_t chain, uint64_t /*size_t*/ height, block_t* out_block, uint64_t /*size_t*/* out_height);

// BITPRIM_EXPORT
// void chain_fetch_block_by_hash(chain_t chain, void* ctx, hash_t hash, block_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_block_by_hash(chain_t chain, hash_t hash, block_t* out_block, uint64_t /*size_t*/* out_height);


// // Merkle Block ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_merkle_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, merkle_block_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_merkle_block_by_height(chain_t chain, uint64_t /*size_t*/ height, merkle_block_t* out_block, uint64_t /*size_t*/* out_height);

// BITPRIM_EXPORT
// void chain_fetch_merkle_block_by_hash(chain_t chain, void* ctx, hash_t hash, merkle_block_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_merkle_block_by_hash(chain_t chain, hash_t hash, merkle_block_t* out_block, uint64_t /*size_t*/* out_height);


// // Compact Block ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_compact_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, compact_block_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_compact_block_by_height(chain_t chain, uint64_t /*size_t*/ height, compact_block_t* out_block, uint64_t /*size_t*/* out_height);

// BITPRIM_EXPORT
// void chain_fetch_compact_block_by_hash(chain_t chain, void* ctx, hash_t hash, compact_block_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_compact_block_by_hash(chain_t chain, hash_t hash, compact_block_t* out_block, uint64_t /*size_t*/* out_height);

// // Transaction ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_transaction(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_transaction(chain_t chain, hash_t hash, int require_confirmed, transaction_t* out_transaction, uint64_t /*size_t*/* out_height, uint64_t /*size_t*/* out_index);

// BITPRIM_EXPORT
// void chain_fetch_transaction_position(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_transaction_position(chain_t chain, hash_t hash, int require_confirmed, uint64_t /*size_t*/* out_position, uint64_t /*size_t*/* out_height);


// // Output  ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_output(chain_t chain, void* ctx, hash_t hash, uint32_t index, int require_confirmed, output_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_output(chain_t chain, hash_t hash, uint32_t index, int require_confirmed, output_t* out_output);

// // Spend ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_spend(chain_t chain, void* ctx, output_point_t op, spend_fetch_handler_t handler);

// // History ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_history(chain_t chain, void* ctx, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_history(chain_t chain, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_compact_list_t* out_history);


// // Stealth ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_stealth(chain_t chain, void* ctx, binary_t filter, uint64_t from_height, stealth_fetch_handler_t handler);

// //BITPRIM_EXPORT
// //void chain_fetch_stealth(const binary& filter, uint64_t /*size_t*/ from_height, stealth_fetch_handler handler);



// BITPRIM_EXPORT
// void chain_fetch_block_locator(chain_t chain, void* ctx, block_indexes_t heights, block_locator_fetch_handler_t handler);

// BITPRIM_EXPORT
// int chain_get_block_locator(chain_t chain, block_indexes_t heights, get_headers_ptr_t* out_headers);


// // ------------------------------------------------------------------
// //virtual void fetch_block_locator(const chain::block::indexes& heights, block_locator_fetch_handler handler) const = 0;
// //virtual void fetch_locator_block_hashes(get_blocks_const_ptr locator, const hash_digest& threshold, size_t limit, inventory_fetch_handler handler) const = 0;
// //virtual void fetch_locator_block_headers(get_headers_const_ptr locator, const hash_digest& threshold, size_t limit, locator_block_headers_fetch_handler handler) const = 0;
// //
// //// Transaction Pool.
// ////-------------------------------------------------------------------------
// //
// //virtual void fetch_template(merkle_block_fetch_handler handler) const = 0;
// //virtual void fetch_mempool(size_t count_limit, uint64_t minimum_fee, inventory_fetch_handler handler) const = 0;
// //
// //// Filters.
// ////-------------------------------------------------------------------------
// //
// //virtual void filter_blocks(get_data_ptr message, result_handler handler) const = 0;
// //virtual void filter_transactions(get_data_ptr message, result_handler handler) const = 0;
// // ------------------------------------------------------------------



// // Subscribers.
// //-------------------------------------------------------------------------

// //virtual void subscribe_blockchain(reorganize_handler&& handler) = 0;
// //virtual void subscribe_transaction(transaction_handler&& handler) = 0;


// BITPRIM_EXPORT
// void chain_subscribe_blockchain(chain_t chain, void* ctx, reorganize_handler_t handler);


// BITPRIM_EXPORT
// void chain_subscribe_transaction(chain_t chain, void* ctx, transaction_handler_t handler);


// // Organizers.
// //-------------------------------------------------------------------------

// //virtual void organize(block_const_ptr block, result_handler handler) = 0;
// //virtual void organize(transaction_const_ptr tx, result_handler handler) = 0;

// BITPRIM_EXPORT
// void chain_organize_block(chain_t chain, void* ctx, block_t block, result_handler_t handler);

// BITPRIM_EXPORT
// int chain_organize_block_sync(chain_t chain, block_t block);

// BITPRIM_EXPORT
// void chain_organize_transaction(chain_t chain, void* ctx, transaction_t transaction, result_handler_t handler);

// BITPRIM_EXPORT
// int chain_organize_transaction_sync(chain_t chain, transaction_t transaction);



// // ------------------------------------------------

// BITPRIM_EXPORT
// transaction_t hex_to_tx(char const* tx_hex);


// BITPRIM_EXPORT
// void chain_validate_tx(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler);


























// Persistent<Function> callback;

// // void chain_validate_tx(chain_t exec, transaction_t tx, run_handler_t handler) {
// // void chain_validate_tx(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler) {

// void chain_validate_tx_callback(int error, char* message) {
//     Isolate* isolate = Isolate::GetCurrent();

//     // printf("chain_validate_tx_callback - 1\n");

//     // printf("chain_validate_tx_callback - error:   %d\n", error);
//     // printf("chain_validate_tx_callback - message: %s\n", message);

// //    unsigned int const argc = 2;
// ////    Local<Value> argv[argc] = { Null(isolate), String::NewFromUtf8(isolate, "success") };
// //    Local<Value> argv[argc] = { Null(isolate), Number::New(isolate, error) };

//     unsigned int const argc = 2;
//     if (message == nullptr) {
//         message = "";
//     }
//     Local<Value> argv[argc] = { Number::New(isolate, error), String::NewFromUtf8(isolate, message) };



//     // printf("chain_validate_tx_callback - 2n");

//     Local<Function>::New(isolate, callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

//     // printf("chain_validate_tx_callback - 3\n");

//     callback.Reset();

//     // printf("chain_validate_tx_callback - 4\n");
// }

// void bitprim_chain_validate_tx(FunctionCallbackInfo<Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

//     // printf("bitprim_chain_validate_tx - 1\n");
//     if (args.Length() != 3) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     // printf("bitprim_chain_validate_tx - 2\n");

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     // printf("bitprim_chain_validate_tx - 3\n");

//     if ( ! args[1]->IsString()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     // printf("bitprim_chain_validate_tx - 4\n");

//     if ( ! args[2]->IsFunction()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//         return;
//     }

//     // printf("bitprim_chain_validate_tx - 5\n");

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     chain_t chain = (chain_t)vptr;

//     // printf("bitprim_chain_validate_tx - 6\n");


//     v8::String::Utf8Value tx_hex(args[1]->ToString());

//     // printf("bitprim_chain_validate_tx - 7\n");


//     callback.Reset(isolate, args[2].As<Function>());

//     // printf("bitprim_chain_validate_tx - 8\n");

//     auto tx = hex_to_tx(*tx_hex);

//     // printf("bitprim_chain_validate_tx - 9\n");

//     // printf("tx: %p\n", tx);

//     chain_validate_tx(chain, tx, chain_validate_tx_callback);

//     // printf("bitprim_chain_validate_tx - 10\n");

//     //TODO: free tx
// }


//    void resize(const v8::FunctionCallbackInfo<Value> &args) {
//        Isolate *isolate = Isolate::GetCurrent();
//        HandleScope scope(isolate);
//        Persistent<Function> callback;
//        callback.Reset(isolate, args[0].As<Function>())
//        const unsigned argc = 2;
//        Local<Value> argv[argc] = { Null(isolate), String::NewFromUtf8(isolate, "success") };
//        Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);
//        callback.Reset();
//    }

//-------------------

//Handle<Value> addEventListener(Arguments const& args) {
//    HandleScope scope;
//    if (!args[0]->IsFunction()) {
//        return ThrowException(Exception::TypeError(String::New("Wrong arguments")));
//    }
//
//    Persistent<Function> fn = Persistent<Function>::New(Handle<Function>::Cast(args[0]));
////    Local<Number> num = Number::New(registerListener(&callback, &fn));
//    Local<Number> num = Number::New(registerListener(&callback, *fn));
//
//    scope.Close(num);
//}
//
//void callback(int event, void* ctx ) {
//    HandleScope scope;
//    Local<Value> args[] = { Local<Value>::New(Number::New(event)) };
//    Persistent<Function> *func = static_cast<Persistent<Function> *>(context);
//    (* func)->Call((* func), 1, args);
//
//    scope.Close(Undefined());
//}

//-------------------


void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "executor_construct", bitprim_executor_construct);
    NODE_SET_METHOD(exports, "executor_destruct", bitprim_executor_destruct);
    NODE_SET_METHOD(exports, "executor_stop", bitprim_executor_stop);
    NODE_SET_METHOD(exports, "executor_initchain", bitprim_executor_initchain);
//    NODE_SET_METHOD(exports, "executor_run", bitprim_executor_run);
    NODE_SET_METHOD(exports, "executor_run_wait", bitprim_executor_run_wait);
    NODE_SET_METHOD(exports, "executor_get_chain", bitprim_executor_get_chain);
    
    
    
    // NODE_SET_METHOD(exports, "chain_validate_tx", bitprim_chain_validate_tx);
    // NODE_SET_METHOD(exports, "chain_get_last_height", bitprim_chain_get_last_height);
    NODE_SET_METHOD(exports, "chain_fetch_last_height", bitprim_chain_fetch_last_height);
}

NODE_MODULE(bitprim, init)

}  // namespace bitprim_ns
