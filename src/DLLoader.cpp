/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

template <typename T>
DLLoader<T>::DLLoader(const std::string& lib_path) {
    lib_handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!lib_handle) {
        std::cerr << dlerror();
        throw OpenLibError();
    }
}

template <typename T>
T* DLLoader<T>::getInstance(std::vector<std::string> gameLibs, std::vector<std::string>graphicLibs) {
    dlerror();
    T* (*create)(std::vector<std::string>, std::vector<std::string>);
    create = reinterpret_cast<T* (*)(std::vector<std::string>, std::vector<std::string>)>(dlsym(lib_handle, "entryPoint"));
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Error loading symbol: " << dlsym_error;
        throw OpenLibError();
    }
    return create(gameLibs, graphicLibs);
}

template <typename T>
DLLoader<T>::~DLLoader() {
    dlclose(lib_handle);
}

template class DLLoader<IGames>;
template class DLLoader<IGraphics>;
