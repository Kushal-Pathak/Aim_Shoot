#include <iostream>
#include <cmath>
#include <windows.h>
#define h 28
#define w 115
#define g 1
using namespace std;

char buffer[h][w];
int game_over = 0;


void display_scene();
void init_buffer();
void change_turn();

class player {
public:
	int x, y, id;
	void create(int x, int y, int id) {
		this->x = x; this->y = y; this->id = id;
		if (y < 2) y = 2;
		if (y > h - 1) y = h - 1;
		if (x < 0) x = 0;
		if (x > w - 3) x = w - 3;
		buffer[y - 2][x + 1] = 'O'; // head
		buffer[y - 1][x] = '/'; // left hand
		buffer[y - 1][x + 1] = 'I'; // chest
		buffer[y - 1][x + 2] = '\\'; // right hand
		buffer[y][x] = '/'; //left leg
		buffer[y][x + 2] = '\\'; //right leg
	}
	int hit(int x, int y) {
		if (y == this->y - 2 && x == this->x + 1) return 1;
		if (y == this->y - 1 && x == this->x) return 1;
		if (y == this->y - 1 && x == this->x + 1) return 1;
		if (y == this->y - 1 && x == this->x + 2) return 1;
		if (y == this->y && x == this->x) return 1;
		if (y == this->y && x == this->x + 2) return 1;
		return 0;
	}
};

class projectile {
public:
	float x = 0, y = 0, vx = 0, vy = 0, mag = 0, angle = 0, vy_cap;
	projectile(float a, float m, player player) {
		angle = (3.14159f * a) / 180.0f;
		mag = m;
		if (player.id == 1) {
			x = player.x + 2.0f; y = player.y - 1.0f;
			vx = cos(angle) * mag;
			vy = sin(angle) * mag;
			vy_cap = -vy;
		}
		else if (player.id == 2) {
			x = player.x + 0.0f; y = player.y - 1.0f;
			vx = -cos(angle) * mag;
			vy = sin(angle) * mag;
			vy_cap = -vy;
		}
		x++; y--;
	}
	void travel() {
		buffer[(int)y][(int)x] = '.';
		x += vx;
		y += vy;
		buffer[(int)y][(int)x] = '*';
		vy -= g;
	}
};

player turn;

int main() {
	init_buffer();
	player p1, p2;
	p1.create(0, h, 1);
	p2.create(w, h, 2);
	display_scene();
	turn = p1;
	while (1) {
		display_scene();
		cout << "Player-" << turn.id << "'s turn: ";
		float angle, mag;
		cin >> angle >> mag;
		projectile bullet(angle, mag, turn);
		while (bullet.y < h - 1) {
			bullet.travel();
			Sleep(50);
			display_scene();
		}
		cin.get();
	}
	cin.get();
	return 0;
}

void display_scene() {
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

void change_turn() {
	if (turn.id == 1) turn.id = 2;
	else turn.id = 1;
}