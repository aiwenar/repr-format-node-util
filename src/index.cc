#include <node.h>

namespace repr_format {

using v8::Array;
using v8::FunctionCallbackInfo;
using v8::Local;
using v8::Object;
using v8::Value;
using v8::Isolate;
using v8::Exception;
using v8::Proxy;
using v8::String;
using v8::Promise;

void inspectProxy(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
        return;
    }

    if (args[0]->IsProxy()) {
        args.GetReturnValue().Set(args[0].As<Proxy>()->GetTarget());
    }
}

void inspectPromise(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
        return;
    }

    if (args[0]->IsPromise()) {
        auto promise = args[0].As<Promise>();
        Local<Value> state;
        Local<Value> value;
        switch (promise->State()) {
        case Promise::kPending:
            state = String::NewFromUtf8(isolate, "pending").ToLocalChecked();
            value = v8::Undefined(isolate);
            break;

        case Promise::kFulfilled:
            state = String::NewFromUtf8(isolate, "resolved").ToLocalChecked();
            value = promise->Result();
            break;

        case Promise::kRejected:
            state = String::NewFromUtf8(isolate, "rejected").ToLocalChecked();
            value = promise->Result();
            break;
        }

        Local<Value> result[2] = {state, value};
        args.GetReturnValue().Set(Array::New(isolate, result, 2));
    }
}

void initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "inspectProxy", inspectProxy);
    NODE_SET_METHOD(exports, "inspectPromise", inspectPromise);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, initialize)

}
