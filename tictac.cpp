#include <bits/stdc++.h>
using namespace std;
const int rows=3;
const int columns=3;
char vacant ='-';// this means vacant location
char player1='X';
char player2='O';

const int infinite=1000;//
// this functions moveisleft checks if there is any vacant location on board where a "X" or and "O" can be filled
 // board has 3 rows and 3 columns .We maintain a flag to check if there is "-"  on board as this symbol indictes vacant location
bool moveisleft(char board[3][3]){
	bool flag=false;
	for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				if(board[i][j]==vacant)
				flag=true;
			}
		}
	return flag;
	
}
//evalauation function 
// we give a score +10 if there  is "X" "X" "X" in same row or same coulmn or in any of the two diagonals 
int evaluationfunction(char board[3][3]){
	for(int i=0;i<rows;i++){
	if(board[i][0]==board[i][1] && board[i][1]==board[i][2]){
				// for each ith row we check (i,0) ,(i,1), (i,2) and if it turns out to be player 1 , we return a score+10 and if turns out to be player 2 we return -10
				if(board[i][0]==player1)
				return 10;
				else if(board[i][0]==player2)
				return -10;
			}
		}
		for(int i=0;i<columns;i++){
			// we check (0,i),(1,i) ,(2,i) for each i i.e we check every column in this part of code and  if it turns out to be player 1 , we return a score+10 and if turns out to be player 2 we return -10
			if(board[0][i]==board[1][i] && board[1][i]==board[2][i]){
				if(board[0][i]==player1)
				return +10;
				else if(board[0][i]==player2)
				return -10;
			}
			
		}
		// now we check daigonals so we just need to check (0,0) (1,1) (2,2) and same way for the other diagonal ((0,2),(1,1) ,(2,0) )
		
		if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){// diagonal from  (0,0)->(2,2)
			if(board[0][0]==player1)
			return 10;
			else if(board[0][0]==player2)
			return -10;
		}
		
		if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){// daigonal from (2,2)->(0,0)
			if(board[0][2]==player1)
			return +10;
			 else if(board[0][2]==player2)
			return -10;
		}
		// in those states of board where neither of the two is in winning condition , we return 0
		return 0;
		
	}
	// this is our minmaxfunction . A recursive function .In  a simple recursive minmax where we go left or left and finally to the terminal node ,but in this we will check if the given current board passed to minmax already leads to some score or nor
	int minmax(char board[3][3],int depth ,bool flag){
		// flag is false means it is turn of player 2 else it is turn of player 1 and we switch flag to true or false
		// unlike normal recursion ,we don't look for terminal node instead for scores
		int value=evaluationfunction(board);
		if(value==10)
		return 10;
	    if (value==-10){
			return -10;
		}
	    if (moveisleft(board)==false){//no move left so we return 0
			return 0;
		}
	   if(flag==true){
			int maxii=-infinite;
			// this is move of player who places 'X' 
			// this is where we use recursion part of minmax
			for(int i=0;i<rows;i++){
				for(int j=0;j<columns;j++){
					if(board[i][j]==vacant){
						board[i][j]=player1;// we palced 'X'
						maxii=max(maxii,minmax(board,depth+1,!flag));
						board[i][j]=vacant;
					}
				}
			}
			return maxii;
			
		}
		else{
			int mini=+infinite;
			for(int i=0;i<rows;i++){
				for(int j=0;j<columns;j++){
					if(board[i][j]==vacant){
						board[i][j]=player2;// placed 'o'
						mini=min(mini,minmax(board,depth+1,!flag));
						board[i][j]=vacant;
					}
				}
			}
			return mini;
		}
	}
		

// Once , we have the board , we pass the board onto the bestrowandcolumnsfinder .this function will tell us the best row and column where the next move should be provided that row and column is vacant 
vector <int> bestrowandcolumnfinder(char board[3][3]){
	vector <int> v;
	v.clear();
	int bestrow=-1;
	int bestcolumn=-1;
	// now inorder to find the best row and cloumn where the next move should be , we try every possible vacant location on board and calcualte value for each such position using minmax function
	int maxii=-infinite;// worst case
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			if(board[i][j]==vacant){
				// place the player 1 i.e X on the board
				board[i][j]=player1;
				// once you placed player on the board , calaculate the value for this position using minmax function
				// while passing baord , we also pass false .think why ?
				int cur_value=minmax(board,0,false);
				board[i][j]=vacant;
				// if current value is greater than max value you have till now , update max value and also update the best row and best column 
		         if(cur_value>maxii){
		         	maxii=cur_value;
				bestrow=i;
				bestcolumn=j;// updated the best row and best column 
				// once you calculated the
				
			}
		}
	}
	
}
//cout<<"bestrow and bestcolumn are "<<bestrow <<" "<<bestcolumn<<endl;
v.push_back(bestrow);
v.push_back(bestcolumn);
return v;
}
void printit(char board[3][3]){
	for(int i=0;i<rows;i++){
	  	for(int j=0;j<columns;j++){
	  		if(j!=2)
	  		cout<<board[i][j]<<" | ";
	  		else
	  		cout<<board[i][j]<<endl;
		  }
	  }
}

void clear()
{
   system("cls");
}
bool isboardempty(char board[3][3]){
	
	bool flag=false;
	for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				if(board[i][j]==vacant)
				flag=true;
			}
		}
	return flag;
}
int main(){
	pair<int,int> p[9];
	int k=1;
	for(int i=1;i<=3;i++)
	{
	  for(int j=1;j<=3;j++)
	  {
	  	p[k].first = i-1;
	  	p[k].second  =j-1;
	  	k++;
	  }
	}
	cout<<"TIC TAC GAME "<<endl;
	cout<<"BAORD DISPALY "<<endl;
      char board[3][3]={{'-','-','-'},
	                   {'-','-','-'},
	                   {'-','-','-'}};
   /*vector <int> v=bestrowandcolumnfinder(board);
	 int x=v[0];int y=v[1];  
	 cout<<"x "<<x<<" and y are"<<y<<endl; */
	 
	          
	     bool flag=false;              
	   while(isboardempty(board)==true && flag==false){
	  int score=evaluationfunction(board) ;
	  cout<<"score is "<<score<<endl;
	  if(score==10){
	  	cout<<"computer wins"<<endl;
	  	flag=true;
	  	break;
	  	
	  }
	 if(score!=10 && isboardempty(board)==false){
	 	cout<<"draw"<<endl;
	 	flag=true;
	  	break;
	 }          
	  cout<<"Enter 1 or 2 or 3 or 4 or 5 or 6 or 7 or 8 or 9  "<<endl;
	  
	  int num;cin>>num;
	  bool entered=false;
	  while(entered==false){
	  	
	  if(num>=1 && num<=9){
	  	int x=p[num].first;
	  	int y=p[num].second;
	  	
	  	if(board[x][y]!=player1){
	  	board[x][y]=player2;
	  	entered=true;
		  }
	  	else{
	  	cout<<"Invalid Move! Dude"<<endl;
	  	cin>>num;
	  }
	  }
}
	  int val1=evaluationfunction(board);
	  printit(board);
	  if(isboardempty(board)==false && val1!=10){
	  	cout<<"match draw"<<endl;
	  	flag=true;
	  	break;
	  }
	   //printit(board);
	  vector <int> v=bestrowandcolumnfinder(board);
	 int x=v[0];int y=v[1];
	   board[x][y]=player1;
	   cout<<"x "<<x<<" and y are"<<y<<endl;
	   cout<<endl;
	 printit(board);
}
}
