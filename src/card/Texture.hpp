/*
 * Graphical representation of a card
 *
 * Width = 11
 * Height = 9
 */
#pragma once
#include <ucurses/ucurses.hpp>
#include <card/Card.hpp>

namespace card {

    static const unsigned char suit_symbols[Card::Suit::NUMSUIT] = { '{', '[', '}', ']' };
    enum ColorID { BLACK = 10, RED };

    class Texture 
    {
        public:

            static const ctk::Vec2<short> size;

            Texture();
            Texture(int id);

            void Load();

            void Render(ucurses::Canvas* canvas, Card::Suit suit, ctk::Vec2<short> pos);

            const std::array<char, 108>& getData() const;

        protected:

            std::array<char, 108> data;
            int id;

    };


}
