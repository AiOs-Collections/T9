//Board.cpp

/*

Initial Board Layout

X-coordinate

9   B   B   B   B

8 B   B   B   B   B

7   B   B   B   B   B

6 B   B   B   B   B  

5 o o o o o o o o o o 

4 o o o o o o o o o o

3   W   W   W   W   W

2 W   W   W   W   W 

1   W   W   W   W   W

0 W   W   W   W   W 
  0 1 2 3 4 5 6 7 8 9

  Y-coordinates
  
char boardState[x-coordinates][y-coordinates];

States: 'w'=White piece
		'b'=Black piece
		'x'=Invalid space (Represented by ' ')
		'e'=Empty space

*/

#include <iostream>

#include "board.h"
#include "piece.h"
#include "validmove.cpp"
#include <QSignalMapper>
using namespace std;

Board::Board(QWidget* parent, int t, int ts, int bs) : QWidget(parent)
{
    QWidget* wdg = new QWidget(this);
    this->setwdg(wdg);
    boardsize=bs;
    tilesize=ts;
    isPaused=false;
    wdg->resize(80+boardsize,80+boardsize);

    //Initialzies Tiles
    selectedPiece=nullptr;
    selectedTile=nullptr;
    boardstate=0;
    theme = t;
   for (int x = MIN_X; x < MAX_X; x++) {
        for (int y = MIN_Y; y < MAX_Y; y++)
        {
            if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
            {
                state[x][y] = new Tile(wdg);
                state[x][y]->setTile(x, y,true, theme, tilesize);
                //Generate white pieces
                if(y<3)
                {
                    state[x][y]->setPiece(new Piece(state[x][y]));
                    state[x][y]->getPiece()->setColor("white");
                    state[x][y]->getPiece()->changePos(x, y);
                    state[x][y]->getPiece()->buildPiece(theme, tilesize);
                    state[x][y]->layout()->addWidget(state[x][y]->getPiece());
                    state[x][y]->setOccupied(true);
                    connect(state[x][y]->getPiece(), &QPushButton::clicked, this, [=]{pieceClicked(x,y);});
                }
                //Generate black pieces
                if(y>4)
                {
                    state[x][y]->setPiece(new Piece(state[x][y]));
                    state[x][y]->getPiece()->setColor("black");
                    state[x][y]->getPiece()->changePos(x, y);
                    state[x][y]->getPiece()->buildPiece(theme, tilesize);
                    state[x][y]->layout()->addWidget(state[x][y]->getPiece());
                    state[x][y]->setOccupied(true);
                    connect(state[x][y]->getPiece(), &QPushButton::clicked, this, [=]{pieceClicked(x,y);});
                }
                connect(state[x][y], &QPushButton::clicked, this, [=]{tileClicked(x,y);});

            }
            else
            {
                state[x][y] = new Tile(wdg);
                state[x][y]->setTile(x,y,false, t, tilesize);
            }
        }
    }
}

Board::Board(const Board& b)
{
    // Copy board state
    for(int i = 0; i < BOARD_SIZE; i ++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            state[i][j] = b.state[i][j];
        }
    }
    // Copy players
    for(int i = 0; i < b.players.size(); i ++)
    {
        Player* p = new Player(*(b.players.at(i)), this);
        players.push_back(p);
    }
}

Piece* Board::getPiece(int xcord, int ycord)
{
    return state[xcord][ycord]->getPiece();
}

void Board::tileClicked(int x, int y)
{
    cout<<"Tile clicked x"<<x<<endl;
    cout<<"Tile clicked y"<<y<<endl;

    if(boardstate==0)
    {

    }
    if(boardstate==1 && state[x][y]->getOccupied()==false) //If unoccupied available tile was selected
    {
        currentPlayer->takeTurn(selectedPiece->getX(), selectedPiece->getY(),
                                x, y);
    }
}

void Board::pieceClicked(int x, int y)
{
    if(boardstate==0) //If player picked their piece
    {
        if(currentPlayer->getColor()==state[x][y]->getPiece()->getColor())
        {
            selectedPiece=state[x][y]->getPiece(); //stores piece
            boardstate=1;
        }
    }
    if(boardstate==1) //If player picked as seperate piece
    {
        if(currentPlayer->getColor()==state[x][y]->getPiece()->getColor())
        {
            selectedPiece=state[x][y]->getPiece();
        }
    }
}



void Board::turnKing(int x, int y)
{
    if(state[x][y]->getPiece()->getColor() == "black")
    {
        if(y==0)
        {
            if(theme==0)
            {
                state[x][y]->getPiece()->setIcon(QIcon(":/Images/Black-King-Piece.png"));
            }
            if(theme==1)
            {
                state[x][y]->getPiece()->setIcon(QIcon(":/Images/TempBlackKing.png"));
            }
            state[x][y]->getPiece()->makeKing();
        }
    }
    if(state[x][y]->getPiece()->getColor() == "white")
    {
        if(y==7)
        {
            if(theme==0)
            {
            state[x][y]->getPiece()->setIcon(QIcon(":/Images/White-King-Piece.png"));
            }
            if(theme==1)
            {
            state[x][y]->getPiece()->setIcon(QIcon(":/Images/TempWhiteKing.png"));
            }
            state[x][y]->getPiece()->makeKing();
        }
    }
}

void Board::rescale(){
    if(80+boardsize <= 200)
    {
        w->resize(200,200);
    }
    else if(80+boardsize > 200)
    {
        w->resize(80+boardsize,80+boardsize);
    }
    for (int x = MIN_X; x < MAX_X; x++) {
        for (int y = MIN_Y; y < MAX_Y; y++){
            state[x][y]->setIconSize(QSize(10+tilesize,10+tilesize));
            state[x][y]->setGeometry(x*(10+tilesize), (((10+tilesize)*8)-(10+tilesize))-(y*(10+tilesize)),
                                     10+tilesize, 10+tilesize);
            if(state[x][y]->getOccupied()==true)
            {
                state[x][y]->getPiece()->setIconSize(QSize(4+tilesize,4+tilesize));
                state[x][y]->getPiece()->setMinimumSize(4+tilesize,4+tilesize);
                state[x][y]->getPiece()->setGeometry(x*(10+tilesize), (((10+tilesize)*8)-(10+tilesize))-(y*(10+tilesize)),
                                                 10+tilesize, 10+tilesize);
            }
        }
    }
}


void Board::deleteBoard(){
    for (int i = 0; i < players.size(); i++){
        vector<Piece *> player_pieces = players[i]->getPieces();
        for (int i = 0; i < player_pieces.size(); i++){
            delete player_pieces[i];
        }
        delete players[i];
    }
}

void Board::trueOutput()
{
    // Create a char array and populate with pieces
    char b[BOARD_SIZE][BOARD_SIZE];
    for(int i = 0; i < BOARD_SIZE; i ++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            b[i][j] = ' ';
        }
    }
    for(int p = 0; p < players.size(); p ++)
    {
        for(int i = 0; i < players[p]->getPieces().size(); i ++)
        {
            int x = players[p]->getPieces()[i]->getX();
            int y = players[p]->getPieces()[i]->getY();
            char c = (players[p]->getPieces()[i]->getColor() == "white") ? ('w') : ('b');
            if(x < BOARD_SIZE && y < BOARD_SIZE)
            {
                b[x][y] = c;
            }
        }

    }
    cout << "x\n";
    for(int x = BOARD_SIZE - 1; x >= 0; x--)
    {
        cout << x << "  ";
        for(int y = 0; y < BOARD_SIZE; y++)
        {
            cout << b[x][y];
            cout << ' ';
        }
        cout << endl;
    }
    cout << "   0 1 2 3 4 5 6 7 8 9 y\n" << endl;
}

void Board::output()
{
    cout << "x\n";
    for(int x=BOARD_SIZE-1; x>=0; x--)
    {
        cout << x << "  ";
        for(int y=0; y<BOARD_SIZE; y++)
        {
            //cout << y + 1 << ' ';
            Piece *piece = getPiece(x, y);
            if(piece != nullptr){
                if( piece->getColor()=="white"){
                    if(piece->isKing()){
                        cout << 'W';
                    } else{
                        cout<<'w';
                    }
                }
                else if(piece->getColor()=="black"){
                    if(piece->isKing()){
                        cout << 'B';
                    } else{
                        cout << 'b';
                    }
                }
                else
                    cout<<'E'; //Error condition, should not be printed
            } else{
                cout << ' ';
            }
            cout<<' ';
        }
        cout<<endl;
    }
    cout << "   0 1 2 3 4 5 6 7 8 9 y\n" << endl;
    return;
}

bool Board::move(Tile start, Tile end){
    //start by verifying beginning and ending pieces are appropriate
        // - starting should have a piece, ending should have a space
    start.setPiece(state[start.getX()][start.getY()]->getPiece());
    if(start.getPiece() != nullptr){
        if(state[end.getX()][end.getY()]->getOccupied()==true)
        {
            end.setPiece(state[end.getX()][end.getY()]->getPiece());
        }
        if(end.getPiece() == nullptr){
            vector<vector<int>> start_piece_moves = start.getPiece()->moveModifiers();
            bool valid_distance = false;	//must be proven true

            for (int i = 0; i < start_piece_moves.size(); i++){
                int new_x,
                    new_y;

                //checking single diagonal move
                new_x = start.getX() + start_piece_moves[i][0];
                new_y = start.getY() + start_piece_moves[i][1];
                //Check if new_x and new_y are within board bounds
                if( (new_x < BOARD_SIZE) && (new_x >= 0) ){
                    if( (new_y < BOARD_SIZE) && (new_y >= 0) ){
                        //Check if the new_x and new_y are at the end point
                        if( new_x == end.getX() && new_y == end.getY()){
                            valid_distance = true;
                            break;
                        }
                    }
                }

                //we may have to check for a middle piece next -which will be
                    //at our current new_x/y position. save tbreakhese for that check
                int middle_x = new_x,
                    middle_y = new_y;

                //checking double diagonal move
                new_x = start.getX() + (2 * start_piece_moves[i][0]);
                new_y = start.getY() + (2 * start_piece_moves[i][1]);
                //Check if new_x and new_y are within board bounds
                if( (new_x < BOARD_SIZE) && (new_x >= 0) ){
                    if( (new_y < BOARD_SIZE) && (new_y >= 0) ){
                        //Check if the new_x and new_y are at the end point
                        if( new_x == end.getX() && new_y == end.getY()){
                            //see if there is a middle piece
                            Piece *middle_piece = getPiece(middle_x, middle_y);
                            if(middle_piece == nullptr){	//invalid move - can only jump a piece
                                break;
                            } else {	//valid option
                                valid_distance = true;

                                //jumping an opponent's piece - we must remove that piece
                                if(start.getPiece()->getColor() != middle_piece->getColor()){
                                    for (int i = 0; i < players.size(); i++){
                                        if(players[i]->getColor() == middle_piece->getColor()){
                                            state[middle_piece->getX()][middle_piece->getY()]->getPiece()->close();
                                            players[i]->removePiece(middle_piece);
                                            state[middle_piece->getX()][middle_piece->getY()]->setPiece(nullptr);
                                            state[middle_piece->getX()][middle_piece->getY()]->setOccupied(false);
                                            incrementNAD(currentPlayer->getColor());
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }//done checking

            if(valid_distance){
                state[end.getX()][end.getY()]->setPiece(start.getPiece());
                state[start.getX()][start.getY()]->removePiece();
                state[end.getX()][end.getY()]->addPiece(end.getX(),end.getY());
                state[end.getX()][end.getY()]->getPiece()->disconnect();
                int x=end.getX();
                int y=end.getY();
                connect(state[end.getX()][end.getY()]->getPiece(), &QPushButton::clicked, this, [=]{pieceClicked(x,y);});
                //if we ended up at the opposite side, make us a king!
                if(start.getPiece()->getColor() == "white"){
                    if(start.getPiece()->getY() == BOARD_SIZE-1){
                        turnKing(start.getPiece()->getX(), start.getPiece()->getY());
                        start.getPiece()->makeKing();
                    }
                } else{
                    if(start.getPiece()->getY() == 0){
                        turnKing(start.getPiece()->getX(), start.getPiece()->getY());
                    }
                }
                return true;
            }
        }
    }
    return false;
}

/* Checks if checker game has reached a end state
 * Returns:
 * 	NULL if no end condition is reached
 * 	Pointer to NOBODY if a tie condition is reached
 * 	Address of the winning player if a win condition is reached
 *
 * Parameters:
 * 	const references to p1 and p2 (or the board's member pointers)
 */

Player* Board::checkWins() // Params can be replaced with board's player pointers
{
    Board * b = new Board;
    b->copyBoard(currentPlayer->getBoard());
    Player 	*p1 = new Player(players[0]->getName(), "white", b),
            *p2 = new Player(players[1]->getName(), "black", b),
            *winner = nullptr;
    ValidMove p1_valid_moves,
              p2_valid_moves;
    b->addPlayer(p1);
    b->addPlayer(p2);
    b->setCurrentPlayer(p1);
    p1_valid_moves.findMoves(*p1);
    b->copyBoard(currentPlayer->getBoard());
    p2_valid_moves.findMoves(*p2);

    if (p1->getPieces().size() == 0 && p2->getPieces().size() == 0)
    {
        cout << "\terrybody's out of pieces!" << endl;
        winner = new Player("NOBODY", "", p1->getBoard());
    }
    else if(p1->getPieces().size() == 0)
    {
        cout << "p1 is out of pieces!" << endl;
        // Player2 wins
        winner = p2;
    }
    else if(p2->getPieces().size() == 0)
    {
        cout << "\tp2 is out of pieces!" << endl;
        // Player1 wins
        winner = p1;
    }
    else if(p1->isForfeit())
    {
        cout << "\tp1 forfeit!" << endl;
        // Player2 wins
        winner = p2;
    }
    else if(p2->isForfeit())
    {
        cout << "\tp2 forfeit!" << endl;
        // Player1 wins
        winner = p1;
    }
    // If some player can't move, they lose
    else if(p1_valid_moves.total_moves == 0)
    {
        cout << "\tp1 out of valid moves!" << endl;
        winner = p2;
    }
    else if(p2_valid_moves.total_moves == 0) // Replace with valid moves checker
    {
        cout << "\tp2 is out of valid moves!" << endl;
        winner = p1;
    }
    // If both players agree to draw, nobody wins
    else if(p1->isDrawing() && p2->isDrawing())
    {
        cout << "\tdraw!" << endl;
        winner = new Player("NOBODY", "", p1->getBoard());
    }
    // If neither player can force a win, nobody wins (40 move rule)
    else if(p1->isDrawing() && p2->getDrawCount() > 40 || p2->isDrawing() && p1->getDrawCount() > 40)
    {
        cout << "\tdraw 2!" << endl;
        winner = new Player("NOBODY", "", p1->getBoard());
    }
    winner = nullptr;
    if(s->Player1NA->text().toInt() == 0)
    {
        QLabel* win = new QLabel("Winner!");
        win->show();
    }
    if(s->Player2NA->text().toInt() == 0)
    {
        QLabel* win = new QLabel("Winner!");
        win->show();
    }
    return winner;
}

void Board::nextPlayer()
{
    for (unsigned k=0; k<players.size(); k++)
    {
        if(players.at(k)==currentPlayer)
        {
            if(k<players.size()-1)
            {
                setCurrentPlayer(players.at(k+1));
                break;
            }
            else if(k>=players.size()-1)
            {
                setCurrentPlayer(players.at(0));
                break;
            }
        }
    }
    s->Player->setText(QString::fromStdString(currentPlayer->getName()));
}


void Board::incrementNAD(string c)
{
    if(c=="white")
    {
        s->Player2NA->setNum(s->Player2NA->text().toInt()-1);
        s->Player2ND->setNum(s->Player2ND->text().toInt()+1);
    }
    else if(c=="black")
    {
        s->Player1NA->setNum(s->Player2NA->text().toInt()-1);
        s->Player1ND->setNum(s->Player2ND->text().toInt()+1);
    }
}

void Board::incrementTurn()
{
    s->Turn->setNum(s->Turn->text().toInt()+1);
}

void Board::copyBoard(Board * b)
{
    for(int x = 0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            if(state[x][y]->getOccupied()==true)
            {
                state[x][y]->removePiece();
            }
            if(b->getTile(x,y)->getOccupied()==true)
            {
                state[x][y]->setPiece(new Piece(state[x][y],b->getPiece(x,y)->getColor(),x,y));
            }
            if(b->getTile(x,y)->getOccupied()==true)
            {

            }
        }
    }

}

/*
Board* oneMove( int startX, int startY, int endX, int endY)
{

}
	
Board** totalMove()
{

}
*/
