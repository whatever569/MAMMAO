#ifndef DATA_H
#define DATA_H

#define MINSPEED 65
#define MAXSPEED 255

// ultrasonic
const int numUltrasonicSamples = 2;
const int numUltrasonicSensors = 3;

//flag to enable and disable debug mode, which sends out serial messages
bool debugMode = false;

enum Dir{
  FORWARD,
  BACK,
  RIGHT,
  NOT_RIGHT,
  STOP
};

int carSpeed = 0;
int motorSpeed = MINSPEED;
int turningSpeed = motorSpeed;
Dir direction = FORWARD; // '^' forward; '<' left; right '>'; 'v' backward

enum Mode{
  AUTOMATED,
  LINE_TRACKING,
  REMOTE
};

Mode mode = REMOTE;
int modeCounter = 2;

#endif