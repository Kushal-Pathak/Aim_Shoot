#include <iostream>
#include <cmath>
#include <windows.h>
#include <ctime>
#define h 28
#define w 115
#define g 0.2f
using namespace std;

char buffer[h][w];
int game_over = 0;

void display_scene();
void init_buffer();


class player {
public:
	int x = 0, y = 0, id = 0;
	player(int x, int y, int id) {
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
	void draw(int x, int y) {
		this->x = x; this->y = y;
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
	player() {

	}
	int hit(float bx, float by) {
		if (bx >= x - 1 && bx <= x + 3 && by >= y - 3 && by <= y) return 1;
		if (by == y - 3 && (bx == x || bx == x + 1 || bx == x + 2)) return 1;
		return 0;
	}
};

class projectile {
public:
	float x = 0, y = 0, vx = 0, vy = 0, gg=0.2f;
	void set(float vel_x, float vel_y, player player) {
		if (player.id == 1) {
			x = player.x + 2.0f + 1.0f; y = player.y - 1.0f - 2.0f;
			vx = vel_x; vy = -vel_y;
			vy = vy / vx;
			gg = g / vx;
			vx = 3;
		}
		
		if (player.id == 2) {
			x = player.x - 3.0f; y = player.y - 1.0f - 2.0f;
			vx = vel_x; vy = -vel_y;
			vy = vy / vx;
			gg = g / vx;
			vx = -3;
		}
	}
	int in_air() {
		if (y < h - 1) return 1;
		return 0;
	}
	void travel() {
		int xx = (int)round(x), yy = (int)round(y);
		if (xx >= 0 && xx < w && yy >= 0 && yy < h) {
			buffer[yy][xx] = '.';
		}
		x += vx;
		y += vy;
		xx = (int)round(x), yy = (int)round(y);
		if (xx >= 0 && xx < w && yy >= 0 && yy < h) {
			buffer[yy][xx] = '*';
		}
		vy += gg;
	}
};

player turn, opponent;
void change_turn(player, player);

int main() {
	srand(time(0));
	char play = 'y';
	while (play=='y') {
		int r1, r2, t;
		r1 = rand() % (w / 2);
		game_over = 0;
		init_buffer();
		r2 = (w/2) + rand() % (w / 2);
		player p1(r1, h, 1), p2(r2, h, 2);
		projectile bullet;
		t = rand() % 3;
		if (t == 0) {
			turn = p1; opponent = p2;
		}
		else if (t == 1) {
			turn = p2; opponent = p1;
		}
		//game loop
		while (!game_over) {
			display_scene();
			cout << "Player-" << turn.id << "'s turn: ";
			float vx, vy;
			cin >> vx >> vy;
			bullet.set(vx, vy, turn);
			int result = 0;
			while (bullet.in_air() && !result) {
				bullet.travel();
				display_scene();
				Sleep(100);
				result = opponent.hit(bullet.x, bullet.y);
				if (result) {
					bullet.travel();
					game_over = 1;
					display_scene();
					cout << "Player-" << turn.id << " wins!" << endl;
				}
			}
			change_turn(p1, p2);
			init_buffer();
			p1.draw(r1, h);
			p2.draw(r2, h);
		}
		play = 'n';
		cout << "Play again (y/n): ";
		cin >> play;
	}
	return 0;
}

void display_scene() {
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) cout << buffer[i][j];
		cout << endl;
	}
}

void init_buffer() {
	for (int i = 0; i < h; i++) 
		for (int j = 0; j < w; j++) buffer[i][j] = ' ';
}

void change_turn(player p1, player p2) {
	if (turn.id == 1) turn = p2;
	else turn = p1;
	if (opponent.id == 1) opponent = p2;
	else opponent = p1;
}