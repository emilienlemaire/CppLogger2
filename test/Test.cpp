//
// Created by Emilien Lemaire on 16/03/2020.
//

#include <CppLogger.h>

int main() {
    CppLogger::CppLogger mainLogger(CppLogger::Level::Trace, "Main");

    mainLogger.printTrace("Test");

    CppLogger::Format mainFormat({
        CppLogger::FormatAttribute::Time,
        CppLogger::FormatAttribute::Name,
        CppLogger::FormatAttribute::Level,
        CppLogger::FormatAttribute::Message
    });

    mainLogger.setFormat(mainFormat);

    mainLogger.printTrace("Main");
    mainLogger.printInfo("Main");
    mainLogger.printWarn("Main");
    mainLogger.printError("Main");
    mainLogger.printFatalError("Main");

    CppLogger::CppLogger errorLogger(CppLogger::Level::Trace, "Error logger");

    errorLogger.setFormat(mainFormat);

    errorLogger.printTrace("Error");
    errorLogger.printInfo("Error");
    errorLogger.printWarn("Error");
    errorLogger.printError("Error");
    errorLogger.printFatalError("Error");

    int a = 5;
    char b = 'b';
    double d = 5.2;
    float f = 5.4f;

    errorLogger.printTrace("{}", a);

}