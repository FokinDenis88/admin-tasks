#include "general.hpp"

#include <boost/regex.hpp>
//#include <regex>
#include <utility>      // for std::move()
#include <Windows.h>    // for GetPrivateProfileStringW

namespace admin_tasks {
    std::wstring ReadWStringFromIni(const std::wstring& section, const std::wstring& key_name, const std::filesystem::path& ini_path) {
        std::wstring ini_buffer{};
        ini_buffer.resize(kPathCharCount);
        size_t readed_chars = GetPrivateProfileStringW(section.c_str(), key_name.c_str(), nullptr, &ini_buffer[0], kPathCharCount, ini_path.c_str());
        return ini_buffer.substr(0, readed_chars);
    }


    /// Get List of values, when one ini value consists list of values separated by char '|'
    std::list<std::wstring> GetIniValuesList(const std::wstring& ini_values) {
        std::list<std::wstring> values_list{};

        // "(?<=\A)[^\|]+(?=\z)|[^\|]+(?=\|)|(?<=\|)[^\|]+(?=\z)"
        boost::wregex pattern{ L"(?<=\\A)[^\\|]+(?=\\z)|[^\\|]+(?=\\|)|(?<=\\|)[^\\|]+(?=\\z)" };
        boost::wsregex_iterator begin(ini_values.begin(), ini_values.end(), pattern);
        const boost::wsregex_iterator end = boost::wsregex_iterator();
        for (boost::wsregex_iterator i = begin; i != end; ++i) {
            values_list.push_back(i->str());
        }

        return values_list;
    }
    // "(?<separator>\|)(?<value>[^\k<separator>]+)(?=\k<separator>)|(?<=\k<separator>)\k<value>(?=\z)"
    // "(?<value>[^\|]+)(?=\|)|(?<=\|)\k<value>(?=\z)"

    /// Returns List of paths connecting directory and list of file names
    PathsList GetSourceFilesPaths(const std::filesystem::path& dir, const std::list<std::wstring>& names) {
        PathsList paths{};
        std::filesystem::path buffer_path{};
        for (const std::wstring& file_name : names) {
            buffer_path = dir;
            paths.emplace_back(std::move(buffer_path /= file_name));
        }
        return paths;
    }

    bool CopyFileToDir(const std::filesystem::path& source_file_path, const std::filesystem::path& target_dir,
        const std::filesystem::copy_options& copy_options_p) {
        std::filesystem::path target_path = target_dir;
        target_path /= source_file_path.filename();
        return std::filesystem::copy_file(source_file_path, target_path, copy_options_p);
    }

    std::list<bool> CopyFilesToDir(const std::list<std::filesystem::path>& source_files_paths, const std::filesystem::path& target_dir,
        const std::filesystem::copy_options& copy_options_p) {
        std::list<bool> copy_results{};
        for (const std::filesystem::path& source_file_path : source_files_paths) {
            copy_results.push_back(CopyFileToDir(source_file_path, target_dir, copy_options_p));
        }
        return copy_results;
    }


    void SevenZipCommandW(const std::wstring& zip_app_path, const std::wstring& command, const std::wstring& switches,
                          const std::wstring& full_path_archive_name,
                          const std::wstring& full_path_file_name, const bool wait_flag) {
        std::wstring buffer{};
        buffer += command + L" ";
        buffer += switches + L" ";
        buffer += full_path_archive_name + L" ";
        buffer += full_path_file_name;
        std::wstring console_command{ L'\"' + zip_app_path + L"\" " + buffer };

        STARTUPINFOW startup_info{};
        ZeroMemory(&startup_info, sizeof(startup_info));
        startup_info.cb = sizeof(startup_info);

        PROCESS_INFORMATION process_info{};
        ZeroMemory(&process_info, sizeof(process_info));

        CreateProcessW(nullptr, &console_command[0], nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS, nullptr, nullptr, &startup_info, &process_info);
        if (wait_flag) { WaitForSingleObject(process_info.hProcess, INFINITE); }
    }

    void SevenZipCommandShellExecW(const std::wstring& zip_app_path, const std::wstring& command, const std::wstring& switches,
                                    const std::wstring& full_path_archive_name,
                                    const std::wstring& full_path_file_name) {
        std::wstring buffer{};
        buffer += command + L" ";
        buffer += switches + L" ";
        buffer += full_path_archive_name + L" ";
        buffer += full_path_file_name;
        const wchar_t* console_command{ buffer.c_str() };
        HINSTANCE retVal = ShellExecuteW(NULL, L"open", zip_app_path.c_str(), console_command, NULL, SW_NORMAL);
    }
    //_wsystem(console_command);

    /// Support Function for Creating List of Paths
    std::list<std::filesystem::path> PathListFromWStringList(const std::list<std::wstring>& wstr_path_list) {
        std::list<std::filesystem::path> path_list{};
        for (const std::wstring& path_wstr : wstr_path_list) {
            path_list.emplace_back(path_wstr);
        }
        return path_list;
    }


} // !namespace admin_tasks
