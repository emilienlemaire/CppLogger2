//
// Created by Emilien Lemaire on 16/03/2020.
//

#pragma once


#include <string>
#include <array>
#include "Format.h"

namespace CppLogger {
    enum Level {
        None = 0,
        Trace, Info, Warn, Error, FatalError
    };
    class CppLogger {
    private:
        Level m_Level;
        std::string m_Name;
        std::array<Format, 5> m_Format{{
            {FormatAttribute::Time, FormatAttribute::Name, FormatAttribute::Message}
        }};
    public:
        CppLogger(Level t_Level, const char* t_Name);

        void setFormat(Format& t_Format);
        void setFormat(Level t_Level, Format& t_Format);
        std::stringstream printFormat(Level t_Level, const char* t_Message);

        void printTrace(const char* t_Message);
        void printInfo(const char* t_Message);
        void printWarn(const char* t_Message);
        void printError(const char* t_Message);
        void printFatalError(const char* t_Message);
        ~CppLogger() = default;
    };
}

