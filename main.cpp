#include <iostream>
#include <string>
#include <vector>
#include <random>

//game by GhostK inspired by Relax

using namespace std;

void newgame(int w, int h, int nmines = 10){
	vector<vector<bool>> mines(w, vector<bool>(h, false));
	for(int i = 0; i < nmines; i++){
		int irand = rand() % (h-2) + 1;
		int jrand = rand() % (w-2) + 1;
		while(mines[irand][jrand]){
			irand = rand() % (h-2) + 1;
			jrand = rand() % (w-2) + 1;
	
		} 
		mines[irand][jrand] = true;
	}
	vector<vector<int>> field(w, vector<int>(h, -1));
	for(int i=1; i<h-1; i++) for(int j=1; j<w-1; j++){
		int bcounter = 0;
		for(int x=-1; x<=1; x++) for(int y=-1; y<=1; y++){
			if (!(x==0 && y==0) && mines[i+x][j+y]) {
				bcounter += 1;
			}
		}
		if(bcounter != 0) field[i][j] = bcounter;
	}

	vector<vector<char>> visible (w-2,vector<char>(h-2,'?'));
	bool end = false, win = false;
	int score = 0;	
	while(!end){
		for(int i=0; i<visible.size(); i++){
			for(int j=0; j<visible[i].size(); j++){
				cout << visible[i][j] << " ";
			}
			cout << endl;
		}
		cout << "Make your move: m [x] [y] to dig or f [x] [y] to flag." << endl;

		char move; int x, y; cin >> move >> x >> y;
		bool isMine = mines[x+1][y+1];
		if(move == 'f'){
			if(visible[x][y]=='f'){
				visible[x][y]='?';
				if(isMine) score--;
			}
			else{
				visible[x][y]='F';
				if(isMine) score++;
			}
			if(score==nmines){win = true; end=true;}
		}
		else if (move == 'm'){
			if(isMine) {win=false; end=true;}
			else visible[x][y] = '0' + field[x+1][y+1];
		}
		else {}
	}

	//show the field
	//
	for(int i=1; i<h-1; i++){
	       for(int j=1; j<w-1; j++){
		       	if (!mines[i][j]){
		       		if (field[i][j] == -1) cout << "- ";
		       		else cout << field[i][j] << " ";
		       	}
			else cout << "X ";
	       }
	       cout << endl;
	}
	//
	
	if(win) cout << "YOU WIN!!!" << endl;
	else cout << "YOU LOOSE!!! BOOOOOO!" << endl;

}

int main(){
	newgame(4, 4, 3);
}

