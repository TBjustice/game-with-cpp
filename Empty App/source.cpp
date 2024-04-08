#define NOMINMAX
#include <Windows.h>


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  if (msg == WM_DESTROY) {
    PostQuitMessage(0);
    return 0;
  } else {
    return DefWindowProcW(hwnd, msg, wp, lp);
  }
}

BOOL RegisterApplication(const wchar_t* window_id, WNDPROC window_proc) {
  WNDCLASSEXW wc;
  wc.cbSize = sizeof(WNDCLASSEXW);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  wc.lpfnWndProc = window_proc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = GetModuleHandleW(NULL);
  wc.hIcon = (HICON)LoadIconW(NULL, IDI_APPLICATION);
  wc.hCursor = (HCURSOR)LoadCursorW(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = window_id;
  wc.hIconSm = (HICON)LoadImageW(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0,
                                 LR_DEFAULTSIZE | LR_SHARED);
  return (RegisterClassExW(&wc));
}

int main(void) {
  const wchar_t* windowid = L"MyFirstApp";
  if (!RegisterApplication(windowid, WndProc)) return 1;
  HWND hwnd = CreateWindowW(windowid, L"Title", WS_OVERLAPPEDWINDOW, 0, 0, 600,
                            400, NULL, NULL, GetModuleHandleW(NULL), NULL);

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);

  MSG msg;
  BOOL value;
  while (true) {
    value = GetMessageW(&msg, NULL, 0, 0);
    if (value == 0) break;
    if (value == -1) return 1;

    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  return msg.wParam;
}
