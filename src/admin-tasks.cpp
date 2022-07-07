#include "admin-tasks.hpp"

#include <iostream>

#include "copy-files-to-multiple-dirs.hpp"
#include "unpack-archives-in-subfolders.hpp"

int main() {
    admin_tasks::CopyFilesToMultipleDirs();
    admin_tasks::UnpackArchivesInSubfolders();

    std::cout << "\n\n";
    return 0;
}