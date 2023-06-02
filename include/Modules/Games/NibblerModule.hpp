/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** NibblerModule
*/

/**
 * @file NibblerModule.hpp
 * @brief Ce fichier implemente le jeu Nibbler
*/

#ifndef NIBBLERMODULE_HPP_
#define NIBBLERMODULE_HPP_

    #include <Games.hpp>

class NibblerModule : public Games {
    public:
        NibblerModule();
        ~NibblerModule() = default;

        void eventHandler(int event);
        std::vector<std::string> getFrame() { return frame; };
        void updateFrame();
        void getMap (std::vector<std::string> frame);
        void setMapDims();

        long getScore() { return _score; };

        void snakeGrow() { this->_snakeSize += 1; };
        int getSnakeSize() const { return this->_snakeSize; };

        std::vector<int> findHeadPos();
        std::vector<int> getHeadPos() const { return this->_headPos; };
        void setHeadPos(std::vector<int> new_pos) { this->_headPos = new_pos; };

        void updatePos(int event);
        void setTail(std::vector<int> headPos);
        void updateTail(std::vector<int> oldHeadPos, bool eatFruit); // à appeler après updatePos().

        int getDirection() const { return this->_direction; };
        void updateDirection(int new_direct);
        bool isSingleWay();
        int findTurn();
        void checkWays();
        bool isWayOpen(int new_direct);

        void checkStageClear();
        void goNextLevel(const char *filepath);
        void resetStats();

    protected:
    private:
        std::vector<std::string> _map;
        bool _started;
        bool _stageTransition;
        int _snakeSize;
        int _score;
        int _time;
        int _level;
        int _direction;
        int _prevDirection;
        std::vector<int> _headPos; // [1]line [2]col
        std::vector<std::vector<int>> _tail;
        std::vector<int> _mapDims;
        bool _upWay;
        bool _downWay;
        bool _rightWay;
        bool _leftWay;
        bool _gameIsOver;
};

#endif
