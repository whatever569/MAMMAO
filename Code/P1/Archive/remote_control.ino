#include <SoftwareSerial.h>   //this needs to be included

SoftwareSerial BT(6, 7);  // TXD to 6, RXD to 7 in this case

void setup() {
  BT.begin(9600);   //a serial connection needs to be set up in order to communicate using the module
}

int input;  //if there already is an "int" or "char" type variable for inputs, that also can be used

void loop()
{
  void remote()   //the remote function itself
  {
    if (BT.available() > 0)
    {
      input = BT.read();
      switch (input)
      {
        case 'F':
        {
          while (BT.read() != 'S')
          {
            //forward function
          }
          break;
        }
        case 'E':
        {
          while (BT.read() != 'S')
          {
            //forward-left function
          }
          break;
        }
        case 'R':
        {
          while (BT.read() != 'S')
          {
            //right
          }
          break;
        }
        case 'C':
        {
          while (BT.read() != 'S')
          {
            //backwards-right
          }
          break;
        }
        case 'G':
        {
          while (BT.read() != 'S')
          {
            //backwards
          }
          break;
        }
        case 'Z':
        {
          while (BT.read() != 'S')
          {
            //backwards-left
          }
          break;
        }
        case 'L':
        {
          while (BT.read() != 'S')
          {
            //left
          }
          break;
        }
        case 'Q':
        {
          while (BT.read() != 'S')
          {
            //forward-left
          }
          break;
        }
        case 'Y':
        {
          if (speed < 4)
          {
            //speed++
          }
          break;
        }
        case 'X':
        {
          if (speed > 0)
          {
            //speed--
          }
        }
        break;
      }
    }
  }
}
