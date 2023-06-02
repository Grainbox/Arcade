/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** Games
*/

#ifndef GAMES_HPP_
#define GAMES_HPP_

    #include "IGames.hpp"

class Games : public IGames {
    public:
        ~Games() = default;

        virtual void eventHandler(int event) = 0;
        virtual std::vector<std::string> getFrame() = 0;

    protected:
        std::vector<std::string> frame;
    private:
};

#endif /* !GAMES_HPP_ */
