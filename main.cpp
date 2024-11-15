#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>

//game by GhostK inspired by Relax
//TODO: figure out the bug when game crashes on delta(x, y) ~>2
//TODO: make it crash resistent when you enter wrong move command
//TODO: fix pseudo random
//TODO: add autofilling empty cells when selected

using namespace std;

int numlen(int n){
	int r=1;
	while(n >= 10) {r++; n/=10;}
	return r;
}

void newgame(int w, int h, int nmines = 10){
	int wlen = 1, hlen = 1;
	int wp = w-1, hp = h-1;
	while(wp >= 10) {wlen++; wp/=10;}
	while(hp >= 10) {hlen++; hp/=10;}
	int maxwhlen = wlen; if (maxwhlen < hlen) maxwhlen = hlen;
	w += 2; h += 2;
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

	bool end = false, win = false;
	vector<vector<char>> visible (w-2,vector<char>(h-2,'?'));
	int score = 0;	
	int falseMined = false;	//true if at lesat one flag is not on the mine
	//game cycle
	while(!end){
		system("cls");
		cout << endl << endl;

		//x coords hint
		cout << ' ';
		for(int i=0;i<maxwhlen;i++) cout << " ";
		for(int j=0; j<visible[0].size(); j++){
			cout << j;
			for(int k=numlen(j)-1;k<maxwhlen;k++) cout << ' ';
		}
		cout << endl;

		//y coords hint
		for(int i=0; i<visible.size(); i++){
			cout << i; 
			for(int k=numlen(i)-1;k<maxwhlen;k++) cout << ' ';
			for(int j=0; j<visible[i].size(); j++){
				cout << visible[i][j];
				for(int i=0;i<maxwhlen;i++) cout << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << "Current score: " << score << endl;
		cout << "Make your move: m [x] [y] to dig or f [x] [y] to flag." << endl;

		char move; int x, y; cin >> move >> y >> x;
		bool isMine = mines[x+1][y+1];
		if(move == 'f'){
			if(visible[x][y]=='f'){
				visible[x][y]='?';
				score--;
				if(!isMine) falseMined = false;
				//old
				//if(isMine) score--;
			}
			else{
				visible[x][y]='F';
				score++;
				if(!isMine) falseMined = true;
				//old
				//if(isMine) score++;
			}
			if(score==nmines && !falseMined){win = true; end=true;}
		}
		else if (move == 'm'){
			if(isMine) {win=false; end=true;}
			else visible[x][y] = '0' + field[x+1][y+1];
		}
		else {}
	}

	cout << endl << endl;

	//show the field
	//
	for(int i=1; i<h-1; i++){
	       	for(int j=1; j<w-1; j++){
		       	if (!mines[i][j]){
		       		if (field[i][j] == -1) cout << "-";
		       		else cout << field[i][j];
			}
			else cout << "X";
			for(int i=0;i<maxwhlen;i++) cout << " ";
		}
	       cout << endl;
	}
	//
	
	if(win) cout << "YOU WIN!!!" << endl;
	else cout << "YOU LOOSE..." << endl;

}

int main(){
	cout << "MINESWEPPER v0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.2" << endl;
	cout << "github link: https://github.com/sun1zu/mineswepper" << endl;
	cout << endl << endl;
	int w, h, n;
	char cont = 'y';
	while(cont != 'n'){
		cout << "Input game parameters: width, height, number of mines" << endl;
		cin >> w >> h >> n;
		newgame(w, h, n);
		cont = '?';
		while(cont != 'y' && cont != 'n'){
			cout << endl << endl << "Play again? y/n: ";
			cin >> cont;
			system("cls");
		}
	}
}
