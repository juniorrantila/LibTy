#include <Core/Print.h>
#include <Core/System.h>
#include <Main/Main.h>
#include <Unit/Unit.h>

ErrorOr<int> Main::main(int argc, c_string argv[])
{
    (void)argc;
    (void)argv;

    writeln("Hello, World!"sv);

    return 0;
}

TEST_CASE(main)
{
    auto buffer = SHOULD(StringBuffer::create_fill("Hello"sv));
    SHOULD(buffer.write(", World!"sv));
    EXPECT(buffer.view() == "Hello, World!"sv);
    return {};
}

TEST_CASE(slow_test)
{
    Core::System::sleep(2);
    return {};
}
