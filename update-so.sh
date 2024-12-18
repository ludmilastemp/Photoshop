g++ -shared plugins/brush.cpp  -o so/brush.so -fPIC
g++ -shared plugins/eraser.cpp -o so/eraser.so -fPIC
g++ -shared plugins/line.cpp   -o so/line.so -fPIC
g++ -shared plugins/tree.cpp   -o so/tree.so -fPIC