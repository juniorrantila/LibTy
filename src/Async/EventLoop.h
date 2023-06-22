#pragma once
#include "Frame.h"
#include <Ty/Base.h>
#include <Ty/New.h>
#include <Ty/Try.h>

namespace Async {

struct EventLoop {
    static constexpr u32 max_frames = 1023;

    static EventLoop create()
    {
        return Frame::create_master();
    }

    template <typename F, typename... Args>
    void append(F func, Args... args)
    {
        VERIFY(m_frames_size < max_frames);
        u16 frame_id = m_frames_size++;
        Frame* frame = &m_frames[frame_id];
        new (frame) Frame(&m_master, frame_id);
        frame->run(func, args...);
    }

    void run()
    {
        if (m_master.save())
            m_frames[m_current_frame].load();

        for (u32 i = 0; i < m_frames_size; i++) {
            m_current_frame = (m_current_frame + 1) % m_frames_size;
            if (!m_frames[m_current_frame].is_done()) {
                m_frames[m_current_frame].load();
            }
        }
    }

private:
    EventLoop(Frame master)
        : m_master(static_cast<Frame&&>(master))
    {
    }

    Frame m_master {};
    Frame m_frames[max_frames] {};
    u32 m_frames_size { 0 };
    volatile u32 m_current_frame { 0 };
};

}
