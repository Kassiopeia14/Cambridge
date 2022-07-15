#include "SHA256GeneratorWrap.h"

SHA256GeneratorWrap::SHA256GeneratorWrap():
	generator()
{
}

SHA256GeneratorWrap::~SHA256GeneratorWrap()
{
}

void SHA256GeneratorWrap::create(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::Isolate* isolate = args.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    if (args.IsConstructCall()) {

        SHA256GeneratorWrap* wrapObject = new SHA256GeneratorWrap();
        node::AddEnvironmentCleanupHook(isolate, SHA256GeneratorWrap::destroy, wrapObject);

        wrapObject->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
}

void SHA256GeneratorWrap::destroy(void* arg)
{
    SHA256GeneratorWrap* wrapObject = (SHA256GeneratorWrap*)arg;
    delete wrapObject;
}

void SHA256GeneratorWrap::generate(const v8::FunctionCallbackInfo<v8::Value>& args)
{

    v8::Isolate* isolate = args.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    SHA256GeneratorWrap* wrapObject = node::ObjectWrap::Unwrap<SHA256GeneratorWrap>(args.Holder());

    v8::Local<v8::String> dataLocal = args[0].As<v8::String>();
    size_t dataLength = dataLocal->Length();
    char* buffer = new char[dataLength];
    (*dataLocal)->WriteUtf8(isolate, buffer);
    std::string data(buffer, buffer + dataLength);
    std::string sha256 = wrapObject->generator.generate(data);

    v8::Local<v8::String> result = v8::String::NewFromUtf8(isolate, (char*)sha256.c_str(), v8::NewStringType::kNormal, sha256.length()).ToLocalChecked();

    if(args.Length() > 1)
    {
        v8::Local<v8::Object> callbackObject = args[1].As<v8::Object>();
        v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(callbackObject);

        const unsigned argc = 1;
        v8::Local<v8::Value> argv[argc] =
        {
            result
        };

        callback->Call(context, v8::Null(isolate), argc, argv).ToLocalChecked();
    }
    else
    {
        args.GetReturnValue().Set(result);
    }
}
