/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** SDLModule
*/

#ifndef SDLMODULE_HPP_
#define SDLMODULE_HPP_

    #include "Graphics.hpp"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>

class OpenFontError : public std::exception {
    public:
        OpenFontError() = default;
        ~OpenFontError() = default;

        const char* what() const noexcept override
        {
            return "Failed to load font";
        }
};

class CreateTextureError : public std::exception {
    public:
        CreateTextureError() = default;
        ~CreateTextureError() = default;

        const char* what() const noexcept override
        {
            return "Cannot create texture";
        }
};

class SDLModule : public Graphics {
    public:
        SDLModule(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs);
        ~SDLModule();

        void display(const std::vector<std::string> frame);
        int getEvent();
    protected:
    private:
        void parse (std::vector<std::string> frame);

        void getMap(std::vector<std::string> frame);
        void getScore(std::vector<std::string> frame);
        void getGameOver(std::vector<std::string> frame);

        void init_content();
        void init_text();

        void display_menu();
        int menuEvent();
        void displayTextBox();

        void upMenuButton(int *button, int max);
        void downMenuButton(int *button, int max);

        void displayGame(std::vector<std::string> tmp_frame);
        int gameEvent();

        int maxGameFocus;
        int maxGraphicFocus;
        int focusGraphics;
        int focusGame;
        int cursorList;

        bool gameOver;

        std::string _score;
        std::vector<std::string> frame;

        bool displayMenu;

        SDL_DisplayMode DM;

        std::vector<std::string> _graphicLibs;
        std::vector<std::string> _gameLibs;

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;

        SDL_Surface* input_srf;
        SDL_Texture* input_txt;
        SDL_Rect inputBoxRect;
        SDL_Rect promptRect;
        SDL_Color inputTextColor;

        TTF_Font* font;

        Uint32 start_time;

        int _lastKey;
};

#endif /* !SDLMODULE_HPP_ */
