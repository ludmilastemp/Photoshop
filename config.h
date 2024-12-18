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

const int kCanvasXBegin = kWidthCanvasCorner;
const int kCanvasXEnd   = kWidthCanvasCorner + kWidthCanvas;
const int kCanvasYBegin = kHeightCanvasCorner;
const int kCanvasYEnd   = kWidthCanvasCorner + kHeightCanvas;

const int kWidthToolbar  = 57;
const int kHeightToolbar = 400;
const int kWidthToolbarCorner  = 6;
const int kHeightToolbarCorner = 95;

const int kWidthParameterManager  = 50;
const int kHeightParameterManager = 400;
const int kWidthParameterManagerCorner  = 725;
const int kHeightParameterManagerCorner = 100;

const int kWidthIcon  = 47;
const int kHeightIcon = 47;
const int kOffsetIcon = 0;

#endif /* CONFIGPHOTOSHOP */

// 57 | 63 |  83 |  76 |  82 |  72 |  69 | 102 | 75
// 0  | 57 | 120 | 203 | 279 | 361 | 433 | 502 | 604