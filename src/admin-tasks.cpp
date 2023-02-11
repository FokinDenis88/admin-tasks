#include "admin-tasks.hpp"

#include <iostream>

#include "copy-files-to-multiple-dirs.hpp"
#include "unpack-archives-in-subfolders.hpp"
#include "tag-management.hpp"
#include "delete-files-from-multiple-dirs.hpp"
#include "copy-full-license-text-file.hpp"
#include "prefix-suffix.hpp"

int main() {
    admin_tasks::UnpackArchivesInSubfolders();
    admin_tasks::ManageTagsInSubfolders();
    admin_tasks::PrefixSuffix();
    admin_tasks::CopyFilesToMultipleDirs();
    admin_tasks::DeleteFilesFromMultipleDirs();
    admin_tasks::CopyFullLicenseTextFile();

    std::cout << "\n\n";
    std::cout << "\nPush any key\n";
    std::string any_key{};
    std::cin >> any_key;
    return 0;
}