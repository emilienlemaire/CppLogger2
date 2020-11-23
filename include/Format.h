//
// Created by Emilien Lemaire on 16/03/2020.
//

#pragma once

#include <initializer_list>
#include <vector>

namespace CppLogger {
    enum class FormatAttribute {
        None = 0,
        Name, Time, Level, Message
    };
    class Format {
    private:
        std::vector<FormatAttribute> m_Format;
    public:
        Format(std::initializer_list<FormatAttribute> t_Format);

        std::vector<FormatAttribute> getFormat() { return m_Format; }

        void addMessage() { m_Format.push_back(FormatAttribute::Message); }
        ~Format() = default;
    };
}
