#pragma once

#ifndef STRING
#    define STRING2(x) #    x
#    define STRING(x) STRING2(x)
#endif
#define EXPECT_MESSAGE(__condition) \
    __FILE__ ":" STRING(__LINE__) ": Expected '" #__condition "'"
#define EXPECT(__condition)                     \
    ({                                          \
        if (!(__condition))                     \
            return EXPECT_MESSAGE(__condition); \
    })

#define SHOULD(__expression)                                \
    ({                                                      \
        decltype(auto) __temporary_result = (__expression); \
        EXPECT(__temporary_result.has_value());             \
        __temporary_result.release_value();                 \
    })
