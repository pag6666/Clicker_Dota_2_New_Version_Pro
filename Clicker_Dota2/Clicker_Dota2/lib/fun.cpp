#include "source/include/fun.h"
bool closingWindwos = false;
bool pause = false;
const char OrderMyItem = '2';
const char OpenOrCloseShop = 'L';
const int INPUTSEND = 1;
const wchar_t* GameWindwosName = L"Dota 2";
const char Atack_Key = 'A';
int timercount = 0;
int twoMinutsTimer = 0;
int key_st = 0x8000;
bool is_debug = true;
bool is_press_key_rashen_dark = false;
bool is_press_key_rashen_light = false;
void InputKey(WORD key) 
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.wScan = MapVirtualKey(key, MAPVK_VK_TO_VSC);
    input.ki.dwFlags = {0};
    input.ki.time = {0};
    input.ki.dwExtraInfo = {0};

    SendInput(INPUTSEND, &input, sizeof(INPUT));
    Sleep(10);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(INPUTSEND, &input, sizeof(INPUT));
}
bool TimerStart(int seconds) 
{
    return false;
}
bool IsDeBug() 
{
    return is_debug;
}
int TwoMinutsTimer() 
{
    return twoMinutsTimer;
}
int ninetime = 0;
int nineMinutsTimer() 
{
    return ninetime;
}
int farmtime = 0;
int FarmTime() 
{
    return farmtime;
}
void print(std::string text) 
{
    std::cout << text << std::endl;
}
bool GetRashenSpawnDark() 
{
    return is_press_key_rashen_dark;
}
bool GetRashenSpawnLight() 
{
    return is_press_key_rashen_light;
}
bool CloseWindows() 
{
    return closingWindwos;
}
void PrintCords(PointF point) 
{
    std::cout << "X = " << point.GetX() << " Y = " << point.GetY() << std::endl;
}
void ShopItem(std::string item) 
{
    InputKey(OpenOrCloseShop);
    Sleep(30);
    InputKey('V');
    Sleep(30);

    std::string name_item = item;
    for (int i = 0; i < name_item.length(); i++)
    {
        InputKey((WORD)name_item[i]);
        Sleep(30);
    }
    Sleep(100);
    InputKey(VK_RETURN);
    Sleep(100);
    InputKey(VK_ESCAPE);
    Sleep(50);
    InputKey(VK_ESCAPE);
    InputKey(OrderMyItem);
}
BOOL CALLBACK GetAllWindowsNameDota(HWND hwnd, LPARAM lParam) 
{
    const wchar_t* targetWindowTitle = GameWindwosName;
    std::vector<HWND>* pWindows = reinterpret_cast<std::vector<HWND>*>(lParam);
    int length = GetWindowTextLength(hwnd);
    if (length == 0) return TRUE; 
    std::wstring windowTitle(length + 1, L'\0');
    GetWindowText(hwnd, &windowTitle[0], length + 1);
    wchar_t buffer[MAX_PATH];
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    DWORD size = (sizeof(buffer) / sizeof(wchar_t));
    QueryFullProcessImageName(process, 0, buffer, &size);
    std::wstring process_name = L"";
    std::wstring fullPath = buffer;
    size_t pos = fullPath.find_last_of(L"\\");
    if (pos != std::wstring::npos) {
        process_name = fullPath.substr(pos + 1);
    }


    if (((windowTitle.find(targetWindowTitle) != std::wstring::npos)  && (process_name == L"dota2.exe" || process_name == L"dota 2 emull.exe"))) {
        std::wcout << L"windows index = /" << process_name<< "/ windwos name = " << windowTitle << std::endl;
        pWindows->push_back(hwnd);
    }

    return TRUE;
}
void MoveTargetPersonal(PointF point, HWND targetWindow) 
{
    RECT windowRect;
    GetWindowRect(targetWindow, &windowRect);


    int move_x = windowRect.left + point.GetX();
    int move_y = windowRect.top + point.GetY();
    point.SetX(move_x);
    point.SetY(move_y);
    SetForegroundWindow(targetWindow);
    
    Sleep(100);
    InputKey(Atack_Key);
    MouseOfclick(point, targetWindow);
}
void MouseOfclick(PointF point, HWND targetWindow)
{
    RECT windowRect;
    GetWindowRect(targetWindow, &windowRect);
    SetCursorPos(point.GetX(), point.GetY());
    Sleep(50);
    ClipCursor(&windowRect);
    Sleep(50);
    SetCursorPos(point.GetX(), point.GetY());
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    ClipCursor(NULL);
}
int Random(int min, int max) 
{
    int result = 1;
    int random = (max - min);
    if (random == 0) {
        result = 1;
    }
    else 
    {
        result = random;
    }
    return  min + rand() % result;
}
void KeyDown(WORD key) 
{
    INPUT keydown = {};
    keydown.type = INPUT_KEYBOARD;
    keydown.ki.wVk = key;
    keydown.ki.wScan = MapVirtualKey(key, MAPVK_VK_TO_VSC);
    keydown.ki.dwFlags = 0;
    keydown.ki.time = 0;
    keydown.ki.dwExtraInfo = 0;
    SendInput(1, &keydown, sizeof(INPUT));
    Sleep(10);
}
void KeyUp(WORD key) 
{
    INPUT keydown = {};
    keydown.type = INPUT_KEYBOARD;
    keydown.ki.wVk = key;
    keydown.ki.wScan = MapVirtualKey(key, MAPVK_VK_TO_VSC);
    keydown.ki.dwFlags = KEYEVENTF_KEYUP;
    keydown.ki.time = 0;
    keydown.ki.dwExtraInfo = 0;
    SendInput(1, &keydown, sizeof(INPUT));
    Sleep(10);
}
void SerchWindwos(std::vector<HWND>& refWindows)
{
    EnumWindows(GetAllWindowsNameDota, reinterpret_cast<LPARAM>(&refWindows));

    //
    if (refWindows.size() > 0) {
        for (int i = 0; i < refWindows.size(); ++i) {
            for (int j = i + 1; j < refWindows.size(); j++) {
                RECT windowRect1;
                RECT windowRect2;
                GetWindowRect(refWindows[i], &windowRect1);
                GetWindowRect(refWindows[j], &windowRect2);
                if (windowRect1.top > windowRect2.top) {
                    HWND temp = refWindows[i];
                    refWindows[i] = refWindows[j];
                    refWindows[j] = temp;
                }
            }
        }
    }
}
void ThreadKeyBoard() 
{
    while (!CloseWindows())
    {
        if (GetAsyncKeyState('1') & key_st)
        {
            pause = true;
        }
        if (GetAsyncKeyState('2') & key_st)
        {
            pause = false;
        }
        if (GetAsyncKeyState('0') & key_st)
        {
            closingWindwos = true;
        }
        if (GetAsyncKeyState('8') & key_st)
        {
            //rashen dk
            is_press_key_rashen_dark = true;
            is_press_key_rashen_light = false;
        }
        if (GetAsyncKeyState('9') & key_st)
        {
            //rashen lt
            is_press_key_rashen_light = true;
            is_press_key_rashen_dark = false;
        }
        if (GetAsyncKeyState('5') & key_st)
        {
            is_press_key_rashen_light = false;
            is_press_key_rashen_dark = false;
        }
        if (GetAsyncKeyState('3') & key_st)
        {
            is_debug = true;
        }
        if (GetAsyncKeyState('4') & key_st)
        {
            is_debug = false;
        }
        Sleep(100);
    }
}
int DeltaTime() 
{
    return timercount;
}
void ThreadTime() 
{
    if (!GetPause()) {
        while (!CloseWindows())
        {
            if (twoMinutsTimer >= (60 * 2) + 15)
            {
                twoMinutsTimer = 0;
            }
            if (farmtime >= 30)
            {
                farmtime = 0;
            }
            if (ninetime >= (60 * 14))
            {
                ninetime = 0;
            }
            ninetime++;
            farmtime++;
            twoMinutsTimer++;
            timercount++;
            Sleep(1000);
        }
    }
    else 
    {
        Sleep(500);
    }
}
bool GetPause() 
{
    return pause;
}
