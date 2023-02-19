#include <Core/Print.h>
#include <Main/Main.h>

ErrorOr<int> Main::main(int argc, c_string argv[])
{
    (void)argc;
    (void)argv;

    writeln("Hello, World!"sv);

    return 0;
}
