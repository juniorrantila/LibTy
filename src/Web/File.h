#pragma once
#include "MimeType.h"
#include <Core/MappedFile.h>
#include <Ty/StringBuffer.h>

namespace Web {

struct File {

    static ErrorOr<File> open(StringView path);

    ErrorOr<void> reload();

    MimeType mime_type() const;
    StringView charset() const;

    StringView view() const { return m_file.view(); }

private:
    File(Core::MappedFile&& file, StringView path);

    Core::MappedFile m_file;
    StringView m_path;
};

}
