#include <array>
#include <cmath>
#include <cstdlib>
#include "../syscall.h"

// #@@range_begin(constants)
using namespace std;

template <class T>
struct Vector3D {
  T x, y, z;
};

template <class T>
struct Vector2D {
  T x, y;
};

void DrawObj(uint64_t layer_id);
void DrawSurface(uint64_t layer_id, int sur);
bool Sleep(unsigned long ms);