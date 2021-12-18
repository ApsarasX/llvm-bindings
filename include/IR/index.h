#pragma once

#include <napi.h>
#include "IR/LLVMContext.h"
#include "IR/Module.h"
#include "IR/Type.h"
#include "IR/DerivedTypes.h"
#include "IR/Value.h"
#include "IR/Argument.h"
#include "IR/BasicBlock.h"
#include "IR/User.h"
#include "IR/Constant.h"
#include "IR/Constants.h"
#include "IR/GlobalValue.h"
#include "IR/GlobalObject.h"
#include "IR/GlobalVariable.h"
#include "IR/Function.h"
#include "IR/Instruction.h"
#include "IR/Instructions.h"
#include "IR/IRBuilder.h"
#include "IR/Metadata.h"
#include "IR/DebugInfoMetadata.h"
#include "IR/DebugLoc.h"
#include "IR/DIBuilder.h"
#include "IR/DataLayout.h"
#include "IR/Verifier.h"
#include "IR/Intrinsic.h"

void InitIR(Napi::Env env, Napi::Object &exports);
