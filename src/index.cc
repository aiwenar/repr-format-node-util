#include <node.h>

namespace repr_format {

using v8::FunctionCallbackInfo;
using v8::Local;
using v8::Object;
using v8::Value;
using v8::Isolate;
using v8::Exception;
using v8::Proxy;
using v8::String;

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

void initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "inspectProxy", inspectProxy);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, initialize)

}
