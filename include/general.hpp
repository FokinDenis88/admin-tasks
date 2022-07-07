#ifndef GENERAL_HPP_
#define GENERAL_HPP_

#include <string>
#include <filesystem>
#include <list>

namespace admin_tasks {
    inline const std::wstring kIniFileName          { L"admin-tasks.ini" };
    inline const std::wstring kIsModuleActiveIniKey { L"is_module_active" };

    inline constexpr size_t kPathCharCount      { 500 };
    inline constexpr size_t kBoolKeyCharCount   { 10 };

    inline const std::string msg_process_start      { " process has been started\n" };
    inline const std::string msg_process_end        { " process has been ended\n" };
    inline const std::string msg_module_disabled    { " module is disabled" };

    inline const std::filesystem::path ini_path{ std::filesystem::current_path() /= kIniFileName };
    //std::filesystem::path current_working_directory{ std::filesystem::current_path() };

    inline bool GetBoolFromIniStr(const std::wstring& str) {
        if (L"true" == str) {
            return true;
        } else if (L"false" == str) {
            return false;
        }
        return false;   // error in parsing
    }

    std::list<std::wstring> GetIniValuesList(const std::wstring& ini_value);

} // !namespace admin_tasks

#endif // !GENERAL_HPP_