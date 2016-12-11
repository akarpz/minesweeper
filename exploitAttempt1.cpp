#include <iostream>
#include<limits>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include<math.h>

using namespace std;

void printBoard(int** board, int** PCBoard, size_t height, size_t width);
bool checkForWin(int** board, int** PCBoard, size_t height, size_t width);
bool userSelection(int** board, int** PCBoard, size_t height, size_t width, int x, int y, int f);
void fillBoard(int** board, size_t height, size_t width, size_t mines);
void getUserSelection(int& x,int& y,int& f, size_t height, size_t width);
void printSolution(int** board,size_t height, size_t width);

void printSolution(int** board,size_t height, size_t width){

       cout<<" ";
    for(int i=0; i<width*2;i++)
        if(i%2 == 0)
            cout<<" ";
        else
            cout<<(i/2);
    cout<<endl<<" ";
    for(int i=0; i<width*2;i++)
        if(i%2 == 0)
            cout<<" ";
        else
            cout<<"-";

    cout<<endl<<"0|";

    for(int i=0;i<height;i++){
        for(int j=0; j<width;j++){

                if(board[i][j] == -1)
                cout << "X|";
                else
                cout << board[i][j]<<"|";
        }
        if(i != height-1)
        cout<<endl<<i+1<<"|";
        else
            cout<<endl<<" ";
    }
    for(int i=0; i<width*2;i++)
        if(i%2 == 0)
            cout<<" ";
        else
            cout<<"-";

            cout<<endl;



}

void printBoard(int** board, int** PCBoard, size_t height, size_t width){

   cout<<" ";
    for(int i=0; i<width*2;i++)
        if(i%2 == 0)
            cout<<" ";
        else
            cout<<(i/2);
    cout<<endl<<" ";
    for(int i=0; i<width*2;i++)
        if(i%2 == 0)
            cout<<" ";
        else
            cout<<"-";

    cout<<endl<<"0|";

    for(int i=0;i<height;i++){
        for(int j=0; j<width;j++){
            if(PCBoard[i][j] == 1){
                if(board[i][j] == -1)
                cout << "X|";
                else
                cout << board[i][j]<<"|";

            }
            else if(PCBoard[i][j] == 0)
                cout <<"*|";
            else if(PCBoard[i][j] == 2)
                cout <<"F|";
        }
        if(i != height-1)
        cout<<endl<<i+1<<"|";
        else
            cout<<endl<<" ";
    }
    for(int i=0; i<width*2;i++)
        if(i%2 == 0)
            cout<<" ";
        else
            cout<<"-";

            cout<<endl;

}




void getUserSelection(int &x,int &y,int &f, size_t height, size_t width){


    string input;

    int temp;
    //getting x coordinates
    while(true){
        cout << "Please Enter row number (digit and less than "<<height<<"): ";
        getline(cin,input);
        stringstream s(input);
        if(s>>temp)
            if(temp < height && temp >= 0){

            x = temp;
            break;
        }

        cout << "You did not enter an acceptable value, Please Enter row number (digit and less than "<<height<<"): ";
    }

    //getting y coordinates
    while(true){
        cout << "Please Enter column number (digit and less than "<<width<<"): ";
        getline(cin,input);

        stringstream s2(input);
        if(s2>>temp)
            if(temp < width && temp >= 0){
            y = temp;
            break;
        }


        cout << "You did not enter an acceptable value, Please Enter column number (digit and less than "<<width<<"): ";}


    //getting f value where 0 means to select the box and 1 means to flag it
    while(true){
        cout << "Please choose 0 to open the location and 1 to set a flag: ";
        getline(cin,input);

        stringstream s3(input);
        if(s3>>temp)
            if(temp == 0 || temp == 1){
            f = temp;
            break;
            }


        cout << "You did not enter an acceptable value, Please choose 0 to open the location and 1 to set a flag: ";
    }


}


bool userSelection(int** board, int** PCBoard, size_t height, size_t width, int x, int y, int f){


    if(x >= height || y >= width)
        return false;

    //in case flag was chosen
    if(f == 1){
        PCBoard[x][y] = 2;
        return false;
    }

    bool temp;
        //in case there were no mines near the selected box recursively
    if(board[x][y]== 0 ){
        PCBoard[x][y]=1;

        //open boxes near it
        int a = -1;
        if(x == 0)
            a =0;

        for (;a <=1;++a){
            int b= -1;
            if(y==0)
                b=0;
            for(;b<=1;++b){

                if(x+a < height && y+b < width){
                    if(PCBoard[x+a][y+b]==1)
                    continue;
                    //cout << "at x= "<<x<<" y= "<<y<<" a= "<<a<<" b= "<<b<<endl;
                    temp = userSelection(board,PCBoard,height,width,x+a,y+b,f);

                    }

                }

            }


        return false;
        }

    // in case of a mine
    if(board[x][y]== -1){
            PCBoard[x][y]=1;
            return true;

    }

        //if none of the above cases
        PCBoard[x][y]=1;
        return false;

    }

void fillBoard(int** board, size_t height, size_t width, size_t mines){

    srand (time(NULL));

    //initialize board with zeros
    for(int a=0;a<height;++a)
        for(int b=0; b<width;++b)
            board[a][b] = 0;

    //fill board with mines
    int i,j;
    for(int counter=0; counter < mines;++counter){
            i = rand() % height;
            j = rand() % width;
            if(board[i][j] == 0)
                board[i][j] = -1;
            else
                --counter;

        }

    //fill board with mines count around each box
    for(int a=0;a<height;++a)
        for(int b=0; b<width;++b){
                if(board[a][b]== -1)
                continue;
                int x = -1;
                if(a == 0)
                    x =0;


                for (;x <=1;++x){
                    int y=-1;
                    if(b==0)
                    y=0;
                    for(;y<=1;++y)
                        if(x+a < height && y+b < width)
                            if(board[a+x][b+y]==-1)
                                ++board[a][b];


            }
        }




}

bool checkForWin(int** board, int** PCBoard, size_t height, size_t width){


    for(int i=0;i<height;i++)
        for(int j=0; j<width;j++){
            if (PCBoard[i][j] == 0)
                return false;
            else if(PCBoard[i][j] == 2)
                    if(board[i][j] != -1)
                        return false;

        }

    return true;


}


int main(int argc, char* argv[])
{
    size_t height, width, mines;

    size_t temp;

    //cout << sqrt((numeric_limits<int>::max()/sizeof(int)))<<endl;


    //check if input is valid
    if(argc < 4){
        cout << "argumantes are too few, ending program"<<endl;
        return -1;
        }
    stringstream s(argv[1]);
    stringstream s2(argv[2]);
    stringstream s3(argv[3]);
    if(s>>temp){
        if( temp>0 && temp<16256)
        height = temp;
        else{
        cout << "Wrong input for height, ending program"<<endl;
        return -1;
    }
        }
    else{
        cout << "Wrong input for height, ending program"<<endl;
        return -1;
    }

    if(s2>>temp){
        if( temp>0 && temp<16256)
        width = temp;
        else{
        cout << "Wrong input for width, ending program"<<endl;
        return -1;
        }
    }
    else{
        cout << "Wrong input for width, ending program"<<endl;
        return -1;
    }

    if(s3>>temp){
        if( temp>0 && temp < height*width)
        mines = temp;
        else{
        cout << "Wrong input for mines, ending program"<<endl;
        return -1;
    }

        }
    else{
        cout << "Wrong input for mines, ending program"<<endl;
        return -1;
    }

    //Define Board and Player Choice Board => PCBoard
    //Board will contain mines locations and number of mines surrounding each box


    int** board = new int*[height];
    if (board == NULL)
        return -2;
    for(int i = 0; i < height; i++){
    board[i] = new int[width];

    if (board[i] == NULL)
        return -2;
        }

    //PCBoard will contain 0 for still not picked, 1 picked, 2 flagged
    int** PCBoard = new int*[height];
    if (PCBoard == NULL)
        return -2;
    for(int i = 0; i < height; i++){
    PCBoard[i] = new int[width];

    if (PCBoard[i] == NULL)
        return -2;
        }

    //Initialize PCBoard

    for(int i=0;i<height;i++)
        for(int j=0; j<width;j++)
            PCBoard[i][j] = 0;

    fillBoard(board,height,width,mines);

    bool win = false;
    bool lose = false;
    int x,y,f;
    printSolution(board,height,width);
        cout<<endl<<endl;

    while(!win && !lose){


        printBoard(board,PCBoard,height,width);
        getUserSelection(x,y,f,height,width);
        lose = userSelection(board,PCBoard,height,width,x,y,f);
        if(lose)
            break;
        win = checkForWin(board,PCBoard,height,width);


    }

if(win){
    cout << "congratulations You have won!"<<endl;
    printBoard(board,PCBoard,height,width);
    }
else{
    cout << "sorry, you have lost!"<<endl;
    printBoard(board,PCBoard,height,width);
    }


for(int i = 0; i < height; i++){
delete[] board[i];
delete[] PCBoard[i];
}
delete[] board;
delete[] PCBoard;
    return 0;
}