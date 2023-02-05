#include "delete-files-from-multiple-dirs.hpp"

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
    const std::string kDeleteFilesModuleName{ "Delete From Multiple Dirs" };

    const std::wstring kDeleteFromMultipleDirsSection   { L"DeleteFromMultipleDirs" };
    const std::wstring kTargetDirectoriesIniKey         { L"target_directories" };
    const std::wstring kDeletingFileNamesIniKey         { L"deleting_file_names" };
    const std::wstring kDeleteFromAllSubfoldersIniKey   { L"delete_from_all_subfolders" };

    //void ReadIniFile

    /// Copy one or many files in selected dirs
    int DeleteFilesFromMultipleDirs() {
        try {
            const bool is_module_active_ini{ ReadBoolFromIni(kDeleteFromMultipleDirsSection, kIsModuleActiveIniKey, ini_path) };
            if (is_module_active_ini) {
                std::cout << kDeleteFilesModuleName + msg_process_start;
                const std::string process_message{ "Deleting from folder " };

                const std::list<std::wstring> target_directories_wstr{ GetIniValuesList(ReadWStringFromIni(kDeleteFromMultipleDirsSection,
                                                                                                        kTargetDirectoriesIniKey, ini_path)) };
                const std::list<boost::filesystem::path> target_directories{ PathListFromWStringList(target_directories_wstr) };
                const std::wstring deleting_file_names_ini{ ReadWStringFromIni(kDeleteFromMultipleDirsSection,
                                                                                kDeletingFileNamesIniKey, ini_path) };
                const bool is_delete_from_subfolders{ ReadBoolFromIni(kDeleteFromMultipleDirsSection,
                                                                      kDeleteFromAllSubfoldersIniKey, ini_path) };

                const std::list<std::wstring> deleting_file_names{ GetIniValuesList(deleting_file_names_ini) };

                std::list<bool> copy_results{};
                if (is_delete_from_subfolders) { // Add to all subfolders copied files
                    for (const boost::filesystem::path& target_directory : target_directories) { // Calc all target directories
                        for (auto const& dir_entry : boost::filesystem::directory_iterator{ target_directory }) {
                            if (boost::filesystem::is_directory(dir_entry)) {
                                DeleteFilesFromDir(deleting_file_names, dir_entry);
                                std::cout << process_message << dir_entry << '\n';
                            }
                        }
                    }
                } else { // Add copied files only to target folder
                    for (const boost::filesystem::path& target_directory : target_directories) {
                        DeleteFilesFromDir(deleting_file_names, target_directory);
                        std::cout << process_message << target_directory << '\n';
                    }
                }

                std::cout << kDeleteFilesModuleName + msg_process_end;
            } else {
                std::cout << kDeleteFilesModuleName + msg_module_disabled;
            }
            std::cout << "\n";
            return 0;
        }
        catch (const boost::filesystem::filesystem_error& error) { return errors::FilesystemErrorHandle(error); }
        catch (const std::runtime_error& error) { return errors::RuntimeErrorHandle(error); }
        catch (...) { return errors::FatalErrorHandle(); }
    }
} // !namespace admin_tasks