#ifndef SELECT_H
#define SELECT_H
enum Mode{
  AUTOMATED,
  LINE_TRACKING,
  REMOTE
};
void modeSelection();
Mode mode = REMOTE;
#endif