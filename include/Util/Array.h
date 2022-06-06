#pragma once

#include <vector>
#include <cstdint>

//===--------------------------------------------------------------------===//
// Assemble array by wrapped type and its corresponding LLVM type
// return false if the type of some elements is not the correct wrapped type
//===--------------------------------------------------------------------===//

template<typename WrappedType, typename LLVMType>
inline bool assembleArray(Napi::Array sources, std::vector<LLVMType> &destinations) {
    unsigned size = sources.Length();
    destinations.resize(size);
    for (unsigned i = 0; i < size; ++i) {
        if (!WrappedType::IsClassOf(sources[i])) {
            return false;
        }
        destinations[i] = WrappedType::Extract(sources[i]);
    }
    return true;
}

//===--------------------------------------------------------------------===//
// Assemble array consisting of numbers
// return false if the type of some elements is not the number type
//===--------------------------------------------------------------------===//

inline bool assembleArray(Napi::Array sources, std::vector<int64_t> &destinations) {
    unsigned size = sources.Length();
    destinations.resize(size);
    for (unsigned i = 0; i < size; ++i) {
        if (!sources.Get(i).IsNumber()) {
            return false;
        }
        destinations[i] = sources.Get(i).As<Napi::Number>().Int64Value();
    }
    return true;
}
