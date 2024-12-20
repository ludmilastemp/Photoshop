#ifndef CONFIGPHOTOSHOP
#define CONFIGPHOTOSHOP

const int kWidthWindow  = 800;//1920;
const int kHeightWindow = 600;//1080;

const int kHalfWidthWindow  = kWidthWindow / 2;
const int kHalfHeightWindow = kHeightWindow / 2;

const int kWidthCanvas  = 600;
const int kHeightCanvas = 400;
const int kWidthCanvasCorner  = 57;
const int kHeightCanvasCorner = 95;

const int kWidthColor  = 53;
const int kHeightColor = 53;
const int kWidthColorCorner  = 2;
const int kHeightColorCorner = 450; //861;

const int kCanvasXBegin = kWidthCanvasCorner;
const int kCanvasXEnd   = kWidthCanvasCorner + kWidthCanvas;
const int kCanvasYBegin = kHeightCanvasCorner;
const int kCanvasYEnd   = kWidthCanvasCorner + kHeightCanvas;

const int kWidthToolbar  = 57;
const int kHeightToolbar = 300;
const int kWidthToolbarCorner  = 6;
const int kHeightToolbarCorner = 95;

const int kWidthFilterbarCorner  = 361;
const int kHeightFilterbarCorner = 40;
const int kWidthFilterIcon  = 150;
const int kHeightFilterIcon = 37;
const int kFilterOffset = 0;

const int kWidthParameterManagerCorner  = 66;
const int kHeightParameterManagerCorner = 50;
const int kWidthParameterManager  = kWidthWindow - kWidthParameterManagerCorner;
const int kHeightParameterManager = 45;

const int kWidthIcon  = 47;
const int kHeightIcon = 47;
const int kOffsetIcon = 0;

const int kWidthParam  = 60;
const int kHeightParam = 45;
const int kOffsetParam = 0;

#endif /* CONFIGPHOTOSHOP */

// 57 | 63 |  83 |  76 |  82 |  72 |  69 | 102 | 75
// 0  | 57 | 120 | 203 | 279 | 361 | 433 | 502 | 604