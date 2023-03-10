#pragma once
#include "File.h"
#include <Ty/Base.h>

namespace Core {

enum class BenchEnableShowOnStopAndShow : bool {
    No = false,
    Yes = true,
};

struct Bench {

    constexpr Bench(BenchEnableShowOnStopAndShow display,
        Core::File& output_file = Core::File::stderr())
        : m_out(output_file)
        , m_should_show_on_stop(
              display == BenchEnableShowOnStopAndShow::Yes)
    {
    }

    static u64 current_tick()
    {
        u64 tick = 0;
        u32 cycles_low = 0;
        u32 cycles_high = 0;
        asm volatile("rdtsc\n"
                     : "=d"(cycles_high), "=a"(cycles_low)::"%rbx",
                     "%rcx");
        tick = ((u64)cycles_high << 32) | cycles_low;
        return tick;
    }

    void start()
    {
        m_total_cycles += m_stop_cycle - m_start_cycle;
        m_start_cycle = current_tick();
    }

    void stop() { m_stop_cycle = current_tick(); }

    void stop_and_show(c_string display_message)
    {
        m_stop_cycle = current_tick();
        if (m_should_show_on_stop)
            show(display_message);
    }

    void show(c_string message) const
    {
        auto cycles = m_stop_cycle - m_start_cycle;
        auto total = m_total_cycles + cycles;

        auto const* cycles_postfix = "";
        if (cycles > 1000) {
            cycles /= 1000;
            cycles_postfix = "K";
        }
        if (cycles > 1000) {
            cycles /= 1000;
            cycles_postfix = "M";
        }

        auto const* total_postfix = "";
        if (total > 1000) {
            total /= 1000;
            total_postfix = "K";
        }
        if (total > 1000) {
            total /= 1000;
            total_postfix = "M";
        }

        auto buffer = StringBuffer();
        auto bytes = __builtin_snprintf(buffer.mutable_data(),
            buffer.capacity(), "%12s: %4d%s cycles | total: %d%s\n",
            message, (u32)cycles, cycles_postfix, (u32)total,
            total_postfix);
        auto view = StringView { buffer.data(), (u32)bytes };
        m_out.write(view).ignore();
    }

    constexpr u64 start_cycle() const { return m_start_cycle; }
    constexpr u64 stop_cycle() const { return m_stop_cycle; }
    constexpr u64 total_cycles() const { return m_total_cycles; }

private:
    Core::File& m_out;
    u64 m_start_cycle { 0 };
    u64 m_stop_cycle { 0 };
    u64 m_total_cycles { 0 };
    bool m_should_show_on_stop { false };
};

}
