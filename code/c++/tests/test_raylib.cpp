#include <raylib.h>

#include <iostream>
using namespace std;

class WinApp {
 public:
  WinApp() : pos(50), fps_(60), width_(1200), height_(800), title_("window") {
    init();
  }
  WinApp(int screenWidth, int screenHeight, string title)
      : pos(50),
        fps_(60),
        width_(screenWidth),
        height_(screenHeight),
        title_(title) {
    init();
  }
  ~WinApp() { CloseWindow(); }

  void Start() {
    while (!WindowShouldClose()) {
      Update();
    }
  }

  void Update() {
    static int direct = 1;
    BeginDrawing();

    ClearBackground(GRAY);
    DrawText("Hello, World!", 190, 200, 50, WHITE);
    DrawCircle(pos, 100, 50, BLUE);
    DrawRectangle(100, 200, 50, 50, RED);

    pos += direct;
    if (pos >= 500 || pos < 50) direct *= -1;

    EndDrawing();
  }

 private:
  void init() {
    InitWindow(width_, height_, title_.c_str());
    SetTargetFPS(fps_);
  }

 private:
  int pos;

  int fps_;
  int width_;
  int height_;
  string title_;
}; 
 
int main(void) {
  WinApp app;

  app.Start(); 
  return 0;
}