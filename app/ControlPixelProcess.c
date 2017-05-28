#include "ControlPixelProcess.h"
uint8 PixelNear[128],PixelForward[128];
extern float32 ExpectOffset;
struct PixelLineStruct PixelLineNear[10],PixelLineForward[10];
uint8 LineStepNear=0,LineStepForward=0;
uint8 RoadWidth=80;
uint8 StepNum=0;
float32 deviation;
uint8 lightflag,ring_center,Ring = 0,flag_rightline;
uint8 PixelBinaryzation(){
    uint8 i,ThresholdNearMax,ThresholdNearMin,ThresholdForwardMax,ThresholdForwardMin,ThresholdNear,ThresholdForward;
    int32 PixelSumNear=0,PixelSumForward=0;
    //平滑处理
    
    for(i=1;i<127;i++){
        PixelNear[i] = (uint8)(0.15*PixelNear[i-1]+0.7*PixelNear[i]+0.15*PixelNear[i+1]);
        PixelForward[i] = (uint8)(0.15*PixelForward[i-1]+0.7*PixelForward[i]+0.15*PixelForward[i+1]);
    }
    
    //边界处理
    PixelNear[4] = PixelNear[5];   PixelNear[123] = PixelNear[122];
    PixelNear[3] = PixelNear[4];   PixelNear[124] = PixelNear[123];
    PixelNear[2] = PixelNear[3];   PixelNear[125] = PixelNear[124];
    PixelNear[1] = PixelNear[2];   PixelNear[126] = PixelNear[125];
    PixelNear[0] = PixelNear[1];   PixelNear[127] = PixelNear[126];

    PixelForward[4] = PixelForward[5];   PixelForward[123] = PixelForward[122];
    PixelForward[3] = PixelForward[4];   PixelForward[124] = PixelForward[123];
    PixelForward[2] = PixelForward[3];   PixelForward[125] = PixelForward[124];
    PixelForward[1] = PixelForward[2];   PixelForward[126] = PixelForward[125];
    PixelForward[0] = PixelForward[1];   PixelForward[127] = PixelForward[126];
    ThresholdNearMax=ThresholdNearMin=PixelNear[0];
    ThresholdForwardMax=ThresholdForwardMin=PixelForward[0];
    for(i=1;i<128;i++){
      if(PixelNear[i]>ThresholdNearMax)ThresholdNearMax=PixelNear[i];
      if(PixelNear[i]<ThresholdNearMin)ThresholdNearMin=PixelNear[i];
      if(PixelForward[i]>ThresholdForwardMax)ThresholdForwardMax=PixelForward[i];
      if(PixelForward[i]<ThresholdForwardMin)ThresholdForwardMin=PixelForward[i];
    }
    
    //计算阈值
    ThresholdNear=(ThresholdNearMax+ThresholdNearMin)/2+ThresholdNearOffset;
    ThresholdForward=(ThresholdForwardMax+ThresholdForwardMax)/2+ThresholdForwardOffset;
    ThresholdNear=180;
    ThresholdForward=180;
    for(i=0;i<=127;i++){//二值化
      PixelSumNear+=PixelNear[i];
      PixelSumForward+=PixelForward[i];
      PixelNear[i]=PixelNear[i]>ThresholdNear?255:0;
      PixelForward[i]=PixelForward[i]>ThresholdForward?255:0;
    }
    
    /*
    if(((PixelSumNear/128)>NearPixelHighThreshold)  || ((PixelSumNear/128)<NearPixelLowThreshold))
      return 1;
    //1:近线全白或全黑
    else return 0;
    //正常情况
   */
    /*
        for(i=0;i<=127;i++){//二值化
      if(PixelNear[i]>200)PixelNear[i]=255;
      else PixelNear[i]=0;
     // PixelNear[i]=(PixelNear[i]>100)?255:0;
      //PixelForward[i]=PixelForward[i]>100?255:0;
    }
    
    return 0;
    */
    /*
    if(((PixelSumNear/128)>NearPixelHighThreshold)  || ((PixelSumNear/128)<NearPixelLowThreshold))
      return 1;
    //1:近线全白或全黑
    else return 0;
    */
    return 0;
}
uint8 PixelIndex(uint8 Pixel[],struct PixelLineStruct PixelLine[],uint8 length){
  uint8 i;
  StepNum = 0;
  for(i=0;i<=126;i++){
    if(Pixel[i]==0&&Pixel[i+1]==255){//上升跳变
      PixelLine[StepNum].Type=UP;
      PixelLine[StepNum].Position=i;
      StepNum++;
    }else if(Pixel[i]==255&&Pixel[i+1]==0){//下降跳变
      PixelLine[StepNum].Type=DOWN;
      PixelLine[StepNum].Position=i;
      StepNum++;
    }
    if(StepNum>=length)break;//需要异常处理，PixelLine溢出，默认长度10
  }
  return StepNum;
}
void ccdringsign(struct PixelLineStruct *PixelLine,uint8 PixelStep){
    ring_center = 0; 
    if(PixelStep==2){//
    if(PixelLine[0].Type==UP){//                                 ______\~~~~Num~~~~\______   
      if((PixelLine[1].Position-PixelLine[0].Position)>=RoadWidthThreshold){//15
        if((PixelLine[1].Position-PixelLine[0].Position)>=AllHighWidthThreshold){//如果路宽大于阈值，判断为全白
          ;
        }//否则为正常情况
        ;
      }else{ //                                                   _____\~\____
        ;
      }
    }else{//
      if((PixelLine[1].Position-PixelLine[0].Position)>CircleWidthThreshold){//阈值！！！！！     ~~~~~~~~~~~~~\_\~~~~~~~~~
        ring_center = 1;
        if((PixelLine[1].Position-PixelLine[0].Position)>20) ;
        else{        
            if(PixelLine[0].Position>(127-PixelLine[1].Position))//     ~~~~~~~~~~~~~~\___\~~
              ;
            else //                                                   ~~~\____\~~~~~~~~~~~~~~~~~~
              ;
        }
      }
      else{
        ; 
      }
    }
  }
  if(PixelStep==3){//
    ring_center = 1;
  }
}
float32 ModeIdentification(struct PixelLineStruct *PixelLine,uint8 PixelStep){

  static float32 StraighWayCNT=0;
  static float32 ExpectOffsetTmp=0;
  lightflag = 0; flag_rightline = 128;
  
  /***********************************************************/
  if(PixelStep==0){
    StraighWayCNT=0;
    lightflag = 1;
    deviation = 0;
  }else if(PixelStep==1){//单跳变，丢线
    StraighWayCNT=0;
    if(PixelLine[0].Type==UP){//                                 ____\~~~~~~
      //ExpectOffsetTmp=PixelLine[0].Position+(RoadWidth/2.0)-63.5;
      if((127-PixelLine[0].Position)>AllHighWidthThreshold){
        lightflag = 1;////单跳变，白宽度大于阈值，判断为全白
        deviation = 0;
      }
      lightflag=0;
      deviation = (PixelLine[0].Position+(RoadWidth/2.0)-63.5);
    }else{//                                                      ~~~~~\______
      if(PixelLine[0].Position>AllHighWidthThreshold){
        lightflag=1;//单跳变，白宽度大于阈值，判断为全白
        deviation = 0;
      }
      lightflag=0;
      deviation = (PixelLine[0].Position-(RoadWidth/2.0)-63.5);
      flag_rightline = PixelLine[0].Position;
    }
  }else if(PixelStep==2){//
    if(PixelLine[0].Type==UP){//                                 ______\~~~~Num~~~~\______   
      if((PixelLine[1].Position-PixelLine[0].Position)>=RoadWidthThreshold){//15
        if((PixelLine[1].Position-PixelLine[0].Position)>=AllHighWidthThreshold){//如果路宽大于阈值，判断为全白
          lightflag=1;
          deviation = 0;
        }//否则为正常情况
        lightflag=0;//
        //赛道宽度动态计算
        if(ABS(((PixelLine[1].Position+PixelLine[0].Position)/2.0-63.5)-ExpectOffsetTmp)<5){
          StraighWayCNT++;
          if(StraighWayCNT>=40){
            RoadWidth=PixelLine[1].Position-PixelLine[0].Position;
            StraighWayCNT=0;
          }
        }
        ExpectOffsetTmp=(PixelLine[1].Position+PixelLine[0].Position)/2.0-63.5;
        deviation = (PixelLine[1].Position+PixelLine[0].Position)/2.0-63.5;
        flag_rightline = PixelLine[1].Position;
      }else{ //                                                   _____\~\____
        lightflag=0;
        deviation = 0;
      }
    }else{//
      StraighWayCNT=0;/// ? ? ? ? ?
      if((PixelLine[1].Position-PixelLine[0].Position)>CircleWidthThreshold){//阈值！！！！！     ~~~~~~~~~~~~~\_\~~~~~~~~~
        if((PixelLine[1].Position-PixelLine[0].Position)>20) deviation = 0;
        else{
            lightflag=0;
        
            if(PixelLine[0].Position>(127-PixelLine[1].Position))//     ~~~~~~~~~~~~~~\___\~~
              deviation = (PixelLine[0].Position-(RoadWidth/2.0)-63.5);
            else //                                                   ~~~\____\~~~~~~~~~~~~~~~~~~
              deviation = (PixelLine[1].Position+(RoadWidth/2.0)-63.5);
        }
      }
      else{
        deviation = 0; 
      }
    }
  }else if(PixelStep==3){//
    StraighWayCNT=0;
    lightflag=0;//清除全白标志位
    if(PixelLine[0].Type==UP){
      if((PixelLine[1].Position-PixelLine[0].Position)>(127-PixelLine[2].Position))//__\~~~~~~~~~~~~\___\~~
        deviation = (PixelLine[0].Position+PixelLine[1].Position)/2.0-63.5;
      else                                                 //                  ___\~~\__\~~~~~~~~~~~~~~~~
        deviation = (PixelLine[2].Position+(RoadWidth/2.0)-63.5);
    }else{
      if((PixelLine[2].Position-PixelLine[1].Position)>PixelLine[0].Position)//~~~~\__\~~~~~~~~~~~~~~\__
        deviation = (PixelLine[2].Position+PixelLine[1].Position)/2.0-63.5;
      else                              //                                  ~~~~~~~~~~~~~~~~\___\~~\__
        deviation = (PixelLine[0].Position-(RoadWidth/2.0)-63.5);
    }
  }else if(PixelStep==4){
    StraighWayCNT=0;
    lightflag=0;//清除全白标志位
    if(PixelLine[0].Type==UP){
      if((PixelLine[1].Position-PixelLine[0].Position)>(PixelLine[3].Position-PixelLine[2].Position))//__\~~~~~~~~~\___\~~\__
        deviation = (PixelLine[0].Position+PixelLine[1].Position)/2.0-63.5;
      else                                                              //                        __\~~\__\~~~~~~~~~~~~\__
        deviation = (PixelLine[2].Position+PixelLine[3].Position)/2.0-63.5; 
    }else{// 
      if((PixelLine[2].Position-PixelLine[1].Position)>RoadWidthThreshold)//                      ~~~\__\~~~~~~Num~~~~~~~\__\~~
        deviation = (PixelLine[1].Position+PixelLine[2].Position)/2.0-63.5;
      else{
        if(PixelLine[0].Position>(127-PixelLine[3].Position))//                                  ~~~~~~~~~~~~~~\__\~~\__\~~~
          deviation = (PixelLine[0].Position-(RoadWidth/2.0)-63.5);
        else                                    //                                                ~~~\__\~~\__\~~~~~~~~~~~~~~
          deviation = (PixelLine[3].Position+(RoadWidth/2.0)-63.5);
      }
    }
  }else{
    StraighWayCNT=0;
    lightflag=0;//清除全白标志位
    deviation = 0;
  }
  
  //Ring 控制          0：非环，1：环入口，2：环中，3：环出口
  if(lightflag && ring_center) Ring = 1;
  if(Ring==1) deviation = 45;
  if(Ring==1 && !ring_center && flag_rightline<108) Ring = 2;
  if(Ring==2) deviation = flag_rightline;
  if(Ring==2 && flag_rightline>124) Ring = 3;
  if(Ring==3) deviation = 45;
  if(Ring==3 && flag_rightline<108) Ring = 0;
  
  
  
  return deviation;
}






/*原本
if(PixelStep==0){
    StraighWayCNT=0;
    lightflag = 1;
    return 0;
  }else if(PixelStep==1){//单跳变，丢线
    StraighWayCNT=0;
    if(PixelLine[0].Type==UP){//                                 ____\~~~~~~
      //ExpectOffsetTmp=PixelLine[0].Position+(RoadWidth/2.0)-63.5;
      if((127-PixelLine[0].Position)>AllHighWidthThreshold){
        lightflag = 1;////单跳变，白宽度大于阈值，判断为全白
        return 0;
      }
      lightflag=0;
      return (PixelLine[0].Position+(RoadWidth/2.0)-63.5);
    }else{//                                                      ~~~~~\______
      if(PixelLine[0].Position>AllHighWidthThreshold){
        lightflag=1;//单跳变，白宽度大于阈值，判断为全白
        return 0;
      }
      lightflag=0;
      return (PixelLine[0].Position-(RoadWidth/2.0)-63.5);
    }
  }else if(PixelStep==2){//
    if(PixelLine[0].Type==UP){//                                 ______\~~~~Num~~~~\______   
      if((PixelLine[1].Position-PixelLine[0].Position)>=RoadWidthThreshold){//15
        if((PixelLine[1].Position-PixelLine[0].Position)>=AllHighWidthThreshold){//如果路宽大于阈值，判断为全白
          lightflag=1;
          return 0;
        }//否则为正常情况
        lightflag=0;//
        //赛道宽度动态计算
        if(ABS(((PixelLine[1].Position+PixelLine[0].Position)/2.0-63.5)-ExpectOffsetTmp)<5){
          StraighWayCNT++;
          if(StraighWayCNT>=40){
            RoadWidth=PixelLine[1].Position-PixelLine[0].Position;
            StraighWayCNT=0;
          }
        }
        ExpectOffsetTmp=(PixelLine[1].Position+PixelLine[0].Position)/2.0-63.5;
        return (PixelLine[1].Position+PixelLine[0].Position)/2.0-63.5;
      }else{ //                                                   _____\~\____
        lightflag=0;
        return 0;
      }
    }else{//
      StraighWayCNT=0;/// ? ? ? ? ?
      if((PixelLine[1].Position-PixelLine[0].Position)>CircleWidthThreshold){//阈值！！！！！     ~~~~~~~~~~~~~\_\~~~~~~~~~
        if((PixelLine[1].Position-PixelLine[0].Position)>20)return 0;
        else{
            lightflag=0;
        
            if(PixelLine[0].Position>(127-PixelLine[1].Position))//     ~~~~~~~~~~~~~~\___\~~
              return (PixelLine[0].Position-(RoadWidth/2.0)-63.5);
            else //                                                   ~~~\____\~~~~~~~~~~~~~~~~~~
              return (PixelLine[1].Position+(RoadWidth/2.0)-63.5);
        }
      }
      else{
        return 0; 
      }
    }
  }else if(PixelStep==3){//
    StraighWayCNT=0;
    lightflag=0;//清除全白标志位
    if(PixelLine[0].Type==UP){
      if((PixelLine[1].Position-PixelLine[0].Position)>(127-PixelLine[2].Position))//__\~~~~~~~~~~~~\___\~~
        return (PixelLine[0].Position+PixelLine[1].Position)/2.0-63.5;
      else                                                 //                  ___\~~\__\~~~~~~~~~~~~~~~~
        return (PixelLine[2].Position+(RoadWidth/2.0)-63.5);
    }else{
      if((PixelLine[2].Position-PixelLine[1].Position)>PixelLine[0].Position)//~~~~\__\~~~~~~~~~~~~~~\__
        return (PixelLine[2].Position+PixelLine[1].Position)/2.0-63.5;
      else                              //                                  ~~~~~~~~~~~~~~~~\___\~~\__
        return (PixelLine[0].Position-(RoadWidth/2.0)-63.5);
    }
  }else if(PixelStep==4){
    StraighWayCNT=0;
    lightflag=0;//清除全白标志位
    if(PixelLine[0].Type==UP){
      if((PixelLine[1].Position-PixelLine[0].Position)>(PixelLine[3].Position-PixelLine[2].Position))//__\~~~~~~~~~\___\~~\__
        return (PixelLine[0].Position+PixelLine[1].Position)/2.0-63.5;
      else                                                              //                        __\~~\__\~~~~~~~~~~~~\__
        return (PixelLine[2].Position+PixelLine[3].Position)/2.0-63.5; 
    }else{// 
      if((PixelLine[2].Position-PixelLine[1].Position)>RoadWidthThreshold)//                      ~~~\__\~~~~~~Num~~~~~~~\__\~~
        return (PixelLine[1].Position+PixelLine[2].Position)/2.0-63.5;
      else{
        if(PixelLine[0].Position>(127-PixelLine[3].Position))//                                  ~~~~~~~~~~~~~~\__\~~\__\~~~
          return (PixelLine[0].Position-(RoadWidth/2.0)-63.5);
        else                                    //                                                ~~~\__\~~\__\~~~~~~~~~~~~~~
          return (PixelLine[3].Position+(RoadWidth/2.0)-63.5);
      }
    }
  }else{
    StraighWayCNT=0;
    lightflag=0;//清除全白标志位
    return 0;
  }
*/






















uint8 StraighWayIndentification(uint8 ExpectOffset,uint8 cnt){
  static int8 Mode=0;
  static uint8 ExpectOffsetLast=0;
  if(ABS(ExpectOffset-ExpectOffsetLast)<7)Mode++;
  else Mode--;
  if(Mode>=20)Mode=20;
  if(Mode<=0)Mode=0;
  if(Mode>=cnt)return 1;
  
  else return 0;
}
uint8 TrendIdentification(uint8 RoadWidth,uint8 cnt){
  static uint8 RoadWidthLast=0;
  static uint8 Mode=0;
  if(RoadWidth>=RoadWidthLast){
    RoadWidthLast=RoadWidth;
    Mode++;
  }else Mode=0;
  if(Mode>=cnt)return 1;
  else return 0;
}
