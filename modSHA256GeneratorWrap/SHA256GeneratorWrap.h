#pragma once

#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include <node_object_wrap.h>

#include "../modSHA256Generator/SHA256Generator.h"

class SHA256GeneratorWrap : public node::ObjectWrap
{
public:
	SHA256GeneratorWrap();
	~SHA256GeneratorWrap();

	static void create(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void destroy(void* arg);

	static void generate(const v8::FunctionCallbackInfo<v8::Value>& args);

private:

	SHA256Generator generator;

};