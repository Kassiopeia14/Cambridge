#include "SHA256GeneratorWrap.h"

void InitSHA256GeneratorWrap(v8::Local<v8::Object> exports, v8::Local<v8::Context>& context, v8::Isolate* isolate, v8::Local<v8::Object>& moduleData)
{
    v8::Local<v8::FunctionTemplate> constructorTemplate = v8::FunctionTemplate::New(isolate, SHA256GeneratorWrap::create, moduleData);
    constructorTemplate->SetClassName(v8::String::NewFromUtf8(isolate, "SHA256Generator").ToLocalChecked());
    constructorTemplate->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "generate", SHA256GeneratorWrap::generate);

    v8::Local<v8::Function> constructor = constructorTemplate->GetFunction(context).ToLocalChecked();
    moduleData->SetInternalField(0, constructor);
    exports->Set(context, v8::String::NewFromUtf8(isolate, "SHA256Generator").ToLocalChecked(), constructor).FromJust();
}

NODE_MODULE_INIT(/* exports, module, context */)
{
    v8::Isolate* isolate = context->GetIsolate();

    v8::Local<v8::ObjectTemplate> moduleDataTemplate = v8::ObjectTemplate::New(isolate);
    moduleDataTemplate->SetInternalFieldCount(1);
    v8::Local<v8::Object> moduleData = moduleDataTemplate->NewInstance(context).ToLocalChecked();

    InitSHA256GeneratorWrap(exports, context, isolate, moduleData);
}