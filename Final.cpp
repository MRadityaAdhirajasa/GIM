/* ----------------------------------  
UAP DDP 2021 - SNAKE GAME
       Kelompok 7-C
1. Kartika Sari (2117051039)
2. M. Raditya Adhirajasa (2157051004)
3. Salsabila Juandira (2117051012)
-------------------------------------*/


//library yang dipakai
#include <iostream> //karena akan memakai cout, cin, endl
#include <conio.h> //karena akan memakai fungsi kbhitt dan getch
#include <windows.h> //karena akan memakai fungsi "cls"
#include <ctime> //karena akan memakai fungsi srand(time(0))
using namespace std;

//deklarasi variabel global
bool gameOver;
bool fruitTail;
const int width = 25;
const int height = 15;
int x, y, fruitX, fruitY, score;
string choose;
int tailX[100], tailY[100];
int nTail;
string player = "*";

//deklarasi tombol
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

void header()
{
	cout<<"\t\t\t\t\t================================== \n";
	cout<<"\t\t\t\t\t            [Snake Game] \n";
	cout<<"\t\t\t\t\t================================== \n";
}

//fungsi game berakhir
void GameOver()
{
	cout<<"\t\t\t\t\t================================== \n";
	cout<<"\t\t\t\t\t            [Game Over] \n";
	cout<<"\t\t\t\t\t================================== \n";
}


//untuk membuat tampilan seperti loading di game
void timer(){
	int waktu;
	for (waktu = 0; waktu <= 5; waktu++){
		cout << "\n";
		cout << "\n";
		cout << "\t\t\t\t\t\tLoading.....";
		Sleep(50);
		system("cls");
		cout << "\n";
		cout << "\n";
		cout << "\t\t\t\t\t\tLoading....";
		Sleep(50);
		system("cls");
		cout << "\n";
		cout << "\n";
		cout << "\t\t\t\t\t\tLoading..";
		Sleep(50);
		system("cls");
	}
}

//fungsi permulaan game, kepala ular dan makanan nya akan berada di tengah
void Setup()
{
	gameOver = false;
	fruitTail = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	
	//buah akan muncul di random tempat
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	
	//penggunaan pustaka #include <ctime> yang tidak mengembalikan nilai
	srand(time(0));
}

//fungsi untuk menggambar bingkai dan ular
void Draw()
{
	system("cls"); 
	
	//bingkai vertikal atas
	for (int i = 0; i < width+2; i++)
		cout << "=";
	cout << endl;

	//bingkai horizontal kanan
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "=";
				
			//kepala ular
			if (i == y && j == x)
				
				cout << player;
			
			//makanan ular	
			else if (i == fruitY && j == fruitX)
				cout << "X";
			else
			{
				bool print = false;
				
				//ekor ular
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
				
			//bingkai horizontal kiri
			if (j == width - 1)
				cout << "=";
		}
		cout << endl;
	}

	//bingkai vertikal bawah
	for (int i = 0; i < width+2; i++)
		cout << "=";
	cout << endl;
	cout << "Score : " << score << endl;
}

//fungsi tombol
void Input()
{
	 if(_kbhit()){ //untuk menentukan apakah tombol sudah ditekan atau belum
        switch (_getch()){
        case 'a': if(dir != RIGHT){dir = LEFT;}
        	player = '<';
            break;
            
        case 'd': if(dir != LEFT){dir = RIGHT;}
        	player = '>';
            break;
            
        case 'w': if(dir != DOWN){dir = UP;}
        	player = '^';
            break;
            
        case 's': if(dir != UP){dir = DOWN;}
        	player = 'v';
            break;
        case 'x': gameOver = true; //tombol jika ingin berhenti ditengah permainan 
            break;
        }
    }
}

//fungsi penambahan badan ular
void Logic()
{
for (int i = nTail; i > 0; i--)
 {
  tailX[i] = tailX[i - 1];
  tailY[i] = tailY[i - 1];
 }
tailX[0] = x;
tailY[0] = y;

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
	//	gameOver = true;
	//"bila ingin ular berakhir ketika menyentuh bingkai"
	
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	//"ular berakhir ketika menyentuh badannya sendiri"

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	//score jika 1x makan adalah 10
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
		
	}
	
	
}

int main()
{

	timer();
	header();
	cout<< "\n\t\t\t\t\t[Y/y] Play Game";
	cout<< "\n\t\t\t\t\t[N/n] Quit Game";
	cout<< "\n\n\t\t\t\t\tChoose : "; cin >> choose;

	
	if(choose=="Y" || choose=="y"){
	
	timer();
	Setup();
	while (!gameOver)
	{
		Draw();
		//Sleep(100);
		Input();
		Logic();
		Sleep(100);
	}
	system("cls");
	

	GameOver();
	cout << "\n\t\t\t\t\t\t     Score = " << score << endl;
}

	else if(choose=="n"||choose=="N"){
	cout<<" ";
	}
	
	else{
		cout<<"\t\t\t\t\t================================== \n";
		cout<<"\t\t\t\t\t         Not detected\n";
	}

	return 0;
}
