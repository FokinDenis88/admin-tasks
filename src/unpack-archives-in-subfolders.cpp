#include "unpack-archives-in-subfolders.hpp"

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include <Windows.h>    // for ShellExecute

//#include "boost/c"
#include "boost/filesystem.hpp"

#include "general.hpp"
#define FILE_SYSTEM_EXCEPTION_HANDLING
#include "exception-handling-console.hpp"
#include "write-text-file.hpp"
#include "logs-support.hpp"
#include "file-service.hpp" // For CorrectOS Name

// Delete file archive after extraction. Possible Loss of Data.
//#define DATA_LOSSY

namespace admin_tasks {
    /// Maximum count of archives extracted simultaneously
    constexpr size_t extraction_max{ 100 };
    const std::string kArchiveSubfoldersModuleName{ "Unpack all archives in subfolders" };

    const std::wstring kUnpackArchivesSection   { L"UnpackArchivesSubfolders" };
    const std::string kUnpackArchivesSectionA   { "UnpackArchivesSubfolders" };
    const std::wstring kZipAppIniKey            { L"zip_app_path" };
    const std::wstring kTargetDirectoriesIniKey { L"target_directories" };
    const std::wstring kDeleteArchiveIniKey     { L"to_delete_archive" };
    const std::wstring kRepeatIniKey            { L"repeat_count" };

    void WriteUnpackLogs(const std::list<boost::filesystem::path>&target_directories,
                         const std::list<boost::filesystem::path>& all_archive_file_paths) {
        std::wcout << L"Writing logs.\n";
        std::string log_name{ logs::DateTimeFormat() + "  " + kUnpackArchivesSectionA + logs::kLogExtension };
        log_name = file::CorrectNameForOS(log_name, "-");
        std::string log_path{ kLogDirA + '\\' + log_name };
        for (const boost::filesystem::path& target_directory : target_directories) {
            file::WriteTextFile(log_path, L"Target Directory: " + target_directory.wstring() + L'\n');
        }
        file::WriteTextFile(log_path, std::wstring(L"\n\n"));
        for (const boost::filesystem::path& path : all_archive_file_paths) {
            std::wcout << path << L'\n';
            file::WriteTextFile(log_path, path.wstring() + L"\n");
        }
        file::WriteTextFile(log_path, std::wstring(L"\n\n"));
    }

    int UnpackArchivesInSubfolders() {
        try {
            const bool is_module_active_ini{ ReadBoolFromIni(kUnpackArchivesSection, kIsModuleActiveIniKey, ini_path) };
            if (is_module_active_ini) {
                std::cout << kArchiveSubfoldersModuleName + msg_process_start;

                const boost::filesystem::path zip_app_path{ ReadWStringFromIni(kUnpackArchivesSection, kZipAppIniKey, ini_path) };
                const std::list<std::wstring> target_directories_wstr{ GetIniValuesList(ReadWStringFromIni(kUnpackArchivesSection, kTargetDirectoriesIniKey, ini_path)) };
                const std::list<boost::filesystem::path> target_directories{ PathListFromWStringList(target_directories_wstr) };
                const bool to_delete_archive{ ReadBoolFromIni(kUnpackArchivesSection, kDeleteArchiveIniKey, ini_path) };
                const size_t repeat_count = GetPrivateProfileIntW(kUnpackArchivesSection.c_str(), kRepeatIniKey.c_str(), 0, ini_path.c_str());

                std::list<boost::filesystem::path> all_archive_file_paths{};

                for (size_t i = 0; i < repeat_count; ++i) {
                    for (const boost::filesystem::path& target_directory : target_directories) { // Calc all target directories
                        for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{ target_directory }) {
                            const boost::filesystem::path entry_path{ dir_entry.path() };
                            if (dir_entry.is_regular_file() && kArchiveExtensions.contains(entry_path.extension())) {
                                if (i == repeat_count - 1) { all_archive_file_paths.emplace_back(entry_path); }
                                boost::filesystem::path target_dir_path{ entry_path.parent_path() };
                                target_dir_path /= entry_path.stem();
                                if (!boost::filesystem::exists(target_dir_path)) { // Create directory for zip files contents
                                    std::filesystem::create_directory(target_dir_path);
                                }
                                //std::wcout << "Extracting file: " << dir_entry << '\n';

                                /// https://info.nrao.edu/computing/guide/file-access-and-archiving/7zip/7z-7za-command-line-guide
                                /// -aos: Skip existing files -o: Output directory
                                std::wstring output_dir_switch{ L"-aos -o\"" + target_dir_path.wstring() + L'\"' };
                                SevenZipCommandW(zip_app_path.wstring(), L"x", output_dir_switch, L'\"' + entry_path.wstring() + L'\"', L"");
#ifdef DATA_LOSSY
                                // Disabled for prevention of data losses
                                if (to_delete_archive) {
                                    std::cout << "Deleting archive file: " << dir_entry << '\n';
                                    std::filesystem::remove(dir_entry);
                                }
#endif // DATA_LOSSY
                            }
                        }
                    } // !Calc all target directories
                }
                std::cout << kArchiveSubfoldersModuleName + msg_process_end << "\n\n";
                std::wcout << L"Files, that have been extracted:\n";

                WriteUnpackLogs(target_directories, all_archive_file_paths);
            }
            std::cout << "\n";
            return 0;
        }
        catch (const std::filesystem::filesystem_error& error)  { return errors::FilesystemErrorHandle(error); }
        catch (const std::runtime_error& error)                 { return errors::RuntimeErrorHandle(error); }
        catch (...)                                             { return errors::FatalErrorHandle(); }
    }
} // !namespace admin_tasks