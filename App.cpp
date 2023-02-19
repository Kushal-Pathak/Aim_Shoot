#include <iostream>
#include <cmath>
#define h 28
#define w 115
#define gx 1
#define gy 1
using namespace std;

char buffer[h][w];
int turn = 1;

void display();
void init_buffer();
void create_player(int, int);
void change_turn();

class projectile {
public:
	char bullet = 'X';
	int id = 1;
	int x = 0;
	int y = 0;
	int vx = 0;
	int vy = 0;
	int ycap = 0;
	float angle, mag;
	void init_projectile(float angle, float mag) {
		angle = (3.14159f * angle) / 180.0f;
		vx = (int)round(mag * cos(angle));
		vy = (int)round(mag * sin(angle));
		ycap = -vy;
		if (id == 1) {
			x = 2;
			y = h - 1;
		}
		else {
			x = w - 3;
			y = h - 1;
		}
	}
	void travel() {
		if (vy > ycap) {
			buffer[y][x] = ' ';
			x += vx;
			y += vy;
			vx -= gx;
			vy -= gy;
			buffer[y][x] = bullet;
		}
	}
};

int main() {
	init_buffer();
	create_player(0, h);
	create_player(w,h);
	display();
	projectile p;
	while (1) {
		display();
		cout << "Player " << turn << "'s turn: ";
		cin >> p.angle >> p.mag;
	}
	cin.get();
	return 0;
}

void display() {
	system("cls");
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

void change_turn() {
	if (turn == 1) turn = 2;
	else turn = 1;
}