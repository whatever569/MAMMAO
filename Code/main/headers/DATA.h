#ifndef DATA_H
#define DATA_H
// ultrasonic
const int numUltrasonicSamples = 2;
const int numUltrasonicSensors = 3;

//flag to enable and disable debug mode, which sends out serial messages
bool debugMode = false;

int speed;
char direction; // '^' forward; '<' left; right '>'; 'v' backward

enum Mode{
  AUTOMATED,
  LINE_TRACKING,
  REMOTE
};

Mode mode = REMOTE;

#endif