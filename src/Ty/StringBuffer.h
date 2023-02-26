#pragma once
#include "Base.h"
#include "Concepts.h"
#include "ErrorOr.h"
#include "FormatConsumer.h"
#include "FormatCounter.h"
#include "Forward.h"
#include "Memory.h"
#include "Traits.h"
#include "Try.h"
#include "Vector.h"

namespace Ty {

struct StringBuffer final : public FormatConsumer<StringBuffer> {

    static constexpr ErrorOr<StringBuffer> create_saturated(
        u32 capacity)
    {
        return StringBuffer {
            (char*)TRY(allocate_memory(capacity)),
            capacity,
        };
    }

    static constexpr ErrorOr<StringBuffer> create(
        u32 capacity = inline_capacity)
    {
        if (capacity > inline_capacity)
            return create_saturated(capacity);
        return StringBuffer();
    }

    template <typename... Args>
    static constexpr ErrorOr<StringBuffer> create_saturated_fill(
        Args... args) requires(sizeof...(args) > 1)
    {
        auto capacity = TRY(FormatCounter::count(args...)) + 1;
        auto buffer = TRY(create_saturated(capacity));
        TRY(buffer.write(args...));
        return buffer;
    }

    template <typename... Args>
    static constexpr ErrorOr<StringBuffer> create_fill(
        Args... args) requires(sizeof...(args) > 1)
    {
        auto capacity = TRY(FormatCounter::count(args...)) + 1;
        auto buffer = TRY(create(capacity));
        TRY(buffer.write(args...));
        return buffer;
    }

    template <typename T>
    static constexpr ErrorOr<StringBuffer> create_fill(T value)
    {
        auto capacity = TRY(FormatCounter::count(value)) + 1;
        auto buffer = TRY(create(capacity));
        TRY(buffer.write(value));
        return buffer;
    }

    constexpr StringBuffer()
        : m_data(m_storage)
        , m_capacity(inline_capacity)
    {
    }

    constexpr StringBuffer(StringBuffer&& other)
        : m_data(other.m_data)
        , m_size(other.m_size)
        , m_capacity(other.m_capacity)
    {
        if (!other.is_saturated()) {
            __builtin_memcpy(m_storage, other.m_storage,
                inline_capacity);
            m_data = m_storage;
        }
        other.invalidate();
    }

    constexpr ~StringBuffer()
    {
        if (is_valid()) {
            if (is_saturated())
                free_memory(m_data);
            invalidate();
        }
    }

    constexpr StringBuffer& operator=(StringBuffer&& other)
    {
        this->~StringBuffer();

        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        if (!other.is_saturated()) {
            __builtin_memcpy(m_storage, other.m_storage,
                inline_capacity);
            m_data = m_storage;
        }
        other.invalidate();

        return *this;
    }

    constexpr ErrorOr<u32> write_impl(StringView string)
    {
        TRY(expand_if_needed_for_write(string.size));
        auto size = string.unchecked_copy_to(&m_data[m_size]);
        m_size += size;
        return size;
    }

    constexpr void clear() { m_size = 0; }

    constexpr char* mutable_data() { return m_data; }
    constexpr char const* data() const { return m_data; }
    constexpr u32 size() const { return m_size; }
    constexpr u32 capacity() const { return m_capacity; }
    constexpr u32 size_left() const { return m_capacity - m_size; }

    constexpr char* begin() { return m_data; }
    constexpr char* end() { return &m_data[m_size]; }

    constexpr c_string begin() const { return m_data; }
    constexpr c_string end() const { return &m_data[m_size]; }

    constexpr StringView view() const { return { m_data, m_size }; }

    constexpr void replace_all(char thing, char with)
    {
        for (auto& c : *this) {
            if (c == thing)
                c = with;
        }
    }

    constexpr c_string leak()
    {
        c_string ptr = data();
        invalidate();
        return ptr;
    }

    ErrorOr<void> expand_if_needed_for_write(u32 size)
    {
        if (m_size + size >= m_capacity)
            TRY(expand_by(size));
        return {};
    }

    ErrorOr<void> expand_by(u32 size)
    {
        auto new_capacity = m_size + size;
        auto* new_data = (char*)TRY(allocate_memory(new_capacity));
        __builtin_memcpy(new_data, data(), m_size);
        if (is_saturated())
            free_memory(m_data);
        m_data = new_data;
        m_capacity = new_capacity;
        return {};
    }

private:
    static constexpr auto max_chars_in_u64 = 20;
    static constexpr auto inline_capacity = 1024;

    static constexpr char number_to_character(u8 number)
    {
        return (char)('0' + number);
    }

    constexpr StringBuffer(char* data, u32 capacity)
        : m_data(data)
        , m_size(0)
        , m_capacity(capacity)
    {
    }

    constexpr bool is_valid() const { return m_data != nullptr; }
    constexpr void invalidate() { m_data = nullptr; }

    constexpr bool is_saturated() const
    {
        return m_data != m_storage;
    }

    char m_storage[inline_capacity];
    char* m_data { nullptr };
    u32 m_size { 0 };
    u32 m_capacity { 0 };
};

template <>
struct Formatter<StringBuffer> {
    template <typename U>
    requires Writable<U>
    static constexpr ErrorOr<u32> write(U& to,
        StringBuffer const& buffer)
    {
        return TRY(to.write(buffer.view()));
    }
};

}
