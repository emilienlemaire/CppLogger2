//
// Created by Emilien Lemaire on 16/03/2020.
//

#include "CppLogger.h"
#include <cstdlib>
#include <ostream>
#include <string>
#include <chrono>
#include <ctime>

namespace CppLogger {
    CppLogger::CppLogger(Level t_Level, const char* t_Name, bool exitOnFatal)
        :m_Level(t_Level), m_Name(t_Name), m_ExitOnFatal(exitOnFatal) {}

    void CppLogger::setFormat(Format& t_Format) {
        if (std::find(t_Format.getFormat().begin(), t_Format.getFormat().end(), FormatAttribute::Message) == t_Format.getFormat().end()) {
            t_Format.addMessage();
        }
        for (auto &format : m_Format) {
            format = t_Format;
        }
    }

    void CppLogger::setFormat(std::initializer_list<FormatAttribute> t_Format) {
        if (std::find(t_Format.begin(), t_Format.end(), FormatAttribute::Message) == t_Format.end()) {
            for(auto &format : m_Format) {
                format = t_Format;
                format.addMessage();
            }
        } else {
            for (auto &format: m_Format)
                format = t_Format;
        }
    }

    void CppLogger::setFormat(Level t_Level, Format& t_Format) {
        if (std::find(t_Format.getFormat().begin(), t_Format.getFormat().end(), FormatAttribute::Message) == t_Format.getFormat().end()) {
            t_Format.addMessage();
        }
        m_Format[t_Level - 1] = t_Format;
    }

    void CppLogger::setOStream(std::ostream& t_OStream) {
        m_TraceStream = &t_OStream;
        m_InfoStream = &t_OStream;
        m_WarnStream = &t_OStream;
        m_ErrorStream = &t_OStream;
        m_FatalErrorStream = &t_OStream;
    }

    void CppLogger::setOStream(Level t_Level, std::ostream& t_OStream) {
        switch (t_Level) {
            case None:
                break;
            case Trace:
                m_TraceStream = &t_OStream;
                break;
            case Info:
                m_InfoStream = &t_OStream;
                break;
            case Warn:
                m_WarnStream = &t_OStream;
                break;
            case Error:
                m_ErrorStream = &t_OStream;
                break;
            case FatalError:
                m_FatalErrorStream = &t_OStream;
                break;
        }
    }

    std::stringstream CppLogger::printFormat(Level t_Level, std::string t_Message) {
        std::vector<FormatAttribute > format = m_Format[t_Level - 1].getFormat();
        std::stringstream sstr;
        for (const auto &attribute : format) {
            switch (attribute) {
                case FormatAttribute::None:
                    break;
                case FormatAttribute::Name:
                    sstr << "[" << m_Name << "] ";
                    break;
                case FormatAttribute::Time: {
                    std::time_t currTime;
                    std::tm * currTm;
                    std::time(&currTime);
                    currTm = std::localtime(&currTime);

                    char time[100];
                    std::strftime(time, 50, "%T", currTm);
                    sstr << time << " ";
                    break;
                }
                case FormatAttribute::Level: {
                    switch (t_Level) {
                        case None:
                            break;
                        case Trace:
                            sstr << "(Trace) ";
                            break;
                        case Info:
                            sstr << "(Info) ";
                            break;
                        case Warn:
                            sstr << "(Warn) ";
                            break;
                        case Error:
                            sstr << "(Error) ";
                            break;
                        case FatalError:
                            sstr << "(Fatal Error) ";
                            break;
                    }
                    break;
                }
                case FormatAttribute::Message:
                    sstr << t_Message << " ";
                    break;
            }
        }
        return sstr;
    }

    void CppLogger::setColor(Level t_Level, std::string t_Color){
        switch (t_Level) {
            case Level::None:
                break;
            case Level::Trace:
                m_TraceColor = t_Color;
                break;
            case Level::Info:
                m_InfoColor = t_Color;
                break;
            case Level::Warn:
                m_WarnColor = t_Color;
                break;
            case Level::Error:
                m_ErrorColor = t_Color;
                break;
            case Level::FatalError:
                m_FatalErrorColor = t_Color;
                break;
        }
    }

    void CppLogger::printTrace(std::string t_Message) {
        std::stringstream formatted = printFormat(Level::Trace, t_Message);
        if (m_Level != Level::None && m_Level <= Level::Trace)
            *m_TraceStream << m_TraceColor << formatted.str() << Color::reset << std::endl;
    }

    void CppLogger::printInfo(std::string t_Message) {
        std::stringstream formatted = printFormat(Level::Info, t_Message);
        if (m_Level != Level::None && m_Level <= Level::Info)
            *m_InfoStream << m_InfoColor << formatted.str() << Color::reset << std::endl;
    }

    void CppLogger::printWarn(std::string t_Message) {
        std::stringstream formatted = printFormat(Level::Warn, t_Message);
        if (m_Level != Level::None && m_Level <= Level::Warn)
            *m_WarnStream << m_WarnColor << formatted.str() << Color::reset << std::endl;
    }

    void CppLogger::printError(std::string t_Message) {
        std::stringstream formatted = printFormat(Level::Error, t_Message);
        if (m_Level != Level::None && m_Level <= Level::Error)
            *m_ErrorStream << m_ErrorColor << formatted.str() << Color::reset << std::endl;
    }

    void CppLogger::printFatalError(std::string t_Message) {
        std::stringstream formatted = printFormat(Level::FatalError, t_Message);
        if (m_Level != Level::None && m_Level <= Level::FatalError)
            *m_FatalErrorStream << m_FatalErrorColor << formatted.str() << Color::reset << std::endl;

        if (m_ExitOnFatal)
            exit(EXIT_FAILURE);
    }
}
