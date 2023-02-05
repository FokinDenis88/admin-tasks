#include "tag-management.hpp"

#include <iostream>
#include <string>
#include <set>
#include <algorithm>    ; For search in list

#include "boost/filesystem.hpp"

#define FILE_SYSTEM_EXCEPTION_HANDLING
#include "tag-path.hpp"
#include "general.hpp"
#include "exception-handling-console.hpp"
#include "errors-handler-file-operations.hpp"
#include "file-service.hpp" // For CorrectOS Name


namespace admin_tasks {
    const std::string kTagManagementModuleName  { "Tag Management" };
    const std::wstring kTagManagementSection    { L"TagManagement" };
    const std::wstring kTargetDirectoriesIniKey { L"target_directories" };
    const std::wstring kSubDirsFlagIniKey       { L"subdirs_flag" };
    const std::wstring kSubDirsFilterIniKey     { L"subdirs_filter" };
    const std::wstring kCommandIniKey           { L"command" };
    const std::wstring kTagSeparatorIniKey      { L"tag_separator" };
    const std::wstring kTagNameIniKey           { L"tag_name" };
    const std::wstring kNewFullTagIniKey        { L"new_full_tag" };

    const std::wstring kAddTagsCommand      { L"AddTags" };
    const std::wstring kDeleteTagsCommand   { L"DeleteTags" };
    const std::wstring kReplaceTagsCommand  { L"ReplaceTags" };
    const std::set<std::wstring> kSetOfCommands { kAddTagsCommand, kDeleteTagsCommand,  kReplaceTagsCommand };

    int ManageTagsInSubfolders() {
        try {
            const bool is_module_active_ini{ ReadBoolFromIni(kTagManagementSection, kIsModuleActiveIniKey, ini_path) };
            if (is_module_active_ini) {
                std::cout << kTagManagementModuleName + msg_process_start;

                const std::list<std::wstring> target_directories_wstr{ GetIniValuesList(ReadWStringFromIni(kTagManagementSection,                                                                                       kTargetDirectoriesIniKey, ini_path)) };
                const std::list<boost::filesystem::path> target_directories{ PathListFromWStringList(target_directories_wstr) };


                const bool subdirs_flag{ ReadBoolFromIni(kTagManagementSection, kSubDirsFlagIniKey, ini_path) };
                const std::list<std::wstring> subdirs_filter_wstr{ GetIniValuesList(ReadWStringFromIni(kTagManagementSection,                                                                                       kSubDirsFilterIniKey, ini_path)) };
                const std::list<boost::filesystem::path> subdirs_filter{ PathListFromWStringList(subdirs_filter_wstr) };

                const std::wstring command{ ReadWStringFromIni(kTagManagementSection, kCommandIniKey, ini_path) };
                std::wstring tag_separator{ ReadWStringFromIni(kTagManagementSection, kTagSeparatorIniKey, ini_path) };
                if (tag_separator.empty()) { tag_separator = file::kDefaultTagSeparatorW; }
                const std::wstring tag_name{ ReadWStringFromIni(kTagManagementSection, kTagNameIniKey, ini_path) };
                const std::wstring new_full_tag{ ReadWStringFromIni(kTagManagementSection, kNewFullTagIniKey, ini_path) };

                std::wstring wstr = file::GetFolderTag(boost::filesystem::path(L"C:\\Development\\Projects\\!Programming\\!git-web\\open-source\\admin-tasks\\test\\!Tags-test\\New folder - Copy (2)___textures.com"), std::wstring(L"___"));

                if (!tag_separator.empty() || !tag_name.empty()) {
                    const std::wstring full_tag{ tag_separator + tag_name };

                    std::list<boost::filesystem::path> real_target_directories{};
                    if (subdirs_flag) {
                        for (const boost::filesystem::path& target_directory : target_directories) { // Calc all target directories
                            for (auto const& dir_entry : boost::filesystem::directory_iterator{ target_directory }) {
                                if (boost::filesystem::is_directory(dir_entry)) {
                                    if ( subdirs_filter.empty() ||
                                        std::find(subdirs_filter.cbegin(), subdirs_filter.cend(),
                                            dir_entry.path().filename()) != subdirs_filter.cend() )
                                    real_target_directories.emplace_back(dir_entry.path());
                                }
                            }
                        }
                    } else {
                        real_target_directories = target_directories;
                    }

                    for (const boost::filesystem::path& target_directory : real_target_directories) { // Calc all target directories
                        for (auto const& dir_entry : boost::filesystem::directory_iterator{ target_directory }) {
                            if (boost::filesystem::is_directory(dir_entry)) {

                                const boost::filesystem::path dir_path{ dir_entry.path() };

                                if (kSetOfCommands.contains(command)) {
                                    if (kAddTagsCommand == command) {
                                        file::AddTagToFolder(dir_path, full_tag);
                                        std::wcout << full_tag << L" has been added to " << dir_path << L"\n";
                                    }
                                    else if (kDeleteTagsCommand == command) {
                                        file::DeleteTagFromFolder(dir_path, full_tag);
                                        std::wcout << full_tag << L" has been deleted from " << dir_path << L"\n";
                                    }
                                    else if (kReplaceTagsCommand == command) {
                                        file::ReplaceTagFromFolder(dir_path, full_tag, new_full_tag);
                                        std::wcout << full_tag << L" has been replaced from " << dir_path << L"\n";
                                    }
                                }
                                else { std::cout << "Undeclared tag command in ini file.\n"; }
                            }
                        }
                    } // !Calc all target directories
                } else { std::cout << "Please setup Tag separator or Tag name.\n"; }

                std::cout << kTagManagementModuleName + msg_process_end;
            } else {
                std::cout << kTagManagementModuleName + msg_module_disabled;
            }
            std::cout << "\n";
            return 0;
        }
        catch (const boost::filesystem::filesystem_error& error) { return errors::FilesystemErrorHandle(error); }
        catch (const std::runtime_error& error) { return errors::RuntimeErrorHandle(error); }
        catch (...) { return errors::FatalErrorHandle(); }
    }

} // !namespace admin_tasks