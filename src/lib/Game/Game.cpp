#include "Game.hpp"
#include "../Set/SetProcess.hpp"

Game::Game()
{
    Coloring clr;
    clr.green();
    cout << "\n __   __  _______  _______  _______  ______    _______    _______  _______  ______    _______  __   __ \n"
            "|  |_|  ||   _   ||       ||  _    ||    _ |  |       |  |       ||   _   ||    _ |  |       ||  | |  |\n"
            "|       ||  |_|  ||  _____|| |_|   ||   | ||  |   _   |  |    _  ||  |_|  ||   | ||  |_     _||  |_|  |\n"
            "|       ||       || |_____ |       ||   |_||_ |  | |  |  |   |_| ||       ||   |_||_   |   |  |       |\n"
            "|       ||       ||_____  ||  _   | |    __  ||  |_|  |  |    ___||       ||    __  |  |   |  |_     _|\n"
            "| ||_|| ||   _   | _____| || |_|   ||   |  | ||       |  |   |    |   _   ||   |  | |  |   |    |   |  \n"
            "|_|   |_||__| |__||_______||_______||___|  |_||_______|  |___|    |__| |__||___|  |_|  |___|    |___|  \n"
         << endl;
    clr.reset();

    for (int i = 0; i < 7; i++)
    {
        string nickname;
        try
        {
            cout << "Enter the nickname of Player " << i + 1 << ": ";
            cin >> nickname;
            if (cin.fail())
            {
                throw StringException();
            }
            Player playerElmt(nickname);
            this->listOfPlayer.push_back(playerElmt);
        }
        catch (StringException &e)
        {
            e.what();
        }
    }
}

void Game::startGame()
{
    int firstPlayerIdx = 0;
    while (!checkEndGame())
    {
        SetProcess gameSet(listOfPlayer, firstPlayerIdx);
        gameSet.getCurrPlayerIdx();
        firstPlayerIdx = (gameSet.getCurrPlayerIdx() + 1) % listOfPlayer.size();
    }
}

bool Game::checkEndGame()
{
    for (auto &p : listOfPlayer)
    {
        if (p.getPoint() >= pow(2, 32))
        {
            cout << "CONGRATULATIONS" << endl;
            return true;
        }
    }
    return false;
}

Game::~Game()
{
    this->listOfPlayer.clear();
}