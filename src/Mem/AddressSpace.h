#pragma once
#include "Sizes.h"
#include <Ty/Base.h>
#include <Ty/ErrorOr.h>
#include <Ty/Try.h>
#include <Unit/Unit.h>

namespace Mem {

namespace Internal {

ErrorOr<void> init(uptr base, uptr size);
ErrorOr<void> deinit(uptr base, uptr size);

}

template <uptr BaseAddress, uptr Size>
struct AddressSpace {
    static constexpr auto base = BaseAddress;
    static constexpr auto size = Size;
    static constexpr auto end = BaseAddress + Size;

    static ErrorOr<void> init()
    {
        TRY(Internal::init(base, size));
        return {};
    }

    static ErrorOr<void> deinit()
    {
        TRY(Internal::deinit(base, size));
        return {};
    }

private:
};

using LoRam = AddressSpace<64 * MiB, 4 * GiB>;
using HiRam = AddressSpace<LoRam::end, 4 * GiB>;

TEST_CASE(low_ram_works)
{
    EXPECT(!LoRam::init().is_error());
    return {};
}

TEST_CASE(high_ram_works)
{
    EXPECT(!HiRam::init().is_error());
    return {};
}

}
