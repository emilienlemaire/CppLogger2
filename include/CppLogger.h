//
// Created by Emilien Lemaire on 16/03/2020.
//

#pragma once


#include <string>
#include <array>
#include <sstream>
#include <iostream>
#include "Format.h"
#include "Color.h"

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
            {FormatAttribute::Time,
             FormatAttribute::Name,
             FormatAttribute::Message}
        }};
        bool m_ExitOnFatal;
    public:
        CppLogger(Level t_Level, const char* t_Name, bool exitOnFatal = false);

        void setFormat(Format& t_Format);
        void setFormat(Level t_Level, Format& t_Format);
        std::stringstream printFormat(Level t_Level, std::string t_Message);

        void printTrace(std::string t_Message);
        void printInfo(std::string t_Message);
        void printWarn(std::string t_Message);
        void printError(std::string t_Message);
        void printFatalError(std::string t_Message);
        ~CppLogger() = default;

        template<typename T, typename... Types>
        std::string formatString(std::string &fmt, T var1, Types... var){
            std::size_t argNum = sizeof...(Types);
            std::size_t found = fmt.find("{}");
            std::stringstream sstr;
            sstr << var1;
            if (found != std::string::npos) fmt.replace(found, 2, sstr.str());
            if (found == std::string::npos) return fmt;
            else return formatString(fmt, var...);
        }

        template<typename T>
        std::string formatString(std::string& fmt, T var) {
            std::size_t found = fmt.find("{}");
            std::stringstream sstr;
            sstr << var;
            if (found != std::string::npos) fmt.replace(found, 2, sstr.str());
            return fmt;
        }

        template<typename T, typename ... Types>
        void printTrace(std::string t_fmt, T var1, Types... var) {

            std::string message = formatString(t_fmt, var1, var...);

            std::stringstream formatted = printFormat(Level::Trace, message);
            if (m_Level != Level::None && m_Level <= Level::Trace)
                std::cout << formatted.str() << std::endl;
        }

        template<typename T, typename ... Types>
        void printInfo(std::string t_fmt, T var1, Types... var) {

            std::string message = formatString(t_fmt, var1, var...);

            std::stringstream formatted = printFormat(Level::Info, message);
            if (m_Level != Level::None && m_Level <= Level::Info)
                std::cout << Color::green << formatted.str() << Color::reset << std::endl;
        }

        template<typename T, typename ... Types>
        void printWarn(std::string t_fmt, T var1, Types... var) {

            std::string message = formatString(t_fmt, var1, var...);

            std::stringstream formatted = printFormat(Level::Warn, message);
            if (m_Level != Level::None && m_Level <= Level::Warn)
                std::cout << Color::yellow << formatted.str() << Color::reset << std::endl;
        }

        template<typename T, typename ... Types>
        void printError(std::string t_fmt, T var1, Types... var) {

            std::string message = formatString(t_fmt, var1, var...);

            std::stringstream formatted = printFormat(Level::Error, message);
            if (m_Level != Level::None && m_Level <= Level::Error)
                std::cout << Color::red << formatted.str() << Color::reset << std::endl;
        }

        template<typename T, typename ... Types>
        void printFatalError(std::string t_fmt, T var1, Types... var) {

            std::string message = formatString(t_fmt, var1, var...);

            std::stringstream formatted = printFormat(Level::FatalError, message);
            if (m_Level != Level::None && m_Level <= Level::FatalError)
                std::cout << Color::red << formatted.str() << Color::reset << std::endl;
        }
    };
}

