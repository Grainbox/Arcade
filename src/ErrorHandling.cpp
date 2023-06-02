/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** ErrorHandling
*/

#include "ErrorHandling.hpp"
#include <experimental/filesystem>

ErrorHandling::ErrorHandling(int argc, char **argv)
{
    if (argc != 2)
        throw (ArgNumberError());
    this->lib = argv[1];
    this->isValidLib();
    this->checkLibExists();
}

ErrorHandling::~ErrorHandling()
{
}

void ErrorHandling::isValidLib()
{
    bool found = false;
    size_t last_slash_index = this->lib.find_last_of("/");
    std::string filename = this->lib.substr(last_slash_index + 1);

    for (auto it : this->graphic_libs) {
        if (filename == it) {
            found = true;
            break;
        }
    }
    if (!found)
        throw (InvalidLibError());
}

void ErrorHandling::checkLibExists()
{
    size_t pos = this->lib.find_last_of('/');
    std::string path = this->lib.substr(0, pos);
    std::string filename = this->lib.substr(pos + 1);
    bool found = false;

    if (!std::filesystem::is_directory(path))
        throw (NoLibDirError());
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        if (this->lib == entry.path())
            found = true;
    }
    if (!found)
        throw (LibNotFoundError());
}
