/*
 * UCurses gui view class
 */

#pragma once
#include <ucurses/ucurses.hpp>
#include <card/Texture.hpp>
#include <app/Application.hpp>

class GameUI : public ucurses::State
{
    public:

        static const ctk::Vec2<short> display_size; 
        static const ctk::Vec2<short> board_size; 

        GameUI(cardgame::Application* handle);

        void Quit();

        // Card of value 0 > x > 13 will cause memory read error
        card::Texture* getCardTexture(int id);
        void Render(const Card& card, ucurses::Canvas* canvas, ctk::Vec2<short> pos);

        void Test();

        virtual void Initialize() {}
            
        void InitializeDisplay(ucurses::Canvas* display);
    

    protected:

        // Card arrays are loaded on game construction
        /*
         * A cards graphic ID is derived as such:
         *
         * Face down - 0
         * Ace - 1
         * J - 11
         * Q - 12
         * K - 13
         */ 
        std::array<card::Texture, 14> textures;
        cardgame::Application* app;
    
};
