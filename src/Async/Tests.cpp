#include "EventLoop.h"

#include "Unit/Expect.h"
#include "Unit/Unit.h"

TEST_CASE(event_loop)
{
    auto event_loop = Async::EventLoop::create();
    const u8 loop_order_capacity = 8;
    volatile u8 loop_order[loop_order_capacity] { };
    volatile u8 loop_id = 0;

    event_loop.append([&](Async::Frame& frame) {
        while(loop_id < loop_order_capacity) {
            loop_order[loop_id] = frame.id();
            loop_id = loop_id + 1;
            frame.yield();
        }
    });

    event_loop.append([&](Async::Frame& frame) {
        while(loop_id < loop_order_capacity) {
            loop_order[loop_id] = frame.id();
            loop_id = loop_id + 1;
            frame.yield();
        }
    });

    event_loop.append([&](Async::Frame& frame) {
        while(loop_id < loop_order_capacity) {
            loop_order[loop_id] = frame.id();
            loop_id = loop_id + 1;
            frame.yield();
        }
    });

    event_loop.append([&](Async::Frame& frame) {
        while(loop_id < loop_order_capacity) {
            loop_order[loop_id] = frame.id();
            loop_id = loop_id + 1;
            frame.yield();
        }
    });

    event_loop.run();

    EXPECT(loop_order[0] == 0);
    EXPECT(loop_order[1] == 1);
    EXPECT(loop_order[2] == 2);
    EXPECT(loop_order[3] == 3);
    EXPECT(loop_order[4] == 0);
    EXPECT(loop_order[5] == 1);
    EXPECT(loop_order[6] == 2);
    EXPECT(loop_order[7] == 3);

    return 0;
}
