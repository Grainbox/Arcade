/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** NCursesModule
*/

/**
 * @file NCursesModule.hpp
 * @brief Ce fichier implemente la lib graphique Ncurses
*/

#ifndef NCURSESMODULE_HPP_
#define NCURSESMODULE_HPP_

    #include "Graphics.hpp"
    #include <ncurses.h>

class NCursesModule : public Graphics {
    public:
        NCursesModule(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs);
        ~NCursesModule();

        void displayMenu();
        int eventMenu(int key);

        void display(const std::vector<std::string> frame);
        int getEvent();
        int inspectKey(int key);
    
        void getLastEvent(std::vector<std::string> tmp_frame);
        void getScore (std::vector<std::string> tmp_frame);
        void getMap (std::vector<std::string> tmp_frame);
    
        void parse (std::vector<std::string> tmp_frame);
        void checkGameOver(std::vector<std::string> tmp_frame);
    protected:
    private:

        void upMenuButton(int *button, int max);
        void downMenuButton(int *button, int max);

        bool _displayMenu;
        std::vector<std::string> _gameLibs;
        std::vector<std::string> _graphicLibs;

        int _lastEvent;
        std::vector<std::string> frame;
        std::vector<std::string> map;
        std::string score;
        bool _gameIsOver;

        bool _isGraphicSelected;
        int _maxGameLib;
        int _maxGraphLib;
        int _gamePointed;
        int _graphPointed;
};

#endif
