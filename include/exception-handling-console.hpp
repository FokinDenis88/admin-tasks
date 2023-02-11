#ifndef EXCEPTION_HANDLING_CONSOLE_HPP_
#define EXCEPTION_HANDLING_CONSOLE_HPP_

#include <exception>
#include <stdexcept>
#include <iostream>

#ifdef FILE_SYSTEM_EXCEPTION_HANDLING
#include <filesystem>
#include <boost/filesystem.hpp>
#endif // FILE_SYSTEM_EXCEPTION_HANDLING

namespace errors {
    inline constexpr int kLogicErrorCode            { -1 };
    inline constexpr int kRuntimeErrorCode          { -2 };
    inline constexpr int kOutOfRangeErrorCode       { -3 };
    inline constexpr int kBadAllocErrorCode         { -4 };
    inline constexpr int kInvalidArgumentErrorCode  { -5 };
    inline constexpr int kDomainErrorCode           { -6 };
    inline constexpr int kLengthErrorCode           { -7 };
    inline constexpr int kRangeErrorCode            { -8 };
    inline constexpr int kOverflowErrorCode         { -9 };
    inline constexpr int kUnderflowErrorCode        { -10 };
    inline constexpr int kFatalErrorCode            { -11 };

    inline const std::string kLogicErrorName            { "Logic" };
    inline const std::string kRuntimeErrorName          { "Runtime" };
    inline const std::string kOutOfRangeErrorName       { "Out of range" };
    inline const std::string kBadAllocErrorName         { "Bad allocation" };
    inline const std::string kInvalidArgumentErrorName  { "Invalid argument" };
    inline const std::string kDomainErrorName           { "Domain" };
    inline const std::string kLengthErrorName           { "Length" };
    inline const std::string kRangeErrorName            { "Range" };
    inline const std::string kOverflowErrorName         { "Overflow" };
    inline const std::string kUnderflowErrorName        { "Underflow" };
    inline const std::string kFatalErrorName            { "Fatal" };

    inline const std::string kTryCatchMessage{ "\n\nTry {} Catch {} block.\n" };
    inline const std::string kErrorTypeMessage{ "C++ Error Type: " };
    inline const std::string kErrorWhatMesssage{ " error. What: " };

    inline const std::string kLogicErrorType            { "std::logic_error" };
    inline const std::string kRuntimeErrorType          { "std::runtime_error" };
    inline const std::string kOutOfRangeErrorType       { "std::out_of_range" };
    inline const std::string kBadAllocErrorType         { "std::bad_alloc" };
    inline const std::string kInvalidArgumentErrorType  { "std::invalid_argument" };
    inline const std::string kDomainErrorType           { "std::domain_error" };
    inline const std::string kLengthErrorType           { "std::length_error" };
    inline const std::string kRangeErrorType            { "std::range_error" };
    inline const std::string kOverflowErrorType         { "std::overflow_error" };
    inline const std::string kUnderflowErrorType        { "std::underflow_error" };
    inline const std::string kFatalErrorType            { "..." };

    int LogicErrorHandle(const std::logic_error& error);
    int RuntimeErrorHandle(const std::runtime_error& error);
    int OutOfRangeErrorHandle(const std::out_of_range& error);
    int BadAllocErrorHandle(const std::bad_alloc& error);
    int InvalidArgumentErrorHandle(const std::bad_alloc& error);
    int DomainErrorHandle(const std::bad_alloc& error);
    int LengthErrorHandle(const std::bad_alloc& error);
    int RangeErrorHandle(const std::bad_alloc& error);
    int OverflowErrorHandle(const std::bad_alloc& error);
    int UnderflowErrorHandle(const std::bad_alloc& error);
    int FatalErrorHandle();

    template<typename ErrorType> requires std::derived_from<ErrorType, std::exception>
    inline void StandardErrorHandle(const ErrorType& error, const std::string& error_name,
        const std::string& error_type) {
        std::cout << kTryCatchMessage;
        std::cout << kErrorTypeMessage << error_type << '\n';
        std::cerr << error_name + kErrorWhatMesssage << error.what();
    }


#ifdef FILE_SYSTEM_EXCEPTION_HANDLING
    inline constexpr int kFilesystemErrorCode       { -13 };
    inline const std::string kFilesystemErrorName   { "Filesystem" };
    inline const std::string kFilesystemErrorType   { "boost::filesystem::filesystem_error" };

    inline int FilesystemErrorHandle(const boost::filesystem::filesystem_error& error) {
        std::cout << kTryCatchMessage;
        std::cout << kErrorTypeMessage << kFilesystemErrorType << '\n';
        std::cerr << "code " << error.code() << '\n';
        std::cerr << "path1 " << error.path1() << '\n';
        std::cerr << "path2 " << error.path2() << '\n';
        std::cerr << "what " << error.what() << '\n';
        return kFilesystemErrorCode;
    }
#endif // FILE_SYSTEM_EXCEPTION_HANDLING

} // !namespace errors

#endif // !EXCEPTION_HANDLING_CONSOLE_HPP_