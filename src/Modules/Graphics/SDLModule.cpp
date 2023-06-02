/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** SDLModule
*/

#include "SDLModule.hpp"
#include <unistd.h>
#include <stdio.h>
#include "Color.hpp"

extern "C"
{

    IGraphics *entryPoint(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs)
    {
        return (new SDLModule(gameLibs, graphicLibs));
    }

    void isGraphic()
    {}

}

SDLModule::SDLModule(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs)
{
    this->displayMenu = true;
    this->_lastKey = NONE;

    this->_gameLibs = gameLibs;
    this->_graphicLibs = graphicLibs;

    this->maxGameFocus = _gameLibs.size() - 1;
    this->maxGraphicFocus = _graphicLibs.size() - 1;
    this->focusGame = 0;
    this->focusGraphics = 0;
    this->cursorList = 0;
    this->start_time = 0;
    this->gameOver = false;

    this->setGameName("");
    this->setLibName("arcade_sdl2");
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_GetCurrentDisplayMode(0, &DM);
    this->window = SDL_CreateWindow("ARCADE",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        DM.w, DM.h, 0);
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    this->init_text();
    this->init_content();
    SDL_StartTextInput();
}

SDLModule::~SDLModule()
{

    SDL_DestroyTexture(this->input_txt);
    SDL_FreeSurface(this->input_srf);

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
    SDL_StopTextInput();
}

void SDLModule::init_content()
{
    this->inputTextColor = {235, 64, 52, 0};
    this->input_srf = TTF_RenderText_Solid(font, "Enter your name", this->inputTextColor);
    this->input_txt = SDL_CreateTextureFromSurface(renderer, this->input_srf);
    this->inputBoxRect = { (DM.w / 2) - 150, (DM.h / 2) + 350, 300, 30 };
    this->promptRect = { (DM.w / 2) - 175, (DM.h / 2) + 300, this->input_srf->w, this->input_srf->h };
}

void SDLModule::init_text()
{
    this->font = TTF_OpenFont("assets/ARCADE_I.TTF", 24);
    if (!font)
        throw OpenFontError();
}

void SDLModule::displayTextBox()
{
    SDL_RenderCopy(renderer, this->input_txt, NULL, &promptRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &inputBoxRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderDrawRect(renderer, &inputBoxRect);
    SDL_Surface* inputSurface = NULL;
    if (playerName == "") {
        inputSurface = TTF_RenderText_Solid(font, " ", this->inputTextColor);
    } else {
        inputSurface = TTF_RenderText_Solid(font, playerName.c_str(), this->inputTextColor);
    }
    SDL_Texture* inputTexture = SDL_CreateTextureFromSurface(renderer, inputSurface);
    SDL_Rect inputRect = { inputBoxRect.x + 5, inputBoxRect.y + 5, inputSurface->w, inputSurface->h };
    SDL_RenderCopy(renderer, inputTexture, NULL, &inputRect);
    SDL_FreeSurface(inputSurface);
    SDL_DestroyTexture(inputTexture);
}

void SDLModule::display_menu()
{
    int i = 0;
    int j = 0;
    int max = _graphicLibs.size() + _gameLibs.size();
    int marge = 0;

    for (auto it : _graphicLibs) {
        SDL_Color color;
        if (!cursorList) {
            if (focusGraphics == i) {
                color = {255, 71, 71, 255};
            } else if (!maxGraphicFocus) {
                color = {255, 71, 71, 255};
            } else
                color = {255, 255, 255, 255};
        } else {
            color = {168, 168, 168, 255};
        }
        SDL_Surface* surface = TTF_RenderText_Solid(font, it.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect;
        rect.w = DM.w / (it.size() / 3);
        rect.h = surface->h;
        rect.x = DM.w / 6;
        rect.y = ((DM.h / 5)) + marge;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        marge += DM.h / 10;
        i++;
    }
    marge = 0;
    for (auto it : _gameLibs) {
        SDL_Color color;
        if (cursorList) {
            if (focusGame == j) {
                color = {255, 71, 71, 255};
            } else if (!maxGameFocus) {
                color = {255, 71, 71, 255};
            } else
                color = {255, 255, 255, 255};
        } else {
            color = {168, 168, 168, 255};
        }
        SDL_Surface* surface = TTF_RenderText_Solid(font, it.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect;
        rect.w = DM.w / (it.size() / 3);
        rect.h = surface->h;
        rect.x = DM.w - 800;
        rect.y = ((DM.h / 5)) + marge;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        marge += DM.h / 10;
        j++;
    }
    this->displayTextBox();
}

/*
*   @brief Cette fonction recupere la map dans la frame
*   @param[in] frame vecteur de string qui contient la map entre <MAP></MAP>
*/
void SDLModule::getMap(std::vector<std::string> tmp_frame)
{
    bool s = false;

    for (auto it : tmp_frame) {
        if (it == "<MAP>\n") {
            s = true;
            continue;
        }
        if (it == "</MAP>\n")
            break;
        if (s) {
            frame.push_back(it);
        }
    }
}
/*
*   @brief Cette fonction recupere le score dans la frame
*   @param[in] frame vecteur de string qui contient le score entre <SCORE></SCORE>
*/
void SDLModule::getScore(std::vector<std::string> tmp_frame)
{
    bool s = false;

    for (auto it : tmp_frame) {
        if (it == "<SCORE>\n") {
            s = true;
            continue;
        }
        if (it == "</SCORE>\n")
            break;
        if (s) {
            _score = it;
            _score.pop_back();
        }
    }
}

void SDLModule::getGameOver(std::vector<std::string> tmp_frame)
{
    bool s = false;

    for (auto it : tmp_frame) {
        if (it == "<GAME_OVER>\n") {
            s = true;
            continue;
        }
        if (it == "</GAME_OVER>\n")
            break;
        if (s) {
            if (it == "true\n")
                this->gameOver = true;
            else
                this->gameOver = false;
        }
    }
}

/*
*   @brief Cette fonction recupere le score et la map dans la frame
*   @param[in] frame vecteur de string qui contient le score et la map entre <MAP></MAP> <SCORE></SCORE>
*/
void SDLModule::parse(std::vector<std::string> tmp_frame)
{
    getMap(tmp_frame);
    getScore(tmp_frame);
    getGameOver(tmp_frame);
}


void SDLModule::displayGame(std::vector<std::string> str)
{
    int t = 0;
    parse(str);
    SDL_DisplayMode _mode;
    SDL_GetCurrentDisplayMode(0, &_mode);

    for (int y = 0; y < (int)frame.size(); y++) {
        for (int i = 0; i < (int)frame[y].size(); i++) {
            SDL_Rect rect;
            rect.w = (_mode.w / frame[y].size()) - t;
            rect.h = (_mode.h / frame.size()) - t;
            rect.x = (_mode.w / frame[y].size()) * i;
            rect.y = (_mode.h / frame.size()) * y;

            SDL_Color color;

            switch (frame[y][i]) {
                case '#':
                    color = { 0, 0, 0, 255 };
                    break;
                case '\n':
                    color = { 0, 0, 0, 255 };
                    break;
                case 'A':
                    color = { 255, 0, 0, 255 };
                    break;
                case 'P':
                    color = { 255, 255, 0, 255 };
                    break;
                case 'G':
                    color = { 0, 255, 0, 255 };
                    break;
                case ' ':
                    color = { 128, 128, 128, 255 };
                    break;
                case '|':
                    color = { 0, 255, 255, 255 };
                    break;
                case 'o':
                    color = { 0, 0, 255, 255 };
                    break;
                case 'U':
                    color = { 255, 192, 203, 255 };
                    break;
                case 'F':
                    color = SDL_Pink;
                    break;
                default:
                    color = { 255, 255, 255, 255 };
                    break;
            }

            SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, rect.w, rect.h, 32, SDL_PIXELFORMAT_RGBA32);
            SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            SDL_Rect dest = { rect.x, rect.y, rect.w, rect.h };
            SDL_RenderCopy(renderer, texture, NULL, &dest);
            SDL_DestroyTexture(texture);
        }
    }
    SDL_Surface* text_surface = TTF_RenderText_Blended(font, (playerName + " " + _score).c_str(), {255, 0, 0, 255});
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    SDL_Rect dstrect = {(DM.w / 2) - 200, 10, 300, 50};

    SDL_RenderCopy(renderer, text_texture, NULL, &dstrect);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    frame.clear();
}

void SDLModule::display(const std::vector<std::string> frame)
{
    SDL_RenderClear(this->renderer);
    if (this->displayMenu)
        this->display_menu();
    else
        this->displayGame(frame);
    SDL_RenderPresent(this->renderer);
}

int SDLModule::menuEvent()
{
    if (this->event.type == SDL_TEXTINPUT && this->playerName.length() < 12) {
        this->playerName += event.text.text;
        return BREAK;
    }
    if (event.key.keysym.sym == SDLK_BACKSPACE && playerName.length() > 0) {
        playerName.pop_back();
        return BREAK;
    }
    if (this->event.type == SDL_KEYDOWN) {
        if (this->event.key.keysym.sym == SDLK_ESCAPE)
            this->displayMenu = false;
        if (this->event.key.keysym.sym == SDLK_LEFT)
            this->cursorList = 0;
        if (this->event.key.keysym.sym == SDLK_RIGHT)
            this->cursorList = 1;
        if (this->event.key.keysym.sym == SDLK_DOWN && !cursorList) {
            this->downMenuButton(&focusGraphics, this->maxGraphicFocus);
        } else if (this->event.key.keysym.sym == SDLK_DOWN && cursorList)
            this->downMenuButton(&focusGame, this->maxGameFocus);
        if (this->event.key.keysym.sym == SDLK_UP && !cursorList) {
            this->upMenuButton(&focusGraphics, this->maxGraphicFocus);
        } else if (this->event.key.keysym.sym == SDLK_UP && cursorList)
            this->upMenuButton(&focusGame, this->maxGameFocus);
        if (this->event.key.keysym.sym == SDLK_RETURN || this->event.key.keysym.sym == SDLK_KP_ENTER) {
            this->setGameName(this->_gameLibs.at(focusGame));
            this->setLibName(this->_graphicLibs.at(focusGraphics));
            if (!cursorList)
                return LIBCHANGED;
            else {
                this->displayMenu = false;
                return GAMECHANGED;
            }
        }
    }
    return BREAK;
}

void SDLModule::upMenuButton(int *button, int max)
{
    if (*button == 0) {
        *button = max;
    } else {
        *button -= 1;
    }
}

void SDLModule::downMenuButton(int *button, int max)
{
    if (*button == max) {
        *button = 0;
    } else {
        *button += 1;
    }
}

int SDLModule::gameEvent()
{
    Uint32 current_time = SDL_GetTicks();

    if (this->event.key.keysym.sym == SDLK_ESCAPE)
        this->displayMenu = true;
    if (gameOver)
        return NONE;
    if (this->event.type == SDL_KEYDOWN) {
        if (this->event.key.keysym.sym == SDLK_z)
            _lastKey = UP;
        if (this->event.key.keysym.sym == SDLK_q)
            _lastKey = LEFT;
        if (this->event.key.keysym.sym == SDLK_s)
            _lastKey = DOWN;
        if (this->event.key.keysym.sym == SDLK_d)
            _lastKey = RIGHT;
    }
    if (current_time - start_time >= 100) {
        start_time = current_time;
        return this->_lastKey;
    }
    return NONE;
}

int SDLModule::getEvent()
{
    while (SDL_PollEvent(&this->event)) {
        if (this->event.type == SDL_QUIT ||
            (this->event.type == SDL_KEYDOWN &&
            this->event.key.keysym.sym == SDLK_DELETE))
            return QUIT;
        if (this->displayMenu)
            return menuEvent();
        if (this->event.type == SDL_KEYDOWN &&
            this->event.key.keysym.sym == SDLK_F1)
            return RESTARTGAME;
        if (this->event.type == SDL_KEYDOWN &&
            this->event.key.keysym.sym == SDLK_F2) {
            return NEXTGRAPHIC;
        }
        if (this->event.type == SDL_KEYDOWN &&
            this->event.key.keysym.sym == SDLK_F3) {
            return NEXTGAME;
        }
        return gameEvent();
    }
    if (this->displayMenu)
        return menuEvent();
    return gameEvent();
}
