/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** NCursesModule
*/

#include "NCursesModule.hpp"

/**
 * @file NCursesModule.cpp
 * @brief Ce fichier implemente l'affichage de la NCurses
*/

extern "C"
{

    IGraphics *entryPoint(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs)
    {
        return (new NCursesModule(gameLibs, graphicLibs));
    }

    void isGraphic()
    {}

}

/*
*   @brief Cette fonction crée l'objet NCurses module qui gerent l'affichage en NCurses.
*   @param[in] gameLibs vecteur de strings qui donnent acces au nom de tous les jeux disponibles.
*   @param[in] graphicLibs vecteur de strings qui donnent acces au nom de toutes les bibliotheques graphiques disponibles.
*/
NCursesModule::NCursesModule(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs)
{
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    _displayMenu = true;
    _gameLibs = gameLibs;
    _graphicLibs = graphicLibs;
    _isGraphicSelected = true;
    _maxGameLib = _gameLibs.size() - 1;
    _maxGraphLib = _graphicLibs.size() - 1;
    _gamePointed = 0;
    _graphPointed = 0;
}

/*
*   @brief Cette fonction Delete l'objet NCursesModule qui gerent l'affichage en NCurses.
*/
NCursesModule::~NCursesModule()
{
    endwin();
}

/*
*   @brief Cette fonction implemente la navigation vers le haut dans le menu
*   NCurses.
*/
void NCursesModule::upMenuButton(int *button, int max)
{
    if (*button == 0)
        *button = max;
    else
        *button -= 1;
}

/*
*   @brief Cette fonction implemente la navigation vers le bas dans le menu
*   NCurses.
*/
void NCursesModule::downMenuButton(int *button, int max)
{
    if (*button == max)
        *button = 0;
    else
        *button += 1;
}

/*
*   @brief Cette fonction gere l'affichage du menu NCurses pour la navigation entre les
*   bibliotheques graphiques disponibles et les jeux.
*/
void NCursesModule::displayMenu()
{
    std::string title = "ARCADE";
    int i = 3;
    clear();
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Base color
    init_pair(2, COLOR_RED, COLOR_BLACK); // Arcade title
    attron(COLOR_PAIR(2));
    mvprintw(0, (COLS / 2) - (title.length() / 2), "%s\n\n", title.c_str());
    attron(COLOR_PAIR(1));
    for (auto it : _graphicLibs) {
        if ((_graphPointed == i - 3) && _isGraphicSelected)
            attron(COLOR_PAIR(2));
        mvprintw(i, COLS / 2 - it.length() - 2, "%s\n", it.c_str());
        attron(COLOR_PAIR(1));
        i++;
    }
    printw("\n");
    i = 3;
    for (auto it : _gameLibs) {
        if ((_gamePointed == i - 3) && !_isGraphicSelected)
            attron(COLOR_PAIR(2));
        mvprintw( i, COLS / 2 + 2, "%s\n", it.c_str());
        attron(COLOR_PAIR(1));
        i++;
    }
}

/*
*   @brief Cette fonction gere le menu NCurses pour la navigation entre les
*   bibliotheques graphiques disponibles et les jeux.
*/
int NCursesModule::eventMenu(int key)
{
    if (key == KEY_LEFT)
        _isGraphicSelected = true;
    if (key == KEY_RIGHT)
        _isGraphicSelected = false;

    if (key == KEY_DOWN && _isGraphicSelected)
        downMenuButton(&_graphPointed, _maxGraphLib);
    if (key == KEY_UP && _isGraphicSelected)
        upMenuButton(&_graphPointed, _maxGraphLib);

    if (key == KEY_DOWN && !_isGraphicSelected)
        downMenuButton(&_gamePointed, _maxGameLib);
    if (key == KEY_UP && !_isGraphicSelected)
        upMenuButton(&_gamePointed, _maxGameLib);

    if (key == KEY_ENTER || key == '\n') {
        this->setGameName(this->_gameLibs.at(_gamePointed));
        this->setLibName(this->_graphicLibs.at(_graphPointed));
        if (_isGraphicSelected) {
            return LIBCHANGED;
        } else {
            _displayMenu = false;
            return GAMECHANGED;
        }

    }
    return BREAK;
}

/*
*   @brief Cette fonction analyse la frame et récupère l'information concernant
*   la map du jeu.
*/
void NCursesModule::getMap(std::vector<std::string> tmp_frame)
{
    bool s = false;

    for (auto it : tmp_frame) {
        if (it == "<MAP>\n") {
            s = true;
            continue;
        }
        if (it == "</MAP>\n")
            break;
        if (s)
            map.push_back(it);
    }
}

/*
*   @brief Cette fonction analyse la frame et récupère l'information concernant
*   le score du jeu.
*/
void NCursesModule::getScore(std::vector<std::string> tmp_frame)
{
    bool s = false;

    for (auto it : tmp_frame) {
        if (it == "<SCORE>\n") {
            s = true;
            continue;
        }
        if (it == "</SCORE>\n")
            break;
        if (s)
            score = it;
    }
}

/*
*   @brief Cette fonction analyse la frame et récupère l'information concernant
*   le dernier event du jeu.
*/
void NCursesModule::getLastEvent(std::vector<std::string> tmp_frame)
{
    bool s = false;

    for (auto it : tmp_frame) {
        if (it == "<LAST_EVENT>\n") {
            s = true;
            continue;
        }
        if (it == "</LAST_EVENT>\n")
            break;
        if (s) {
            // _lastEvent = std::stoi(it);
            break;
        }
    }
}

/*
*   @brief Cette fonction analyse la frame et récupère l'information concernant
*   la fin du jeu.
*/
void NCursesModule::checkGameOver(std::vector<std::string> tmp_frame)
{
    bool s = false;
    std::string buffer;

    for (auto it : tmp_frame) {
        if (it == "<GAME_OVER>\n") {
            s = true;
            continue;
        }
        if (it == "</GAME_OVER>\n")
            break;
        if (s) {
            buffer = it;
            break;
        }
    }
    if (buffer == "true\n")
        _gameIsOver = true;
    else
        _gameIsOver = false;
}

/*
*   @brief Cette fonction analyse la frame et recupere les informations telles
*   que la map et les informations du jeu pour les stocké dans l'object
*   NCursesModule.
*/
void NCursesModule::parse(std::vector<std::string> tmp_frame)
{
    getMap(tmp_frame);
    getScore(tmp_frame);
    checkGameOver(tmp_frame);
    // getLastEvent(tmp_frame);
}

/*
*   @brief Cette fonction gere les differents affichages NCurses du programme :
*   des menus aux jeux. Elle analyse la taille de la fenetre afin de centrer
*   l'affichage
*/
void NCursesModule::display(const std::vector<std::string> tmp_frame)
{
    std::string buffer;

    if (_displayMenu)
        return displayMenu();
    parse(tmp_frame);
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_BLUE, 0, 0, 255);
    init_pair(1, COLOR_BLACK, COLOR_BLUE);      // Walls
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);    // Player
    init_pair(3, COLOR_BLACK, COLOR_RED);       // Fruit
    init_pair(4, COLOR_BLACK, COLOR_GREEN);     // Ground
    init_pair(5, COLOR_BLACK, COLOR_CYAN);      // Snake tail
    init_pair(6, COLOR_WHITE, COLOR_BLACK);     // base font
    clear();
    int line = 0;
    int col = 0;
    bool sig = true;
    int mapLines = map.size();
    int mapCols = map[0].size();
    std::string death_msg = "Press F1 to restart the game.";
    if (_gameIsOver) {
        mvprintw(LINES / 2 - (mapLines / 2) - 2, COLS / 2 - 4, "GAME OVER\n");
        mvprintw(LINES / 2 - (mapLines / 2) - 1, COLS / 2 - death_msg.size() / 2, "%s", death_msg.c_str());
    }
    for (auto it : map) {
        for (int i = 0; it.c_str()[i] != 0; i++) {
            buffer = it.c_str()[i];
            if (it.c_str()[i] == '#')
                attron(COLOR_PAIR(1));
            if (!_gameIsOver) {
                if (it.c_str()[i] == 'P')
                    attron(COLOR_PAIR(2));
                if (it.c_str()[i] == '+')
                    attron(COLOR_PAIR(4));
            } else {
                if (it.c_str()[i] == 'P')
                    attron(COLOR_PAIR(3));
                if (it.c_str()[i] == '+')
                    attron(COLOR_PAIR(3));
            }
            if (it.c_str()[i] == ' ')
                attron(COLOR_PAIR(5));
            if (it.c_str()[i] == 'F')
                attron(COLOR_PAIR(3));
            if (it.c_str()[i] == '#' || it.c_str()[i] == '+' ||
                it.c_str()[i] == 'P' || it.c_str()[i] == 'F')
                buffer = " ";
            if (sig)
                mvprintw(LINES / 2 - (mapLines / 2) + line, COLS / 2 - (mapCols / 2), "%s", buffer.c_str());
            else
                printw("%s", buffer.c_str());
            sig = false;
        }
        sig = true;
        line++;
    }
    attron(COLOR_PAIR(6));
    mvprintw(LINES / 2 - (mapLines / 2) + line + 1, COLS / 2 - 4, "Score: %s", score.c_str());
    map.clear();
    refresh();
}

static bool isKeyValid(int key)
{
    if (key == ' ' || key == 'z' || key == 'q' || key == 's' || key == 'd')
        return true;
    return false;
}

/*
*   @brief Cette fonction inspecte la touche pressee.
*   @param[in] renvoi la bonne instruction à envoyer au jeu.
*/
int NCursesModule::inspectKey(int key)
{
    if (_displayMenu)
        return eventMenu(key);
    if (!_gameIsOver) {
        if (key == 'z')
            return UP;
        if (key == 's')
            return DOWN;
        if (key == 'q')
            return LEFT;
        if (key == 'd')
            return RIGHT;
        if (key == ' ')
            return _lastEvent;
    }
    return _lastEvent;
}

/*
*   @brief Cette fonction gerent les events du JEU ...
*   Elle permet de fermer la pages, gerer les mouvements, quitter le jeu,
*   changer de bibliotheque graphique et de retourner au menu principal.
*/
int NCursesModule::getEvent()
{
    int key = NONE;

    halfdelay(2); // durée du delai
    // getLastEvent(frame);
    while (!isKeyValid(key)) {
        key = getch();
        if (key == KEY_F(1))
            return RESTARTGAME;
        if (key == KEY_F(2))
            return NEXTGRAPHIC;
        if (key == KEY_F(3))
            return NEXTGAME;
        if (key == 27) {
            _displayMenu = !_displayMenu;
            return BREAK;
        }
        if (key == KEY_DC)
            return QUIT;
        if (key != ERR)
            _lastEvent = inspectKey(key);
        return _lastEvent;
    }
    return _lastEvent;
}
