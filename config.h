#ifndef CONFIGPHOTOSHOP
#define CONFIGPHOTOSHOP

const int kWidthWindow  = 800;
const int kHeightWindow = 550;

const int kHalfWidthWindow  = kWidthWindow / 2;
const int kHalfHeightWindow = kHeightWindow / 2;

const int kWidthCanvas  = 600;
const int kHeightCanvas = 400;
const int kWidthCanvasCorner  = 100;
const int kHeightCanvasCorner = 100;

const int kCanvasXBegin =                kWidthCanvasCorner;
const int kCanvasXEnd   = kWidthWindow - kWidthCanvasCorner;
const int kCanvasYBegin =                 kHeightCanvasCorner;
const int kCanvasYEnd   = kHeightWindow - kHeightCanvasCorner;

const int kWidthToolbar  = 50;
const int kHeightToolbar = 400;
const int kWidthToolbarCorner  = 25;
const int kHeightToolbarCorner = 100;

const int kWidthParameterManager  = 50;
const int kHeightParameterManager = 400;
const int kWidthParameterManagerCorner  = 725;
const int kHeightParameterManagerCorner = 100;

const int kWidthIcon  = 50;
const int kHeightIcon = 50;
const int kOffsetIcon = 10;

#endif /* CONFIGPHOTOSHOP */