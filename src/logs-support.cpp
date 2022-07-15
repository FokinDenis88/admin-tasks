#include "logs-support.hpp"

#include <chrono>

namespace logs {
    std::string CurrentDate() {
        const std::chrono::time_point now{ std::chrono::system_clock::now() };
        const std::chrono::year_month_day current_date{ std::chrono::floor<std::chrono::days>(now) };
        const int year{ static_cast<int>(current_date.year()) };
        const unsigned month{ static_cast<unsigned>(current_date.month()) };
        const unsigned day{ static_cast<unsigned>(current_date.day()) };
        const std::string text{ std::to_string(year) + '.' + std::to_string(month) + '.' + std::to_string(day) };
        return text;
    }

    ///
    /*std::string CurrentTime() {
        const std::chrono::system_clock::time_point now_time = std::chrono::system_clock::now();
        now_time
    }*/

    void AppendLogLine() {

    }

    std::string NowToString() {
        std::chrono::system_clock::time_point now_time = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(now_time);
        char str[26]{};
        ctime_s(str, sizeof str, &time);
        return str;
    }

    std::string DateTime() {
        constexpr size_t char_count{ 26 };
        std::time_t time{ std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) };
        std::string time_str{};
        time_str.resize(char_count);
        ctime_s(&time_str[0], sizeof(time_str[0]) * char_count, &time);
        time_str.pop_back();
        time_str.erase(24, 2);
        return time_str;
    }

    std::string DateTimeFormat(const std::string& format) {
        time_t current_time{ std::time(nullptr) };
        auto tm = *std::localtime(&current_time);
        std::ostringstream oss;
        oss << std::put_time(&tm, format.c_str());
        return oss.str();
    }

} // !namespace logs
