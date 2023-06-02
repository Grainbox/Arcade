/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

    #include <iostream>
    #include <stdio.h>
    #include <string.h>
    #include <cstring>
    #include <vector>
    #include <ncurses.h>
    #include "events.hpp"

/**
 * @interface IGames
 * Gère les différents jeux de l'arcade
 */
    class IGames {
        public:
            virtual ~IGames() = default;

            /**
             * @fn virtual void eventHandler(int event) = 0;
             * Récupère l'event provenant d IGraphics::getEvent() et update la frame en fonction de l'event
             * @param event L'event envoyé par IGraphics::getEvent()
            */
            virtual void eventHandler(int event) = 0;

            /**
             * @fn virtual std::vector<std::string> getFrame() = 0;
             * Renvoi la Frame dans son état actuel
            */
            virtual std::vector<std::string> getFrame() = 0;

        protected:
        private:
    };

#endif /* !IGAMES_HPP_ */
