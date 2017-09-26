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

    printf("chain_fetch_last_height_handler - 1\n");

    printf("chain_fetch_last_height_handler - error:   %d\n", error);
    printf("chain_fetch_last_height_handler - h:       %d\n", h);

    unsigned int const argc = 2;
    Local<Value> argv[argc] = { Number::New(isolate, error), Number::New(isolate, h) };

    printf("chain_fetch_last_height_handler - 2n");

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    printf("chain_fetch_last_height_handler - 3\n");

    callback->Reset();

    printf("chain_fetch_last_height_handler - 4\n");

    delete callback;

    printf("chain_fetch_last_height_handler - 5\n");
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
