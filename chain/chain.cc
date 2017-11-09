#include <node.h>

#include <bitprim/nodecint/chain/chain.h>

#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)

#include "chain.h"
#include "tools.h"

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

// ---------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------------------

// void chain_fetch_last_height(chain_t chain, void* ctx, last_height_fetch_handler_t handler);
// int chain_get_last_height(chain_t chain, uint64_t /*size_t*/* height);

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
    //callback->Dispose();

    // printf("chain_fetch_last_height_handler - 4\n");

    delete callback;

    // printf("chain_fetch_last_height_handler - 5\n");
}

// void chain_fetch_last_height(chain_t chain, void* ctx, last_height_fetch_handler_t handler);
void bitprim_chain_fetch_last_height(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

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


// void bitprim_chain_get_last_height(FunctionCallbackInfo<Value> const& args) {
//     Isolate* isolate = args.GetIsolate();

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











// ---------------------------------------------------------------------------------------------------------------------------------------


// void chain_fetch_block_height(chain_t chain, void* ctx, hash_t hash, block_height_fetch_handler_t handler);
// int chain_get_block_height(chain_t chain, hash_t hash, uint64_t /*size_t*/* height);
// typedef void (*block_height_fetch_handler_t)(chain_t, void*, int, uint64_t /*size_t*/ h);

void chain_fetch_block_height_handler(chain_t chain, void* ctx, int error, uint64_t h) {

    // printf("chain_fetch_block_height_handler - 1\n");
    // printf("chain_fetch_block_height_handler - error:   %d\n", error);
    // printf("chain_fetch_block_height_handler - h:       %d\n", h);

    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 2;
    Local<Value> argv[argc] = { Number::New(isolate, error), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_block_height(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    // if ( ! args[1]->IsString()) {
    if ( ! args[1]->IsUint8Array()) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    // printf("arr->Length() - error:   %d\n", arr->Length());

    if (arr->Length() != 32) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1, number of bytes")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    hash_t hash = to_native_hash(arr);

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_block_height(chain, callback, hash, chain_fetch_block_height_handler);
}







// // Block Header ---------------------------------------------------------------------

// void chain_fetch_block_header_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_header_fetch_handler_t handler);
// int chain_get_block_header_by_height(chain_t chain, uint64_t /*size_t*/ height, header_t* out_header, uint64_t /*size_t*/* out_height);
// typedef void (*block_header_fetch_handler_t)(chain_t, void*, int, header_t header, uint64_t /*size_t*/ h);

void chain_fetch_block_header_by_height_handler(chain_t chain, void* ctx, int error, header_t header, uint64_t h) {

    // printf("chain_fetch_block_header_by_height_handler - 1\n");
    // printf("chain_fetch_block_header_by_height_handler - error:   %d\n", error);
    // printf("chain_fetch_block_header_by_height_handler - header:  %p\n", header);
    // printf("chain_fetch_block_header_by_height_handler - h:       %d\n", h);

    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 3;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, header), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_block_header_by_height(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    
    uint64_t height = args[1]->IntegerValue();

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_block_header_by_height(chain, callback, height, chain_fetch_block_header_by_height_handler);
}
    
    



// void chain_fetch_block_header_by_hash(chain_t chain, void* ctx, hash_t hash, block_header_fetch_handler_t handler);
// int chain_get_block_header_by_hash(chain_t chain, hash_t hash, header_t* out_header, uint64_t /*size_t*/* out_height);

void chain_fetch_block_header_by_hash_handler(chain_t chain, void* ctx, int error, header_t header, uint64_t h) {

    // printf("chain_fetch_block_header_by_hash_handler - 1\n");
    // printf("chain_fetch_block_header_by_hash_handler - error:   %d\n", error);
    // printf("chain_fetch_block_header_by_hash_handler - header:  %p\n", header);
    // printf("chain_fetch_block_header_by_hash_handler - h:       %d\n", h);

    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 3;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, header), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_block_header_by_hash(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsUint8Array()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1, number of bytes")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    hash_t hash = to_native_hash(arr);
    
    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_block_header_by_hash(chain, callback, hash, chain_fetch_block_header_by_hash_handler);
}
    



// // Block ---------------------------------------------------------------------
// void chain_fetch_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_fetch_handler_t handler);
// int chain_get_block_by_height(chain_t chain, uint64_t /*size_t*/ height, block_t* out_block, uint64_t /*size_t*/* out_height);
// typedef void (*block_fetch_handler_t)(chain_t, void*, int, block_t block, uint64_t /*size_t*/ h);


void chain_fetch_block_by_height_handler(chain_t chain, void* ctx, int error, block_t block, uint64_t h) {

    // printf("chain_fetch_block_by_height_handler - 1\n");
    // printf("chain_fetch_block_by_height_handler - error:   %d\n", error);
    // printf("chain_fetch_block_by_height_handler - block:  %p\n", block);
    // printf("chain_fetch_block_by_height_handler - h:       %d\n", h);

    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 3;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, block), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_block_by_height(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    
    uint64_t height = args[1]->IntegerValue();

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_block_by_height(chain, callback, height, chain_fetch_block_by_height_handler);
}
    

// void chain_fetch_block_by_hash(chain_t chain, void* ctx, hash_t hash, block_fetch_handler_t handler);
// int chain_get_block_by_hash(chain_t chain, hash_t hash, block_t* out_block, uint64_t /*size_t*/* out_height);
void chain_fetch_block_by_hash_handler(chain_t chain, void* ctx, int error, block_t block, uint64_t h) {

    // printf("chain_fetch_block_by_hash_handler - 1\n");
    // printf("chain_fetch_block_by_hash_handler - error:   %d\n", error);
    // printf("chain_fetch_block_by_hash_handler - block:  %p\n", block);
    // printf("chain_fetch_block_by_hash_handler - h:       %d\n", h);

    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 3;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, block), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_block_by_hash(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsUint8Array()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1, number of bytes")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    hash_t hash = to_native_hash(arr);
    
    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_block_by_hash(chain, callback, hash, chain_fetch_block_by_hash_handler);
}
    
    




// // Merkle Block ---------------------------------------------------------------------
// void chain_fetch_merkle_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, merkle_block_fetch_handler_t handler);
// int chain_get_merkle_block_by_height(chain_t chain, uint64_t /*size_t*/ height, merkle_block_t* out_block, uint64_t /*size_t*/* out_height);
// typedef void (*merkle_block_fetch_handler_t)(chain_t, void*, int, merkle_block_t block, uint64_t /*size_t*/ h);


void chain_fetch_merkle_block_by_height_handler(chain_t chain, void* ctx, int error, merkle_block_t merkle_block, uint64_t h) {

    // printf("chain_fetch_merkle_block_by_height_handler - 1\n");
    // printf("chain_fetch_merkle_block_by_height_handler - error:   %d\n", error);
    // printf("chain_fetch_merkle_block_by_height_handler - merkle_block:  %p\n", merkle_block);
    // printf("chain_fetch_merkle_block_by_height_handler - h:       %d\n", h);

    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 3;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, merkle_block), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_merkle_block_by_height(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    
    uint64_t height = args[1]->IntegerValue();

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_merkle_block_by_height(chain, callback, height, chain_fetch_merkle_block_by_height_handler);
}
    


// void chain_fetch_merkle_block_by_hash(chain_t chain, void* ctx, hash_t hash, merkle_block_fetch_handler_t handler);
// int chain_get_merkle_block_by_hash(chain_t chain, hash_t hash, merkle_block_t* out_merkle_block, uint64_t /*size_t*/* out_height);

void chain_fetch_merkle_block_by_hash_handler(chain_t chain, void* ctx, int error, merkle_block_t merkle_block, uint64_t h) {

    // printf("chain_fetch_merkle_block_by_hash_handler - 1\n");
    // printf("chain_fetch_merkle_block_by_hash_handler - error:   %d\n", error);
    // printf("chain_fetch_merkle_block_by_hash_handler - merkle_block:  %p\n", merkle_block);
    // printf("chain_fetch_merkle_block_by_hash_handler - h:       %d\n", h);

    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 3;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, merkle_block), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_merkle_block_by_hash(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsUint8Array()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1, number of bytes")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    hash_t hash = to_native_hash(arr);
    
    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_merkle_block_by_hash(chain, callback, hash, chain_fetch_merkle_block_by_hash_handler);
}
    
    
    





// // Compact Block ---------------------------------------------------------------------
// void chain_fetch_compact_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, compact_block_fetch_handler_t handler);
// int chain_get_compact_block_by_height(chain_t chain, uint64_t /*size_t*/ height, compact_block_t* out_block, uint64_t /*size_t*/* out_height);
// typedef void (*compact_block_fetch_handler_t)(chain_t, void*, int, compact_block_t block, uint64_t /*size_t*/ h);


void chain_fetch_compact_block_by_height_handler(chain_t chain, void* ctx, int error, compact_block_t compact_block, uint64_t h) {

    // printf("chain_fetch_compact_block_by_height_handler - 1\n");
    // printf("chain_fetch_compact_block_by_height_handler - error:   %d\n", error);
    // printf("chain_fetch_compact_block_by_height_handler - compact_block:  %p\n", compact_block);
    // printf("chain_fetch_compact_block_by_height_handler - h:       %d\n", h);

    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 3;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, compact_block), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_compact_block_by_height(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    
    uint64_t height = args[1]->IntegerValue();

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_compact_block_by_height(chain, callback, height, chain_fetch_compact_block_by_height_handler);
}
    

// void chain_fetch_compact_block_by_hash(chain_t chain, void* ctx, hash_t hash, compact_block_fetch_handler_t handler);
// int chain_get_compact_block_by_hash(chain_t chain, hash_t hash, compact_block_t* out_compact_block, uint64_t /*size_t*/* out_height);

void chain_fetch_compact_block_by_hash_handler(chain_t chain, void* ctx, int error, compact_block_t compact_block, uint64_t h) {

    // printf("chain_fetch_compact_block_by_hash_handler - 1\n");
    // printf("chain_fetch_compact_block_by_hash_handler - error:   %d\n", error);
    // printf("chain_fetch_compact_block_by_hash_handler - compact_block:  %p\n", compact_block);
    // printf("chain_fetch_compact_block_by_hash_handler - h:       %d\n", h);

    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 3;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, compact_block), Number::New(isolate, h) };

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_compact_block_by_hash(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsUint8Array()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1, number of bytes")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    hash_t hash = to_native_hash(arr);
    
    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_compact_block_by_hash(chain, callback, hash, chain_fetch_compact_block_by_hash_handler);
}
    
    
    
    


// // Transaction ---------------------------------------------------------------------
// void chain_fetch_transaction(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler);
// int chain_get_transaction(chain_t chain, hash_t hash, int require_confirmed, transaction_t* out_transaction, uint64_t /*size_t*/* out_height, uint64_t /*size_t*/* out_index);
// typedef void (*transaction_fetch_handler_t)(chain_t, void*, int, transaction_t transaction, uint64_t i, uint64_t h);
 

void chain_fetch_transaction_handler(chain_t chain, void* ctx, int error, transaction_t transaction, uint64_t i, uint64_t h) {

    printf("chain_fetch_transaction_handler - 1\n");
    printf("chain_fetch_transaction_handler - error:   %d\n", error);
    printf("chain_fetch_transaction_handler - transaction:  %p\n", transaction);
    printf("chain_fetch_transaction_handler - i:       %d\n", i);
    printf("chain_fetch_transaction_handler - h:       %d\n", h);
    
    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 4;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, transaction), Number::New(isolate, i), Number::New(isolate, h)};

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_transaction(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 4) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsUint8Array()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsBoolean()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }


    if ( ! args[3]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 3")));
        return;
    }    

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1, number of bytes")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    hash_t hash = to_native_hash(arr);
    bool require_confirmed = args[2]->BooleanValue();
    
    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[3].As<Function>());

    chain_fetch_transaction(chain, callback, hash, require_confirmed, chain_fetch_transaction_handler);
}
    
// // Transaction Position ---------------------------------------------------------------------
// void chain_fetch_transaction_position(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler);
// int chain_get_transaction_position(chain_t chain, hash_t hash, int require_confirmed, uint64_t /*size_t*/* out_position, uint64_t /*size_t*/* out_height);
// typedef void (*transaction_index_fetch_handler_t)(chain_t, void*, int, uint64_t position, uint64_t height);



void chain_fetch_transaction_position_handler(chain_t chain, void* ctx, int error, uint64_t i, uint64_t h) {

    printf("chain_fetch_transaction_position_handler - 1\n");
    printf("chain_fetch_transaction_position_handler - error:   %d\n", error);
    printf("chain_fetch_transaction_position_handler - i:       %d\n", i);
    printf("chain_fetch_transaction_position_handler - h:       %d\n", h);
    
    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 3;
    Local<Value> argv[argc] = { Number::New(isolate, error), Number::New(isolate, i), Number::New(isolate, h)};

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_transaction_position(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 4) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }
    
    if ( ! args[1]->IsUint8Array()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsBoolean()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }


    if ( ! args[3]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 3")));
        return;
    }    

    v8::Local<v8::Uint8Array> arr = v8::Local<v8::Uint8Array>::Cast(args[1]);

    if (arr->Length() != 32) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1, number of bytes")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    hash_t hash = to_native_hash(arr);
    bool require_confirmed = args[2]->BooleanValue();
    
    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[3].As<Function>());

    chain_fetch_transaction_position(chain, callback, hash, require_confirmed, chain_fetch_transaction_position_handler);
}






// // Spend ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_spend(chain_t chain, void* ctx, output_point_t op, spend_fetch_handler_t handler);
// typedef void (*spend_fetch_handler_t)(chain_t, void*, int, input_point_t input_point);


void chain_fetch_spend_handler(chain_t chain, void* ctx, int error, input_point_t input_point) {

    printf("chain_fetch_spend_handler - 1\n");
    printf("chain_fetch_spend_handler - error:   %d\n", error);
    printf("chain_fetch_spend_handler - input_point:  %p\n", input_point);
    
    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 2;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, input_point)};

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_spend(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }

    if ( ! args[1]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    


    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    void* op_vptr = v8::External::Cast(*args[1])->Value();
    output_point_t op = (output_point_t)op_vptr;
    
    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_fetch_spend(chain, callback, op, chain_fetch_spend_handler);
}



// // History ---------------------------------------------------------------------
// void chain_fetch_history(chain_t chain, void* ctx, payment_address_t address, uint64_t limit, uint64_t from_height, history_fetch_handler_t handler);
// int chain_get_history(chain_t chain, payment_address_t address, uint64_t limit, uint64_t from_height, history_compact_list_t* out_history);
// typedef void (*history_fetch_handler_t)(chain_t, void*, int, history_compact_list_t history);

void chain_fetch_history_handler(chain_t chain, void* ctx, int error, history_compact_list_t history) {

    printf("chain_fetch_history_handler - 1\n");
    printf("chain_fetch_history_handler - error:   %d\n", error);
    printf("chain_fetch_history_handler - history:  %p\n", history);
    
    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 2;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, history)};

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_history(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 5) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }

    if ( ! args[1]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }
    
    if ( ! args[2]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }

    if ( ! args[3]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 3")));
        return;
    }

    if ( ! args[4]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    void* address_vptr = v8::External::Cast(*args[1])->Value();
    payment_address_t address = (payment_address_t)address_vptr;
    
    uint64_t limit = args[2]->IntegerValue();
    uint64_t from_height = args[3]->IntegerValue();

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[4].As<Function>());

    chain_fetch_history(chain, callback, address, limit, from_height, chain_fetch_history_handler);
}

    

// // Stealth ---------------------------------------------------------------------
// BITPRIM_EXPORT
// void chain_fetch_stealth(chain_t chain, void* ctx, binary_t filter, uint64_t from_height, stealth_fetch_handler_t handler);
// typedef void (*stealth_fetch_handler_t)(chain_t chain, void*, int, stealth_compact_list_t stealth);


void chain_fetch_stealth_handler(chain_t chain, void* ctx, int error, stealth_compact_list_t stealth) {

    printf("chain_fetch_stealth_handler - 1\n");
    printf("chain_fetch_stealth_handler - error:   %d\n", error);
    printf("chain_fetch_stealth_handler - stealth:  %p\n", stealth);
    
    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 2;
    Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, stealth)};

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_fetch_stealth(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // chain_t chain, binary_t filter, uint64_t from_height, stealth_fetch_handler_t handler

    if (args.Length() != 4) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }

    if ( ! args[1]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }
    
    if ( ! args[2]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }

    if ( ! args[3]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    void* filter_vptr = v8::External::Cast(*args[1])->Value();
    binary_t filter = (binary_t)filter_vptr;
    
    uint64_t from_height = args[2]->IntegerValue();

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[3].As<Function>());

    chain_fetch_stealth(chain, callback, filter, from_height, chain_fetch_stealth_handler);
}

    


// // // Block Locator ---------------------------------------------------------------------

// // void chain_fetch_block_locator(chain_t chain, void* ctx, block_indexes_t heights, block_locator_fetch_handler_t handler);
// // int chain_get_block_locator(chain_t chain, block_indexes_t heights, get_headers_ptr_t* out_headers);
// // typedef void (*block_locator_fetch_handler_t)(chain_t, void*, int, get_headers_ptr_t);

// void chain_fetch_block_locator_handler(chain_t chain, void* ctx, int error, get_headers_ptr_t headers) {

//     printf("chain_fetch_block_locator_handler - 1\n");
//     printf("chain_fetch_block_locator_handler - error:   %d\n", error);
//     printf("chain_fetch_block_locator_handler - headers:  %p\n", headers);
    
//     Isolate* isolate = Isolate::GetCurrent();

//     unsigned int const argc = 2;
//     Local<Value> argv[argc] = { Number::New(isolate, error), External::New(isolate, headers)};

//     Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

//     Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

//     callback->Reset();
//     //callback->Dispose();
//     delete callback;
// }

// void bitprim_chain_fetch_block_locator(FunctionCallbackInfo<Value> const& args) {
//     Isolate* isolate = args.GetIsolate();


//     // chain_t chain, block_indexes_t heights, block_locator_fetch_handler_t handler)

//     if (args.Length() != 3) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//         return;
//     }

//     if ( ! args[0]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
//         return;
//     }

//     if ( ! args[1]->IsExternal()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
//         return;
//     }

//     if ( ! args[2]->IsFunction()) {
//         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
//         return;
//     }    

//     void* vptr = v8::External::Cast(*args[0])->Value();
//     chain_t chain = (chain_t)vptr;

//     void* heights_vptr = v8::External::Cast(*args[1])->Value();
//     block_indexes_t heights = (block_indexes_t)heights_vptr;

//     Persistent<Function>* callback = new Persistent<Function>;
//     callback->Reset(isolate, args[2].As<Function>());

//     chain_fetch_block_locator(chain, callback, heights, chain_fetch_block_locator_handler);
// }

    


// // Organizers.
// //-------------------------------------------------------------------------

// void chain_organize_block(chain_t chain, void* ctx, block_t block, result_handler_t handler);
// int chain_organize_block_sync(chain_t chain, block_t block);
// typedef void (*result_handler_t)(chain_t, void*, int);

void chain_organize_block_handler(chain_t chain, void* ctx, int error) {

    printf("chain_organize_block_handler - 1\n");
    printf("chain_organize_block_handler - error:   %d\n", error);
    
    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 1;
    Local<Value> argv[argc] = { Number::New(isolate, error)};

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_organize_block(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // chain_t chain, block_t block, result_handler_t handler

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }

    if ( ! args[1]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    void* block_vptr = v8::External::Cast(*args[1])->Value();
    block_t block = (block_t)block_vptr;

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_organize_block(chain, callback, block, chain_organize_block_handler);
}


// void chain_organize_transaction(chain_t chain, void* ctx, transaction_t transaction, result_handler_t handler);
// int chain_organize_transaction_sync(chain_t chain, transaction_t transaction);
// typedef void (*result_handler_t)(chain_t, void*, int);


void chain_organize_transaction_handler(chain_t chain, void* ctx, int error) {

    printf("chain_organize_transaction_handler - 1\n");
    printf("chain_organize_transaction_handler - error:   %d\n", error);
    
    Isolate* isolate = Isolate::GetCurrent();

    unsigned int const argc = 1;
    Local<Value> argv[argc] = { Number::New(isolate, error)};

    Persistent<Function>* callback = static_cast<Persistent<Function>*>(ctx);

    Local<Function>::New(isolate, *callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    callback->Reset();
    //callback->Dispose();
    delete callback;
}

void bitprim_chain_organize_transaction(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    // chain_t chain, transaction_t transaction, result_handler_t handler

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 0")));
        return;
    }

    if ( ! args[1]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 1")));
        return;
    }

    if ( ! args[2]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments, 2")));
        return;
    }    

    void* vptr = v8::External::Cast(*args[0])->Value();
    chain_t chain = (chain_t)vptr;

    void* transaction_vptr = v8::External::Cast(*args[1])->Value();
    transaction_t transaction = (transaction_t)transaction_vptr;

    Persistent<Function>* callback = new Persistent<Function>;
    callback->Reset(isolate, args[2].As<Function>());

    chain_organize_transaction(chain, callback, transaction, chain_organize_transaction_handler);
}
    


// // Subscribers.
// //-------------------------------------------------------------------------

// BITPRIM_EXPORT
// void chain_subscribe_blockchain(chain_t chain, void* ctx, reorganize_handler_t handler);

// BITPRIM_EXPORT
// void chain_subscribe_transaction(chain_t chain, void* ctx, transaction_handler_t handler);



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


}  // namespace bitprim_ns
