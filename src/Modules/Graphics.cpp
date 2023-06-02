/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** Graphics
*/

#include "Graphics.hpp"

std::string Graphics::getGameName() const
{
    return this->gameName;
}

std::string Graphics::getLibName() const
{
    return this->libName;
}

void Graphics::setGameName(std::string name)
{
    this->gameName = name;
}

void Graphics::setLibName(std::string name)
{
    this->libName = name;
}

std::string Graphics::getPlayerName()
{
    return this->playerName;
}

void Graphics::setPlayerName(std::string name)
{
    this->playerName = name;
}
