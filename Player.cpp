#include "Player.h"


Player::Player(string n, string c, Board *b, AI *a){
    forfeit = false;
    drawing = false;
    draw_count = 0;
    name = n;
    color = c;
    board = b;
    player_type = 'a';
    findPieces();
    agent = a;
}

Player::Player(const Player& p, Board* newBoard)
{
    name = p.name;
    color = p.color;
    board = newBoard;
    player_type = p.player_type;
    drawing = p.drawing;
    forfeit = p.forfeit;
    draw_count = p.draw_count;
    for(int i = 0; i < p.pieces.size(); i ++)
    {
        pieces.push_back(new Piece(*(p.pieces[i])));
    }
}

void Player::findPieces(){
    //delete the current pieces - if there aren't any, this does nothing
    pieces.clear();
    Piece *tmp;
    //scan entire board
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board->getTile(i,j)->getOccupied()==true)
            {
                tmp = board->getPiece(i, j);
            }
            if(tmp != nullptr){
                if (tmp->getColor() == color){
                    pieces.push_back(tmp);
                }
            }
        }
    }
}

bool Player::removePiece(Piece *p){
    for (int i = 0; i < pieces.size(); i++){
        if (pieces[i] == p){
            //vectors remove elements by using an iterator to denote location
                //pieces.begin() is the start iterator - adding int keeps it an iterator
            pieces.erase(pieces.begin() + i);
            return true;
        }
    }
    return false;   //piece not found for removal
}

bool Player::hasPiece(Piece *p){
    for (int i = 0; i < pieces.size(); i++){
        if(pieces[i] == p){
            return true;
        }
    }
    return false;
}

bool Player::makeMove(Tile start, Tile end){
    return board->move(start, end);
}

void Player::takeTurn(int gx, int gy, int x, int y){
    if(player_type == 'a'){
        std::vector<Tile> move_pair;
                do{
                     move_pair = agent->getNextMove();
                }while(!board->move(move_pair[0], move_pair[1]));
                QThread::sleep(2);

    }
    if(player_type == 'p'){
        bool successful_move;
            successful_move = board->move(Tile(gx, gy), Tile(x, y));
        if(successful_move == false && board->getTile(x,y)->getOccupied()==true)
        {
            if(board->getPiece(x,y)->getColor()==color)
            {
                board->setSP(board->getPiece(x,y)); //selected piece
                board->setBoardState(1);
            }
        }
        if(successful_move==true)
        {
            board->checkWins();
            board->setBoardState(0);
            board->nextPlayer();
            board->incrementTurn();
            if(board->getCurrentPlayer()->getType()=='a')
            {

            }
        }
    }
}

void Player::startDraw(){
        drawing = true;
        draw_count = 0;
}

void Player::stopDrawing(){
    drawing = false;
    draw_count = 0; //not strictly necessary, but maybe a good idea
}
