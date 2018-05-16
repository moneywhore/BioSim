#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int running;
typedef struct {
	int num;
	int lv;
	int pos[2];
} Creature;

int sunlight;
Creature* living[6];
Creature* board[10][10];

Creature *createCreature(int id, int r, int r1, int r2) {

	Creature *c = (Creature*)malloc(sizeof(Creature));
	c->num = id;
	c->lv = r;
	c->pos[0] = r1;
	c->pos[1] = r2;
	return c;
}

int initLife(void) {
	sunlight = rand() % 101;
	int r;
	int r1;
	int r2;
	for (int i = 0; i < 10; i++) {
		for (int x = 0; x < 10; x++) {
			board[i][x] = createCreature(-1, 0, i, x);
		}
	}
	for (int i = 0;i <= 5;i++) {
		r = rand() % 3;
		r1 = rand() % 10;
		r2 = rand() % 10;
		living[i] = createCreature(i, r, r1, r2);
		board[r1][r2] = living[i];
	}
	return 0;
}

int run(void) {
	for (int i = 0;i <= 5;i++) {
		printf("\n%d", living[i]->num);
	}
	for (int i = 0; i < 10; i++) {
		for (int x = 0; x < 10; x++) {
			printf("\n%d", board[i][x]->num);
		}
	}
	return 0;
}

int main(void) {
	srand(time(0));
	initLife();
	run();
	return 0;
}