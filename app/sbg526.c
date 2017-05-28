#include "AllInclude.h"
extern uint8 Pixel[128];
extern int LeftSpeed,RightSpeed;
extern int LeftDuty,RightDuty;
extern float32 Angle,AngleSpeed;
extern int GyroStandard;
extern float32 P_Balance,D_Balance,P_Speed,I_Speed,P_Turn;
extern uint8 PixelProcessBegin;
extern void Havemidline();
extern void CCDhandle();
extern uint8 midline_2[2];
extern float32 ExpectOffset;
extern int PhysicalZero;
extern float32 GyroIntegral;
extern int8 MotorState;
extern uint8 Pixel_2[128],PixelB_2[128];
extern struct PixelLineStruct PixelLineNear[10],PixelLineForward[10];
extern uint8 PixelNear[128],PixelForward[128];
extern float32 TmpAngle;
void delay();
float32 tmp;
void main(){
    DisableInterrupts;
    FPUEnable();
/************System Init*************/
    OLEDInit();
    OLEDShowString(0,0,"System Initing ...");
    OLEDShowString(0,2,"Please wait without touching !");
    MotorInit();
    UARTInit();//Default for UART5
    ADCInit();
    SwitchInit();
    LEDInit();
    CCDInit();
    EncoderInit();
    FTM3Init();
    TeleControlInit();
    InfraredTubeInit();
    ButtonInit();
    MPU6050Init();
/***********End of System Init********/
    //U5PutChar('a');
    //PutChar('b');
/***************/
    delay();
    EnableInterrupts;
    GetGyroStandard();
    //GetPhysicalZero();
    ScheduleInit();
    OLEDClear();
    MotorState=-1;
    //GyroIntegral=(float32)(-GetADC0AD12()+PhysicalZero);
    GyroIntegral=(float32)(GetAccelZ());
    TmpAngle=(float32)(GetAccelZ());
 //   ExpectOffset=PixelIndex(PixelNear,PixelLineNear,10);
//    tmp=ModeIdentification(PixelLineNear,4);
    //PixelBinaryzation();
    //PixelIndex(PixelNear,PixelLineNear,10);
    //tmp=ModeIdentification(PixelLineNear,PixelIndex(PixelNear,PixelLineNear,10));
    LED1(1);
    LED2(1);
    LED3(1);
    LED4(1);
   for(;;){
/*
          if(PixelProcessBegin){
       if(PixelBinaryzation()==1){
        // CCDView(PixelNear);
         ExpectOffset=0;
         PixelProcessBegin=0;
       }else{
         //CCDView(PixelNear);
         ExpectOffset=ModeIdentification(PixelLineNear,PixelIndex(PixelNear,PixelLineNear,10));
         PixelProcessBegin=0;
         //CCDView(PixelNear);
       }
     }
*/
         /*
     if(PixelProcessBegin){
       CCDhandle();
       Havemidline();
       ExpectOffset=midline_2[1]-64;
       //GetTurnAngleSpeed();
       //TurnCtrl();
       PixelProcessBegin=0;
     }
     */
    
     /***********************************/
     //CCDView(PixelNear);
     /*
          if(PixelProcessBegin){
       if(PixelBinaryzation()==1){
         CCDView(PixelNear);
       }else{
         CCDView(PixelNear);
       }
       PixelProcessBegin=0;
     }
     */
     /*
     if(PixelProcessBegin){
       if(PixelBinaryzation()==1){
         ExpectOffset=0;//ии??a??
       }else{
         ExpectOffset=ModeIdentification(PixelLineNear,PixelIndex(PixelNear,PixelLineNear,10));
       }
       GetTurnAngleSpeed();
       TurnCtrl();
       PixelProcessBegin=0;
     }
     */
    /*
     if(PixelProcessBegin){
       CCDhandle();
       Havemidline();
       ExpectOffset=midline_2[1]-64;
       //GetTurnAngleSpeed();
       //TurnCtrl();
       PixelProcessBegin=0;
     }
     */
     /*******
         accel_x = MPU6050GetResult(ACCEL_XOUT_H);
    accel_y = MPU6050GetResult(ACCEL_YOUT_H);
    accel_z = MPU6050GetResult(ACCEL_ZOUT_H);
    gyro_x  = MPU6050GetResult(GYRO_XOUT_H);
    gyro_y  = MPU6050GetResult(GYRO_YOUT_H);
    gyro_z  = MPU6050GetResult(GYRO_ZOUT_H);
     *****/
       /*
     if(PixelProcessBegin){
       if(PixelBinaryzation()==1){
         ExpectOffset=0;//ии??a??
       }else{
         ExpectOffset=ModeIdentification(PixelLineNear,PixelIndex(PixelNear,PixelLineNear,10));
       }
       GetTurnAngleSpeed();
       TurnCtrl();
       PixelProcessBegin=0;
     }
       */
    // ccdPlot();
    OLEDShow();
 //  if(!PTB17_I)LED1(1);

 // delay();
/*
int i=0;
    LPLD_UART_PutChar(UART3,0x02);
    LPLD_UART_PutChar(UART3,0xFD);
    for( i = 0;i<128;i++){
  //  if(Pixel[i]==0xFF)Pixel[i] = 0xFE; 
      LPLD_UART_PutChar(UART3,Pixel_2[i]);
    }
    for( i = 0;i<128;i++){
  //  if(Pixel[i]==0xFF)Pixel[i] = 0xFE; 
      LPLD_UART_PutChar(UART3,PixelB_2[i]);
    }
    LPLD_UART_PutChar(UART3,0xFD);
    LPLD_UART_PutChar(UART3,0x02);
   */
    }
}
      
      //ADC
     // printf("%d-%d\n",GetADC1AD12(),GetADC1AD13());
    //printf("%d-%d-%d-%d-%d-%d-%d-%d-%d\n",GetADC0AD12(),GetADC0AD13(),GetADC0AD14(),GetADC0AD17(),GetADC0AD18(),GetADC2AD12(),GetADC2AD13(),GetADC3AD16(),GetADC3AD17());
/*
   //printf("PWMLeft=%d,PWMRight=%d,EncoderLeft=%d,EncoderRight=%d\n",LeftDuty,RightDuty,LeftSpeed,RightSpeed);
#define GetADC0AD12() LPLD_ADC_Get(ADC0,AD12)//PTB2
#define GetADC0AD13() LPLD_ADC_Get(ADC0,AD13)//PTB3
#define GetADC0AD14() LPLD_ADC_Get(ADC0,AD14)//PTC0
#define GetADC0AD17() LPLD_ADC_Get(ADC0,AD17)//PTE24
#define GetADC0AD18() LPLD_ADC_Get(ADC0,AD18)//PTE25
#define GetADC2AD12() LPLD_ADC_Get(ADC2,AD12)//PTA29
#define GetADC2AD13() LPLD_ADC_Get(ADC2,AD13)//PTA28
#define GetADC3AD16() LPLD_ADC_Get(ADC3,AD16)//PTE11
#define GetADC3AD17() LPLD_ADC_Get(ADC3,AD17)//PTE12
*/
    //CCD1View(20);
//delay();
//}
 ///////////////////////////////////////////////////////
/*
   LPLD_UART_PutCharArr(UART3,"Input something:\r\n",18);
   int8 get;
   // /ar ch;
    while(1)
    {
   // / = in_char();
    //   out_char(ch);
      get = LPLD_UART_GetChar(UART3);
      LPLD_UART_PutChar(UART3,get);
    } 
    ///////////////////////////////////////////////////////
*/


/*
uint32 sec=1;
void pit_test_isr(){
    U5PutChar('a');
    PIT->CHANNEL[PIT2].LDVAL = sec*1000000*(g_bus_clock/1000000)-1;
    sec++;
}
*/
void delay()
{
  uint16 i, n;
  for(i=0;i<90;i++)
  {
    for(n=0;n<200;n++)
    {
      asm("nop");
    }
  }
}
    
    
    
    
    /*
    for(;;){
    MotorChangeLeftDuty(i);    
    MotorChangeRightDuty(i-100);
   //     PutChar('a');

    //OLED_Init();
    //OLED_Display_On();
    //OLED_ShowString(0,0,"MotorLeftDuty");
    //OLED_ShowNum(4,0,i,4,16);
    //OLED_Clear();
    printf("%d-",LPLD_ADC_Get(ADC0, AD12));
    printf("%d\n",LPLD_ADC_Get(ADC1, AD12));
   // delay();
    //SDS_OutData[0]=LPLD_ADC_Get(ADC0, AD12);
    //SDS_OutPut_Data(SDS_OutData);
    }
    //ADCInit();
    */
    /*****************CCD************
    for(;;){
      CCDGetLine(gPixel);
      int i=0;
      for(;i<128;i++){
      //printf("%d\n",gPixel[i]);
        if(gPixel[i]==0xFF) 
        gPixel[i] = 0xFE; 
        U5PutChar(gPixel[i]);
      }
    
  ExposureDelay(50);
    }
    *********************************/


