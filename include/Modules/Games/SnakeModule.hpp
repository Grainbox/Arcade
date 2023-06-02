/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** SnakeModule
*/

/**
 * @file SnakeModule.hpp
 * @brief Ce fichier implemente le jeu Snake
*/

#ifndef SNAKEMODULE_HPP_
#define SNAKEMODULE_HPP_

    #include <Games.hpp>

class SnakeModule : public Games {
    public:
        SnakeModule();
        ~SnakeModule() = default;

        void eventHandler(int event);
        std::vector<std::string> getFrame() { return frame; };
        void updateFrame();
        void getMap (std::vector<std::string> frame);

        long getScore() { return _score; };

        void snakeGrow() { this->_snakeSize += 1; };
        void spawnFruit();
        void setMapDims(); // analyse la frame et en déduit la taille de la map
        std::vector<int> getMapDims() const;
        int getSnakeSize() const { return this->_snakeSize; };

        std::vector<int> findHeadPos();
        std::vector<int> getHeadPos() const { return this->_headPos; };
        void setHeadPos(std::vector<int> new_pos) { this->_headPos = new_pos; };

        // int getScore() const { return this->_score; };
        // void setScore(int new_score) { this->_score = new_score; };

        void updatePos(int event);
        void setTail(std::vector<int> headPos);
        void updateTail(std::vector<int> oldHeadPos, bool eatFruit); // à appeler après updatePos().

        int getDirection() const { return this->_direction; };
        void updateDirection(int new_direct);

    protected:
    private:
        std::vector<std::string> _map;
        bool _started;
        int _snakeSize;
        int _score;
        int _direction;
        int _prevDirection;
        std::vector<int> _headPos; // [1]line [2]col
        std::vector<std::vector<int>> _tail;
        std::vector<int> _mapDims;
        bool _gameIsOver;
};

class InvalidMap : public std::exception {
public:
    InvalidMap() = default;
    ~InvalidMap() = default;

    const char* what() const noexcept override
    {
        return "Map is invalid";
    }
};
#endif
