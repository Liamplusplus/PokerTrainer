#include <holdem/Game.hpp>
#include <fstream>

namespace holdem{

    Game::Game() : button_pos(0)
    {
        player_seat = rand_gen.generateUniform(0, 8);
        board.Reset();
    
    }
    
    void Game::Start()
    {
    
    }
            
    void Game::Setup()
    {
    
    }

    void Game::InitialDeal()
    {
    
        std::ofstream test("testfile", std::ios_base::app);
        deck.Reset(rand_gen);
        // Set starting hand to small blind
        int index = button_pos + 1;
        int count = 0;
        while (count <= 17) 
        {
            if (index == 9)
                index = 0;
            test << index << " ";
            if (count <= 8)
                hands[index].cards[0] = deck.Top();
            else
                hands[index].cards[1] = deck.Top();
            ++index;
            ++count;
        }
        hands[player_seat].setVisible(true);
        if (++button_pos == 9)
            button_pos = 0;
    }

    Hand* Game::getHand(int index)
    {
        return &hands[index];
    }
    void Game::NextStreet()
    {
        switch (board.nextStreet())
        {
            case Street::FLOP:
                board.cards[0] = deck.Top();
                board.cards[1] = deck.Top();
                board.cards[2] = deck.Top();
                board.setVisible(true);
                break;
            case Street::TURN:
                board.cards[3] = deck.Top();
                board.setVisible(true);
                break;
            case Street::RIVER:
                board.cards[4] = deck.Top();
                board.setVisible(true);
                break;
        }
        board.Refresh();
        //player_hand.calculateStrength(board);
        //dealer_hand.calculateStrength(board);      
    }
}

