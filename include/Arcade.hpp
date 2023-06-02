/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** Arcade
*/

/**
 * @file Arcade.hpp
 * @brief Ce fichier est le 'core' de l'arcade, c'est lui qui fait la jointure entre IGraphics et IGames
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

    #include <iostream>
    #include <dirent.h>
    #include <filesystem>
    #include "IGraphics.hpp"
    #include "IGames.hpp"
    #include "DLLoader.hpp"
    #include "events.hpp"

class OpenLibFolderError : public std::exception {
    public:
        OpenLibFolderError() = default;
        ~OpenLibFolderError() = default;

        const char* what() const noexcept override
        {
            return "Cannot open lib folder";
        }
};

class DLLoaderError : public std::exception {
    public:
        DLLoaderError() = default;
        ~DLLoaderError() = default;

        const char* what() const noexcept override
        {
            return "Cannot open lib in core";
        }
};

class Arcade {
    public:
        Arcade(std::string graphicLibPath);
        ~Arcade();

        void loadGraphic(std::string path);
        void loadGame(std::string path);

    protected:
    private:
        void getGameLibs();
        void getGraphicLibs();
        void getAllLibs();

        std::string currentGame;
        std::string currentGraphic;

        std::string playerName;

        std::string libPath;
        std::vector<std::string> allLibs;
        std::vector<std::string> graphicLibs;
        std::vector<std::string> gameLibs;
        DLLoader<IGames> *gameLoader;
        DLLoader<IGraphics> *graphicLoader;
        IGames *game;
        IGraphics *graphic;
};

#endif /* !ARCADE_HPP_ */
