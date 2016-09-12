#include "minesweeper.h"

using namespace std;


/* default constructor, initializes the mineField to a 9x9 size with 10 mines
*/
minesweeper::minesweeper() {
	// TODO - default two dimension array is 9 X 9 with 10 mines
	colNum = 9;
	rowNum = 9;
	end = 0;
  	minesNum = 10;
	this->mineField.resize(rowNum);
	for(int i=0;i<rowNum;i++)
	this->mineField[i].resize(colNum);
}

minesweeper::minesweeper(int row, int col, int numOfMines, vector<vector<int> >&mineField) {
	// TODO Auto-generated constructor stub
	// TODO - two dimension gameboard size col x num with numOfMines mines
	colNum = col;
	rowNum = row;
	end=0;	
	//cout<<"inside constructor "<<colNum<<" "<<rowNum<<endl;
	minesNum = numOfMines;
	revealCount = 0;
	this->mineField.resize(rowNum);
	for(int i=0;i<rowNum;i++)
	this->mineField[i].resize(colNum);
	for(int m=0; m<rowNum;m++){
		for(int n=0;n<colNum;n++){
			//cout<<"inside for loop "<<endl;
			if(mineField[m][n]==1){
				//cout<<" this is a mine "<<endl;
				this->mineField[m][n].isMine = true;
			}
			else
				this->mineField[m][n].isMine = false;
			this->mineField[m][n].state = 0;
			this->mineField[m][n].value = 0;
		}
	}

}

minesweeper::~minesweeper() {
	// TODO Auto-generated destructor stub
}

/**
 * Returns int representing number of rows of current playing field.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getRowNum()
{

}

/**
 * Returns int representing number of columns of current playing field.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getColNum()
{

}
/**
 * Returns int representing number of mines on current playing field.
 * Includes both hidden and revealed mines.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getMinesNum()
{

}



/*
 * Generates numbers for surrounding tiles of mines. The only
 * tiles with numbers are those surrounding mines; these tiles are
 * updated as mines are generated.

 *
 * @param   row Row number of generated mine
 * @param   col Column number of generated mine
 * */
void minesweeper::calculateSurrounding(int row, int col) {
	//TODO - should update surrounding tiles to reflect
	//presence of adjacent mine
	if(mineField[row][col].isMine==true){

			incrementCellValue(row-1,col-1);
			incrementCellValue(row-1,col);
            incrementCellValue(row-1,col+1);
            incrementCellValue(row,col+1);
            incrementCellValue(row+1,col+1);
            incrementCellValue(row+1,col);
            incrementCellValue(row+1,col-1);
            incrementCellValue(row,col-1);

	}
}

/* increments the cell value(number of mines surrounding it) if the input location is valid
*
*/
void minesweeper::incrementCellValue(int row, int col){

	if(row<0||row>=rowNum||col<0||col>=colNum)
		return;

	else if(mineField[row][col].isMine==true)
		return;
	else
		mineField[row][col].value++;

}


/*This method sets up the game Board by calculating the number of neighbouring mines for each cell. 
*/

void minesweeper::setupGameBoard(){
	
	for(int i=0;i<rowNum;i++){
		for(int j=0;j<colNum;j++){
			calculateSurrounding(i,j);
		}
	}

}
/**
 * Updates mineField with user selection of revealed location.
 * Reveals current location and immediately checks mineField
 * for mine. 
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         unmask();
 * */
void minesweeper::revealLocation(int x, int y) {
	//TODO - update the bitField to reflect the user's
	//tile selection. Should rely on unmask to do actual
	//reveal operation.
	if(x>=rowNum||x<0||y>=colNum||y<0)
		return;
	if(mineField[x][y].state == 0){
		if(mineField[x][y].isMine == true){
			end = -1;
			return;			
		}
		else if(mineField[x][y].value == 0){
			unmask(x,y);
			return;
		} 
		else if(mineField[x][y].value>0){
			mineField[x][y].state=1;
			revealCount++;
			return;
		}
	}
}

/**
 * Allow the user to mark a cell as a potential mine. Marking an already
 * marked cell will result in no operation.
 * @param x column number of the cell selected
 * @param y row number of the cell selected
 */
void minesweeper::markLocation(int x, int y) {
    // TODO - update the display for the selected cell, change it
    // to marked if it's not marked, or to unmarked if it's already marked
    if (mineField[x][y].state == 0 )
		mineField[x][y].state = 2;
    return;	   
}

/**
 * Allow the user to unmark a cell that is already marked. Unmarking an already
 * unmarked cell will result in no operation.
 * @param x column number of the cell selected
 * @param y row number of the cell selected
 */
void minesweeper::unmarkLocation(int x,int y){
	if (mineField[x][y].state == 2)
		mineField[x][y].state = 0;
    return;	   
}

/**
 * Checks end game status (int end). End -1 is loss condition.
 * Also checks onlyMines() for a win condition. onlyMines will
 * update the end game status and endGame should return this value.
 *
 * @return      end game status (-1 loss, 0 ongoing, 1 win)
 * @see         onlyMines();
 * @see		revealLocation();
 * */
int minesweeper::endGame() {
	//TODO - return current end game status.
	//Calling this method should only update int end with
	//win or ongoing condition. revealLocation should
	//update if there is loss condition.
	cout<<" revealCount "<<revealCount<<endl;
	if(revealCount == (rowNum*colNum - minesNum) )
		end = 1;

	return end;
}


/**
 * Checks if the value of selected tile. isRevealed
 * should be called before this for correct gameplay. 
 * 
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         isRevealed();
 * */
int minesweeper::valueOf(int x, int y) {
	//TODO - returns the value of specific tile.
	//should only be called if tile isRevealed.
	return mineField[x][y].value;
}

/**
 * Reveals surrounding tiles. Should only be called if
 * user selected tile was not mine or had no surrounding
 * mines. Will recursively call itself to reveal all
 * adjacent blank tiles.
 *
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         revealLocation();
 * */
void minesweeper::unmask(int row,int col) {
	//TODO - reveal the tile here.
	//This method should reveal surrounding tiles
	//if the tile revealed had a value of 0
	if(row>=rowNum||row<0||col>=colNum||col<0)
		return;
	if(mineField[row][col].isMine == true)
		return;
	else if(mineField[row][col].value==0&&mineField[row][col].state==0){
		
		revealCount++;
		mineField[row][col].state = 1;
	    unmask(row-1,col-1);
        unmask(row-1,col);
		unmask(row-1,col+1);
		unmask(row,col+1);
		unmask(row+1,col+1);
		unmask(row+1,col);
		unmask(row+1,col-1);
		unmask(row,col-1);
		return;
	}
	else if(mineField[row][col].value>0 && mineField[row][col].state==0){
		mineField[row][col].state = 1;
		revealCount++;
		return;
	}
}


/* This method is called at each turn of the user input. This method dispalys the actual status of the game.
*  It queries the status of each cell if it has to marked, unmarked or revealed and displays the result accordingly
*  '#' indicates the cell is hidden, '!' indicates the cell is marked, and a number indicates the cell is 
* revealed and has so many mines in the neighbourhood.
*/

void minesweeper::displayGameBoard(){
	system("clear");
	cout<<endl<<endl;
	cout<<"\t";
	for(int i=0;i<colNum;i++)
	   cout<<i<<"\t";
	cout<<endl<<"=================================================================================="<<endl;
	cout<<"   |"<<endl;	
	for(int i=0;i<rowNum;i++){
		cout<<" "<<i<<" |";
		for(int j=0;j<colNum;j++){
			if(mineField[i][j].state == 0){                     //if the cell is hidden
				cout<<"\t#";
			}
			else if(mineField[i][j].state == 1){			    //if the cell is revealed
				cout<<"\t"<<mineField[i][j].value;
			}
			else{
				cout<<"\t!";				   					//if the cell is marked as mine
			}

		}
		cout<<"\t|"<<endl<<"   |"<<endl;;
	}
	cout<<endl<<"=================================================================================="<<endl;

}

/* This method is called at the end of the game play when the game is lost. This method displays all the mines to the user.
*
*/


void minesweeper::displayMines(){
	system("clear");
	cout<<"=========================================================================================="<<endl;
	cout<<"=========================================================================================="<<endl;
	cout<<"||                              		Game Over                      						||"<<endl;
	cout<<"=========================================================================================="<<endl;
	cout<<"=========================================================================================="<<endl;
	cout<<endl<<endl<<endl;
	cout<<"\t";
	for(int i=0;i<colNum;i++)
	   cout<<i<<"\t";
	cout<<endl<<"=================================================================================="<<endl;
	cout<<"   |"<<endl;	
	for(int i=0;i<rowNum;i++){
		cout<<" "<<i<<" |";
		for(int j=0;j<colNum;j++){
			if(mineField[i][j].state == 1){                     //if the cell is hidden
				cout<<"\t"<<mineField[i][j].value;
			}
			else if(mineField[i][j].state == 0){			    //if the cell is revealed
				if(mineField[i][j].isMine == true)
					cout<<"\t*";
				else
					cout<<"\t#";
			}
			else{
				cout<<"\t!";				   					//if the cell is marked as mine
			}

		}
		cout<<"\t|"<<endl<<"   |"<<endl;;
	}
	cout<<endl<<"=================================================================================="<<endl;
	
}
