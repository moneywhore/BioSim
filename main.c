#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
int running;
typedef struct {
	int num;
	int lv;
	int pos[2];
	int energy;
} Creature;

int sunlight;
Creature* living[19];
Creature* board[20][20];

Creature *createCreature(int id, int r, int r1, int r2, int e) {

	Creature *c = (Creature*)malloc(sizeof(Creature));
	c->num = id;
	c->lv = r;
	c->pos[0] = r1;
	c->pos[1] = r2;
	c->energy = e;
	return c;
}

void initLife() {
	sunlight = rand() % 101;
	int r;
	int r1;
	int r2;
	for (int i = 0; i < 20; i++) {
		for (int x = 0; x < 20; x++) {
			board[i][x] = createCreature(-1, 0, i, x, 0);
		}
	}

	for (int i = 0; i <= 6; i++) {
		r1 = rand() % 20;
		r2 = rand() % 20;
		living[i] = createCreature(i, 0, r1, r2, 20);
		board[r1][r2] = living[i];
	}

	for (int i = 7;i <= 11;i++) {
		r = rand() % 4;
		r1 = rand() % 20;
		r2 = rand() % 20;
		living[i] = createCreature(i, r, r1, r2, (1 / (r + 1)) * 20);
		board[r1][r2] = living[i];
	}
	return;
}

Creature *moveCreature(Creature *c) {
	int dir = rand() % 4;

	switch (dir) {
	case 0:
		if (c->pos[0] - 1 < 0) {
			break;
		}
		c->pos[0]--;
		break;
	case 1:
		if (c->pos[0] + 1 >= 19) {
			break;
		}
		c->pos[0]++;
		break;
	case 2:
		if (c->pos[1] - 1 < 0) {
			break;
		}
		c->pos[1]--;
		break;
	case 3:
		if (c->pos[1] + 1 >= 19) {
			break;
		}
		c->pos[1]++;
		break;
	}

	return c;
}

void processCreatures() {

	for (int i = 0; i < 19; i++) {
		if (living[i]->lv == 0) {
			continue;
		}
		if (living[i]->lv > 0) {
			// Move organism from old space to new space. First line clears previous space, second sets the new space equal to position
			board[living[i]->pos[0]][living[i]->pos[1]] = createCreature(-1, 0, living[i]->pos[0], living[i]->pos[1], 0);
			board[moveCreature(living[i])->pos[0]][moveCreature(living[i])->pos[1]] = moveCreature(living[i]);
		}
	}

}

void display() {
	Sleep(500);
	system("cls");
	for (int i = 0; i < 20; i++) {
		for (int x = 0; x < 20; x++) {
			if (x % 20 == 0) {
				if (board[i][x]->num == -1) {
					printf("\n");
				}
				else {
					printf("\n%d", board[i][x]->lv);
				}
			}
			else {
				if (board[i][x]->num == -1) {
					printf("  ");
				}
				else {
					printf(" %d ", board[i][x]->lv);
				}
			}
		}
	}
	return;
}

void run() {
	processCreatures();
	display();
	return;
}

int main(void) {
	srand(time(0));
	initLife();
	running = 1;
	while (running) {
		run();
	}
	return 0;
}