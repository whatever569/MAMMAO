enum Mode{
  AUTOMATED,
  LINE_TRACKING,
  REMOTE
}

Mode mode = AUTOMATED;
void setup() {
  Serial.begin(19200);
  remote_setup();
}

void loop() {  

switch (mode)
{
  case AUTOMATED:
    activate_automated_mode();
  case LINE_TRACKING:

  case REMOTE:
    remote();
}
}