#include <string.h>
#include <stdlib.h>

#include <node.h>

#include <kth/c-api/wallet/word_list.h>

#include "word_list.h"

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


void kth_wallet_word_list_construct(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 0) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    word_list_t res = word_list_construct();
    args.GetReturnValue().Set(External::New(isolate, res));
}

void kth_wallet_word_list_destruct(v8::FunctionCallbackInfo<v8::Value> const& args) {
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
    word_list_t word_list = (word_list_t)vptr;

    word_list_destruct(word_list);
}

void kth_wallet_word_list_push_back(v8::FunctionCallbackInfo<v8::Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if ( ! args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    if ( ! args[1]->IsString()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    word_list_t word_list = (word_list_t)vptr;

    v8::String::Utf8Value word(args[0]->ToString());

    word_list_add_word(word_list, *word);
}

}  // namespace kth_native
