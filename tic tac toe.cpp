#include<iostream>
#include<fstream>
using namespace std;
char board[3][3];
int moves=0;
inline void board_initialization(){
	moves=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
		board[i][j]=' ';
	}
	}
}
void print_board(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
		 cout<<" "<<*(*(board+i)+j); 
			if(j<2){
			cout<<" | ";
		}
		}
		cout<<endl;
		if(i<2){
		cout<<" ----------"<<endl;
		}
	}
}
inline void player_move(int row,int col,char player){
	board[row][col]=player;
    print_board();
	moves++;
}
bool check_winner(char player){
	for(int i=0;i<3;i++){
		if(board[i][0]==player && board[i][1]==player && board[i][2]==player){
		return true;
	}
	}
	for(int j=0;j<3;j++){
	 if(board[0][j]==player && board[1][j]==player && board[2][j]==player){
	    return true;
	}
	}
	if(board[0][0]==player && board[1][1]==player && board[2][2]==player){
		return true;
	}
	else if(board[0][2]==player && board[1][1]==player && board[2][0]==player){
		return true;
	}
	return false;
}
void store_result(char winner){
	int winX=0,winO=0,draws=0;
	ifstream file("Result.txt");
	if(file){
		file>>winX>>winO>>draws;
		file.close();
	}
	if(winner=='X'){
		winX++;
	}
	else if(winner=='O') {
		winO++;
	}
	else{
		draws++;
	}
	ofstream infile("Result.txt");
	infile<<winX<<"  "<<winO<<" "<<draws;
	infile.close();
}
void show_stats(){
    int winX=0, winO=0, draws=0;
    ifstream read("Result.txt");
    if(read){
        read>>winX>>winO>>draws;
        read.close();
    }
   cout<<" PlayerX total wins: "<<winX<<endl;
   cout<<" PlayerO total wins: "<<winO<<endl;
   cout<<" Total Draws: "<<draws<<endl;
   cout<<endl;
}
int main(){
	
	int row,col;
	string choice;
	char currentplayer='X';
	cout<<" TIC TAC TOE"<<endl;
	cout<<" Player 1(X) and Player 2(O)"<<endl;
	do{
	board_initialization();
	print_board();
	
    while(moves<9){
    	
	cout<<" Use (0-2) for placing "<<endl;
	retry:
	cout<<" player "<<currentplayer	<<" Turn:"<<" ";
	cin>>row>>col;
	cout<<endl;
	
    if(board[row][col]==' '){
        player_move(row,col,currentplayer);
	}
	else{
		cout<<"Try again, invalid position"<<endl;
		goto retry;
	}
	if(check_winner(currentplayer)){
		cout<<endl;
		cout<<" Player "<<currentplayer<<" wins."<<endl;
		store_result(currentplayer);
		show_stats();
		break;
	}
	else if(moves==9){
		cout<<endl;
		cout<<" Game draw "<<endl;
		store_result('D');
		show_stats();
		break;
	}
	else{
		if(currentplayer=='X'){
    	 currentplayer='O';
	}
	     else{
		currentplayer='X';
	}
  }  
}
	cout<<"Do you want to play more.";
	cin>>choice;
	cout<<endl;
    }while(choice=="Yes"||choice=="yes");
    cout<<"Thank you for playing.";
    return 0;
}
