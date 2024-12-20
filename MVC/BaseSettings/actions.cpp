// #include "menu.hpp"

// bool ActionFilter::call (Event event)
// {
//     // int x = event.getCoord().x;
//     // int y = event.getCoord().y;

//     int y = event.getCoord().y;

//     if (y / (kHeightIcon + kOffsetIcon) < modelCanvas.toolbar.getSize() && 
//         y % (kHeightIcon + kOffsetIcon) <= kHeightIcon)
//     {
//         int object = y / (kHeightIcon + kOffsetIcon);
//         printf ("setActiveTool %d\n", object);
//         if (modelCanvas.toolbar.activeObject == object)
//         {
//             modelCanvas.setActiveTool (-1);
//         }
//         else
//         {
//             modelCanvas.setActiveTool (object);
//         }
//         return true;
//     }
//     return false;

//     if (0 * 36 < y && y < 1 * 36)
//     {
//         Blur (modelCanvas);
//         return true;
//     }
//     if (1 * 36 < y && y < 2 * 36)
//     {
//         GaussianBlur (modelCanvas);
//         return true;
//     }
//     if (2 * 36 < y && y < 3 * 36)
//     {
//         UnsharpMask (modelCanvas);
//         return true;
//     }
//     if (3 * 36 < y && y < 4 * 36)
//     {
//         Invert (modelCanvas);
//         return true;
//     }
//     if (4 * 36 < y && y < 5 * 36)
//     {
//         Brightness (modelCanvas);
//         return true;
//     }
//     if (5 * 36 < y && y < 6 * 36)
//     {
//         Contrast (modelCanvas);
//         return true;
//     }
//     return false;
// }