#include <app/Game.hpp>
#include <app/Config.hpp>
#include <player/PlayerCreate.hpp>

namespace cardgame 
{

    Game::Game() : min_bet(0.f)
    {
        deck.Shuffle(rand_gen);
        card_flip_buffer.loadFromFile("./src/card/cardtake.wav");
        chip_sound_buffer.loadFromFile("./src/app/pokerchips.wav");

        card_flip.setBuffer(card_flip_buffer);
        chip_sound.setBuffer(chip_sound_buffer);
    }

    void Game::_Setup()
    {
        Setup();
    }
            
    void Game::_SetType(unsigned int type)
    { 
        this->type = static_cast<GameType>(type); 
    }

    bool Game::saveExists()
    {
        std::ifstream test(game::save);
        return test.good();
    }

    void Game::Load()
    {
        std::ifstream stream(game::save, std::ios_base::in);
        player.read_binary(stream);
    }

    void Game::Save()
    {
        std::fstream file(game::save, std::ios_base::out | std::ios_base::binary);
        player.write_binary(file);
    }

    void Game::createNewPlayer(const std::string& name)
    {
        player.setName(name);
    }

    Player& Game::getPlayer()
    {
        return player;
    }
}
