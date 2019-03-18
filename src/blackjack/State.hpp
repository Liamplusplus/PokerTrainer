/*
 * Attempt at an abstract game state
 * class to reduce amount of code in
 * Game class for the various game states
 *
 * States are responsible for advancing the game one
 * step at a time make it easier for saving and maintaining
 * code
 */
namespace blackjack {
    class State 
    {

        public:

            enum class _State;

            void 	Setup()		{}
            void 	Advance() 	{}

            _State 	getState()	{ return state; }

        protected:

            _State state;


    };
}
