#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#define orgs 5
#define padProducers 6
#define totalOrgs 11
#define boardDim1 20
#define boardDim2 20

int levels = 4;
int boardDims[2] = { boardDim1, boardDim2 };
int sunlight;
int running;
int directions = 4;
int noCreature = -1;
int gameSpeed = 500;

typedef struct {
	int num;
	int lv;
	int pos[2];
	int energy;
} Creature;

// Array of living things and their attributes
Creature* living[orgs + padProducers];

// The actual board
Creature* board[boardDim1][boardDim2];

Creature *createCreature(int id, int randLevel, int randLoc1, int randLoc2, int e) {

	Creature *c = (Creature*)malloc(sizeof(Creature));
	c->num = id;
	c->lv = randLevel;
	c->pos[0] = randLoc1;
	c->pos[1] = randLoc2;
	c->energy = e;
	return c;
}

int calculateEnergy(int level) {
	return (20 / (level + 1));
}

// Initialize life on the board before the game loop starts
void initLife() {

	int randLevel;
	int randLoc1;
	int randLoc2;

	// Set all board spaces equal to creatures that have no real attributes
	for (int i = 0; i < boardDims[0]; i++) {
		for (int x = 0; x < boardDims[1]; x++) {
			board[i][x] = createCreature(-1, 0, i, x, 0);
		}
	}

	// Add producers that pad the board
	for (int i = 0; i < padProducers; i++) {
		randLoc1 = rand() % boardDims[0];
		randLoc2 = rand() % boardDims[1];
		living[i] = createCreature(i, 0, randLoc1, randLoc2, calculateEnergy(0));
		board[randLoc1][randLoc2] = living[i];
	}

	// Add actual random organisms
	for (int i = padProducers; i < totalOrgs; i++) {
		randLevel = rand() % levels;
		randLoc1 = rand() % boardDims[0];
		randLoc2 = rand() % boardDims[1];
		living[i] = createCreature(i, randLevel, randLoc1, randLoc2, calculateEnergy(randLevel));
		board[randLoc1][randLoc2] = living[i];
	}

	return;
}

Creature *moveCreature(Creature *c) {

	int dir = rand() % directions;

	switch (dir) {

	case 0:
		if (c->pos[0] - 1 < 0) {
			break;
		}
		c->pos[0]--;
		break;

	case 1:
		if (c->pos[0] + 1 >= boardDims[0]) {
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
		if (c->pos[1] + 1 >= boardDims[1]) {
			break;
		}
		c->pos[1]++;
		break;
	}

	return c;
}

void processCreatures() {
	int oldPos[2];
	int newPos[2];
	Creature *movedCreature;
	for (int i = 0; i < totalOrgs; i++) {
		if (living[i]->lv == 0) {
			continue;
		}

		movedCreature = moveCreature(living[i]);

		oldPos[0] = living[i]->pos[0];
		oldPos[1] = living[i]->pos[1];

		newPos[0] = movedCreature->pos[0];
		newPos[1] = movedCreature->pos[1];

		if (living[i]->lv > 0) {
			// Move organism from old space to new space. First line clears previous space, second sets the new space equal to position
			board[oldPos[0]][oldPos[1]] = createCreature(noCreature, 0, oldPos[0], oldPos[1], 0);
			board[newPos[0]][newPos[1]] = movedCreature;
		}

	}

}

void display() {

	Sleep(gameSpeed);
	system("cls");

	for (int i = 0; i < boardDims[0]; i++) {
		for (int x = 0; x < boardDims[1]; x++) {

			if (x % boardDims[1] == 0) {

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