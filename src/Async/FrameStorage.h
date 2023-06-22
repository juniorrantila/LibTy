#pragma once
#include "Forward.h"

namespace Async {

template <typename T>
struct FrameStorage {
    T& operator[](Frame const& frame) { return m_data[frame.id()]; }
private:
    T m_data[EventLoop::max_frames];
};

}
