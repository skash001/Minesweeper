#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "minesweeper.h"
using namespace std;


/* structure to receive the user input and pass it to processInput() for game play 
*
*/
struct input_t{
	char operation;			// 'm'= mark,'u' = unmark, 'r' = reveal 
	int  row;
	int  column;
};


void playTime(minesweeper& play);
void viewStatistics();
void loadGameFromFile();
input_t loadGameFromProgram();
input_t getUserInput( );
void processInput(minesweeper& play, input_t input);


/* Global variables that read the minefield and number of rows and columns
* the minesweeper object is constructed using these values
*/
vector<vector<int> > mineField;
int rows=0;
int columns=0;
int mines=0;



/*
 * 
 */
int main() {

	 
     int option;

    
     /* This will be your main GUI loop. You should query the user for  
     *  starting a game, or quitting the program. You should
     * 	handle user input either succinctly or by making a call to a helper method
     *	to perform the desired operations.
     */
     while (1) {

		// TODO - Ask the user with options to perform either Starting a game, Viewing
		// statistics, Quitting the program,  and any 
   		// other functionality you feel is necessary.
    	// Each iteration here is one round of the game.
	
    	// somewhere you need to create a minesweeper game object first if the 
    	// user decides to start a new round of game, e.g., 
    	// minesweeper play();

		mineField.clear();
		cout<<"what would you like to do ?"<<endl<<" 1. Play game "<<endl<<" 2. Quit"<<endl;
		cin>>option;

		if(option>2||option<1||cin.fail()){
			cout<<"please enter number between 1 and 2"<<endl;
			cin.clear();
			continue;
		}
	
		if(option==2){
			cout<<"bye bye"<<endl;
			return 0;
		}

   		else if(option==1){

		int loadOption;
		cout<<"How would you like to load the mines into game?"<<endl<<"1. Load from file "<<endl<<"2. generate from program"<<endl;
		cin>>loadOption;
		while(cin.fail()){

			if(loadOption>2||loadOption<1){
				cout<<" Enter either 1 or 2"<<endl;
				cin>>loadOption;
			}
		}
		
		// initialize input to an invalid location,	
		input_t firstInput;
		firstInput.operation = 'r';
		firstInput.row = -1;
		firstInput.column =-1;

		if(loadOption==1)	
			loadGameFromFile();										//read the input file to populate mineField
		else
			firstInput = loadGameFromProgram();						//populate mineField based on user's first input.

			
		cout<<rows<<" "<<columns<<" "<<mines<<endl;
		for(int i=0; i<mineField.size();i++){
			for(int j=0;j<mineField[0].size();j++)
				cout<<mineField[i][j]<<" ";
			cout<<endl;
		}
		minesweeper game(rows,columns,mines,mineField);
		game.displayGameBoard();
		game.setupGameBoard();
		game.revealLocation(firstInput.row,firstInput.column);
		cout<<endl<<endl;
		game.displayGameBoard();
		playTime(game);	
		 
	}  
		
  }
    return 0;
}


/* This method is used to populate the minefield by reading the input file.
 *  Ensure that the input file is according to the specified format.
*/
void loadGameFromFile(){

		
	int lineCount =0;
	string line;
	ifstream myfile("input.txt");					//input file located in the same directory
	if(!myfile)
	{
   		cout<<"File cannot be opened" << endl;
		return;
	}
	else
	{
		cout<<"file is opened "<<endl;
		while(getline(myfile,line)){
			int a =0;
			stringstream sp(line);
   			string t;
			if(lineCount<3){
    				while(getline(sp,t,' '))
    				{
					if(a==1){
					if(lineCount==0)
					rows = atoi(t.c_str());
					else if(lineCount==1)
					columns = atoi(t.c_str());
					else if(lineCount==2)
					mines = atoi(t.c_str());
					}	
					a++;	
				}
				a=0;
			}
			else{
				vector<int> rowVector;		
				while(getline(sp,t,' ')){
					int temp= atoi(t.c_str());
					rowVector.push_back(temp);
				}
				mineField.push_back(rowVector);

			}
			lineCount++;
			
		}

		cout<<rows<<" "<<columns<<" "<<mines<<endl;
		for(int i=0; i<mineField.size();i++){
			for(int j=0;j<mineField[0].size();j++)
				cout<<mineField[i][j]<<" ";
				cout<<endl;
		}
			
	}

}

/* method to check if the random number generated is a duplicate.
*  called from loadGameFromProgram(). 	 
*/

int find(vector<int>&unique,int rand){

        for(int i=0;i<mines;i++){
            if(unique[i]==rand)
                return -1;
        }
        return 0;
    }



/*
* This method is used to populate the minefield by randomly generated location values.
* This method will query the user for the first input and based on that input,
* it will populate the minefield such that the  first input is not a mine and the user does not lose the game on first turn.
* Returns the first input to be updated on the actual minesweeper object.
*/

input_t loadGameFromProgram(){

	cout<<"Please enter number of rows"<<endl;
	cin>>rows;
	cout<<"Please enter number of columns"<<endl;
	cin>>columns;
	cout<<"Please enter number of mines"<<endl;
	cin>>mines;
   
   	mineField.resize(rows);
	for(int i=0;i<rows;i++)
		mineField[i].resize(columns);

	int initial;//to be taken from user
    cout<<"enter the co-ordinates of first move"<<endl;
    int x,y;
    cin>>x>>y;
    cout<<x<<" "<<y<<endl;
    initial=(columns*x)+y;
    vector<int> unique;
	unique.resize(mines+1,-1);
    unique[mines]=initial;
    int incrementer=0;
	for(int i=0;i<mines;i++){
             	
		int rando=-1,temp=-2;
             
            
        do {
              rando = rand()%(rows*columns);
              temp=find(unique,rando);
        }while( temp==-1);
       	unique[incrementer]=rando;
        incrementer++;
        //cout<<rando<<endl;
        int row_random = rando / columns;
        int col_random = rando % columns;
        mineField[row_random][col_random] = 1;
    }

	input_t firstInput;                          //Populate the first input
	firstInput.operation = 'r'; 
	firstInput.row = x;
	firstInput.column = y;
	
	return firstInput;

}


/* This should be your game UI function. If a user decides to play a game of minesweeper,
* UI interaction with a minesweeper object should be done here. This method repeatedly 
* queries for user input and checks the game staus at each turn. If game is ongoing, user is queried for input
* and the function processInput is called.
* If the user hits a mine, the game is lost and the message along with all the mines is displayed on the console.
* If the user reveals all the locations without hitting a mine, the game is won and the message is displayed on the console.
*/
void playTime(minesweeper& play) {
//TODO - Begin the minesweeper game function; should interact with minesweeper class/object here
	cout<<" The game is Setup!! Let us Play "<<endl;
	while(play.endGame()==0){

		input_t input = getUserInput();
		cout<<" after user input " <<input.operation<<" "<<input.row<<" "<<input.column<<endl;
		processInput(play,input);
	}
	if(play.endGame()== -1){
		cout<<" you lose "<< endl;
		play.displayMines();
	}
	else if(play.endGame()==1){
			cout<<"====================================================================="<<endl;
			cout<<"||                     You Win!!!!!!!!!!!!!!!                      ||"<<endl;
			cout<<"====================================================================="<<endl;
			mineField.clear();
	}		

}



/* This method queries the user for location input. 
*  It validates the operation to be performed (mark, unmark, reveal) on a cell and the coordinates of the cell.
*  Returns a structure input_t that packs these values.
*/


input_t getUserInput(){
	
    input_t input_ret;
	char operation;
    int x,y;
   	cout<<"Select the row and column numbers to be MARKED,UNMARKED or REVEALED within the range"<<endl;
        
    do{
		cout<<"usage: 'm 5 4', 'u 5 4' or 'r 5 4'"<<endl; 
        cin>>operation;
		cin>>x;
        cin>>y;
    }while(!(operation=='m'||operation =='u'||operation =='r')||x>=rows || y>=columns || x<0 || y<0);
	
	input_ret.operation=operation;		    
    input_ret.row=x;
    input_ret.column=y;
    return input_ret;
    
}

/*
*This method performs the user actions on the minesweeper object.
* For example, the repeated printing of the board state
* and handling of user game action such as left/right click
* on a particular cell should be done here.
*/


void processInput(minesweeper& play, input_t input){


	if(input.operation=='u'){									// unmark a location
		cout<<"received u"<<endl;
		play.unmarkLocation(input.row,input.column);
		play.displayGameBoard();
		return;
	}
	
	if(input.operation=='m'){									// mark a location
		cout<<"received m"<<endl;
		play.markLocation(input.row,input.column);
		play.displayGameBoard();
		return;
	}
	else if(input.operation=='r'){								//reveal a location
		cout<<"received r"<<endl;

		play.revealLocation(input.row,input.column);
		play.displayGameBoard();
		return;
	}
		

}

