/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** SFMLModule
*/

/**
 * @file SFMLModule.hpp
 * @brief Ce fichier implémente la lib graphique SFML
*/

#ifndef SFMLMODULE_HPP_
#define SFMLMODULE_HPP_

    #include "Graphics.hpp"
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Graphics/Color.hpp>

class SFMLModule : public Graphics {
    public:
        SFMLModule(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs);
        ~SFMLModule();
        void displayGame(std::vector<std::string> str);
        void displayMenu();
        void display(const std::vector<std::string> frame);
        int getEvent();
        void initRectangle ();
        std::vector<sf::RectangleShape> getRectangle() { return rectangles; };
        void key_handler(sf::RenderWindow *_window);
        void parse (std::vector<std::string> frame);
        void getMap (std::vector<std::string> frame);
        void getScore (std::vector<std::string> frame);
        void getGameOver(std::vector<std::string> frame);
        void initTextMenu();
        void keyboardFactory();
        void initText ();
    protected:
    private:
        std::vector<std::string> map;
        std::vector<sf::RectangleShape> rectangles;
        std::vector<sf::Text> text_menu_graphic;
        std::vector<sf::Text> text_menu_game;
        std::vector<sf::Text> pseudo;
        sf::Text affiche_text;
        std::vector<std::string> _gameLibs;
        std::vector<std::string> _graphicLibs;
        sf::RenderWindow *_window;
        int Last_Key = NONE;
        std::string _score;
        bool display_menu;
        sf::Font font;
        int tmp;
        int focusGame = 0;
        int maxGameFocus = 0;
        int focusGraphics = 0;
        int maxGraphicFocus = 0;
        int cursorList = 0;
        std::string selectedLib;
        sf::Clock clock;
        sf::Time elapsed;
        int tick = 500;
        int game_enabled = false;
        bool gameOver = false;
};

#endif /* !SFMLMODULE_HPP_ */
