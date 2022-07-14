#ifndef GENERAL_HPP_
#define GENERAL_HPP_

#include <string>
#include <filesystem>
#include <list>
#include <set>  // for zip set

namespace admin_tasks {
    using PathsList = std::list<std::filesystem::path>;

    inline const std::wstring kIniFileName          { L"admin-tasks.ini" };
    inline const std::wstring kIsModuleActiveIniKey { L"is_module_active" };

    inline constexpr size_t kPathCharCount      { 500 };
    inline constexpr size_t kBoolKeyCharCount   { 10 };

    inline const std::string msg_process_start      { " process has been started\n" };
    inline const std::string msg_process_end        { " process has been ended\n" };
    inline const std::string msg_module_disabled    { " module is disabled" };

    inline const std::wstring kSourceCodeDir{ L"C:\\Development\\Projects\\!Programming\\!it-projects\\!best-projects\\admin-tasks\\" + kIniFileName };
    inline const std::filesystem::path ini_path{ kSourceCodeDir };
    //inline const std::filesystem::path ini_path{ std::filesystem::current_path() /= kIniFileName };
    //std::filesystem::path current_working_directory{ std::filesystem::current_path() };



    inline bool GetBoolFromStr(const std::wstring& str) {
        if (L"true" == str) {
            return true;
        } else if (L"false" == str) {
            return false;
        }
        return false;   // error in parsing
    }

    std::wstring ReadWStringFromIni(const std::wstring& section, const std::wstring& key_name, const std::filesystem::path& ini_path);
    inline bool ReadBoolFromIni(const std::wstring& section, const std::wstring& key_name, const std::filesystem::path& ini_path) {
        return GetBoolFromStr(ReadWStringFromIni(section, key_name, ini_path));
    }

    std::list<std::wstring> GetIniValuesList(const std::wstring& ini_value);
    PathsList GetSourceFilesPaths(const std::filesystem::path& dir, const std::list<std::wstring>& names);

    bool CopyFileToDir(const std::filesystem::path& source_file_path, const std::filesystem::path& target_dir,
                       const std::filesystem::copy_options& copy_options_p = std::filesystem::copy_options::none);
    std::list<bool> CopyFilesToDir(const std::list<std::filesystem::path>& source_files_paths, const std::filesystem::path& target_dir,
                                   const std::filesystem::copy_options& copy_options_p = std::filesystem::copy_options::none);

    const std::set<std::wstring> kArchiveExtensions{ L".7z", L".rar", L".zip", L".tar.bz2", L".tar.gz", L".zipx" };

    /// Command to 7-zip application
    /// Console: 7z.exe "command"   "switches"   "full_path_archive_name"   "full_path_file_name"
    /// https://info.nrao.edu/computing/guide/file-access-and-archiving/7zip/7z-7za-command-line-guide
    /// https://www.7-zip.org/sdk.html
    void SevenZipCommandW(const std::wstring& zip_app_path, const std::wstring& command, const std::wstring& switches,
                          const std::wstring& full_path_archive_name,
                          const std::wstring& full_path_file_name, const bool wait_flag = true);


    /// Command to 7-zip application
    /// Console: 7z.exe "command"   "switches"   "full_path_archive_name"   "full_path_file_name"
    /// https://info.nrao.edu/computing/guide/file-access-and-archiving/7zip/7z-7za-command-line-guide
    /// https://www.7-zip.org/sdk.html
    [[deprecated]]
    void SevenZipCommandShellExecW(const std::wstring& zip_app_path, const std::wstring& command, const std::wstring& switches,
                                    const std::wstring& full_path_archive_name,
                                    const std::wstring& full_path_file_name);

    std::list<std::filesystem::path> PathListFromWStringList(const std::list<std::wstring>& wstr_path_list);

} // !namespace admin_tasks

#endif // !GENERAL_HPP_