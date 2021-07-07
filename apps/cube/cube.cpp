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

  int thx = 0, thy = 0, thz = 0;
  const double to_rad = 3.14159265358979323 / 0x8000;
  for (;;) {
    // 立方体を X, Y, Z 軸回りに回転
    thx = (thx + 182) & 0xffff;
    thy = (thy + 273) & 0xffff;
    thz = (thz + 364) & 0xffff;
    const double xp = cos(thx * to_rad), xa = sin(thx * to_rad);
    const double yp = cos(thy * to_rad), ya = sin(thy * to_rad);
    const double zp = cos(thz * to_rad), za = sin(thz * to_rad);
    for (int i = 0; i < kCube.size(); i++) {
      const auto cv = kCube[i];
      const double zt = kScale*cv.z * xp + kScale*cv.y * xa;
      const double yt = kScale*cv.y * xp - kScale*cv.z * xa;
      const double xt = kScale*cv.x * yp + zt          * ya;
      vert[i].z       = zt          * yp - kScale*cv.x * ya;
      vert[i].x       = xt          * zp - yt          * za;
      vert[i].y       = yt          * zp + xt          * za;
    }

    // 面中心の Z 座標（を 4 倍した値）を 6 面について計算
    for (int sur = 0; sur < kSurface.size(); ++sur) {
      centerz4[sur] = 0;
      for (int i = 0; i < kSurface[sur].size(); ++i) {
        centerz4[sur] += vert[kSurface[sur][i]].z;
      }
    }

    // 画面を一旦クリアし，立方体を描画
    SyscallWinFillRectangle(layer_id | LAYER_NO_REDRAW,
                            4, 24, kCanvasSize, kCanvasSize, 0);
    DrawObj(layer_id | LAYER_NO_REDRAW);
    SyscallWinRedraw(layer_id);
    if (Sleep(50)) {
      break;
    }
  }

  SyscallCloseWindow(layer_id);
  exit(0);
}
// #@@range_end(main)
