#ifndef _CONTROLPIXELPROCESS_H_
#define _CONTROLPIXELPROCESS_H_ 
#include "AllInclude.h"
#define ThresholdNearOffset 0
#define ThresholdForwardOffset 0
#define NearPixelHighThreshold 230
#define NearPixelLowThreshold 100
#define ForwardPixelHighThreshold 150
//#define RoadWidth 80
#define AllHighWidthThreshold 120
#define RoadWidthThreshold 0
#define CircleWidthThreshold 4
#define Offset 45
#define ABS(x) (x>=0?x:-x)
#define CNT 3
enum PixelLineType{
  UP,
  DOWN
};
struct PixelLineStruct{
  enum PixelLineType Type;
  uint8 Position;
};
uint8 PixelBinaryzation();
uint8 PixelIndex(uint8 Pixel[],struct PixelLineStruct *PixelLine,uint8 length);
void ccdringsign(struct PixelLineStruct *PixelLine,uint8 PixelStep);
float32 ModeIdentification(struct PixelLineStruct *PixelLine,uint8 PixelStep);
uint8 TrendIdentification(uint8 RoadWidth,uint8 cnt);
uint8 StraighWayIndentification(uint8 ExpectOffset,uint8 cnt);
#endif