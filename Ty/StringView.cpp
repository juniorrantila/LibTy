#include "StringView.h"
#include "ErrorOr.h"
#include "Vector.h"
#include <Unit/Unit.h>

namespace Ty {

ErrorOr<Vector<u32>> StringView::find_all(char character) const
{
    auto occurrences = TRY(Vector<u32>::create());

    for (u32 i = 0; i < size; i++) {
        if (data[i] == character)
            TRY(occurrences.append(i));
    }

    return occurrences;
}

TEST_CASE(string_view_can_find_all)
{
    auto foo = "foo baam baz"sv;

    auto find_result = foo.find_all(' ');
    EXPECT(!find_result.is_error());
    auto finds = find_result.release_value();

    EXPECT(finds.size() == 2);
    EXPECT(finds[0] == 3);
    EXPECT(finds[1] == 8);

    return {};
}

ErrorOr<Vector<StringView>> StringView::split_on(
    char character) const
{
    auto indexes = TRY(find_all(character));
    if (indexes.is_empty())
        return {};

    auto splits = TRY(Vector<StringView>::create());

    u32 last_index = 0xFFFFFFFF; // Intentional overflow
    for (auto index : indexes) {
        TRY(splits.append(part(last_index + 1, index)));
        last_index = index;
    }
    TRY(splits.append(part(last_index + 1, size)));

    return splits;
}

TEST_CASE(string_view_can_split)
{
    auto foo = "foo bar baz"sv;

    auto split_result = foo.split_on(' ');
    EXPECT(!split_result.is_error());
    auto split = split_result.release_value();

    EXPECT(split.size() == 3);
    EXPECT(split[0] == "foo"sv);
    EXPECT(split[1] == "bar"sv);
    EXPECT(split[2] == "baz"sv);

    return {};
}

}
