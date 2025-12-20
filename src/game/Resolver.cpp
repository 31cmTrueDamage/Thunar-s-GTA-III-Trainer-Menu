#include "Resolver.h"
#include <cstddef>
#include <cstdint>

uintptr_t Resolver::ResolvePointerChain(uintptr_t base, const std::vector<uintptr_t>& offsets) {
    uintptr_t address = base;

    for (size_t i = 0; i < offsets.size() - 1; ++i) {
        address = *(uintptr_t*)(address + offsets[i]);
        if (!address)
            return 0;
    }

    return address + offsets.back();
}
