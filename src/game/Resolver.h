#pragma once
#include <vector>
#include <cstdint>

namespace Resolver {
    uintptr_t ResolvePointerChain(uintptr_t base, const std::vector<uintptr_t>& offsets);
}
