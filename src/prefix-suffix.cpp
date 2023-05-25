#include "tag-management.hpp"

#include <iostream>
#include <string>
#include <unordered_set>
#include <list>
#include <algorithm>    ; For search in list

#include "boost/filesystem.hpp"

#define FILE_SYSTEM_EXCEPTION_HANDLING
#include "prefix-suffix-path.hpp"
#include "general.hpp"
#include "exception-handling-console.hpp"
#include "errors-handler-file-operations.hpp"
#include "file-service.hpp" // For CorrectOS Name


namespace admin_tasks {
    const std::string kPrefixSuffixModuleName   { "PrefixSuffix" };
    const std::wstring kPrefixSuffixSection     { L"PrefixSuffix" };
    const std::wstring kTargetDirectoriesIniKey { L"target_directories" };
    const std::wstring kSubDirsFlagIniKey       { L"subdirs_flag" };
    const std::wstring kSubDirsFilterIniKey     { L"subdirs_filter" };
    const std::wstring kCommandIniKey           { L"command" };
    const std::wstring kPrefixIniKey            { L"prefix" };
    const std::wstring kSuffixIniKey            { L"suffix" };
    const std::wstring kNewPrefixIniKey         { L"new_prefix" };
    const std::wstring kNewSuffixIniKey         { L"new_suffix" };
    const std::wstring kWithFileIniKey          { L"with_file" };
    const std::wstring kWithDirectoryIniKey     { L"with_directory" };

    const std::wstring kAddCommand      { L"Add" };
    const std::wstring kDeleteCommand   { L"Delete" };
    const std::wstring kRefreshCommand  { L"Refresh" };
    const std::unordered_set<std::wstring> kSetOfCommands { kAddCommand, kDeleteCommand,  kRefreshCommand };

    const std::wstring kHasBeenAdded{ L" has been added to " };
    const std::wstring kHasBeenDeleted{ L" has been deleted to " };

    bool IsIdle(const std::wstring& command, const std::wstring& prefix, const std::wstring& suffix,
                const std::wstring& new_prefix, const std::wstring& new_suffix) {
        if (command.empty()) { return true; }
        if (command == kAddCommand || command == kDeleteCommand) {
            if (prefix.empty() && suffix.empty()) { return true; }
        } else { // command == kRefreshCommand
            if (prefix.empty() && suffix.empty() && new_prefix.empty() && new_suffix.empty()) {
                return true;
            }
        }

        return false;
    }

    std::list<boost::filesystem::path> FilterDirectories(const std::list<boost::filesystem::path>& target_directories,
                                                        const bool subdirs_flag,
                                                        const std::list<boost::filesystem::path>& subdirs_filter) {
        std::list<boost::filesystem::path> filtered_directories{};
        if (subdirs_flag) {
            for (const boost::filesystem::path& target_directory : target_directories) { // Calc all target directories
                for (auto const& dir_entry : boost::filesystem::directory_iterator{ target_directory }) {
                    if (boost::filesystem::is_directory(dir_entry)) {
                        if (subdirs_filter.empty() ||
                            std::find(subdirs_filter.cbegin(), subdirs_filter.cend(),
                                dir_entry.path().filename()) != subdirs_filter.cend()) // Directory equal to filter condition
                            filtered_directories.emplace_back(dir_entry.path());
                    }
                }
            }
        } else {
            filtered_directories = target_directories;
        }
        return filtered_directories;
    }

    int PrefixSuffix() {
        try {
            const bool is_module_active_ini{ ReadBoolFromIni(kPrefixSuffixSection, kIsModuleActiveIniKey, ini_path) };
            if (is_module_active_ini) {
                std::cout << kPrefixSuffixModuleName + msg_process_start;

                const std::list<std::wstring> target_directories_wstr{
                    GetIniValuesList(ReadWStringFromIni(kPrefixSuffixSection,kTargetDirectoriesIniKey, ini_path))
                };
                const std::list<boost::filesystem::path> target_directories{ PathListFromWStringList(target_directories_wstr) };


                const bool subdirs_flag{ ReadBoolFromIni(kPrefixSuffixSection, kSubDirsFlagIniKey, ini_path) };
                const std::list<std::wstring> subdirs_filter_wstr{ GetIniValuesList(ReadWStringFromIni(kPrefixSuffixSection,                                                                                       kSubDirsFilterIniKey, ini_path)) };
                const std::list<boost::filesystem::path> subdirs_filter{ PathListFromWStringList(subdirs_filter_wstr) };

                const std::wstring command{ ReadWStringFromIni(kPrefixSuffixSection, kCommandIniKey, ini_path) };
                const std::wstring prefix{ ReadWStringFromIni(kPrefixSuffixSection, kPrefixIniKey, ini_path) };
                const std::wstring suffix{ ReadWStringFromIni(kPrefixSuffixSection, kSuffixIniKey, ini_path) };
                const std::wstring new_prefix{ ReadWStringFromIni(kPrefixSuffixSection, kNewPrefixIniKey, ini_path) };
                const std::wstring new_suffix{ ReadWStringFromIni(kPrefixSuffixSection, kNewSuffixIniKey, ini_path) };
                const bool with_file{ ReadBoolFromIni(kPrefixSuffixSection, kWithFileIniKey, ini_path) };
                const bool with_directory{ ReadBoolFromIni(kPrefixSuffixSection, kWithDirectoryIniKey, ini_path) };

                //std::wstring wstr = file::GetFolderTag(boost::filesystem::path(L"C:\\Development\\Projects\\!Programming\\!git-web\\open-source\\admin-tasks\\test\\!Tags-test\\New folder - Copy (2)___textures.com"), std::wstring(L"___"));

                if (!IsIdle(command, prefix, suffix, new_prefix, new_suffix)) {
                    std::list<boost::filesystem::path> real_target_directories{ FilterDirectories(target_directories, subdirs_flag, subdirs_filter) };

                    for (const boost::filesystem::path& target_directory : real_target_directories) { // Calc all target directories
                        for (auto const& dir_entry : boost::filesystem::directory_iterator{ target_directory }) {
                            const bool is_file_target{ with_file && boost::filesystem::is_regular_file(dir_entry) };
                            const bool is_directory_target{ with_directory && boost::filesystem::is_directory(dir_entry) };
                            if (is_file_target || is_directory_target) {
                                const boost::filesystem::path dir_path{ dir_entry.path() };

                                if (kSetOfCommands.contains(command)) {
                                    if (kAddCommand == command) {
                                        file::AddPrefixSuffixToPath(dir_path, prefix, suffix);
                                        if (!prefix.empty()) {
                                            std::wcout << prefix << kHasBeenAdded << dir_path << L"\n";
                                        }
                                        if (!suffix.empty()) {
                                            std::wcout << suffix << kHasBeenAdded << dir_path << L"\n";
                                        }
                                    } else if (kDeleteCommand == command) {
                                        file::DeletePrefixSuffixFromPath(dir_path, prefix, suffix);
                                        if (!prefix.empty()) {
                                            std::wcout << prefix << kHasBeenDeleted << dir_path << L"\n";
                                        }
                                        if (!suffix.empty()) {
                                            std::wcout << suffix << kHasBeenDeleted << dir_path << L"\n";
                                        }
                                    } else if (kRefreshCommand == command) {
                                        file::RefreshPrefixSuffixFromPath(dir_path, prefix, suffix, new_prefix, new_suffix);
                                        std::wcout << prefix << L" And " << suffix << L" has been refreshed in " << dir_path << L"\n";
                                    }
                                } else { std::cout << "Undeclared tag command in ini file.\n"; }
                            }
                        }
                    } // !Calc all target directories
                } else { std::cout << "Please setup prefix, suffix.\n"; }

                std::cout << kPrefixSuffixModuleName + msg_process_end;
            } else {
                std::cout << kPrefixSuffixModuleName + msg_module_disabled;
            }
            std::cout << "\n";
            return 0;
        }
        catch (const boost::filesystem::filesystem_error& error) { return errors::FilesystemErrorHandle(error); }
        catch (const std::runtime_error& error) { return errors::RuntimeErrorHandle(error); }
        catch (...) { return errors::FatalErrorHandle(); }
    }

} // !namespace admin_tasks