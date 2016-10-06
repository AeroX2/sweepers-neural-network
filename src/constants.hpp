#ifndef CONSTANTS_H
#define CONSTANTS_H

static int SCREEN_WIDTH = 640;
static int SCREEN_HEIGHT = 480;

static float FRAMERATE = 1000.0/60.0;

static int ROLLING_AVERAGE = 10;

static int POPULATION = 20;
static int MINE_LEN = 40;
static int EPOCH_TICK_OVER = 2000;
static int HIT_DISTANCE = 5;
static int TOURNAMENT_SIZE = 4;

extern float MUTATION_CHANCE;
extern float COMBINE_CHANCE;
extern float MAX_PERTURB;

static float CONTROL_SWEEPER_SPEED = 1.5;
static float MAX_SWEEPER_TURN_RATE = 0.3;
static float MAX_SWEEPER_SPEED = 2.0;

static int BRAIN_INPUT_LEN = 5;
static int BRAIN_OUTPUT_LEN = 2;
static int BRAIN_HIDDEN_LEN = 10;
static int BRAIN_HIDDEN_LAYER_LEN = 1;

#define WHITE 255,255,255
#define BLACK 0,0,0

#define RED 255,0,0
#define BLUE 0,0,255
#define GREEN 0,255,0

#define ORANGE 255,159,0
#define PURPLE 255,0,255

#endif
