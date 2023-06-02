/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** ErrorHandling
*/

/**
 * @file ErrorHandling.hpp
 * @brief Ce fichier contient l'handling des arguments d'entrée.
*/

#ifndef ERRORHANDLING_HPP_
#define ERRORHANDLING_HPP_

    #include <exception>
    #include <vector>
    #include <string>
    #include <iostream>
    #include <filesystem>

class ArgNumberError : public std::exception {
    public:
        ArgNumberError() = default;
        ~ArgNumberError() = default;

        const char* what() const noexcept override
        {
            return "Wrong argument";
        }
};

class InvalidLibError : public std::exception {
    public:
        InvalidLibError() = default;
        ~InvalidLibError() = default;

        const char* what() const noexcept override
        {
            return "Invalid Library";
        }
};

class NoLibDirError : public std::exception {
    public:
        NoLibDirError() = default;
        ~NoLibDirError() = default;

        const char* what() const noexcept override
        {
            return "lib folder cannot be found";
        }
};

class LibNotFoundError : public std::exception {
    public:
        LibNotFoundError() = default;
        ~LibNotFoundError() = default;

        const char* what() const noexcept override
        {
            return "Library cannot be found";
        }
};

class ErrorHandling {
    public:
        ErrorHandling(int argc, char **argv);
        ~ErrorHandling();
    protected:
    private:
        void isValidLib();
        void checkLibExists();

        std::string lib;
        const std::vector<std::string> graphic_libs = {
            "arcade_ndk++.so",
            "arcade_aalib.so",
            "arcade_libcaca.so",
            "arcade_allegro5.so",
            "arcade_xlib.so",
            "arcade_gtk+.so",
            "arcade_sfml.so",
            "arcade_irrlicht.so",
            "arcade_opengl.so",
            "arcade_vulkan.so",
            "arcade_qt5.so",
            "arcade_ncurses.so",
            "arcade_sdl2.so"
        };
};

#endif /* !ERRORHANDLING_HPP_ */
