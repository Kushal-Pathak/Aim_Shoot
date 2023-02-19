#include <iostream>
#define h 28
#define w 115
using namespace std;

char buffer[h][w];

void display();
void init_buffer();
void create_player(int, int);

int main() {
	init_buffer();
	create_player(0, h);
	create_player(w,h);
	display();
	cin.get();
	return 0;
}

void display() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << buffer[i][j];
		}
		cout << endl;
	}
}

void init_buffer() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			buffer[i][j] = ' ';
		}
	}
	
}

void create_player(int x, int y) {
	if (y < 2) y = 2;
	if (y > h - 1) y = h - 1;
	if (x < 0) x = 0;
	if (x > w - 3) x = w - 3;
	buffer[y-2][x+1] = 'O'; // head
	buffer[y-1][x] = '/'; // left hand
	buffer[y-1][x+1] = 'I'; // chest
	buffer[y-1][x+2] = '\\'; // right hand
	buffer[y][x] = '/'; //left leg
	buffer[y][x+2] = '\\'; //right leg
}