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

const int kScale = 50, kMargin = 10;
const int kCanvasSize = 3 * kScale + kMargin;
const array<Vector3D<int>, 8> kCube{{
  { 1,  1,  1}, { 1,  1, -1}, { 1, -1,  1}, { 1, -1, -1},
  {-1,  1,  1}, {-1,  1, -1}, {-1, -1,  1}, {-1, -1, -1}
}};
const array<array<int, 4>, 6> kSurface{{
 {0,4,6,2}, {1,3,7,5}, {0,2,3,1}, {0,1,5,4}, {4,5,7,6}, {6,7,3,2}
}};
const array<uint32_t, kSurface.size()> kColor{
  0xff0000, 0x00ff00, 0xffff00, 0x0000ff, 0xff00ff, 0x00ffff
};

array<Vector3D<double>, kCube.size()> vert;
array<double, kSurface.size()> centerz4;
array<Vector2D<int>, kCube.size()> scr;
// #@@range_end(constants)

// #@@range_begin(main)
extern "C" void main(int argc, char** argv) {
  auto [layer_id, err_openwin]
    = SyscallOpenWindow(kCanvasSize + 8, kCanvasSize + 28, 10, 10, "cube");
  if (err_openwin) {
    exit(err_openwin);
  }
