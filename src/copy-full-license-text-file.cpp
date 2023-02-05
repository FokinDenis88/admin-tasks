#include "copy-full-license-text-file.hpp"

#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <list>
#include <exception>
#include <stdexcept>

#include "boost/filesystem.hpp"
#include "boost/regex.hpp"

//#include "boost"

#include "general.hpp"
#define FILE_SYSTEM_EXCEPTION_HANDLING
#include "exception-handling-console.hpp"
#include "read-text-file.hpp"

namespace admin_tasks {
    const std::string kCopyLicenseModuleName{ "Copy license full text file" };

    const std::wstring kCopyToMultipleDirsSection{ L"CopyFullLicenseTextFile" };
    const std::wstring kTargetDirectoriesIniKey{ L"target_directories" };
    const std::wstring kSourceFilesDirectoryIniKey{ L"source_files_directory" };
    const std::wstring kSubfoldersIniKey{ L"copy_to_all_subfolders" };
    const std::wstring kRewriteDuplicatesIniKey{ L"rewrite_duplicates" };

    //void ReadIniFile

    const std::wstring kLicenseDirPath{ L"K:\\!Development K\\Projects\\3D Models\\!Other\\!Licenses" };
    const std::wstring kAssetLicenseFileName{ L"license.txt" };



// "CC Attribution" "CC Attribution-ShareAlike" "CC Attribution-NoDerivs" "CC Attribution-NonCommercial"
// "CC Attribution-NonCommercial-ShareAlike" "CC Attribution-NonCommercial-NoDerivs" "CC0 Public Domain"

        /*If StringRegExp($license_text, "CC Attribution") Then
        Return CopyFullLicenseTextFile($asset_folder, "License - CC Attribution 3.0 Unported.txt")

        If StringRegExp($license_text, "CC Attribution-ShareAlike") Then
        Return CopyFullLicenseTextFile($asset_folder, "License - CC Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).txt")

        If StringRegExp($license_text, "CC Attribution-NoDerivs") Then
        Return CopyFullLicenseTextFile($asset_folder, "License - CC Attribution-NoDerivs.txt")

        If StringRegExp($license_text, "CC Attribution-NonCommercial") Then
        Return CopyFullLicenseTextFile($asset_folder, "License - CC Attribution-NonCommercial 4.0 International (CC BY-NC 4.0).txt")

        If StringRegExp($license_text, "CC Attribution-NonCommercial-ShareAlike") Then
        Return CopyFullLicenseTextFile($asset_folder, "License - CC Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0).txt")

        If StringRegExp($license_text, "CC Attribution-NonCommercial-NoDerivs") Then
        Return CopyFullLicenseTextFile($asset_folder, "License - CC Attribution-NonCommercial-NoDerivatives 4.0 International (CC BY-NC-ND 4.0) .txt")

        If StringRegExp($license_text, "CC0 Public Domain") Then
        Return CopyFullLicenseTextFile($asset_folder, "License - CC0 1.0 Universal (CC0 1.0) Public Domain Dedication.txt")*/

    void CopyLicense(const boost::filesystem::path& licenses_dir,
                     const boost::filesystem::path& asset_license_path,
                     const boost::filesystem::copy_options& copy_options_p,
                     const std::wstring& correct_license_file_name) {
        boost::filesystem::path correct_license_src_path{ licenses_dir };
        correct_license_src_path /= correct_license_file_name;
        boost::filesystem::path target_path{ asset_license_path.parent_path() };
        target_path /= correct_license_file_name;
        boost::filesystem::copy_file(correct_license_src_path, target_path, copy_options_p);
    }

    void CopyCorrectLicenseFileSwitch(const boost::filesystem::path& licenses_dir, const std::string& license_text,
                                const boost::filesystem::path& asset_license_path,
                                const boost::filesystem::copy_options& copy_options_p) {
        if (!licenses_dir.empty() && !license_text.empty() && !asset_license_path.empty()) {
            boost::regex pattern{};
            boost::sregex_iterator iterator{};
            const boost::sregex_iterator end_iterator = boost::sregex_iterator();

            pattern = "CC Attribution-ShareAlike";
            iterator = boost::sregex_iterator(license_text.cbegin(), license_text.cend(), pattern);
            if (iterator != end_iterator && !iterator->empty()) {
                CopyLicense(licenses_dir, asset_license_path, copy_options_p,
                            L"License - CC Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).txt");
                return;
            }

            pattern = "CC Attribution-NoDerivs";
            iterator = boost::sregex_iterator(license_text.cbegin(), license_text.cend(), pattern);
            if (iterator != end_iterator && !iterator->empty()) {
                CopyLicense(licenses_dir, asset_license_path, copy_options_p, L"License - CC Attribution-NoDerivs.txt");
                return;
            }

            pattern = "CC Attribution-NonCommercial-ShareAlike";
            iterator = boost::sregex_iterator(license_text.cbegin(), license_text.cend(), pattern);
            if (iterator != end_iterator && !iterator->empty()) {
                CopyLicense(licenses_dir, asset_license_path, copy_options_p,
                            L"License - CC Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0).txt");
                return;
            }

            pattern = "CC Attribution-NonCommercial-NoDerivs";
            iterator = boost::sregex_iterator(license_text.cbegin(), license_text.cend(), pattern);
            if (iterator != end_iterator && !iterator->empty()) {
                CopyLicense(licenses_dir, asset_license_path, copy_options_p,
                            L"License - CC Attribution-NonCommercial-NoDerivatives 4.0 International (CC BY-NC-ND 4.0) .txt");
                return;
            }

            pattern = "CC0 Public Domain";
            iterator = boost::sregex_iterator(license_text.cbegin(), license_text.cend(), pattern);
            if (iterator != end_iterator && !iterator->empty()) {
                CopyLicense(licenses_dir, asset_license_path, copy_options_p,
                            L"License - CC0 1.0 Universal (CC0 1.0) Public Domain Dedication.txt");
                return;
            }

            pattern = "CC Attribution-NonCommercial";
            iterator = boost::sregex_iterator(license_text.cbegin(), license_text.cend(), pattern);
            if (iterator != end_iterator && !iterator->empty()) {
                CopyLicense(licenses_dir, asset_license_path, copy_options_p,
                    L"License - CC Attribution-NonCommercial 4.0 International (CC BY-NC 4.0).txt");
                return;
            }

            pattern = "CC Attribution";
            iterator = boost::sregex_iterator(license_text.cbegin(), license_text.cend(), pattern);
            if (iterator != end_iterator && !iterator->empty()) {
                CopyLicense(licenses_dir, asset_license_path, copy_options_p, L"License - CC Attribution 3.0 Unported.txt");
                return;
            }
        }
    }

    /// Copy one or many files in selected dirs
    int CopyFullLicenseTextFile() {
        try {
            const bool is_module_active_ini{ ReadBoolFromIni(kCopyToMultipleDirsSection, kIsModuleActiveIniKey, ini_path) };
            if (is_module_active_ini) {
                std::cout << kCopyLicenseModuleName + msg_process_start;

                const std::list<std::wstring> target_directories_wstr{ GetIniValuesList(ReadWStringFromIni(kCopyToMultipleDirsSection, kTargetDirectoriesIniKey, ini_path)) };
                const std::list<boost::filesystem::path> target_directories{ PathListFromWStringList(target_directories_wstr) };
                const boost::filesystem::path source_files_directory{ ReadWStringFromIni(kCopyToMultipleDirsSection, kSourceFilesDirectoryIniKey, ini_path) };
                const bool is_copy_subfolders{ ReadBoolFromIni(kCopyToMultipleDirsSection, kSubfoldersIniKey, ini_path) };
                const bool to_rewrite_duplicates{ ReadBoolFromIni(kCopyToMultipleDirsSection, kRewriteDuplicatesIniKey, ini_path) };

                std::list<bool> copy_results{};
                const boost::filesystem::copy_options copy_option = [to_rewrite_duplicates]() {
                    if (to_rewrite_duplicates) { return boost::filesystem::copy_options::overwrite_existing; }
                    else { return boost::filesystem::copy_options::skip_existing; }
                }();
                if (is_copy_subfolders) { // Add to all subfolders copied files
                    for (const boost::filesystem::path& target_directory : target_directories) { // Calc all target directories
                        for (auto const& dir_entry : boost::filesystem::recursive_directory_iterator{ target_directory }) {
                            if (kAssetLicenseFileName == dir_entry.path().filename()) {
                                const std::string license_text{ file::ReadTextFile(dir_entry.path().string()) };
                                CopyCorrectLicenseFileSwitch(source_files_directory, license_text, dir_entry.path(), copy_option);
                                std::cout << "Coping license file to folder " << dir_entry << '\n';
                            }
                        }
                    }
                } else { // Add copied files only to target folder
                    for (const boost::filesystem::path& target_directory : target_directories) {
                        for (auto const& dir_entry : boost::filesystem::recursive_directory_iterator{ target_directory }) {
                            if (kAssetLicenseFileName == dir_entry.path().filename()) {
                                const std::string license_text{ file::ReadTextFile(dir_entry.path().string()) };
                                CopyCorrectLicenseFileSwitch(source_files_directory, license_text, dir_entry.path(), copy_option);
                                std::cout << "Coping license file to folder " << target_directory << '\n';
                            }
                        }
                    }
                }

                std::cout << kCopyLicenseModuleName + msg_process_end;
            } else {
                std::cout << kCopyLicenseModuleName + msg_module_disabled;
            }
            std::cout << "\n";
            return 0;
        }
        catch (const errors::OpenFileError<char>& error) { return errors::OpenFileErrorHandle(error); }
        catch (const boost::filesystem::filesystem_error& error) { return errors::FilesystemErrorHandle(error); }
        catch (const std::runtime_error& error) { return errors::RuntimeErrorHandle(error); }
        catch (...) { return errors::FatalErrorHandle(); }
    }
} // !namespace admin_tasks