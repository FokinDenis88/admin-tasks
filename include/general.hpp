#ifndef GENERAL_HPP_
#define GENERAL_HPP_

#include <string>
#include <filesystem>
#include <list>
#include <set>  // for zip set

#include "boost/filesystem.hpp"

namespace admin_tasks {
    using PathsList = std::list<boost::filesystem::path>;

    inline const std::wstring kIniFileName          { L"admin-tasks.ini" };
    inline const std::wstring kIsModuleActiveIniKey { L"is_module_active" };

    inline constexpr size_t kPathCharCount      { 500 };
    inline constexpr size_t kBoolKeyCharCount   { 10 };

    inline const std::string msg_process_start      { " process has been started\n" };
    inline const std::string msg_process_end        { " process has been ended\n" };
    inline const std::string msg_module_disabled    { " module is disabled" };

    inline const std::wstring kSourceCodeDir{ LR"(C:\Development\Projects\IT\Programming\git-web\public\admin-tasks)" };
    //inline const boost::filesystem::path ini_path{ kSourceCodeDir + L"\\" + kIniFileName };
    inline const boost::filesystem::path ini_path{ boost::filesystem::current_path().append(kIniFileName) };

    //inline const boost::filesystem::path ini_path{ boost::filesystem::current_path() /= kIniFileName };
    //boost::filesystem::path current_working_directory{ boost::filesystem::current_path() };

    inline const std::wstring kLogDirW{ kSourceCodeDir + L"\\log" };
    inline const std::string kLogDirA{ R"(C:\Development\Projects\IT\Programming\!git-web\public\admin-tasks\log)" };


    inline bool GetBoolFromStr(const std::wstring& str) {
        if (L"true" == str) {
            return true;
        } else if (L"false" == str) {
            return false;
        }
        return false;   // error in parsing
    }

    std::wstring ReadWStringFromIni(const std::wstring& section, const std::wstring& key_name, const boost::filesystem::path& ini_path);
    inline bool ReadBoolFromIni(const std::wstring& section, const std::wstring& key_name, const boost::filesystem::path& ini_path) {
        return GetBoolFromStr(ReadWStringFromIni(section, key_name, ini_path));
    }

    std::list<std::wstring> GetIniValuesList(const std::wstring& ini_value);
    PathsList GetSourceFilesPaths(const boost::filesystem::path& dir, const std::list<std::wstring>& names);

    bool CopyFileToDir(const boost::filesystem::path& source_file_path, const boost::filesystem::path& target_dir,
                       const boost::filesystem::copy_options& copy_options_p = boost::filesystem::copy_options::none);
    std::list<bool> CopyFilesToDir(const std::list<boost::filesystem::path>& source_files_paths, const boost::filesystem::path& target_dir,
                                   const boost::filesystem::copy_options& copy_options_p = boost::filesystem::copy_options::none);

    void DeleteFilesFromDir(const std::list<std::wstring>& file_names, const boost::filesystem::path& target_dir);
    void DeleteFilesFromDirs(const std::list<std::wstring>& file_names, const std::list<boost::filesystem::path>& target_dirs);

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

    std::list<boost::filesystem::path> PathListFromWStringList(const std::list<std::wstring>& wstr_path_list);

} // !namespace admin_tasks

#endif // !GENERAL_HPP_