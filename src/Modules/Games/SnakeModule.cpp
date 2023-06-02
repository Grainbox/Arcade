/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** snake
*/

#include <stdio.h>
#include "SnakeModule.hpp"
#include <fstream>

#define HeadChar    'P'
#define TailChar    '+'
#define EmptyChar   ' '
#define WallChar    '#'
#define FruitChar   'F'

/**
 * @file SnakeModule.cpp
 * @brief Ce fichier implemente la gestion du jeu Snake
*/

extern "C"
{

    IGames *entryPoint()
    {
        return (new SnakeModule);
    }

    void isGame()
    {}

}

/*
*   @brief Cette fonction modifie la direction du snake pour des mouvements
*   cohérents et stock la direction precedente dans une variable de SnakeModule.
*   @param[in] Nouvelle direction envoyee au jeu.
*/
void SnakeModule::updateDirection(int new_direct)
{
    if (_direction != new_direct)
        _prevDirection = _direction;
    _direction = new_direct;
    if ((_direction == UP && _prevDirection == DOWN) ||
        (_direction == DOWN && _prevDirection == UP) ||
        (_direction == RIGHT && _prevDirection == LEFT) ||
        (_direction == LEFT && _prevDirection == RIGHT))
        _direction = _prevDirection;
}

/*
*   @brief Cette fonction met à jour la position de la queue du serpent en
*   fonction du mouvement de la tete. La queue grandit lorsque qu'un fruit est
*   mange.
*   @param[in] Nouvelle position de la tete.
*   @param[in] Information precisant si un fruit a ete mange ou non.
*/
void SnakeModule::updateTail(std::vector<int> oldHeadPos, bool eatFruit)
{
    std::vector<int> tailTip = _tail[_snakeSize - 2];

    for (int sig = _snakeSize - 2; sig != 0; sig--) {
        if (sig == _snakeSize - 2 && !eatFruit) {
            if (_tail[sig] == _headPos)
                _map[_tail[sig][0]][_tail[sig][1]] = HeadChar;
            else
                _map[_tail[sig][0]][_tail[sig][1]] = EmptyChar;
        }
        _tail[sig][0] = _tail[sig - 1][0];
        _tail[sig][1] = _tail[sig - 1][1];
        _map[_tail[sig][0]][_tail[sig][1]] = TailChar;
    }
    if (eatFruit) {
        _tail.push_back(tailTip);
        snakeGrow();
    }
    _tail[0] = oldHeadPos;
    _map[_tail[0][0]][_tail[0][1]] = TailChar;
}

static int randomNum(int x, int y)
{
    srand(time(0));
    x--;
    y--;
    return rand() % (y - x + 1) + x;

}

/*
*   @brief Cette fonction fait reapparaitre un fruit sur la map lorsque le
*   serpent en mange un.
*/
void SnakeModule::spawnFruit()
{
    std::vector<std::vector<int>> tab;
    int i = 0;
    int randNum = 0;

    for (int line = 1; line != _mapDims[0]; line++)
        for (int col = 1; col != _mapDims[1]; col++)
            if (_map[line][col] == EmptyChar)
                i++;
    tab.resize(i, std::vector<int>(2, 0));
    i = 0;
    for (int line = 1; line != _mapDims[0]; line++)
        for (int col = 1; col != _mapDims[1]; col++)
            if (_map[line][col] == EmptyChar) {
                tab[i].resize(2, 0);
                tab[i][0] = line;
                tab[i][1] = col;
                i++;
            }
    randNum = randomNum(0, i);
    _map[tab[randNum][0]][tab[randNum][1]] = FruitChar;
}

/*
*   @brief Cette fonction met a jour la position et la taille du serpent en
*   fonction de l'event envoye. Elle incremente egalement le score lorsqu'un
*   fruit est mange par le serpent.
*/
void SnakeModule::updatePos(int event)
{
    int lineVar = 0;
    int colVar = 0;
    std::vector<int> oldHeadPos;
    std::vector<int> newHeadPos;
    bool eatFruit = false;

    updateDirection(event);
    if (_direction == UP)
        lineVar = -1;
    if (_direction == DOWN)
        lineVar = 1;
    if (_direction == RIGHT)
        colVar = 1;
    if (_direction == LEFT)
        colVar = -1;
    oldHeadPos = getHeadPos();
    newHeadPos.push_back(getHeadPos()[0] + lineVar);
    newHeadPos.push_back(getHeadPos()[1] + colVar);
    if (_map[newHeadPos[0]][newHeadPos[1]] == FruitChar) {
        eatFruit = true;
        _score++;
    }
    if (!(_map[newHeadPos[0]][newHeadPos[1]] == WallChar || (
        _map[newHeadPos[0]][newHeadPos[1]] == TailChar &&
        newHeadPos != _tail[_snakeSize - 2]))) {
        _map[newHeadPos[0]][newHeadPos[1]] = HeadChar;
        setHeadPos(newHeadPos);
        updateTail(oldHeadPos, eatFruit);
    } else
        _gameIsOver = true;
    if (eatFruit)
        spawnFruit();
}

/*
*   @brief Cette fonction met a jour la frame de jeu, elle y inscrit la map et
*   les diverses infos dont le core aura a besoin pour l'affichage de jeu.
*/
void SnakeModule::updateFrame()
{
    std::vector<std::string> new_frame;
    std::string score_str = std::to_string(_score);
    std::string dir_str = std::to_string(_direction);

    score_str += "\n";
    dir_str += "\n";
    new_frame.push_back("<MAP>\n");
    for (auto it : _map)
        new_frame.push_back(it);
    new_frame.push_back("</MAP>\n");
    new_frame.push_back("<SCORE>\n");
    new_frame.push_back(score_str);
    new_frame.push_back("</SCORE>\n");
    new_frame.push_back("<LAST_EVENT>\n");
    new_frame.push_back(dir_str);
    new_frame.push_back("</LAST_EVENT>\n");
    new_frame.push_back("<GAME_OVER>\n");
    if (_gameIsOver)
        new_frame.push_back("true\n");
    else
        new_frame.push_back("false\n");
    new_frame.push_back("</GAME_OVER>\n");
    frame = new_frame;
}

/*
*   @brief Cette fonction analyse l'event envoye et appelle updatePos si
*   celui-ci correspond a un event pour bouger le serpent.
*   @param[in] event envoye au jeu.
*/
void SnakeModule::eventHandler(int event)
{
    if ((event == UP) || event == DOWN || event == RIGHT || event == LEFT)
        updatePos(event);
    updateFrame();
}

/*
*   @brief Cette fonction analyse la map de jeu pour trouver la position de la
*   tete du serpent.
*   @param[out] vecteur de int pour la position de la tete.
*/
std::vector<int> SnakeModule::findHeadPos()
{
    std::vector<int> result;
    int col = 0;

    for (int line = 0; _map[line].c_str() != NULL; line++) {
        for (; _map[line][col] != '\0'; col++)
            if (_map[line][col] == HeadChar) {
                result.push_back(line);
                result.push_back(col);
                return result;
            }
        col = 0;
    }
    return result;
}

/*
*   @brief Cette fonction stocke les positions de la queue du serpent au debut
*   du jeu en se basant sur la position de la tete du serpent.
*/
void SnakeModule::setTail(std::vector<int> headPos)
{
    _tail.resize(3, std::vector<int>(2, 0));
    for (int i = 0; i < 3; i++) {
        _tail[i][0] = headPos[0];
        _tail[i][1] = headPos[1] + 1 + i;
    }
}

/*
*   @brief Cette fonction analyse la map pour en deduire les dimensions de la
*   map et les stocker dans l'objet SnakeModule.
*/
void SnakeModule::setMapDims()
{
    _mapDims.resize(2, 0);
    for (auto it : _map)
        _mapDims[0]++;
    _mapDims[1] = _map[0].length();
}

/*
*   @brief Cette fonction analyse la frame pour recuperer la map et la stocker
*   dans l'objet SnakeModule.
*/
void SnakeModule::getMap(std::vector<std::string> frame)
{
    bool s = false;

    for (auto it : frame) {
        if (it == "<MAP>\n") {
            s = true;
            continue;
        }
        if (it == "</MAP>\n")
            break;
        if (s)
            _map.push_back(it);
    }
}

/*
*   @brief Le constructeur de l'objet SnakeModule, il va ouvrir le fichier
*   "gameMaps/snakeMap" en lecture only et va y recuperer la frame de jeu.
*   Divers parametres de base y sont initialises (taille du serpent, directions
*   de base, score et etat du jeu).
*/
SnakeModule::SnakeModule()
{
    FILE *fp = fopen("gameMaps/snakeMap", "r");
    char line[1024];

    while (fgets(line, 1024, fp))
        frame.push_back(line);
    getMap(frame);
    setMapDims();
    setHeadPos(findHeadPos());
    setTail(getHeadPos());
    _started = false;
    _snakeSize = 4;
    _direction = LEFT;
    _prevDirection = LEFT;
    _score = 0;
    _gameIsOver = false;
}
