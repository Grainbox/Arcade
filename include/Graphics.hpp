/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** Graphics
*/

#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

    #include "IGraphics.hpp"

class Graphics : public IGraphics {
    public:
        virtual ~Graphics() = default;

        virtual void display(const std::vector<std::string> frame) = 0;
        virtual int getEvent() = 0;

        std::string getGameName() const;
        std::string getLibName() const;
        void setGameName(std::string name);
        void setLibName(std::string name);
        std::string getPlayerName();
        void setPlayerName(std::string name);
    protected:
        std::string playerName;
    private:
        std::string gameName;
        std::string libName;
};

#endif /* !GRAPHICS_HPP_ */
