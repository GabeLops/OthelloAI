// MyOthelloAI.cpp


#include <ics46/factory/DynamicFactory.hpp>
#include "MyOthelloAI.hpp"
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, glops::MyOthelloAI, "MY AI(Required)");


std::pair<int, int> glops::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
    // implementation of my AI goes here
    int depth = 4;
    OthelloCell myPlayerType=OthelloCell::black;
    if(state.isWhiteTurn()){
        myPlayerType=OthelloCell::white;
    }
    int maxScore = -1*state.board().width()*state.board().height();
    std::pair<int,int> rv;
    for(int i=0;i<state.board().height();i++){
        for(int j=0;j<state.board().width();j++){
            if(state.isValidMove(i,j)){
                std::unique_ptr<OthelloGameState> stateCopy = state.clone();
                stateCopy->makeMove(i,j);
                int score = recurse(stateCopy, myPlayerType, depth);
                if(score>maxScore){
                    maxScore = score;
                    rv = std::make_pair(i,j);
                }
            }
        }
    }
//    std::cout<<"With Score: "<<maxScore<<std::endl;
    return rv;
}

int glops::MyOthelloAI::recurse(std::unique_ptr<OthelloGameState>& state, OthelloCell myPlayerType, int depth){
    int maxScore = state->board().width()*state->board().height() * -1;
    int minScore = maxScore * -1;
    if(depth==0 || state->isGameOver()){
        return evaluate(state, myPlayerType);
    }else{
        const OthelloBoard& board = state->board();
        for(int i=0;i<board.height();i++){
            for(int j=0;j<board.width();j++){
                if(state->isValidMove(i,j)){
                    std::unique_ptr<OthelloGameState> clonedState = state->clone();           
                    clonedState->makeMove(i,j);
                    int currentScore = recurse(clonedState, myPlayerType, depth-1);
                    if(isMyTurn(state, myPlayerType)){
                        if(maxScore<currentScore){
                            maxScore = currentScore;
                        }
                    }else{
                        if(minScore > currentScore){
                            minScore = currentScore;
                        }
                    }
                }
            }
        }
    }
    if(isMyTurn(state, myPlayerType)){
        return maxScore;
    }
    return minScore;
}

int glops::MyOthelloAI::evaluate(std::unique_ptr<OthelloGameState>& state, OthelloCell myPlayerType){
    int myCount =0;
    int opponentCount =0;
    for(int i=0;i<state->board().height();i++){
        for(int j=0;j<state->board().width();j++){
            if(state->board().cellAt(i,j)==OthelloCell::empty){
                continue;
            }else if(state->board().cellAt(i,j)==myPlayerType){
                myCount++;
            }else{
                opponentCount++;
            }
        }
    }
   // std::cout<<"My Count: "<<myCount<<" Opp Count: "<<opponentCount<<std::endl;
    return myCount-opponentCount;
}

bool glops::MyOthelloAI::isMyTurn(std::unique_ptr<OthelloGameState>& state, OthelloCell myPlayerType){
    if(myPlayerType==OthelloCell::white){
        return state->isWhiteTurn();
    }    
    else{
        return state->isBlackTurn();
    }
}

void glops::MyOthelloAI::printCounts(std::unique_ptr<OthelloGameState>& state){

    int e=0;
    int w=0;
    int b=0;
    for(int i=0;i<state->board().height();i++){
        for(int j=0;j<state->board().width();j++){
            if(state->board().cellAt(i,j)==OthelloCell::empty){
                e++;
            }else if(state->board().cellAt(i,j)==OthelloCell::white){
                w++;
            }else{
                b++;
            }
        
        }
    }

   std::cout<<"Empty: "<<e<<" White: "<<w<<" Black: "<<b<<std::endl;
}
