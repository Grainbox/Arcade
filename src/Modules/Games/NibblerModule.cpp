/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** NibblerModule
*/

#include "NibblerModule.hpp"

#define HeadChar    'P'
#define TailChar    '+'
#define EmptyChar   ' '
#define WallChar    '#'
#define FruitChar   'F'

/**
 * @file NibblerModule.cpp
 * @brief Ce fichier implemente la gestion du jeu Nibbler
*/

extern "C"
{

    IGames *entryPoint()
    {
        return (new NibblerModule);
    }

    void isGame()
    {}

}


/*
*   @brief Cette fonction reinitialise les infos necessaire au demarrage d'un
*   nouveau niveau.
*/
void NibblerModule::resetStats()
{
    _headPos.clear();
    _tail.clear();
    setHeadPos(findHeadPos());
    setTail(getHeadPos());
    _snakeSize = 4;
    _time = 990;
    _direction = RIGHT;
    _prevDirection = DOWN;
}

/*
*   @brief Cette fonction va chercher la nouvelle map pour le niveau suivant,
*   elle reset egalement les infos necessaires.
*/
void NibblerModule::goNextLevel(const char *filepath)
{
    FILE *fp = fopen(filepath, "r");
    char line[1024];

    clear();
    frame.clear();
    while (fgets(line, 1024, fp))
        frame.push_back(line);
    _map.clear();
    getMap(frame);
    setMapDims();
    resetStats();
}


/*
*   @brief Cette fonction analyse la map, compte le nombre de fruits, si il n'y
*   a plus de fruit, passage au niveau suivant.
*/
void NibblerModule::checkStageClear()
{
    int fruitCount = 0;

    for (auto it : _map)
        for (auto it2 : it)
            if (it2 == FruitChar)
                fruitCount++;
    if (fruitCount != 0)
        return;
    _level++;
    if (_level == 2) {
        goNextLevel("gameMaps/nibblerMap2");
        _stageTransition = true;
    }
    if (_level == 3) {
        goNextLevel("gameMaps/nibblerMap3");
        _stageTransition = true;
    }
    if (_level == 4) {
        goNextLevel("gameMaps/nibblerMap4");
        _stageTransition = true;
    }
}

/*
*   @brief Cette fonction analyse les differentes directions ouvertes autour de
*   la tete du serpent et en deduit la direction a suivre.
*/
int NibblerModule::findTurn()
{
    if (_upWay)
        return UP;
    if (_downWay)
        return DOWN;
    if (_rightWay)
        return RIGHT;
    if (_leftWay)
        return LEFT;
    return _direction;
}

/*
*   @brief Cette fonction analyse les differentes directions ouvertes autour de
*   la tete du serpent et en si une seule voie est possible ou non.
*/
bool NibblerModule::isSingleWay()
{
    if ((_upWay && !_downWay && !_leftWay && !_rightWay) ||
        (!_upWay && _downWay && !_leftWay && !_rightWay) ||
        (!_upWay && !_downWay && _leftWay && !_rightWay) ||
        (!_upWay && !_downWay && !_leftWay && _rightWay))
        return true;
    return false;
}

/*
*   @brief Cette fonction verifie si la voie pointe par la nouvelle direction
*   est ouverte.
*   @param[out] Booleen vrai si la voie est ouverte, faux sinon.
*/
bool NibblerModule::isWayOpen(int new_direct)
{
    if ((new_direct == UP && _upWay) ||
        (new_direct == DOWN && _downWay) ||
        (new_direct == LEFT && _leftWay) ||
        (new_direct == RIGHT && _rightWay))
        return true;
    return false;
}

/*
*   @brief Cette fonction met a jour la direction du serpent en fonction de la
*   direction envoyee par le joueur et la position du serpent dans la map.
*   @param[in] Nouvelle direction envoyee au jeu.
*/
void NibblerModule::updateDirection(int new_direct)
{
    int lineVar = 0;
    int colVar = 0;

    if ((_direction == UP && _prevDirection == DOWN) ||
        (_direction == DOWN && _prevDirection == UP) ||
        (_direction == RIGHT && _prevDirection == LEFT) ||
        (_direction == LEFT && _prevDirection == RIGHT))
        _direction = _prevDirection;
    if (isSingleWay())
        new_direct = findTurn();
    if (isWayOpen(new_direct)) {
        if (_direction != new_direct && _direction != NONE)
            _prevDirection = _direction;
        _direction = new_direct;
    }
}

/*
*   @brief Cette fonction met à jour la position de la queue du serpent en
*   fonction du mouvement de la tete. La queue grandit lorsque qu'un fruit est
*   mange.
*   @param[in] Nouvelle position de la tete.
*   @param[in] Information precisant si un fruit a ete mange ou non.
*/
void NibblerModule::updateTail(std::vector<int> oldHeadPos, bool eatFruit)
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
        checkStageClear();
    }
    if (!_stageTransition) {
        _tail[0] = oldHeadPos;
        _map[_tail[0][0]][_tail[0][1]] = TailChar;
    } else
        _stageTransition = false;
}

/*
*   @brief Cette fonction met a jour la position et la taille du serpent en
*   fonction de l'event envoye. Elle incremente egalement le score lorsqu'un
*   fruit est mange par le serpent.
*/
void NibblerModule::updatePos(int event)
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
        _score += 10 * _level;
    }
    if (_map[newHeadPos[0]][newHeadPos[1]] == TailChar &&
        newHeadPos != _tail[_snakeSize - 2])
        _gameIsOver = true;
    if (!(_map[newHeadPos[0]][newHeadPos[1]] == WallChar || (
        _map[newHeadPos[0]][newHeadPos[1]] == TailChar &&
        newHeadPos != _tail[_snakeSize - 2]))) {
        _map[newHeadPos[0]][newHeadPos[1]] = HeadChar;
        setHeadPos(newHeadPos);
        if (_direction != NONE)
            updateTail(oldHeadPos, eatFruit);
    }
    checkWays();
}

/*
*   @brief Cette fonction met a jour la frame de jeu, elle y inscrit la map et
*   les diverses infos dont le core aura a besoin pour l'affichage de jeu.
*/
void NibblerModule::updateFrame()
{
    std::vector<std::string> new_frame;
    std::string score_str = std::to_string(_score);
    std::string dir_str = std::to_string(_direction);

    score_str += "\n";
    dir_str += "\n";
    new_frame.push_back("<MAP>\n");
    for (auto it : _map)
        new_frame.push_back(it);
    // std::string debug;
    // for (auto it : _tail) {
    //     debug = "tail:_";
    //     debug += std::to_string(it[0]);
    //     debug += "-";
    //     debug += std::to_string(it[1]);
    //     debug += "\n";
    //     new_frame.push_back(debug);
    //     debug.clear();
    // }
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
void NibblerModule::eventHandler(int event)
{
    if ((event == UP) || event == DOWN || event == RIGHT || event == LEFT)
        updatePos(event);
    updateFrame();
}

/*
*   @brief Cette fonction stocke les positions de la queue du serpent au debut
*   du jeu en se basant sur la position de la tete du serpent.
*/
void NibblerModule::setTail(std::vector<int> headPos)
{
    _tail.resize(3, std::vector<int>(2, 0));
    for (int i = 0; i < 3; i++) {
        _tail[i][0] = headPos[0];
        _tail[i][1] = headPos[1] - 1 - i;
    }
}

/*
*   @brief Cette fonstion verifie si le caractere mis en argument correspond a
*   une case vide ou a un fruit.
*   @param[in] caractere.
*   @param[out] booleen indiquant si le char est soit une case vide, soit un
*   fruit.
*/
static bool isWayOK(char bloc)
{
    if (bloc == EmptyChar || bloc == FruitChar)
        return true;
    return false;
}

/*
*   @brief Cette fonction analyse la map de jeu pour observer les directions
*   possible pour le serpent et stocker 4 booleens dans l'objet NibblerModule.
*/
void NibblerModule::checkWays()
{
    if (isWayOK(_map[_headPos[0] - 1][_headPos[1]]))
        _upWay = true;
    else
        _upWay = false;
    if (isWayOK(_map[_headPos[0] + 1][_headPos[1]]))
        _downWay = true;
    else
        _downWay = false;
    if (isWayOK(_map[_headPos[0]][_headPos[1] - 1]))
        _leftWay = true;
    else
        _leftWay = false;
    if (isWayOK(_map[_headPos[0]][_headPos[1] + 1]))
        _rightWay = true;
    else
        _rightWay = false;
}

/*
*   @brief Cette fonction analyse la map de jeu pour trouver la position de la
*   tete du serpent.
*   @param[out] vecteur de int pour la position de la tete.
*/
std::vector<int> NibblerModule::findHeadPos()
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
*   @brief Cette fonction analyse la map pour en deduire les dimensions de la
*   map et les stocker dans l'objet NibblerModule.
*/
void NibblerModule::setMapDims()
{
    _mapDims.resize(2, 0);
    for (auto it : _map)
        _mapDims[0]++;
    _mapDims[1] = _map[0].length();
}

/*
*   @brief Cette fonction analyse la frame pour recuperer la map et la stocker
*   dans l'objet NibblerModule.
*/
void NibblerModule::getMap(std::vector<std::string> frame)
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
*   @brief Le constructeur de l'objet NibblerModule, il va ouvrir le fichier
*   "gameMaps/nibblerMap" en lecture only et va y recuperer la frame de jeu.
*   Divers parametres de base y sont initialises (taille du serpent, directions
*   de base, score et etat du jeu).
*/
NibblerModule::NibblerModule()
{
    FILE *fp = fopen("gameMaps/nibblerMap", "r");
    char line[1024];

    while (fgets(line, 1024, fp))
        frame.push_back(line);
    getMap(frame);
    setMapDims();
    setHeadPos(findHeadPos());
    setTail(getHeadPos());
    _started = false;
    _snakeSize = 4;
    _direction = RIGHT;
    _prevDirection = DOWN;
    _score = 0;
    _time = 990;
    _level = 1;
    checkWays();
    _gameIsOver = false;
    _stageTransition = false;
}
