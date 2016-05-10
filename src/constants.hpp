#ifndef CONSTANTS_H
#define CONSTANTS_H

static int SCREEN_WIDTH = 640;
static int SCREEN_HEIGHT = 480;

static float FRAMERATE = 1000/60;

static int POPULATION = 20;
static int MINE_LEN = 40;
static int EPOCH_TICK_OVER = 2000;
static int HIT_DISTANCE = 5;

static float MUTATION_CHANCE = 0.1;
static float COMBINE_CHANCE = 0.7;
static float MAX_PERTURB = 0.3;

static float CONTROL_SWEEPER_SPEED = 1.5;
static float MAX_SWEEPER_TURN_RATE = 0.3;
static float MAX_SWEEPER_SPEED = 2.0;

static int BRAIN_INPUT_LEN = 4;
static int BRAIN_OUTPUT_LEN = 2;
static int BRAIN_HIDDEN_LEN = 6;
static int BRAIN_HIDDEN_LAYER_LEN = 1;

#define WHITE 255,255,255
#define BLACK 0,0,0
#define RED 255,0,0
#define PURPLE 255,0,255

#endif
