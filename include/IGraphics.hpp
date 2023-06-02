/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** IGraphics
*/

#ifndef IGRAPHICS_HPP_
#define IGRAPHICS_HPP_

    #include <iostream>
    #include <vector>
    #include "events.hpp"

/**
 * @interface IGames
 * Gère les différentes libs graphiques de l'arcade
 */
class IGraphics {
    public:
        virtual ~IGraphics() = default;

        /**
         * @fn virtual void display(std::vector<std::string> frame) = 0;
         * S'occupe d'interpréter la frame reçue depuis IGames::getFrame() et de l'afficher correctement
         * @param frame La frame envoyée par IGames::getFrame()
        */
        virtual void display(const std::vector<std::string> frame) = 0;
        /**
         * @fn virtual int getEvent() = 0;
         * Interprète l'évenement du joueur et le retourne avec la table dans events.hpp
         * @param frame La frame envoyée par IGames::getFrame()
        */
        virtual int getEvent() = 0;

        /**
         * @fn virtual std::string getGameName() const = 0;
         * Renvoie le nom du jeu qui doit être joué. Sous forme: "arcade_nom" (Ex: arcade_snake), le core le récupère pour charger la lib en ajoutant "./lib/" et ".so"
        */
        virtual std::string getGameName() const = 0;
        /**
         * @fn virtual std::string getLibName() const = 0;
         * Renvoie le nom de la lib graphique qui doit tourner. Sour forme: "arcade_nom", le core le récupère pour charger la lib en ajoutant "./lib/" et ".so"
        */
        virtual std::string getLibName() const = 0;
        /**
         * @fn virtual void setGameName(std::string name) = 0;
         * Assigne un jeu à jouer sous forme: "arcade_nom"
        */
        virtual void setGameName(std::string name) = 0;
        /**
         * @fn virtual void setLibName(std::string name) = 0;
         * Assigne la lib graphique qui doit tourner sous forme: "arcade_nom"
        */
        virtual void setLibName(std::string name) = 0;
        /**
         * @fn virtual std::string getPlayerName() = 0;
         * Récupoère le nom du joueur
        */
        virtual std::string getPlayerName() = 0;
        /**
         * @fn virtual void setPlayerName(std::string name) = 0;
         * Assigne le nom du joueur
        */
        virtual void setPlayerName(std::string name) = 0;
    protected:
    private:
};

#endif /* !IGRAPHICS_HPP_ */
