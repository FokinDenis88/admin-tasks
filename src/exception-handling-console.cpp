#include "exception-handling-console.hpp"


// Macroses: FILE_SYSTEM_EXCEPTION_HANDLING

namespace errors {
    /// logic_error - exception class to indicate violations of logical preconditions or class invariants
    int LogicErrorHandle(const std::logic_error& error) {
        StandardErrorHandle(error, kLogicErrorName, kLogicErrorType);
        return kLogicErrorCode;
    }

    /// runtime_error - exception class to indicate conditions only detectable at run time
    int RuntimeErrorHandle(const std::runtime_error& error) {
        StandardErrorHandle(error, kRuntimeErrorName, kRuntimeErrorType);
        return kRuntimeErrorCode;
    }

    /// out_of_range - exception class to report arguments outside of expected range
    int OutOfRangeErrorHandle(const std::out_of_range& error) {
        StandardErrorHandle(error, kOutOfRangeErrorName, kOutOfRangeErrorType);
        return kOutOfRangeErrorCode;
    }

    int BadAllocErrorHandle(const std::bad_alloc& error) {
        StandardErrorHandle(error, kBadAllocErrorName, kBadAllocErrorType);
        return kBadAllocErrorCode;
    }

    /// invalid_argument - exception class to report invalid arguments
    int InvalidArgumentErrorHandle(const std::invalid_argument& error) {
        StandardErrorHandle(error, kInvalidArgumentErrorName, kInvalidArgumentErrorType);
        return kInvalidArgumentErrorCode;
    }

    /// domain_error - exception class to report domain errors
    int DomainErrorHandle(const std::domain_error& error) {
        StandardErrorHandle(error, kDomainErrorName, kDomainErrorType);
        return kDomainErrorCode;
    }

    /// length_error - exception class to report attempts to exceed maximum allowed size
    int LengthErrorHandle(const std::length_error& error) {
        StandardErrorHandle(error, kLengthErrorName, kLengthErrorType);
        return kLengthErrorCode;
    }

    /// range_error - exception class to report range errors in internal computations
    int RangeErrorHandle(const std::range_error& error) {
        StandardErrorHandle(error, kRangeErrorName, kRangeErrorType);
        return kRangeErrorCode;
    }

    /// overflow_error - exception class to report arithmetic overflows
    int OverflowErrorHandle(const std::overflow_error& error) {
        StandardErrorHandle(error, kOverflowErrorName, kOverflowErrorType);
        return kOverflowErrorCode;
    }

    /// underflow_error - exception class to report arithmetic underflows
    int UnderflowErrorHandle(const std::underflow_error& error) {
        StandardErrorHandle(error, kUnderflowErrorName, kUnderflowErrorType);
        return kUnderflowErrorCode;
    }

    /// Not recognized type of error
    int FatalErrorHandle() {
        std::cout << kTryCatchMessage;
        std::cout << kErrorTypeMessage << kFatalErrorType << '\n';
        std::cerr << kFatalErrorName + " error";
        return kFatalErrorCode;
    }

} // !namespace errors

