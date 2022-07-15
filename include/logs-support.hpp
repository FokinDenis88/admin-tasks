#ifndef LOGS_SUPPORT_HPP_
#define LOGS_SUPPORT_HPP_

#include <string>

namespace logs {
    const std::string kLogExtension{ ".log" };

    std::string CurrentDate();
    std::string CurrentTime();
    std::string DateTime();
    std::string DateTimeFormat(const std::string& format = "%d-%m-%Y %H-%M-%S");
} // !namespace log

#endif // !LOGS_SUPPORT_HPP_