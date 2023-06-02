/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-hugo1.fontaine
** File description:
** Arcade
*/

#include "Arcade.hpp"

Arcade::Arcade(std::string graphicLibPath)
{
    size_t pos = graphicLibPath.find_last_of('/');
    this->libPath = graphicLibPath.substr(0, pos);
    this->game = nullptr;
    this->graphic = nullptr;
    this->gameLoader = nullptr;
    this->graphicLoader = nullptr;

    this->getAllLibs();
    this->getGameLibs();
    this->getGraphicLibs();

    this->loadGraphic(graphicLibPath);
    std::vector<std::string> frame;
    long score = 0;
    int event = NONE;

    int i = 0;

    loadGame(libPath + "/arcade_nibbler.so");

    while (1) {
        if (this->game != nullptr)
            frame = this->game->getFrame();
        this->graphic->display(frame);
        if ((event = this->graphic->getEvent()) == QUIT)
            break;
        if (event == LIBCHANGED) {
            this->loadGraphic(this->libPath + "/" + this->graphic->getLibName());
            continue;
        }
        if (event == GAMECHANGED) {
            this->loadGame(this->libPath + "/" + this->graphic->getGameName());
            continue;
        }
        if (event == RESTARTGAME) {
            this->loadGame(this->currentGame);
            continue;
        }
        if (event == NEXTGRAPHIC) {
            std::filesystem::path path(this->currentGraphic);
            std::string filename = path.filename().string();
            for (long unsigned int i = 0; i < this->graphicLibs.size(); i++) {
                if (this->graphicLibs[i] == filename && (i + 1) != this->graphicLibs.size())
                    this->loadGraphic(this->libPath + "/" + this->graphicLibs[i + 1]);
                if (this->graphicLibs[i] == filename && (i + 1) == this->graphicLibs.size())
                    this->loadGraphic(this->libPath + "/" + this->graphicLibs[0]);
            }
            continue;
        }
        if (event == NEXTGAME) {
            std::filesystem::path path(this->currentGame);
            std::string filename = path.filename().string();
            for (long unsigned int i = 0; i < this->gameLibs.size(); i++) {
                if (this->gameLibs[i] == filename && (i + 1) != this->gameLibs.size())
                    this->loadGame(this->libPath + "/" + this->gameLibs[i + 1]);
                if (this->gameLibs[i] == filename && (i + 1) == this->gameLibs.size())
                    this->loadGame(this->libPath + "/" + this->gameLibs[0]);
            }
            continue;
        }
        if (this->game != nullptr)
            this->game->eventHandler(event);
        // for (auto it : frame) {
        //     printf("%s", it.c_str());
        // }
    }
}

Arcade::~Arcade()
{
    if (this->game != nullptr)
        delete this->game;
    if (this->graphic != nullptr)
        delete this->graphic;
    if (this->gameLoader != nullptr)
        delete this->gameLoader;
    if (this->graphicLoader != nullptr)
        delete this->graphicLoader;
}

void Arcade::getAllLibs()
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(this->libPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                this->allLibs.push_back(ent->d_name);
            }
        }
        closedir(dir);
    } else
        throw (OpenLibFolderError());
}

void Arcade::getGameLibs()
{
    void* handle = nullptr;
    void* sym = NULL;
    char *error = NULL;

    for (auto it : this->allLibs) {
        if (handle != nullptr) {
            dlclose(handle);
            handle = nullptr;
        }
        handle = dlopen((this->libPath + "/" + it).c_str(), RTLD_NOW);
        if (!handle)
            throw (DLLoaderError());
        sym = dlsym(handle, "isGame");
        if (sym)
            this->gameLibs.push_back(it);
    }
    if (handle != nullptr)
        dlclose(handle);
}

void Arcade::getGraphicLibs()
{
    void* handle = nullptr;
    void* sym = NULL;
    char *error = NULL;

    for (auto it : this->allLibs) {
        if (handle != nullptr) {
            dlclose(handle);
            handle = nullptr;
        }
        handle = dlopen((this->libPath + "/" + it).c_str(), RTLD_NOW);
        if (!handle)
            throw (DLLoaderError());
        sym = dlsym(handle, "isGraphic");
        if (sym)
            this->graphicLibs.push_back(it);
    }
    if (handle != nullptr)
        dlclose(handle);
}

void Arcade::loadGraphic(std::string path)
{
    playerName = "Pseudo..";
    if (this->graphic != nullptr) {
        playerName = this->graphic->getPlayerName();
        delete this->graphic;
        this->graphic = nullptr;
    }
    this->graphicLoader = new DLLoader<IGraphics>(path);
    this->graphic = this->graphicLoader->getInstance(this->gameLibs, this->graphicLibs);
    this->currentGraphic = path;
    this->graphic->setPlayerName(playerName);
}

void Arcade::loadGame(std::string path)
{
    if (this->game != nullptr) {
        delete this->game;
        this->game = nullptr;
    }
    this->gameLoader = new DLLoader<IGames>(path);
    this->game = this->gameLoader->getInstance(this->gameLibs, this->graphicLibs);
    this->currentGame = path;
}
