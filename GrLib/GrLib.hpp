#ifndef STL_GrLib
#define STL_GrLib

#include "GrLibCtx.hpp"
#include "vectors/vectorDec.hpp"

bool IsWindowOpen          (GraphicsCtx& ctx);
bool CheckEventCloseWindow (GraphicsCtx& ctx);
void DisplayWindow         (GraphicsCtx& ctx);
void CleanWindow           (GraphicsCtx& ctx);

#endif /* STL_GrLib */