#ifndef __LLVM_BINDINGS_NODEJS_ASSERT__
#define __LLVM_BINDINGS_NODEJS_ASSERT__

#ifdef __cplusplus
void llvm_bindings_assert(const char* expr, const char* file, int line);

#define __assert(e, file, line) ((void)llvm_bindings_assert ((e), (file), (line)))

#define assert(e) ((void) ((e) ? ((void)0) : __assert (#e, __FILE__, __LINE__)))

#endif

#endif
