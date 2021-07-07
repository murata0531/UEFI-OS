#include <array>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include "../syscall.h"

using namespace std;

const int kNumBlocksX = 10, kNumBlocksY = 5;
const int kBlockWidth = 20, kBlockHeight = 10;
const int kBarWidth = 30, kBarHeight = 5, kBallRadius = 5;
const int kGapWidth = 30, kGapHeight = 30, kGapBar = 80, kBarFloat = 10;

const int kCanvasWidth = kNumBlocksX * kBlockWidth + 2 * kGapWidth;
const int kCanvasHeight = kGapHeight + kNumBlocksY * kBlockHeight
                          + kGapBar + kBarHeight + kBarFloat;
const int kBarY = kCanvasHeight - kBarFloat - kBarHeight;

const int kFrameRate = 60; // frames/sec
const int kBarSpeed = kCanvasWidth / 2; // pixels/sec
const int kBallSpeed = kBarSpeed;

array<bitset<kNumBlocksX>, kNumBlocksY> blocks;

void DrawBlocks(uint64_t layer_id) {
  for (int by = 0; by < kNumBlocksY; ++by) {
    const int y = 24 + kGapHeight + by * kBlockHeight;
    const uint32_t color = 0xff << (by % 3) * 8;

    for (int bx = 0; bx < kNumBlocksX; ++bx) {
      if (blocks[by][bx]) {
        const int x = 4 + kGapWidth + bx * kBlockWidth;
        const uint32_t c = color | (0xff << ((bx + by) % 3) * 8);
        SyscallWinFillRectangle(layer_id, x, y, kBlockWidth, kBlockHeight, c);
      }
    }
  }
}

void DrawBar(uint64_t layer_id, int bar_x) {
  SyscallWinFillRectangle(layer_id,
                          4 + bar_x, 24 + kBarY,
                          kBarWidth, kBarHeight, 0xffffff);
}

void DrawBall(uint64_t layer_id, int x, int y) {
  SyscallWinFillRectangle(layer_id,
                          4 + x - kBallRadius, 24 + y - kBallRadius,
                          2 * kBallRadius, 2 * kBallRadius, 0x007f00);
  SyscallWinFillRectangle(layer_id,
                          4 + x - kBallRadius/2, 24 + y - kBallRadius/2,
                          kBallRadius, kBallRadius, 0x00ff00);
}