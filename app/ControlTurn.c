#include "ControlTurn.h"
extern float32 ExpectOffset;
extern float32 TurnAngleSpeed;
extern int TurnDuty;
extern float32 P_Turn,D_Turn;
void TurnCtrl(){
  //GetTurnAngleSpeed();
  static float32 ExpectOffsetLast=0;

  ExpectOffset=ExpectOffset>=TurnMax?TurnMax:ExpectOffset;
  ExpectOffset=ExpectOffset<=-TurnMax?-TurnMax:ExpectOffset;
  ExpectOffset=0.6 * ExpectOffset + 0.4 * ExpectOffsetLast;
  ExpectOffsetLast=ExpectOffsetLast;
  TurnDuty=(int)(P_Turn * ExpectOffset + D_Turn * TurnAngleSpeed);
}