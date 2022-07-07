#include "copy-files-to-multiple-dirs.hpp"

#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <list>


#include "general.hpp"

namespace admin_tasks {
    const std::wstring kCopyToMultipleDirsSection   { L"CopyToMultipleDirs" };
    const std::wstring kTargetDirectoryIniKey       { L"target_directory" };
    const std::wstring kSourceFilesDirectoryIniKey  { L"source_files_directory" };
    const std::wstring kSourceFilesNamesListIniKey  { L"source_files_names_list" };
    const std::wstring kSubfoldersIniKey            { L"copy_to_all_subfolders" };

    //void Read

    /// Copy one or many files in selected dirs
    void CopyFilesToMultipleDirs() {
        std::wstring ini_buffer{};
        ini_buffer.resize(kPathCharCount);
        size_t readed_chars  = GetPrivateProfileStringW(kCopyToMultipleDirsSection.c_str(), kIsModuleActiveIniKey.c_str(),
                                 nullptr, &ini_buffer[0], kPathCharCount, ini_path.c_str());
        bool is_module_active_ini{ GetBoolFromIniStr(ini_buffer.substr(0, readed_chars)) };

        if (is_module_active_ini) {
            std::cout << "Coping" + msg_process_start;

            readed_chars = GetPrivateProfileStringW(kCopyToMultipleDirsSection.c_str(), kTargetDirectoryIniKey.c_str(),
                                     nullptr, &ini_buffer[0], kPathCharCount, ini_path.c_str());
            const std::wstring target_directory{ ini_buffer.substr(0, readed_chars) };

            readed_chars = GetPrivateProfileStringW(kCopyToMultipleDirsSection.c_str(), kSourceFilesDirectoryIniKey.c_str(),
                                     nullptr, &ini_buffer[0], kPathCharCount, ini_path.c_str());
            const std::wstring source_files_directory{ ini_buffer.substr(0, readed_chars) };


            readed_chars = GetPrivateProfileStringW(kCopyToMultipleDirsSection.c_str(), kSourceFilesNamesListIniKey.c_str(),
                                     nullptr, &ini_buffer[0], kPathCharCount, ini_path.c_str());
            const std::wstring source_files_names_list_ini{ ini_buffer.substr(0, readed_chars) };

            readed_chars = GetPrivateProfileStringW(kCopyToMultipleDirsSection.c_str(), kSubfoldersIniKey.c_str(),
                                     nullptr, &ini_buffer[0], kBoolKeyCharCount, ini_path.c_str());
            const bool is_copy_subfolders{ GetBoolFromIniStr(ini_buffer.substr(0, readed_chars)) };


            const std::list<std::wstring> source_files_names{ GetIniValuesList(source_files_names_list_ini)};

            if (is_copy_subfolders) {

            } else {

            }

            std::cout << "Coping" + msg_process_end;
        } else {
            std::cout << "CopyFilesToMultipleDirs" + msg_module_disabled;
        }
    }
} // !namespace admin_tasks


/*std::cout << "Where to copy files?";
std::cout << "What files should i copy?";
std::cout << "Copy in all subdirectories?";*/