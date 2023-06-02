/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** DLLoader
*/

/**
 * @file DLLoader.hpp
 * @brief Ce fichier est l'encapsulation de <dlfcn.h> en C
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

    #include <iostream>
    #include <dlfcn.h>
    #include "IGraphics.hpp"
    #include "IGames.hpp"

class OpenLibError : public std::exception {
    public:
        OpenLibError() = default;
        ~OpenLibError() = default;

        const char* what() const noexcept override
        {
            return "";
        }
};

template <typename T>
class DLLoader {
    public:
        DLLoader(const std::string& lib_path);
        ~DLLoader();

        T* getInstance(std::vector<std::string> gameLibs, std::vector<std::string>graphicLibs);

    private:
        void* lib_handle;
};

#endif /* !DLLOADER_HPP_ */
