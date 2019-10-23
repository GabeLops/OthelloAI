#include "OthelloAI.hpp"
#include "OthelloCell.hpp"

namespace glops
{
    class MyOthelloAI : public OthelloAI
    {
    public:
        virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
    private:
        int recurse(std::unique_ptr<OthelloGameState>& state, OthelloCell myPlayerType, int depth);
        int evaluate(std::unique_ptr<OthelloGameState>& state, OthelloCell myPlayerType);
        bool isMyTurn(std::unique_ptr<OthelloGameState>& state, OthelloCell myPlayerType);
        void printCounts(std::unique_ptr<OthelloGameState>& state);
    };
    
}

