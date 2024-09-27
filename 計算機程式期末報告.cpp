#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  
#include <ctime> 
using namespace std ;

#define big 7 
#define mid 2 
#define small 8 
#define col 2 

int flag=1,total=0;		
		
void gotoxy(int x, int y){ 
	x++, y++ ; 
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
 
void color(int b){
    HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE)) ;
    SetConsoleTextAttribute(hConsole, b) ;
}

void Boundary(){
	char i ;
	gotoxy(3,1);
	color(big);
	cout << "+---+---+---+---+---+---+---+---+---+" ;
	color(small);
	for(int i=1;i<10;++i){
		color(small);  
		gotoxy(3,i*2+1);
		if(i==3 || i==6){
			color(mid);   
		}
		cout << "+---+---+---+---+---+---+---+---+---+" ; 
		for(int j=0;j<10;++j){
			gotoxy(3+j*4,i*2);
			if(j==3 || j==6){
				color(mid);  
			}
			if(j==0 || j==9){
				color(big);  
			}
			cout << "|   " ;
			color(7);
			gotoxy(3+j*4,i*2+1);
			if(i%3!=0 || j%3!=0){
				color(small);  
			}
			if(j==0 || j==9){
				color(big);  
			}
			if((i%3==0 || j%3==0) && j!=0 && j!=9){
				color(mid);  
			}
			cout << "+" ;
			color(small);
		}
	}
	color(big);   
	gotoxy(3,19);
	cout << "+---+---+---+---+---+---+---+---+---+" ;
	color(15);   
	gotoxy(60,1);
	cout << "數獨小遊戲" ;
	gotoxy(45,3);
	cout << "組員 : 歐芹年 & 吳佳軒 & 林怡欣 & 林睿麟" ; 
	gotoxy(45,7);
	cout << "操作中輸入'678',表示對6行7列標記為8;輸入'999'表示放棄遊戲" ;
	for(int i=0; i<9; i++) {
		
		gotoxy(4*i+5,0) ;
		cout << i ;
		gotoxy(4*i+5,20) ;
		cout << i ; 
		gotoxy(1,2*i+2) ;
		cout << i ;
		gotoxy(41,2*i+2) ;
		cout << i ;
	} 
}  

bool Flag(int m,int n,int b,int board[9][9]) {
	int a[9] ;
	for(int i=0; i<9; i++) {
		if(board[i][m]==b){
			return false;
		}
		if(board[n][i]==b){
			return false;
		}
	}
	for(int i=0; i<9; i++) {
		a[i]=0 ;
	}
	a[0]=b ;
	gotoxy(50,15) ;
	int q=(n/3)*3, p=(m/3)*3, r=1 ;
	for(int i=p; i<p+3; i++) {
		for(int j=q; j<q+3; j++) {
			if(board[j][i]>0 && board[j][i]<10) {
				a[r]=board[j][i] ;
				r++ ;
			}
		}
	} 
	for(int i=0; i<9; i++){
		for(int j=i+1; j<9; j++) {
			if(a[i]==a[j] && i!=j && a[i]!=0) {
				return false ;
			}
		}
	}
	return true ;
}  

void Sudoku(int board[9][9]) {
	time_t seed ;
	srand(time(&seed)) ;
	int number=15, p=0, q=0, i=0 ;
	while(i<number) {
		int m=rand()%9, n=rand()%9, b=rand()%9+1;
		if(Flag(n,m,b,board)==true) {
			board[m][n]=b;
			p=m, q=n ;
			i++ ; 
		}
	}
	board[p][q]=0 ;
} 

int bfs(int x,int y,int num,int board[9][9]) {
	int m,n,time=0 ;
	int dir[9][2]={{1,1}, {1,0}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1}, {0,0}} ;
	for(int i=0; i<9; i++) {
		m=x+dir[i][0], n=y+dir[i][1] ;
		if(num==board[n][m]) {
			time++  ;
		}
		if(time>1) {
			return 0 ;
		}
	}
	return 1 ;
}

int Judge(int x,int y,int n,int board[9][9]) {
	int t=0 ;
	for(int i=0; i<9; i++) {
		if(board[y][i]==n) {
			t++ ;
			if(t>1){
				return 1;
			}
		}
	}
	t=0 ;
	for(int i=0; i<9; i++) {
		if(board[i][x]==n) {
			t++;
			if(t>1) {
				return 1 ;
			}
		}
	}
	int nu, m ;
	if(bfs(1+(x/3)*3, 1+(y/3)*3, n, board)==0) {
		return 1 ;
	}
}

void Show(int input,int board[9][9], int sudoku[9][9][2]) {
	time_t seed ;
	srand(time(&seed)) ;
	int i=0 ;
	color(col) ;
	for(int i=0; i<9; i++) {
		
		for(int j=0; j<9; j++) {
			
			gotoxy(5+j*4,i*2+2) ;
			cout << "" ;
			board[i][j]=0 ; 
		}
	}
	while(i<input) {
		int m=rand()%9, n=rand()%9 ;
		if(sudoku[m][n][1]==0) {
			gotoxy(5+n*4,m*2+2) ;
			cout << sudoku[m][n][0] ;
			sudoku[m][n][1]=1;
			board[m][n]=sudoku[m][n][0];
			i++ ;
		}
	}
} 

void Sel(int x,int y,int kind,int board[9][9],int sudoku[9][9][2],int &total) {
	if(flag==0 && kind==0){
		return ;
	}
	if(y<9) {
		if(x<9) {
			if(board[y][x]<1 || board[y][x]>9) {
				for(int i=1;i<=9;i++){
					board[y][x]=i ;
					int k=Judge(x,y,i,board) ;
					if(k==0){
						Sel(x+1,y,kind,board,sudoku,total) ;
					}
					board[y][x]=0 ;
				}
			}else {
				Sel(x+1,y,kind,board,sudoku,total) ;
			}
		}else {
			Sel(0,y+1,kind,board,sudoku,total) ;
		}
	}
	else {
		total++;
		flag=0;
		if(kind==0) {
			for(int i=0; i<9; i++) {
				for(int j=0; j<9; j++) {
					sudoku[i][j][0]=board[i][j] ;
				}
			}
		}
	}
} 
int main() {
	int board[9][9], sudoku[9][9][2] ;
	
	int leve,op,input=0 ;  
		
	
	while(input == 0) {
		for(int i=0; i<9; i++) {
			for(int j=0; j<9; j++) {
				board[i][j] ;
				sudoku[i][j][1]=0 ;
			}
		}
		Boundary() ;
		gotoxy(45,17);
		color(15) ;
		cout << "選擇難易度 : 初級請輸入1  中級請輸入2  高級請輸入3  "  ; 
		cin >> input ;
		switch(input) {
			case 1 :
				input = 55 ;
				break;
			case 2 :
				input = 45 ;	
				break;			
			case 3 :
				input = 40 ;
				break;
			default :
				gotoxy(45,19);
				cout << "請重新輸入" ;
				break ;	
	} 	
		total=0, flag=1 ;
		while(total==0) {
			Sudoku(board) ;
			Sel(0,0,0,board,sudoku,total) ;
			gotoxy(50,22) ;
		} 
		
		Show(input,board,sudoku) ;
		
		Sel(0,0,1,board,sudoku,total) ; 
		gotoxy(45,5) ;
		color(15) ;
		cout << "解法 : " << total-1 <<"種" ;
		gotoxy(54,9);
		int key=1 ;
		while(key==1) {
			int h=0; 
			gotoxy(45,9);
			color(15) ;
			cout << "操作 輸入3位數:" ;
			cin >> op ;  
					
			gotoxy(5+(op/100%10)*4,(op/10%10)*2+2) ;
			
			if(sudoku[op/10%10][op/100%10][1]==0 && op%10!=0 && op<999 && op/10%10!=9 && op/100%10!=9) {
				
				board[op/10%10][op/100%10]=0 ;
				if(Flag(op/100%10,op/10%10,op%10,board)==true) {
					
					board[op/10%10][op/100%10]=op%10 ;
					gotoxy(5+(op/100%10)*4,(op/10%10)*2+2) ;
					cout << op%10  ;  
					for(int i=0; i<9; i++) {
						
						for(int j=0; j<9; j++) {
							
							if(board[i][j]!=0) {
								h++; 
								
							}
						}
					}
					if(h==81) {
						key=0 ;
						color(14);
						gotoxy(45,11) ;
						cout << "你贏了！" ;
					}
				}
				else{
					color(12);
					gotoxy(45,11);
					cout << "輸入錯誤！" ;
					Sleep(500); 
					gotoxy(45,11);
					cout << "          " ;
				} 
			}  
			else{
				if(op<999){
					color(12);
					gotoxy(45,11);
					cout << "操作非法！" ;
					Sleep(500);
					gotoxy(45,11);
					cout << "          " ;
				}
			}
			if(op==999) { 
				key=0;
				gotoxy(45,9);
				color(12);
				cout << "你輸了！現在顯示其中一種解法！" ;
				for(int i=0; i<9; i++){
					for(int j=0; j<9; j++){
						if(sudoku[i][j][1]==0) {
							Sleep(100) ;
							gotoxy(5+j*4,i*2+2) ;
							cout << sudoku[i][j][0]  ; 
						}
						board[i][j]=0;
						sudoku[i][j][0]=0;
						sudoku[i][j][1]=0;  
					}
				} 
			} 
		
		}
		gotoxy(45,9);
		color(12);
		cout << "                              " ;
		color(15);
		gotoxy(45,13);
		cout << "遊戲結束，按1退出遊戲 ：" ; 
		cin >> input ;
		gotoxy(82,13);
		cout << " " ;
		gotoxy(109,17);
		cout << "  " ;
		color(14);
		gotoxy(45,11) ;
		cout << "        " ; 
	} 
	gotoxy(0,20);
	return 0; 
}
