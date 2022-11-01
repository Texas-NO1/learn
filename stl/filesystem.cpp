#include <iostream>
#include <experimental/filesystem>

void showAllFile(std::string path) {
    for (auto &file : std::experimental::filesystem::directory_iterator(path)) {
        if (std::experimental::filesystem::is_regular_file(file.status())) {
            if (std::experimental::filesystem::path(file.path()).extension() == ".cpp") {
                std::cout << file.path().string() << std::endl;
            }
        } else {
            showAllFile(file.path().string());
        }
    }
}

int main () {
    std::cout << __cplusplus << std::endl;
    showAllFile("/app");
    return 0;
}