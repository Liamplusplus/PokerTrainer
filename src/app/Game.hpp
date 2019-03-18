/*
 * Base virtual class designed for indirection between application and game data
 * Game classes will implement methods to organise data and game flow.
 */

#pragma once
#include <player/Player.hpp>
#include <card/Deck.hpp>
#include <ctk/random/RandomGenerator.hpp>
#include <SFML/Audio.hpp>

namespace cardgame
{
    enum class GameType { HOUSE = 0, HOLDEM, BLACKJACK };

    class Game
    {
        public:

            Game();

            virtual void Setup() = 0;
            virtual void Start() = 0;

            /* Hidden methods */

            void _Setup();
            void _SetType(unsigned int type); 

            // Data and accessors
            Player player;
            Player& getPlayer();

            Deck deck;
            GameType Type() { return type; }

            void createNewPlayer(const std::string& name);
            bool saveExists();

            void Save();
            void Load();

            float min_bet;

            sf::Sound card_flip;
            sf::Sound chip_sound;

        protected:

            GameType type;
		    ctk::RandomGenerator rand_gen;

            sf::SoundBuffer card_flip_buffer;
            sf::SoundBuffer chip_sound_buffer;
    };

}
