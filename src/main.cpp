/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** main
*/

#include "Arcade.hpp"
#include "ErrorHandling.hpp"

int main(int argc, char **argv)
{
    try {
        ErrorHandling error(argc, argv);
        Arcade arcade(argv[1]);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }

    return 0;
}

