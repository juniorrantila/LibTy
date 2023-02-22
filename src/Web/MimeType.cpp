#include "MimeType.h"

namespace Web {

StringView MimeType::name() const
{
    switch (m_type) {
    case MimeType::ApplicationJson: return "application/json"sv;
    case MimeType::ApplicationOctetStream:
        return "application/octet-stream"sv;
    case MimeType::ImageIco: return "image/vnd.microsoft.icon"sv;
    case MimeType::ImagePng: return "image/png"sv;
    case MimeType::TextCss: return "text/css"sv;
    case MimeType::TextHtml: return "text/html"sv;
    case MimeType::TextJavascript: return "text/javascript"sv;
    case MimeType::TextMarkdown: return "text/markdown"sv;
    case MimeType::TextPlain: return "text/plain"sv;
    }
}

}
