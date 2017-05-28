#include "Control.h"
PIT_InitTypeDef Control;
extern void CCDhandle();
extern void Havemidline();
/*****Global Variable********/
int LeftDuty=0,RightDuty=0;
int LeftSpeed=0,RightSpeed=0;
int BalanceDuty=0,SpeedDuty=0,TurnDuty=0;
float32 Angle=0,AngleSpeed=0;
float32 TurnAngleSpeed=0;
float32 GyroIntegral=0;
int32 SpeedIntegral=0;
int Speed=0;
int ExpectSpeed=0;
int ExpectSpeedSet=0;
float32 ExpectOffset=0;
uint8 Pixel[128];
int GyroStandard=0;
int TurnGyroStandard=0;
float32 PhysicalZero=0;//370;//zero 2300
/*
float32 P_Balance=178,D_Balance=7.79;//350 13 1350 12///12//2350//15.6
float32 P_Speed=127,I_Speed=0,D_Speed=0;//23 -0.0002
float32 P_Turn=100,D_Turn=2.8;
*/
float32 P_Balance=47,D_Balance=30.59;//350 13 1350 12///12//2350//15.6
float32 P_Speed=45,I_Speed=0,D_Speed=0;//23 -0.0002
float32 P_Turn=120,D_Turn=5.7;
uint8 IncreaseValue=20;
int8 MotorState=1;
uint8 PixelProcessBegin=0;
extern uint8 PixelNear[128],PixelForward[128];
extern struct PixelLineStruct PixelLineNear[10],PixelLineForward[10];
/**********CCD*********/
extern unsigned char Pixel_2[128];
extern unsigned char Pixel_1[128];
extern uint8 midline_2[2];
extern uint8 PixelB_2[128];
//uint8 DelayForExpectSpeedSet=10; //100ms for each time
/*******function**************
P_Balance 2540 D_Balance 15.5
          480            16.520






**************************/
void ScheduleInit(){
    Control.PIT_Pitx = PIT0;
    Control.PIT_PeriodMs =1;
    Control.PIT_PeriodS=NULL;
    Control.PIT_PeriodUs=NULL;
    Control.PIT_Isr = GlobalControl;
    LPLD_PIT_Init(Control);
    LPLD_PIT_EnableIrq(Control);
}
void GlobalControl(){ //主时序控制
  static unsigned char FlagMs=0;
  static unsigned char FlagGetSpeed=0;
  static unsigned char FlagSpeed=0;
  static unsigned char FlagCCD=0;
  FlagMs++;


  
  if(FlagMs==1){
  
  FlagCCD++;
  if(FlagCCD==1){
    CCD1Integration();
    CCD2Integration();
  }
  else if(FlagCCD==2){
  
    //CCD2ImageCapture(Pixel_2);
    CCD1ImageCapture(PixelForward);
    CCD2ImageCapture(PixelNear);
   //CCDhandle();
    //Havemidline();
    FlagCCD=0;
    //CCDView(PixelNear);
    PixelProcessBegin=1;
    //ExpectOffset=midline_2[1]-64;
  }
  
  }else if(FlagMs==2){
    
     if(PixelProcessBegin){
       if(PixelBinaryzation()==1){
         ExpectOffset=0;
         PixelProcessBegin=0;
       }else{
         //CCDView(PixelForward);
         //CCDView(PixelNear);
         ccdringsign(PixelLineForward,PixelIndex(PixelForward,PixelLineForward,10));
         ExpectOffset=ModeIdentification(PixelLineNear,PixelIndex(PixelNear,PixelLineNear,10));
         PixelProcessBegin=0;

       }

     }
   

  }else if(FlagMs==3){
//        if(PixelProcessBegin==2)ExpectOffset=ModeIdentification(PixelLineNear,PixelIndex(PixelNear,PixelLineNear,10)),PixelProcessBegin=0;

       //GetTurnAngleSpeed();
      if(1) Plot();
      else Viewccd();
  }else if(FlagMs==4){
    
    FlagGetSpeed++;
    FlagSpeed++;
    if(FlagGetSpeed==2)GetSpeed(),FlagGetSpeed=0;
    if(FlagSpeed==SpeedPeriod){
      I_Speed=(P_Speed/200);
      //达到ExpectSpeedSet的缓冲  ExpectSpeed平滑输出
      //if(ExpectSpeed!=ExpectSpeedSet)ExpectSpeed+=((ExpectSpeedSet-ExpectSpeed)>0?1:-1) * IncreaseValue;
      
      FlagSpeed=0,SpeedCtrl();//速度环控制
    }
    
  }else if(FlagMs==5){
    
    GetAngle();
    //GetTurnAngleSpeed();
    TurnCtrl();
    BalanceCtrl();//直立环控制
    OutputSmooth();//速度平滑输出
    //PWM 限幅
    /*
    if(TurnDuty>0){
    LeftDuty=BalanceDuty - SpeedDuty;
    RightDuty=BalanceDuty - SpeedDuty + TurnDuty;
    }else{
    LeftDuty=BalanceDuty - SpeedDuty - TurnDuty;
    RightDuty=BalanceDuty - SpeedDuty;
    }
    */
    LeftDuty=BalanceDuty - SpeedDuty - TurnDuty;
    RightDuty=BalanceDuty - SpeedDuty + TurnDuty;
    if(MotorState==1)UpdateDuty();//更新占空比
    else {
    //关电机
      FTM0ChangeCH0Duty(0);
      FTM0ChangeCH1Duty(0);
      FTM0ChangeCH2Duty(0);
      FTM0ChangeCH3Duty(0);
    }
    
    /*
      FTM0ChangeCH0Duty(0);
      FTM0ChangeCH1Duty(1200);
      FTM0ChangeCH2Duty(1200);
      FTM0ChangeCH3Duty(0);
    */

   
  }
  if(FlagMs==5)FlagMs=0;
}
//平滑输出函数
void OutputSmooth(){
    static unsigned char CounterForSpeedOutput=0;
    static int SpeedDutyDiff=0;
    static int SpeedDutyLast=0;
    CounterForSpeedOutput++;
    if(CounterForSpeedOutput==1)SpeedDutyDiff=(SpeedDuty-SpeedDutyLast)/SpeedPeriod,SpeedDuty=SpeedDutyLast;
    SpeedDuty+=SpeedDutyDiff;
    if(CounterForSpeedOutput==SpeedPeriod)CounterForSpeedOutput=0,SpeedDutyLast=SpeedDuty;
}