#pragma once
#include <Ty/Base.h>
#include "Context.h"

namespace Async {

struct Frame {
    constexpr Frame() = default;
    Frame(Frame const&) = delete;

    constexpr Frame(Frame&& other)
        : m_context(other.m_context)
        , m_master(other.m_master)
        , m_id(other.m_id)
    {
    }

    constexpr Frame(Frame const* master, u16 id)
        : m_master(master->context())
        , m_id(id)
    {
    }

    static constexpr Frame create_master() { return Frame(nullptr); }
    
    bool save() { return save_context(&m_context) != 0; }
    void load() const { load_context(&m_context); }

    void yield() { swap_context(&m_context, m_master); }

    template <typename F, typename... Args>
    void run(F func, Args... args)
    {
        if (save())
            return;
        func(*this, args...);
        set_done();
    }

    bool is_done() const { return m_master == nullptr; }

    u16 id() const { return m_id; }

private:
    void set_done()
    {
        Context const* context = m_master;
        m_master = nullptr;
        load_context(context);
    }

    constexpr Frame(decltype(nullptr))
        : m_master(nullptr)
    {
    }

    Context const* context() const { return &m_context; }

    Context m_context {};
    Context const* m_master { 0 };
    u16 m_id { 0 };
};

}
