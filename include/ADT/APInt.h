#include <napi.h>
#include <llvm/ADT/APInt.h>

class APInt : public Napi::ObjectWrap<APInt> {
public:
    static inline Napi::FunctionReference constructor; // NOLINT;

    static void Init(Napi::Env env, Napi::Object &exports);

    static bool IsClassOf(const Napi::Value &value);

    static llvm::APInt &Extract(const Napi::Value &value);

    explicit APInt(const Napi::CallbackInfo &info);

    llvm::APInt &getLLVMPrimitive();

private:
    llvm::APInt *apInt = nullptr;
};