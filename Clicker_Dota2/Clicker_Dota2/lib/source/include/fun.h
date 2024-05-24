#pragma once
#include "include.h"
void print(std::string text);
bool GetPause();
void ShopItem(std::string item);
void InputKey(WORD key);
bool TimerStart(int seconds);
bool CloseWindows();
void PrintCords(PointF point);
BOOL CALLBACK GetAllWindowsNameDota(HWND hwnd, LPARAM lParam);
void MoveTargetPersonal(PointF point, HWND targetWindow);
void MouseOfclick(PointF point, HWND targetWindwo);
int Random(int min, int max);
void KeyDown(WORD key);
void KeyUp(WORD key);
void SerchWindwos(std::vector<HWND>& refWindows);
void ThreadKeyBoard();
void ThreadTime();
bool GetRashenSpawnDark();
bool GetRashenSpawnLight();
int DeltaTime();
int TwoMinutsTimer();
bool IsDeBug();
int FarmTime();


