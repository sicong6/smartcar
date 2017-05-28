#include "DriverDebugger.h"
PIT_InitTypeDef Debug;
unsigned char Counter=1;
extern float SDS_OutData[4];
extern int LeftSpeed,RightSpeed;
extern int LeftDuty,RightDuty;
extern float32 Angle;
extern float32 AngleSpeed;
extern float32 GyroIntegral;
extern float32 P_Balance,D_Balance;
extern int SpeedDuty;
extern int BalanceDuty;
extern int TurnDuty;
extern int Speed;
extern float32 I_Speed;
extern int32 SpeedIntegral;
extern float32 AngleFilter;
extern int GyroStandard;
extern float32 PhysicalZero;
extern float32 P_Speed;
extern float32 D_Speed;
extern float32 P_Turn;
extern float32 D_Turn;
extern int SpeedError,SpeedErrorLast;
extern int ExpectSpeed;
extern int ExpectSpeedSet;
extern float32 TurnAngleSpeed;
extern float32 ExpectOffset;
extern uint8 Pixel[128];
int16 accel_x,accel_y,accel_z,gyro_x,gyro_y,gyro_z;
extern uint8 PixelNear[128],PixelForward[128];
extern uint8 lightflag,ring_center,Ring;
extern int TurnGyroStandard;
extern uint8 RoadWidth,StepNum;
void Viewccd(){
    int i=0;
    
    LPLD_UART_PutChar(UART5,0x02);
    LPLD_UART_PutChar(UART5,0xFD);
    
    for( i = 0;i<128;i++){
      LPLD_UART_PutChar(UART5,PixelNear[i]);
    }
    for( i = 0;i<128;i++){
      LPLD_UART_PutChar(UART5,PixelForward[i]);
    }

    LPLD_UART_PutChar(UART5,0xFD);
    LPLD_UART_PutChar(UART5,0x02);

}
void CCDView(uint8 Pixel[128]){
    int i=0;
  
    LPLD_UART_PutChar(UART5,0x02);
    LPLD_UART_PutChar(UART5,0xFD);
    for( i = 0;i<128;i++){
  //  if(Pixel[i]==0xFF)Pixel[i] = 0xFE; 
      LPLD_UART_PutChar(UART5,Pixel[i]);
    }
    /*
    for( i = 0;i<128;i++){
  //  if(Pixel[i]==0xFF)Pixel[i] = 0xFE; 
      LPLD_UART_PutChar(UART5,Pixel[i]);
    }
   */ 
    LPLD_UART_PutChar(UART5,0xFD);
    LPLD_UART_PutChar(UART5,0x02);
 
  /*
        for(i=0;i<128;i++){
        if(Pixel[i]==0xFF)Pixel[i] = 0xFE; 
        LPLD_UART_PutChar(UART5,Pixel[i]);
      }
  */
}

void ccdPlot(){
   SDS_OutData[0]=lightflag;
   SDS_OutData[1]=ring_center;
   SDS_OutData[2]=Ring; 
   SDS_OutData[3]=ExpectOffset;
}
void Plot(){

   SDS_OutData[0]=lightflag*100;//Angle;
   SDS_OutData[1]=ring_center*100;
   SDS_OutData[2]=Ring*100; 
   SDS_OutData[3]=ExpectOffset*10;
  
  
   //SDS_OutData[0]=GetAccelZ()+PhysicalZero;
/*  
   SDS_OutData[0]=ExpectOffset;//Speed;
   SDS_OutData[1]=RoadWidth;
   SDS_OutData[2]=StepNum;//ExpectOffset; 
   SDS_OutData[3]=lightflag;
 */ 
/*
   SDS_OutData[0]=Angle;
   SDS_OutData[1]=AngleSpeed;
   SDS_OutData[2]=BalanceDuty;
   SDS_OutData[3]=LeftDuty;
 */
  //if(!PTB16){
  /*
   SDS_OutData[0]=GetADC0AD13()-TurnGyroStandard;
   SDS_OutData[1]=TurnGyroStandard;
   SDS_OutData[2]=ExpectOffset;
   SDS_OutData[3]=TurnDuty;
  */
  //}else{
   /*
   SDS_OutData[0]=ExpectOffset;//Gyro
   SDS_OutData[1]=Speed;
   SDS_OutData[2]=SpeedDuty;
   SDS_OutData[3]=LeftDuty;
   */
  /*
   SDS_OutData[0]=GetADC0AD14()-PhysicalZero;//Gyro
   SDS_OutData[1]=GyroIntegral;
   SDS_OutData[2]=GyroStandard-GetADC0AD12();
   SDS_OutData[3]=AngleSpeed;
*/
  
  /*
   SDS_OutData[0]=LeftDuty;
   SDS_OutData[1]=LeftSpeed;
   SDS_OutData[2]=RightSpeed;
   SDS_OutPut_Data(SDS_OutData);
  */
    
   SDS_OutPut_Data(SDS_OutData);
}
void AppShow(){
printf("%d-%d\n",LeftSpeed,RightSpeed);
}
void OLEDShow(){

OLEDShowString(0,0,"PB");
OLEDShowNum(15,0,(int)(P_Balance),4,16);
OLEDShowString(60,0,"DB");
OLEDShowDecimal(80,0,D_Balance,3,2,16); 
OLEDShowString(0,2,"Phy");
OLEDShowDecimal(40,2,PhysicalZero,2,1,16); 
OLEDShowString(0,4,"PS");
OLEDShowNum(15,4,(int)(P_Speed),4,16);
OLEDShowString(50,4,"DS");
OLEDShowNum(65,4,(int)(D_Speed),4,16);
OLEDShowString(0,6,"PT");
OLEDShowNum(15,6,(int)P_Turn,4,16);
OLEDShowString(60,6,"DT");
OLEDShowDecimal(75,6,D_Turn,2,1,16);
/*
OLEDShowString(0,0,"P_Turn");
OLEDShowDecimal(80,0,P_Turn,3,1,16);
OLEDShowString(0,2,"D_Turn");
OLEDShowDecimal(70,2,D_Turn,2,1,16);
OLEDShowString(0,4,"P_Speed");
OLEDShowNum(60,4,(int)(P_Speed),4,16);
OLEDShowString(0,6,"ExpOffset");
OLEDShowNum(60,6,(int)ExpectOffset,4,16);
 */
  /*
OLEDShowString(0,0,"P_Turn");
OLEDShowDecimal(80,0,P_Turn,2,1,16);
OLEDShowString(0,2,"D_Turn");
OLEDShowDecimal(70,2,D_Turn,2,1,16);
OLEDShowString(0,4,"P_Speed");
OLEDShowNum(80,4,(int)(P_Speed),4,16);
OLEDShowString(0,6,"Phy");
OLEDShowNum(60,6,PhysicalZero,4,16); 
  */
}
void GetGyroStandard(){
    Debug.PIT_Pitx = PIT0;
    Debug.PIT_PeriodMs =1;
    Debug.PIT_PeriodS=NULL;
    Debug.PIT_PeriodUs=NULL;
    Debug.PIT_Isr = GetGyroStandardISR;
    LPLD_PIT_Init(Debug);
    LPLD_PIT_EnableIrq(Debug);
    while(Counter);
}
void GetGyroStandardISR(){
    static int GyroCounter=0;
    static int32 SumforGyro0=0;
    static int32 SumforGyro1=0;
    GyroCounter++;
    SumforGyro0+=GetGyroZ();
    SumforGyro1+=GetGyroY();
    //SumforGyro0+=GetADC0AD14();
    //SumforGyro1+=GetADC0AD13();
    if(GyroCounter>=100){
      GyroStandard=SumforGyro0/100;
      TurnGyroStandard=SumforGyro1/100;
      LPLD_PIT_DisableIrq(Debug);
      LPLD_PIT_Deinit(Debug);
      Counter=0;
    }
}
void GetPhysicalZero(){
    Debug.PIT_Pitx = PIT0;
    Debug.PIT_PeriodMs =1;
    Debug.PIT_PeriodS=NULL;
    Debug.PIT_PeriodUs=NULL;
    Debug.PIT_Isr = GetPhysicalZeroISR;
    LPLD_PIT_Init(Debug);
    LPLD_PIT_EnableIrq(Debug);
    while(Counter);
}
void GetPhysicalZeroISR(){
  static int AccelCounter=0;
  static int32 SumforAccel=0;
  AccelCounter++;
  SumforAccel+=GetAccelZ();
  if(AccelCounter>=2000){
    PhysicalZero=SumforAccel/2000;
    LPLD_PIT_DisableIrq(Debug);
    LPLD_PIT_Deinit(Debug);
    Counter=0;
  }
}

