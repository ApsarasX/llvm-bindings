#include "ADT/index.h"
#include "BinaryFormat/index.h"
#include "Bitcode/index.h"
#include "Config/index.h"
#include "IR/index.h"
#include "IRReader/index.h"
#include "Linker/index.h"
#include "MC/index.h"
#include "Support/index.h"
#include "Target/index.h"

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

static std::unique_ptr<Napi::Env> node_env;

void llvm_bindings_assert(const char* e, const char* file, int line)
{
    throw Napi::Error::New(
        *node_env, string_format("%s:%d: failed assertion `%s'\n", file, line, e));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    node_env = std::make_unique<Napi::Env>(env);
    InitADT(env, exports);
    InitBinaryFormat(env, exports);
    InitBitCode(env, exports);
    InitConfig(env, exports);
    InitIR(env, exports);
    InitIRReader(env, exports);
    InitLinker(env, exports);
    InitMC(env, exports);
    InitSupport(env, exports);
    InitTarget(env, exports);
    return exports;
}

NODE_API_MODULE(llvm, Init)
