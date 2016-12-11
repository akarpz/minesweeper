#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;

class Tile {
    public:
        int xLoc;
        int yLoc;
        int nearMines;
        bool isMine;
        bool isVisible;
        Tile(int, int);
        Tile();
};

Tile::Tile(int x, int y) {
    xLoc = x;
    yLoc = y;
    nearMines = 0;
    isVisible = false;
    isMine = false;
}

Tile::Tile() {}



class Board {
    public:
        int width;
        int height;
        int numMines;
        vector<vector<Tile> > tiles;
        Board(int, int, int);
        bool valid_location(int, int);
        //Tile findTile(int, int);
};

Board::Board(int w, int h, int n) {
    width = w;
    height = h;
    numMines = n;
    
    for(int i = 0; i < height; i++) {
        
        vector<Tile> temp;
        
        for(int j = 0; j < width; j++) {
            temp.push_back(Tile(i, j));
        }
        
        tiles.push_back(temp);
    }
}

bool Board::valid_location(int x, int y) {
    return ((x >=0 && x < width) && y >= 0 && y < height);
}

// Tile Board::findTile(int x, int y){
    
//     return tiles.at(x).at(y);
    
// }

bool check_win(Board &board) {
    int unmarked_count = 0;
    for(int j = 0; j < board.height; j++) {
        for(int k = 0; k < board.width; k++) {
            if(board.tiles.at(j).at(k).isVisible == false) {
                unmarked_count++;
            }
        }
    }
    return unmarked_count == board.numMines;
}



bool look_around(Board &board, int x, int y) {
    bool update = 0;
    
    if(board.valid_location(x-1,y-1)) {
        if(board.tiles.at(x-1).at(y-1).isMine == false && board.tiles.at(x-1).at(y-1).isVisible == false) {
            board.tiles.at(x-1).at(y-1).isVisible = true;
            if(board.tiles.at(x-1).at(y-1).nearMines == 0) {
                update = 1;
            }
        }
    }
    
    if(board.valid_location(x-1,y)) {
        if(board.tiles.at(x-1).at(y).isMine == false && board.tiles.at(x-1).at(y).isVisible == false) {
            board.tiles.at(x-1).at(y).isVisible = true;
            if(board.tiles.at(x-1).at(y).nearMines == 0) {
                update = 1;
            }
        }
    }
    
    if(board.valid_location(x-1,y+1)) {
        if(board.tiles.at(x-1).at(y+1).isMine == false && board.tiles.at(x-1).at(y+1).isVisible == false) {
            board.tiles.at(x-1).at(y+1).isVisible = true;
            if(board.tiles.at(x-1).at(y+1).nearMines == 0) {
                update = 1;
            }
        }
    }
    
    if(board.valid_location(x,y-1)) {
        if(board.tiles.at(x).at(y-1).isMine == false && board.tiles.at(x).at(y-1).isVisible == false) {
            board.tiles.at(x).at(y-1).isVisible = true;
            if(board.tiles.at(x).at(y-1).nearMines == 0) {
                update = 1;
            }
        }
    }
    
    if(board.valid_location(x,y+1)) {
        if(board.tiles.at(x).at(y+1).isMine == false && board.tiles.at(x).at(y+1).isVisible == false) {
            board.tiles.at(x).at(y+1).isVisible = true;
            if(board.tiles.at(x).at(y+1).nearMines == 0) {
                update = 1;
            }
        }
    }
    
    if(board.valid_location(x+1,y-1)) {
        if(board.tiles.at(x+1).at(y-1).isMine == false && board.tiles.at(x+1).at(y-1).isVisible == false) {
            board.tiles.at(x+1).at(y-1).isVisible = true;
            if(board.tiles.at(x+1).at(y-1).nearMines == 0) {
                update = 1;
            }
        }
    }
    
    if(board.valid_location(x+1,y)) {
        if(board.tiles.at(x+1).at(y).isMine == false && board.tiles.at(x+1).at(y).isVisible == false) {
            board.tiles.at(x+1).at(y).isVisible = true;
            if(board.tiles.at(x+1).at(y).nearMines == 0) {
                update = 1;
            }
        }
    }
    
    if(board.valid_location(x+1,y+1)) {
        if(board.tiles.at(x+1).at(y+1).isMine == false && board.tiles.at(x+1).at(y+1).isVisible == false) {
            board.tiles.at(x+1).at(y+1).isVisible = true;
            if(board.tiles.at(x+1).at(y+1).nearMines == 0) {
                update = 1;
            }
        }
    }
    
    
    return update;
}


void update_board(Board &board) { // TODO make comment to explain what this does
    bool update = 1;
    
    while(update) {
        for(int j = 0; j < board.height; j++) {
            for(int k = 0; k < board.width; k++) {
                if(board.tiles.at(j).at(k).nearMines == 0 && board.tiles.at(j).at(k).isVisible == true) {
                    update = look_around(board, j, k);
                }
    
            }
            
       }
    }
}

void play_move(Board &board, int x, int y) {
    if(x >= board.height || y >= board.width || x < 0 || y < 0) {
        cout << "That's not in the range of the board!" << endl;
    }
   
    
    if(board.tiles.at(x).at(y).isMine){
        cout << "You hit a mine! Try again" << endl;
        exit(0);
    }
     else { 
        
        board.tiles.at(x).at(y).isVisible = true;
        update_board(board);
       
    }
    
    
    
} // TODO: add if in range and not a mine functionality



void distribute_mines(Board &board) {// this is not done yet
    srand(time(NULL));
    int x, y;
    for(int i = 0; i < board.numMines; i++) {
        x = rand() % board.height;
        y = rand() % board.width;
        if(board.tiles.at(x).at(y).isMine){
            i--;
            continue;
        }
        board.tiles.at(x).at(y).isMine = true;
//THIS IS WHERE I LEFT OFF ----------------------------------------
        if(x == 0) { // top row
            if(y == 0) { // top left corner
                board.tiles.at(x+1).at(y).nearMines += 1;
                board.tiles.at(x+1).at(y+1).nearMines += 1;
                board.tiles.at(x).at(y+1).nearMines += 1;
            }
            else if( y == board.width - 1) { // top right corner
                board.tiles.at(x).at(y-1).nearMines += 1;
                board.tiles.at(x+1).at(y-1).nearMines += 1;
                board.tiles.at(x+1).at(y).nearMines += 1;
            }
            else { // top row center
                board.tiles.at(x).at(y-1).nearMines += 1;
                board.tiles.at(x+1).at(y-1).nearMines += 1;
                board.tiles.at(x+1).at(y).nearMines += 1;
                board.tiles.at(x+1).at(y+1).nearMines += 1;
                board.tiles.at(x).at(y+1).nearMines += 1;
            }
        }
        else if(x == board.height -1) { // bottom row
            if(y == 0) { // bottom left corner
                board.tiles.at(x-1).at(y).nearMines += 1;
                board.tiles.at(x-1).at(y+1).nearMines += 1;
                board.tiles.at(x).at(y+1).nearMines += 1;
            }
            else if(y == board.width - 1) { // bottom right corner
                board.tiles.at(x).at(y-1).nearMines += 1;
                board.tiles.at(x-1).at(y-1).nearMines += 1;
                board.tiles.at(x-1).at(y).nearMines += 1;
            }
            else { // bottom middle
                board.tiles.at(x).at(y-1).nearMines += 1;
                board.tiles.at(x-1).at(y-1).nearMines += 1;
                board.tiles.at(x-1).at(y).nearMines += 1;
                board.tiles.at(x-1).at(y+1).nearMines += 1;
                board.tiles.at(x).at(y+1).nearMines += 1;
            }
        }
        else if(y == 0) { // center left side, if it was the top corners, it would have been caught in previous "if"
            board.tiles.at(x-1).at(y).nearMines += 1;
            board.tiles.at(x-1).at(y+1).nearMines += 1;
            board.tiles.at(x).at(y+1).nearMines += 1;
            board.tiles.at(x+1).at(y+1).nearMines += 1;
            board.tiles.at(x+1).at(y).nearMines += 1;
        }
        else if(y == board.width - 1) { // center right side, see above comment
            board.tiles.at(x-1).at(y).nearMines += 1;
            board.tiles.at(x-1).at(y-1).nearMines += 1;
            board.tiles.at(x).at(y-1).nearMines += 1;
            board.tiles.at(x+1).at(y-1).nearMines += 1;
            board.tiles.at(x+1).at(y).nearMines += 1;
        }
        else { // the tile is not on an outside wall of the board
            board.tiles.at(x-1).at(y).nearMines += 1;
            board.tiles.at(x-1).at(y-1).nearMines += 1;
            board.tiles.at(x).at(y-1).nearMines += 1;
            board.tiles.at(x+1).at(y-1).nearMines += 1;
            board.tiles.at(x+1).at(y).nearMines += 1;
            board.tiles.at(x-1).at(y+1).nearMines += 1;
            board.tiles.at(x).at(y+1).nearMines += 1;
            board.tiles.at(x+1).at(y+1).nearMines += 1;
        }
    }
}







int main(int argc, char *argv[]) {
    if(argc != 4) {
        cout << "Wrong number of arguments" << endl;
        return(0);
    
    }
    
    if((atoi(argv[1]) || atoi(argv[2])) > 32766 ){
        cout << "sorry we can't make a board that big" << endl;
        return(0);    
    }//blocks user from passing arguments larger than int type can handle
    
    else {
        
        cout << argv[0] << endl;
        
        Board board (atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        
        
        distribute_mines(board);
        /*
        for(int i = 0; i < board.tiles.size(); i++) {
            for(int j = 0; j < board.tiles.at(0).size(); j++) {
                cout << board.tiles.at(i).at(j).xLoc << board.tiles.at(i).at(j).yLoc << board.tiles.at(i).at(j).isMine 
                << board.tiles.at(i).at(j).nearMines << " ";
            }
            cout << endl;
        }
        */
        // for(int i = 0; i < board.tiles.size(); i ++){
        //     for(int j = 0; j< board.tiles.at(0).size(); j ++){
        //         mine_proximity_check(board, i, j);
        //         cout << board.tiles.at(i).at(j).nearMines << " " << i << j;
        //     }
        // }//print row of number of neighboring tiles with mines and their indexes
        
        // mine_proximity_check(board, 0, 0);
        // cout << board.tiles.at(0).at(0).nearMines << endl;
        
        string input = "";
        int x = 0;
        int y = 0;
        while(true){
            
            while(true) {
                cout << "Enter coordinates to play in the form X [SPACE] Y . Type \"Q\" to quit" << endl;
                getline(cin, input);
                
                stringstream ss(input);
                
                if(ss >> x){
                }
                if(ss >> y){
                    break;
                }
            }
            play_move(board, x, y);
            
            cout << "  " ;
            for(int j = 0; j < board.width; j++) {
                cout << j << "_";
            }
            cout << endl;
            
            for(int i = 0; i < board.tiles.size(); i++) {
                cout << i <<"|";
                for(int j = 0; j < board.tiles.at(0).size(); j++) {
                    
                if(board.tiles.at(i).at(j).isVisible) {
                    if(board.tiles.at(i).at(j).nearMines == 0) {
                        cout << "_|";
                    }
                    else {
                        cout << board.tiles.at(i).at(j).nearMines << "|";
                    }
                }
                else {
                    cout << "[]";
                }
            }
            cout << endl;
            
            
        }
        
        if(check_win(board)) {
            cout << "You win..... good job" << endl;
            break;
        }
            
        }
    }
}