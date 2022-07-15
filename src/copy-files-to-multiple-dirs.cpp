#include "copy-files-to-multiple-dirs.hpp"

#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <list>
#include <exception>
#include <stdexcept>

#include "boost/filesystem.hpp"

//#include "boost"

#include "general.hpp"
#define FILE_SYSTEM_EXCEPTION_HANDLING
#include "exception-handling-console.hpp"

namespace admin_tasks {
    const std::string kCopyModuleName{ "Copy to multiple dirs" };

    const std::wstring kCopyToMultipleDirsSection   { L"CopyToMultipleDirs" };
    const std::wstring kTargetDirectoriesIniKey     { L"target_directories" };
    const std::wstring kSourceFilesDirectoryIniKey  { L"source_files_directory" };
    const std::wstring kSourceFilesNamesListIniKey  { L"source_files_names_list" };
    const std::wstring kSubfoldersIniKey            { L"copy_to_all_subfolders" };

    //void ReadIniFile

    /// Copy one or many files in selected dirs
    int CopyFilesToMultipleDirs() {
        try {
            const bool is_module_active_ini{ ReadBoolFromIni(kCopyToMultipleDirsSection, kIsModuleActiveIniKey, ini_path) };
            if (is_module_active_ini) {
                std::cout << kCopyModuleName + msg_process_start;

                const std::list<std::wstring> target_directories_wstr{ GetIniValuesList(ReadWStringFromIni(kCopyToMultipleDirsSection, kTargetDirectoriesIniKey, ini_path)) };
                const std::list<boost::filesystem::path> target_directories{ PathListFromWStringList(target_directories_wstr) };
                const boost::filesystem::path source_files_directory  { ReadWStringFromIni(kCopyToMultipleDirsSection, kSourceFilesDirectoryIniKey, ini_path) };
                const std::wstring source_files_names_list_ini      { ReadWStringFromIni(kCopyToMultipleDirsSection, kSourceFilesNamesListIniKey, ini_path) };
                const bool is_copy_subfolders                          { ReadBoolFromIni(kCopyToMultipleDirsSection, kSubfoldersIniKey, ini_path) };

                const std::list<std::wstring> source_files_names{ GetIniValuesList(source_files_names_list_ini) };
                const PathsList source_files_paths{ GetSourceFilesPaths(source_files_directory, source_files_names) };

                std::list<bool> copy_results{};
                if (is_copy_subfolders) { // Add to all subfolders copied files
                    for (const boost::filesystem::path& target_directory : target_directories) { // Calc all target directories
                        for (auto const& dir_entry : boost::filesystem::directory_iterator{ target_directory }) {
                            if (boost::filesystem::is_directory(dir_entry)) {
                                CopyFilesToDir(source_files_paths, dir_entry, boost::filesystem::copy_options::skip_existing);
                                std::cout << "Coping to folder " << dir_entry << '\n';
                            }
                        }
                    }
                } else { // Add copied files only to target folder
                    for (const boost::filesystem::path& target_directory : target_directories) {
                        CopyFilesToDir(source_files_paths, target_directory, boost::filesystem::copy_options::skip_existing);
                        std::cout << "Coping to folder " << target_directory << '\n';
                    }
                }

                std::cout << kCopyModuleName + msg_process_end;
            } else {
                std::cout << kCopyModuleName + msg_module_disabled;
            }
            std::cout << "\n";
            return 0;
        }
        catch (const boost::filesystem::filesystem_error& error)  { return errors::FilesystemErrorHandle(error); }
        catch (const std::runtime_error& error)                 { return errors::RuntimeErrorHandle(error); }
        catch (...)                                             { return errors::FatalErrorHandle(); }
    }
} // !namespace admin_tasks


/*std::cout << "Where to copy files?";
std::cout << "What files should i copy?";
std::cout << "Copy in all subdirectories?";*/