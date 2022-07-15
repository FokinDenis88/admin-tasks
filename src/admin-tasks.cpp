#include "admin-tasks.hpp"

#include <iostream>

#include "copy-files-to-multiple-dirs.hpp"
#include "unpack-archives-in-subfolders.hpp"

int main() {
    admin_tasks::CopyFilesToMultipleDirs();
    admin_tasks::UnpackArchivesInSubfolders();

    std::cout << "\n\n";
    std::cout << "\nPush any key\n";
    std::string any_key{};
    std::cin >> any_key;
    return 0;
}