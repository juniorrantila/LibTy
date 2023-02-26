#pragma once
#include "ErrorOr.h"
#include "Formatter.h"

namespace Ty {

template <typename Self>
struct FormatConsumer {
    constexpr Self& self() { return *static_cast<Self*>(this); }

    template <typename... Args>
    constexpr ErrorOr<u32> write(Args const&... args) requires(
        sizeof...(Args) > 1)
    {
        constexpr auto args_size = sizeof...(Args);
        ErrorOr<u32> results[args_size] = {
            write(args)...,
        };
        u32 written = 0;
        for (u32 i = 0; i < args_size; i++)
            written += TRY(move(results[i]));
        return written;
    }

    constexpr ErrorOr<u32> write(StringView string)
    {
        return TRY(self().write_impl(string));
    }

    template <typename... Args>
    constexpr ErrorOr<u32> writeln(Args const&... args)
    {
        return TRY(write(args..., "\n"sv));
    }

    template <typename T>
    requires is_trivially_copyable<T>
    constexpr ErrorOr<u32> write(T value)
    {
        return TRY(Formatter<T>::write(*this, value));
    }

    template <typename T>
    requires(!is_trivially_copyable<T>) constexpr ErrorOr<
        u32> write(T const& value)
    {
        return TRY(Formatter<T>::write(*this, value));
    }
};

}
