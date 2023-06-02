/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** SFMLModule
*/

#include "SFMLModule.hpp"
#define WIN _window
#include "Color.hpp"
#include "events.hpp"

/**
 * @file SFMLModule.cpp
 * @brief Ce fichier implemente l'affichage de la SFML
*/

extern "C"
{

    IGraphics *entryPoint(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs)
    {
        return (new SFMLModule(gameLibs, graphicLibs));
    }

    void isGraphic()
    {}

}
/*
*   @brief Cette fonction crée l'objet SFML module qui gerent l'affichage en SFML.
*   @param[in] drawMenu variable bool qui permet l'affichage ou non du menu/jeu
*   @param[in] gameLibs vecteur de strings qui donnent acces au nom de tous les jeux disponibles.
*   @param[in] drawMenu vecteur de strings qui donnent acces au nom de toutes les libs graphiques disponibles.
*/
SFMLModule::SFMLModule(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs)
{
    sf::VideoMode _mode = sf::VideoMode::getDesktopMode();
    this->_window = new sf::RenderWindow(_mode, "ARCADE", sf::Style::Resize | sf::Style::Close);
    Last_Key = LEFT;
    display_menu = true;
    _gameLibs = gameLibs;
    _graphicLibs = graphicLibs;
    font.loadFromFile("assets/ARCADE_I.TTF");
    tmp = BREAK;
    elapsed = clock.getElapsedTime();
}

/*
*   @brief Cette fonction Delete l'objet SFML module qui gerent l'affichage en SFML.
*/
SFMLModule::~SFMLModule()
{
    if (_window->isOpen())
        _window->close();
    delete _window;
}
/*
*   @brief Cette fonction gerent les events du JEU ...
*   Elle permet de fermer la pages, de handle les mouvements,
*   de quitter le jeu, de changer de lib, de retourner
*   au menu principal.
*/
int SFMLModule::getEvent()
{
    if (display_menu) {
        if (tmp == GAMECHANGED) {
            this->display_menu = false;
            this->game_enabled = true;
        }
        return tmp;
    }

    elapsed = clock.getElapsedTime();

    sf::Event event;

    while (WIN->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                return QUIT;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::F3) {
                    return NEXTGAME;
                }
                if (event.key.code == sf::Keyboard::F2) {
                    return NEXTGRAPHIC;
                }
                if (event.key.code == sf::Keyboard::F1) {
                    return RESTARTGAME;
                }
                if (event.key.code == sf::Keyboard::BackSpace) {
                    return QUIT;
                }
                if (gameOver)
                    return BREAK;
                if (event.key.code == sf::Keyboard::Z) {
                    Last_Key = UP;
                }
                if (event.key.code == sf::Keyboard::S) {
                    Last_Key = DOWN;
                }
                if (event.key.code == sf::Keyboard::Q) {
                    Last_Key = LEFT;
                }
                if (event.key.code == sf::Keyboard::D) {
                    Last_Key = RIGHT;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    display_menu = true;
                    tmp = BREAK;
                }
                break;
            default:
                break;
        }
    }
    if (elapsed.asMilliseconds() > tick) {
        clock.restart();
        return Last_Key;
    } else
        return NONE;
    return Last_Key;
}

/*
*   @brief Cette fonction crée les objects rectangles
*   utiliser pour afficher la map.
*/
void SFMLModule::initRectangle ()
{
    int t = 0;
    int top_margin = 100;

    sf::VideoMode _mode = sf::VideoMode::getDesktopMode();
    for (int y = 0; y < (int) map.size(); y++) {
        for (int i = 0; i < (int) map[y].size(); i++) {
            sf::RectangleShape square(sf::Vector2f((((_mode.width / map[y].size()) + 10) - t),\
             (((_mode.height / map.size()) + 8) - t)));
            if (map[y][i] == '#')
                square.setFillColor(SFML_Black);
            if (map[y][i] == 'A')
                square.setFillColor(SFML_Red);
            if (map[y][i] == 'P')
                square.setFillColor(SFML_Yellow);
            if (map[y][i] == 'G')
                square.setFillColor(SFML_Green);
            if (map[y][i] == ' ')
                square.setFillColor(SFML_Grey);
            if (map[y][i] == '|')
                square.setFillColor(SFML_Cyan);
            if (map[y][i] == 'o')
                square.setFillColor(SFML_Blue);
            if (map[y][i] == 'U')
                square.setFillColor(SFML_Pink);
            if (map[y][i] == 'F')
                square.setFillColor(SFML_Pink);
            if (map[y][i] == '\n')
                square.setFillColor(SFML_Black);
            square.setPosition(((_mode.width / (map[y].size() - 1)) * i),\
             ((_mode.height / (map.size() + 1)) * y) + top_margin);
            rectangles.push_back(square);
        }
    }
}

void SFMLModule::getGameOver(std::vector<std::string> tmp_frame)
{
    bool s = false;

    for (auto it : tmp_frame) {
        if (it == "<GAME_OVER>\n") {
            s = true;
            continue;
        }
        if (it == "</GAME_OVER>\n")
            break;
        if (s) {
            if (it == "true\n")
                this->gameOver = true;
            else
                this->gameOver = false;
        }
    }
}

/*
*   @brief Cette fonction recupere la map dans la frame
*   @param[in] frame vecteur de string qui contient la map entre <MAP></MAP>
*/
void SFMLModule::getMap (std::vector<std::string> frame)
{
    bool s = false;

    for (auto it : frame) {
        if (it == "<MAP>\n") {
            s = true;
            continue;
        }
        if (it == "</MAP>\n")
            break;
        if (s) {
            map.push_back(it);
        }
    }
}
/*
*   @brief Cette fonction recupere le score dans la frame
*   @param[in] frame vecteur de string qui contient le score entre <SCORE></SCORE>
*/
void SFMLModule::getScore (std::vector<std::string> frame)
{
    bool s = false;

    for (auto it : frame) {
        if (it == "<SCORE>\n") {
            s = true;
            continue;
        }
        if (it == "</SCORE>\n")
            break;
        if (s)
            _score = it;
    }
}
/*
*   @brief Cette fonction recupere le score et la map dans la frame
*   @param[in] frame vecteur de string qui contient le score et la map entre <MAP></MAP> <SCORE></SCORE>
*/
void SFMLModule::parse (std::vector<std::string> frame)
{
    getMap(frame);
    getScore(frame);
    getGameOver(frame);
}
/*
*   @brief Cette fonction affiche le jeux en sfml en appelant de multiple inits
*   @param[in] str vecteur de string qui contient la map
*/
void SFMLModule::displayGame (std::vector<std::string> str)
{
    parse(str);
    initRectangle();
    initText();
    WIN->clear( sf::Color::Black );
    for (auto it : rectangles)
        WIN->draw(it);
    WIN->draw(affiche_text);
    WIN->display();
    map.clear();
    rectangles.clear();
}
/*
*   @brief Cette fonction recupere le score le pseudo pour crée un sf::Text
*   @param[out] sf::Text dans "affiche_text"
*/
void SFMLModule::initText ()
{
    std::string tmp_text = playerName + " " + _score;
    sf::Text score_text(tmp_text, font, 40);
    score_text.setPosition((_window->getSize().x / 2.3), (_window->getSize().x / 100) * 1);
    score_text.setFillColor(SFML_White);
    affiche_text = score_text;
}

void SFMLModule::initTextMenu ()
{
    int i = 1;
    int j = 1;
    int tmp_truc = 0;
    int marge = (_window->getSize().x / 100) * 10;
    int max = _graphicLibs.size() + _gameLibs.size();
    maxGameFocus = _gameLibs.size() - 1;
    maxGraphicFocus = _graphicLibs.size() - 1;

    for (auto it : _graphicLibs) {
        sf::Text text(it, font, ((_window->getSize().x - marge) / it.size()) / 3);
        text.setPosition(marge, ((_window->getSize().y / 2) / max) * i);
        if (!cursorList) { // definie le curseur sur l'une des listes
            if (focusGraphics == (i - 1)) {
                text.setFillColor(SFML_Red);
            } else {
                if (!maxGraphicFocus)
                    text.setFillColor(SFML_Red);
                else
                    text.setFillColor(sf::Color::White);
            }
        } else {
            text.setFillColor(SFML_Grey);
        }
        text_menu_graphic.push_back(text);
        i++;
    }
    tmp_truc = i;
    i = 0;
    for (auto it : _gameLibs) {
        sf::Text text(it, font, ((_window->getSize().x - marge) / it.size()) / 3);
        text.setPosition((_window->getSize().x / 2) + marge, ((_window->getSize().y / 2) / max) * j);
        if (cursorList) { // definie le curseur sur l'une des listes
            if (focusGame == i) {
                text.setFillColor(SFML_Red);
            } else {
                if (!maxGameFocus)
                    text.setFillColor(SFML_Red);
                else
                    text.setFillColor(sf::Color::White);
            }
        } else {
            text.setFillColor(SFML_Grey);
        }
        text_menu_game.push_back(text);
        j++;
        i++;
    }

    sf::Text text(playerName, font, 50);
    text.setPosition(marge, marge * tmp_truc);
    text.setFillColor(sf::Color::White);
    pseudo.push_back(text);
}

void SFMLModule::keyboardFactory()
{
    sf::Event event;

    while (WIN->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                tmp = QUIT;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    if (game_enabled)
                        display_menu = false;
                }
                if (event.key.code == sf::Keyboard::A)
                    playerName += "A";
                if (event.key.code == sf::Keyboard::B)
                    playerName += "B";
                if (event.key.code == sf::Keyboard::C)
                    playerName += "C";
                if (event.key.code == sf::Keyboard::D)
                    playerName += "D";
                if (event.key.code == sf::Keyboard::E)
                    playerName += "E";
                if (event.key.code == sf::Keyboard::F)
                    playerName += "F";
                if (event.key.code == sf::Keyboard::G)
                    playerName += "G";
                if (event.key.code == sf::Keyboard::H)
                    playerName += "H";
                if (event.key.code == sf::Keyboard::I)
                    playerName += "I";
                if (event.key.code == sf::Keyboard::J)
                    playerName += "J";
                if (event.key.code == sf::Keyboard::K)
                    playerName += "K";
                if (event.key.code == sf::Keyboard::L)
                    playerName += "L";
                if (event.key.code == sf::Keyboard::M)
                    playerName += "M";
                if (event.key.code == sf::Keyboard::N)
                    playerName += "N";
                if (event.key.code == sf::Keyboard::O)
                    playerName += "O";
                if (event.key.code == sf::Keyboard::P)
                    playerName += "P";
                if (event.key.code == sf::Keyboard::Q)
                    playerName += "Q";
                if (event.key.code == sf::Keyboard::R)
                    playerName += "R";
                if (event.key.code == sf::Keyboard::S)
                    playerName += "S";
                if (event.key.code == sf::Keyboard::T)
                    playerName += "T";
                if (event.key.code == sf::Keyboard::U)
                    playerName += "U";
                if (event.key.code == sf::Keyboard::V)
                    playerName += "V";
                if (event.key.code == sf::Keyboard::W)
                    playerName += "W";
                if (event.key.code == sf::Keyboard::X)
                    playerName += "X";
                if (event.key.code == sf::Keyboard::Y)
                    playerName += "Y";
                if (event.key.code == sf::Keyboard::Z)
                    playerName += "Z";
                if (event.key.code == sf::Keyboard::Space)
                    playerName += " ";
                if (event.key.code == sf::Keyboard::BackSpace && playerName.size() > 0)
                    playerName.pop_back();
                if (event.key.code == sf::Keyboard::Right) // deplace le curseur sur la liste de droite
                    cursorList = 1;
                if (event.key.code == sf::Keyboard::Left) // deplace le curseur sur la liste de gauche
                    cursorList = 0;
                if (event.key.code == sf::Keyboard::Down) { // deplace le focus sur celui de dessous
                    if (!cursorList && focusGraphics < maxGraphicFocus)
                        focusGraphics++;
                    else if (cursorList && focusGame < maxGameFocus)
                        focusGame++;
                }
                if (event.key.code == sf::Keyboard::Up) { // deplace le focus sur celui de dessus
                    if (!cursorList && focusGraphics)
                        focusGraphics--;
                    else if (cursorList && focusGame)
                        focusGame--;
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    this->setGameName(_gameLibs.at(focusGame));
                    this->setLibName(_graphicLibs.at(focusGraphics));
                    if (!cursorList) {
                        tmp = LIBCHANGED;
                    } else {
                        tmp = GAMECHANGED;
                    }
                }
                break;
            default:
                break;
        }
    }
}

void SFMLModule::displayMenu ()
{
    keyboardFactory();
    WIN->clear(sf::Color::Black);
    initTextMenu();
    for (auto it : text_menu_game)
        WIN->draw(it);
    for (auto it : text_menu_graphic)
        WIN->draw(it);
    for (auto it : pseudo)
        WIN->draw(it);
    WIN->display();
    pseudo.clear();
    text_menu_graphic.clear();
    text_menu_game.clear();
}

void SFMLModule::display(const std::vector<std::string> str)
{
    if (display_menu)
        displayMenu();
    else
        displayGame(str);
}
