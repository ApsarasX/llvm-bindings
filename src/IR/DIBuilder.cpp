#include "IR/IR.h"
#include "Util/Util.h"

void DIBuilder::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DIBuilder", {
            InstanceMethod("createFile", &DIBuilder::createFile),
            InstanceMethod("createCompileUnit", &DIBuilder::createCompileUnit),
            InstanceMethod("createFunction", &DIBuilder::createFunction),
            InstanceMethod("createLexicalBlock", &DIBuilder::createLexicalBlock),
            InstanceMethod("createBasicType", &DIBuilder::createBasicType),
            InstanceMethod("getOrCreateTypeArray", &DIBuilder::getOrCreateTypeArray),
            InstanceMethod("createSubroutineType", &DIBuilder::createSubroutineType),
            InstanceMethod("createExpression", &DIBuilder::createExpression),
            InstanceMethod("createParameterVariable", &DIBuilder::createParameterVariable),
            InstanceMethod("createAutoVariable", &DIBuilder::createAutoVariable),
            InstanceMethod("createGlobalVariableExpression", &DIBuilder::createGlobalVariableExpression),
            InstanceMethod("insertDeclare", &DIBuilder::insertDeclare),
            InstanceMethod("insertDbgValueIntrinsic", &DIBuilder::insertDbgValueIntrinsic),
            InstanceMethod("finalizeSubprogram", &DIBuilder::finalizeSubprogram),
            InstanceMethod("finalize", &DIBuilder::finalize),

    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("DIBuilder", func);
}

Napi::Value DIBuilder::New(Napi::Env env, llvm::DIBuilder *builder) {
    return constructor.New({Napi::External<llvm::DIBuilder>::New(env, builder)});
}

bool DIBuilder::IsClassOf(const Napi::Value &value) {
    return value.IsNull() || value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::DIBuilder *DIBuilder::Extract(const Napi::Value &value) {
    if (value.IsNull()) {
        return nullptr;
    }
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

DIBuilder::DIBuilder(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1) {
        if (info[0].IsExternal()) {
            auto external = info[0].As<Napi::External<llvm::DIBuilder>>();
            builder = external.Data();
            return;
        } else if (Module::IsClassOf(info[0])) {
            llvm::Module *module = Module::Extract(info[0]);
            builder = new llvm::DIBuilder(*module);
            return;
        }
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::constructor);
}

llvm::DIBuilder *DIBuilder::getLLVMPrimitive() {
    return builder;
}

Napi::Value DIBuilder::createFile(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 2 && info[0].IsString() && info[1].IsString()) {
        const std::string &filename = info[0].As<Napi::String>();
        const std::string &directory = info[1].As<Napi::String>();
        return DIFile::New(env, builder->createFile(filename, directory));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::createFile);
}

Napi::Value DIBuilder::createCompileUnit(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 6
        && info[0].IsNumber()
        && DIFile::IsClassOf(info[1])
        && info[2].IsString()
        && info[3].IsBoolean()
        && info[4].IsString()
        && info[5].IsNumber()) {
        unsigned lang = info[0].As<Napi::Number>();
        llvm::DIFile *file = DIFile::Extract(info[1]);
        const std::string &producer = info[2].As<Napi::String>();
        bool isOptimized = info[3].As<Napi::Boolean>();
        const std::string &flags = info[4].As<Napi::String>();
        unsigned rv = info[5].As<Napi::Number>();
        llvm::DICompileUnit *unit = builder->createCompileUnit(lang, file, producer, isOptimized, flags, rv);
        return DICompileUnit::New(env, unit);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::createCompileUnit);
}

Napi::Value DIBuilder::createFunction(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 9
        && DIScope::IsClassOf(info[0])
        && info[1].IsString()
        && info[2].IsString()
        && DIFile::IsClassOf(info[3])
        && info[4].IsNumber()
        && DISubroutineType::IsClassOf(info[5])
        && info[6].IsNumber()
        && info[7].IsNumber()
        && info[8].IsNumber()) {
        llvm::DIScope *scope = DIScope::Extract(info[0]);
        const std::string &name = info[1].As<Napi::String>();
        const std::string &linkage = info[2].As<Napi::String>();
        llvm::DIFile *file = DIFile::Extract(info[3]);
        unsigned line = info[4].As<Napi::Number>();
        llvm::DISubroutineType *type = DISubroutineType::Extract(info[5]);
        unsigned scopeLine = info[6].As<Napi::Number>();
        unsigned flagsNum = info[7].As<Napi::Number>();
        unsigned spFlagsNum = info[8].As<Napi::Number>();
        auto flags = llvm::DINode::DIFlags(flagsNum);
        auto spFlags = llvm::DISubprogram::DISPFlags(spFlagsNum);
        llvm::DISubprogram *subprogram = builder->createFunction(scope, name, linkage, file, line, type, scopeLine, flags, spFlags);
        return DISubprogram::New(env, subprogram);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::createFunction);
}

Napi::Value DIBuilder::createLexicalBlock(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 4
        && DIScope::IsClassOf(info[0])
        && DIFile::IsClassOf(info[1])
        && info[2].IsNumber()
        && info[3].IsNumber()) {
        llvm::DIScope *scope = DIScope::Extract(info[0]);
        llvm::DIFile *file = DIFile::Extract(info[1]);
        unsigned line = info[2].As<Napi::Number>();
        unsigned column = info[3].As<Napi::Number>();
        llvm::DILexicalBlock *block = builder->createLexicalBlock(scope, file, line, column);
        return DILexicalBlock::New(env, block);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::createLexicalBlock);
}

Napi::Value DIBuilder::createBasicType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 3 && info[0].IsString() && info[1].IsNumber() && info[2].IsNumber()) {
        const std::string &name = info[0].As<Napi::String>();
        unsigned sizeInBits = info[1].As<Napi::Number>();
        unsigned encoding = info[2].As<Napi::Number>();
        llvm::DIBasicType *type = builder->createBasicType(name, sizeInBits, encoding);
        return DIBasicType::New(env, type);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::createBasicType);
}

Napi::Value DIBuilder::getOrCreateTypeArray(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && info[0].IsArray()) {
        auto elementArray = info[0].As<Napi::Array>();
        unsigned numElements = elementArray.Length();
        std::vector<llvm::Metadata *> elements(numElements);
        for (unsigned i = 0; i < numElements; ++i) {
            elements[i] = Metadata::Extract(elementArray.Get(i));
        }
        llvm::DITypeRefArray typeRefArray = builder->getOrCreateTypeArray(elements);
        return DITypeRefArray::New(env, new llvm::DITypeRefArray(typeRefArray.get()));
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::getOrCreateTypeArray);
}

Napi::Value DIBuilder::createSubroutineType(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && DITypeRefArray::IsClassOf(info[0])) {
        llvm::DITypeRefArray *paramTypes = DITypeRefArray::Extract(info[0]);
        llvm::DISubroutineType *type = builder->createSubroutineType(*paramTypes);
        return DISubroutineType::New(env, type);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::createSubroutineType);
}

Napi::Value DIBuilder::createExpression(const Napi::CallbackInfo &info) {
    llvm::DIExpression *expression = builder->createExpression();
    return DIExpression::New(info.Env(), expression);
}

Napi::Value DIBuilder::createParameterVariable(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    llvm::DILocalVariable *variable = nullptr;
    if (argsLen >= 6
        && DIScope::IsClassOf(info[0])
        && info[1].IsString()
        && info[2].IsNumber()
        && DIFile::IsClassOf(info[3])
        && info[4].IsNumber()
        && DIType::IsClassOf(info[5])) {
        llvm::DIScope *scope = DIScope::Extract(info[0]);
        const std::string &name = info[1].As<Napi::String>();
        unsigned argNo = info[2].As<Napi::Number>();
        llvm::DIFile *file = DIFile::Extract(info[3]);
        unsigned line = info[4].As<Napi::Number>();
        llvm::DIType *type = DIType::Extract(info[5]);
        if (argsLen == 6) {
            variable = builder->createParameterVariable(scope, name, argNo, file, line, type);
        } else if (argsLen == 7 && info[6].IsBoolean()) {
            bool alwaysPreserve = info[6].As<Napi::Boolean>();
            variable = builder->createParameterVariable(scope, name, argNo, file, line, type, alwaysPreserve);
        }
    }
    if (variable) {
        return DILocalVariable::New(env, variable);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::createParameterVariable);
}

Napi::Value DIBuilder::createAutoVariable(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    llvm::DILocalVariable *variable = nullptr;
    if (argsLen >= 5
        && DIScope::IsClassOf(info[0])
        && info[1].IsString()
        && DIFile::IsClassOf(info[2])
        && info[3].IsNumber()
        && DIType::IsClassOf(info[4])) {
        llvm::DIScope *scope = DIScope::Extract(info[0]);
        const std::string &name = info[1].As<Napi::String>();
        llvm::DIFile *file = DIFile::Extract(info[2]);
        unsigned line = info[3].As<Napi::Number>();
        llvm::DIType *type = DIType::Extract(info[4]);
        if (argsLen == 5) {
            variable = builder->createAutoVariable(scope, name, file, line, type);
        } else if (argsLen == 6 && info[5].IsBoolean()) {
            bool alwaysPreserve = info[5].As<Napi::Boolean>();
            variable = builder->createAutoVariable(scope, name, file, line, type, alwaysPreserve);
        }
    }
    if (variable) {
        return DILocalVariable::New(env, variable);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::createAutoVariable);
}

Napi::Value DIBuilder::createGlobalVariableExpression(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 7
        && DIScope::IsClassOf(info[0])
        && info[1].IsString()
        && info[2].IsString()
        && DIFile::IsClassOf(info[3])
        && info[4].IsNumber()
        && DIType::IsClassOf(info[5])
        && info[6].IsBoolean()) {
        llvm::DIScope *scope = DIScope::Extract(info[0]);
        const std::string &name = info[1].As<Napi::String>();
        const std::string &linkage = info[2].As<Napi::String>();
        llvm::DIFile *file = DIFile::Extract(info[3]);
        unsigned line = info[4].As<Napi::Number>();
        llvm::DIType *type = DIType::Extract(info[5]);
        bool IsLocalToUnit = info[6].As<Napi::Boolean>();
        llvm::DIGlobalVariableExpression *variable = builder->createGlobalVariableExpression(scope, name, linkage, file, line, type, IsLocalToUnit);
        return DIGlobalVariableExpression::New(env, variable);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::createGlobalVariableExpression);
}

Napi::Value DIBuilder::insertDeclare(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Instruction *instruction = nullptr;
    if (info.Length() == 5
        && Value::IsClassOf(info[0])
        && DILocalVariable::IsClassOf(info[1])
        && DIExpression::IsClassOf(info[2])
        && DILocation::IsClassOf(info[3])) {
        llvm::Value *storage = Value::Extract(info[0]);
        llvm::DILocalVariable *variable = DILocalVariable::Extract(info[1]);
        llvm::DIExpression *expr = DIExpression::Extract(info[2]);
        llvm::DILocation *location = DILocation::Extract(info[3]);
        if (BasicBlock::IsClassOf(info[4])) {
            llvm::BasicBlock *insertBB = BasicBlock::Extract(info[4]);
            instruction = builder->insertDeclare(storage, variable, expr, location, insertBB);
        } else if (Instruction::IsClassOf(info[4])) {
            llvm::Instruction *insertBefore = Instruction::Extract(info[4]);
            instruction = builder->insertDeclare(storage, variable, expr, location, insertBefore);
        }
    }
    if (instruction) {
        return Instruction::New(env, instruction);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::insertDeclare);
}

Napi::Value DIBuilder::insertDbgValueIntrinsic(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    llvm::Instruction *instruction = nullptr;
    if (info.Length() == 5
        && Value::IsClassOf(info[0])
        && DILocalVariable::IsClassOf(info[1])
        && DIExpression::IsClassOf(info[2])
        && DILocation::IsClassOf(info[3])) {
        llvm::Value *value = Value::Extract(info[0]);
        llvm::DILocalVariable *variable = DILocalVariable::Extract(info[1]);
        llvm::DIExpression *expr = DIExpression::Extract(info[2]);
        llvm::DILocation *location = DILocation::Extract(info[3]);
        if (BasicBlock::IsClassOf(info[4])) {
            llvm::BasicBlock *insertBB = BasicBlock::Extract(info[4]);
            instruction = builder->insertDbgValueIntrinsic(value, variable, expr, location, insertBB);
        } else if (Instruction::IsClassOf(info[4])) {
            llvm::Instruction *insertBefore = Instruction::Extract(info[4]);
            instruction = builder->insertDbgValueIntrinsic(value, variable, expr, location, insertBefore);
        }
    }
    if (instruction) {
        return Instruction::New(env, instruction);
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::insertDbgValueIntrinsic);
}

void DIBuilder::finalizeSubprogram(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && DISubprogram::IsClassOf(info[0])) {
        llvm::DISubprogram *subprogram = DISubprogram::Extract(info[0]);
        builder->finalizeSubprogram(subprogram);
        return;
    }
    throw Napi::TypeError::New(env, ErrMsg::Class::DIBuilder::finalizeSubprogram);
}

void DIBuilder::finalize(const Napi::CallbackInfo &info) {
    builder->finalize();
}
