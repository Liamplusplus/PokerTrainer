#include <house/Game.hpp>
#include <fstream>
#include <ctk/io/conversion.hpp>

namespace house {

    Game::Game() : ante(0.f)
    {
        min_bet = 5.f;
        play = 0.f;
    }

    void Game::Start()
    {
    
    }

    void Game::Setup()
    {
    
    }

    void Game::Reset()
    {
        deck.Reset(rand_gen);
        player_hand.Reset();
        dealer_hand.Reset();
        board.Reset();
        ante = 0.f;
        play = 0.f;
    }
            
    float Game::calculatePayout()
    {
        player_hand.calculateStrength(board);
        dealer_hand.calculateStrength(board);

        std::fstream file("payout", std::ios_base::out);
        file << "Hand: " << player_hand.getStrengthName() << " vs " << dealer_hand.getStrengthName() << '\n';
        bool open = (std::get<0>(dealer_hand.strength) >= Hand::Strength::PAIR);
        file << "Dealer opens? " << std::boolalpha << open << '\n';

        float stake = (2 * ante + play);
        float payout = 0.f;

        if (player_hand.strength == dealer_hand.strength)
        {
            player.ChangeBalance(stake);
            file << "Tie: Player wins $" << ctk::to_string(0.f) << '\n';
            return 0.f;
        }
        else if (player_hand.strength > dealer_hand.strength)
        {
            if (open)
            {
                payout = 2 * ante;
                file << "Win: player wins $" << ctk::to_string(2 * ante + play) << '\n';
            }
            else
            {
                payout = ante;
                file << "Win: player wins $" << ctk::to_string(ante + play) << '\n';
            }
            payout += play;
            player.ChangeBalance(stake + payout);
            return payout;
        }
        else
        {
            if (open)
            {
                file << "Lose: player loses $" << ctk::to_string(2 * ante + play) << '\n';
                return -(play + 2 * ante);
            }
            else
            {
                file << "Lose: player loses $" << ctk::to_string(ante + play) << '\n';
                player.ChangeBalance(ante);
                return -(play + ante);
            }
        }
    }

    void Game::InitialDeal()
    {
        deck.Reset(rand_gen);
        player_hand.cards[0] = deck.Top();
        dealer_hand.cards[0] = deck.Top();
        player_hand.cards[1] = deck.Top();
        dealer_hand.cards[1] = deck.Top();
        //player_hand.calculateStrength(board);
        //dealer_hand.calculateStrength(board);
        player_hand.setVisible(true);
    }
           
    void Game::PlaceBet()
    {
        player.ChangeBalance(-ante * 2); 
    }

    int Game::changeBet(float amount)
    {
        float desired_bet = ante + amount;
        if (desired_bet >= 0.f && desired_bet  * 4 <= player.getBalance())
        {
            ante = desired_bet; 
            return 0;
        }
        else
            return -1;
    }
            
    int Game::Play(float multiplier)
    {
        float amount = ante * multiplier; 
        if (player.getBalance() > amount)
        {
            play = amount;
            player.ChangeBalance(-amount);
            return 0;
        }
        else
            return -1;

    }
            
    void Game::NextStreet()
    {
        switch (board.nextStreet())
        {
            case Street::FLOP:
                board.cards[0] = deck.Top();
                board.cards[1] = deck.Top();
                board.cards[2] = deck.Top();
                if (play != 0.f)
                {
                    board.cards[3] = deck.Top();
                    board.cards[4] = deck.Top();
                }
                break;
            case Street::TURN:
                board.cards[3] = deck.Top();
                board.cards[4] = deck.Top();
                break;
        }
        board.Refresh();
        //player_hand.calculateStrength(board);
        //dealer_hand.calculateStrength(board);
    }

}
