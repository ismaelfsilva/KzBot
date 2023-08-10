#include <codecvt>
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <Psapi.h>
#include "kzhelper.h"
#include <Qt>
#include <map>

#include "../Settings/globals.h"
#include "../Objects/client.h"

bool Util::KzHelper::ReadMemory(HANDLE &handle, uint32_t address, LPVOID lpBuffer, DWORD_PTR dwSize) {
    return ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), lpBuffer, dwSize, NULL) == TRUE;
}

uint8_t Util::KzHelper::ReadMemoryByte(HANDLE &handle, uint32_t address) {
    uint8_t value;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &value, sizeof(value), NULL);
    return value;
}

std::vector<uint8_t> ReadBytes(HANDLE handle, uintptr_t address, uint32_t bytesToRead)
{
    std::vector<uint8_t> buffer(bytesToRead);
    SIZE_T bytesRead;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &buffer[0], bytesToRead, &bytesRead);
    return buffer;
}


int16_t Util::KzHelper::ReadMemoryInt16(HANDLE &handle, uint32_t address) {
    int16_t value;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &value, sizeof(value), NULL);
    return value;
}

int32_t Util::KzHelper::ReadMemoryInt32(HANDLE &handle, uint32_t address) {
    int32_t value;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &value, sizeof(value), NULL);
    return value;
}

int64_t Util::KzHelper::ReadMemoryInt64(HANDLE &handle, uint32_t address) {
    int64_t value;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &value, sizeof(value), NULL);
    return value;
}


uint16_t Util::KzHelper::ReadMemoryUInt16(HANDLE &handle, uint32_t address) {
    uint16_t value;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &value, sizeof(value), NULL);
    return value;
}

uint32_t Util::KzHelper::ReadMemoryUInt32(HANDLE &handle, uint32_t address) {
    uint32_t value;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &value, sizeof(value), NULL);
    return value;
}

void Util::KzHelper::WriteMemoryUInt32(HANDLE &handle, uint32_t address, uint32_t value) {
    WriteProcessMemory(handle, reinterpret_cast<LPVOID>(address), &value, sizeof(value), nullptr);
}

void Util::KzHelper::WriteMemoryByte(HANDLE &handle, uint32_t address, uint8_t value) {
    WriteProcessMemory(handle, reinterpret_cast<LPVOID>(address), &value, sizeof(value), nullptr);
}

void Util::KzHelper::WriteMemoryInt32(HANDLE &handle, uint32_t address, int32_t value) {
    WriteProcessMemory(handle, reinterpret_cast<LPVOID>(address), &value, sizeof(value), nullptr);
}

uint64_t Util::KzHelper::ReadMemoryUInt64(HANDLE &handle, uint32_t address) {
    uint64_t value;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &value, sizeof(value), NULL);
    return value;
}

float Util::KzHelper::ReadMemoryFloat(HANDLE &handle, uint32_t address) {
    float value;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &value, sizeof(value), NULL);
    return value;
}

double Util::KzHelper::ReadMemoryDouble(HANDLE &handle, uint32_t address) {
    double value;
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), &value, sizeof(value), NULL);
    return value;
}

std::string Util::KzHelper::ReadMemoryString(HANDLE &handle, uint32_t address) {
    char buffer[1024];
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), buffer, sizeof(buffer), NULL);
    return std::string(buffer);
}

std::string Util::KzHelper::ReadMemoryStringUnicode(HANDLE &handle, uint32_t address) {
    wchar_t buffer[1024];
    ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(address), buffer, sizeof(buffer), NULL);

    int len = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, NULL, 0, NULL, NULL);
    char* mbBuffer = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, buffer, -1, mbBuffer, len, NULL, NULL);

    std::string result(mbBuffer);

    delete[] mbBuffer;

    return result;
}
void Util::KzHelper::WriteMemoryString(HANDLE &handle, uint32_t address, std::string value)
{
    SIZE_T bytesWritten = 0;
    WriteProcessMemory(handle, reinterpret_cast<LPVOID>(address), value.c_str(), value.size(), &bytesWritten);
}

void Util::KzHelper::WriteMemoryStringUnicode(HANDLE &handle, uint32_t address, std::string value)
{
    int length = MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, nullptr, 0);
    std::wstring unicodeString(length - 1, L'\0');  // Excluindo o caractere nulo de terminação

    MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, &unicodeString[0], length - 1);

    SIZE_T bytesWritten = 0;
    WriteProcessMemory(handle, reinterpret_cast<LPVOID>(address), unicodeString.c_str(), unicodeString.size() * sizeof(wchar_t), &bytesWritten);
}

uint32_t Util::KzHelper::GetProcessBaseAddress( DWORD processID )
{
    DWORD_PTR   baseAddress = 0;
    HANDLE      &processHandle = Globals::getHandle();
    HMODULE     *moduleArray;
    LPBYTE      moduleArrayBytes;
    DWORD       bytesRequired;

    if ( processHandle )
    {
        if ( EnumProcessModules( processHandle, NULL, 0, &bytesRequired ) )
        {
            if ( bytesRequired )
            {
                moduleArrayBytes = (LPBYTE)LocalAlloc( LPTR, bytesRequired );

                if ( moduleArrayBytes )
                {
                    moduleArray = (HMODULE *)moduleArrayBytes;

                    if ( EnumProcessModules( processHandle, moduleArray, bytesRequired, &bytesRequired ) )
                    {
                        baseAddress = (DWORD_PTR)moduleArray[0];
                    }

                    LocalFree( moduleArrayBytes );
                }
            }
        }
    }

    return baseAddress;
}



BOOL CALLBACK Util::KzHelper::EnumWindowsCallback(HWND hWnd, LPARAM lParam)
{
    auto windowList = reinterpret_cast<std::vector<HWND>*>(lParam);
    if (IsWindowVisible(hWnd))
        windowList->push_back(hWnd);

    return TRUE;
}
std::vector<HWND> Util::KzHelper::getWindows()
{
    std::vector<HWND> windows;
    EnumWindows(&Util::KzHelper::EnumWindowsCallback, reinterpret_cast<LPARAM>(&windows));

    return windows;
}
std::vector<HWND> Util::KzHelper::getWindowsByTitle(std::string title, bool startsWith = false)
{
    std::vector<HWND> foundWindows;

    std::vector<HWND> windows;
    EnumWindows(&Util::KzHelper::EnumWindowsCallback, reinterpret_cast<LPARAM>(&windows));

    for (HWND &window : windows)
    {
        std::string windowTitle = Util::KzHelper::getWindowTitle(window);
        if ((windowTitle == title) || (startsWith && windowTitle.rfind(title, 0) != std::string::npos))
            foundWindows.push_back(window);
    }

    return foundWindows;
}
HWND Util::KzHelper::getWindowById(DWORD pId)
{
    std::vector<HWND> windows;
    EnumWindows(&Util::KzHelper::EnumWindowsCallback, reinterpret_cast<LPARAM>(&windows));

    for (HWND &window : windows)
    {
        if (Util::KzHelper::getWindowProcessId(window) == pId)
            return window;
    }

    return 0;
}
std::string Util::KzHelper::getWindowTitle(HWND hwnd)
{
    int length = GetWindowTextLength(hwnd);
    if (length == 0)
        return "";

    DWORD bufferSize = GetWindowTextLength(hwnd) + 1;
    wchar_t* windowTitleBuffer = new wchar_t[bufferSize];
    GetWindowText(hwnd, windowTitleBuffer, bufferSize);
    std::wstring ws(windowTitleBuffer);
    std::string str(ws.begin(), ws.end());

    delete[] windowTitleBuffer;

    return str;
}
DWORD Util::KzHelper::getWindowProcessId(HWND hwnd)
{
    DWORD id;
    GetWindowThreadProcessId(hwnd, &id);

    return id;
}
std::filesystem::path Util::KzHelper::getWindowPath(HWND hwnd)
{
    DWORD id = Util::KzHelper::getWindowProcessId(hwnd);

    wchar_t* path = new wchar_t[MAX_PATH];
    DWORD size = MAX_PATH;
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, id);
    QueryFullProcessImageNameW(hProc, 0, path, &size);
    CloseHandle(hProc);

    return path;
}

void Util::KzHelper::SendKey(uint32_t key, bool extended)
{
    SendMessage(Globals::getHWnd(), WM_KEYDOWN, key, getlParam(key, false, extended));
    SendMessage(Globals::getHWnd(), WM_KEYUP, key, getlParam(key, true, extended));
}

void Util::KzHelper::LeftClick(int x, int y)
{
    uint32_t lParam = MAKELPARAM(x, y);
    SendMessage(Globals::getHWnd(), WM_MOUSEMOVE, 0x0, lParam);
    SendMessage(Globals::getHWnd(), WM_LBUTTONDOWN, MK_LBUTTON, lParam);
    SendMessage(Globals::getHWnd(), WM_MOUSEMOVE, 0x0, lParam);
    SendMessage(Globals::getHWnd(), WM_LBUTTONUP, 0x0, lParam);
}

void Util::KzHelper::LeftClick(Point* p)
{
    if (p == nullptr)
        return;
    uint32_t lParam = MAKELPARAM(p->x, p->y);
    SendMessage(Globals::getHWnd(), WM_MOUSEMOVE, 0x0, lParam);
    SendMessage(Globals::getHWnd(), WM_LBUTTONDOWN, MK_LBUTTON, lParam);
    SendMessage(Globals::getHWnd(), WM_MOUSEMOVE, 0x0, lParam);
    SendMessage(Globals::getHWnd(), WM_LBUTTONUP, 0x0, lParam);
}

void Util::KzHelper::RightClick(int x, int y)
{
    uint32_t lParam = MAKELPARAM(x, y);
    SendMessage(Globals::getHWnd(), WM_MOUSEMOVE, 0x0, lParam);
    SendMessage(Globals::getHWnd(), WM_RBUTTONDOWN, MK_RBUTTON, lParam);
    SendMessage(Globals::getHWnd(), WM_MOUSEMOVE, 0x0, lParam);
    SendMessage(Globals::getHWnd(), WM_RBUTTONUP, 0x0, lParam);
}

void Util::KzHelper::RightClick(Point* p)
{
    if (p == nullptr)
        return;
    uint32_t lParam = MAKELPARAM(p->x, p->y);
    SendMessage(Globals::getHWnd(), WM_MOUSEMOVE, 0x0, lParam);
    SendMessage(Globals::getHWnd(), WM_RBUTTONDOWN, MK_RBUTTON, lParam);
    SendMessage(Globals::getHWnd(), WM_MOUSEMOVE, 0x0, lParam);
    SendMessage(Globals::getHWnd(), WM_RBUTTONUP, 0x0, lParam);
}

void Util::KzHelper::SendText(std::string text, bool lockKeyboard)
{
    if (lockKeyboard)
    {
        BlockInput(true);
        Sleep(1);
    }

    SendMessage(Globals::getHWnd(), WM_KEYDOWN, VK_RETURN, 0x0);
    SendMessage(Globals::getHWnd(), WM_KEYUP, VK_RETURN, 0x0);
    Sleep(1);

    for (char c : text)
        SendMessage(Globals::getHWnd(), WM_CHAR, c, 0);

    Sleep(1);

    SendMessage(Globals::getHWnd(), WM_KEYDOWN, VK_RETURN, 0x0);
    SendMessage(Globals::getHWnd(), WM_KEYUP, VK_RETURN, 0x0);

    if (lockKeyboard)
    {
        BlockInput(false);
        Sleep(1);
    }
}

uint32_t Util::KzHelper::qtKeyToVK(uint32_t key, bool& extended)
{
    uint32_t modifiers = 0; // Inicialize os modificadores como zero

    // Verifique se os modificadores estão presentes na chave
    if (key & Qt::ShiftModifier)
        return 0;
        //modifiers |= VK_SHIFT;
    if (key & Qt::ControlModifier)
        return 0;
        //modifiers |= VK_CONTROL;
    if (key & Qt::AltModifier)
        return 0;
        //modifiers |= VK_MENU;
    if (key & Qt::MetaModifier)
        modifiers |= VK_LWIN;

    if (key & Qt::KeypadModifier)
        extended = true;

    // Remova os modificadores da chave para obter a chave pura
    key &= ~(Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier | Qt::KeypadModifier);

    switch (key)
    {
    case Qt::Key_Escape:
        return VK_ESCAPE;
    case Qt::Key_Tab:
    case Qt::Key_Backtab:
        return VK_TAB;
    case Qt::Key_Backspace:
        return VK_BACK;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        return VK_RETURN;
    case Qt::Key_Insert:
        return VK_INSERT;
    case Qt::Key_Delete:
        return VK_DELETE;
    case Qt::Key_Pause:
        return VK_PAUSE;
    case Qt::Key_Print:
        return VK_PRINT;
    case Qt::Key_Clear:
        return VK_CLEAR;
    case Qt::Key_Home:
        return VK_HOME;
    case Qt::Key_End:
        return VK_END;
    case Qt::Key_Left:
        return VK_LEFT;
    case Qt::Key_Up:
        return VK_UP;
    case Qt::Key_Right:
        return VK_RIGHT;
    case Qt::Key_Down:
        return VK_DOWN;
    case Qt::Key_PageUp:
        return VK_PRIOR;
    case Qt::Key_PageDown:
        return VK_NEXT;
    case Qt::Key_F1:
        return VK_F1;
    case Qt::Key_F2:
        return VK_F2;
    case Qt::Key_F3:
        return VK_F3;
    case Qt::Key_F4:
        return VK_F4;
    case Qt::Key_F5:
        return VK_F5;
    case Qt::Key_F6:
        return VK_F6;
    case Qt::Key_F7:
        return VK_F7;
    case Qt::Key_F8:
        return VK_F8;
    case Qt::Key_F9:
        return VK_F9;
    case Qt::Key_F10:
        return VK_F10;
    case Qt::Key_F11:
        return VK_F11;
    case Qt::Key_F12:
        return VK_F12;
    case Qt::Key_F13:
        return VK_F13;
    case Qt::Key_F14:
        return VK_F14;
    case Qt::Key_F15:
        return VK_F15;
    case Qt::Key_F16:
        return VK_F16;
    case Qt::Key_F17:
        return VK_F17;
    case Qt::Key_F18:
        return VK_F18;
    case Qt::Key_F19:
        return VK_F19;
    case Qt::Key_F20:
        return VK_F20;
    case Qt::Key_F21:
        return VK_F21;
    case Qt::Key_F22:
        return VK_F22;
    case Qt::Key_F23:
        return VK_F23;
    case Qt::Key_F24:
        return VK_F24;
    case Qt::Key_Space:
        return VK_SPACE;
    case Qt::Key_Asterisk:
        return VK_MULTIPLY;
    case Qt::Key_Plus:
        return VK_ADD;
    case Qt::Key_Comma:
        return VK_SEPARATOR;
    case Qt::Key_Minus:
        return VK_SUBTRACT;
    case Qt::Key_Slash:
        return VK_DIVIDE;
    case Qt::Key_MediaNext:
        return VK_MEDIA_NEXT_TRACK;
    case Qt::Key_MediaPrevious:
        return VK_MEDIA_PREV_TRACK;
    case Qt::Key_MediaPlay:
        return VK_MEDIA_PLAY_PAUSE;
    case Qt::Key_MediaStop:
        return VK_MEDIA_STOP;
        // couldn't find those in VK_*
        //case Qt::Key_MediaLast:
        //case Qt::Key_MediaRecord:
    case Qt::Key_VolumeDown:
        return VK_VOLUME_DOWN;
    case Qt::Key_VolumeUp:
        return VK_VOLUME_UP;
    case Qt::Key_VolumeMute:
        return VK_VOLUME_MUTE;

        // numbers
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        return key;

        // letters
    case Qt::Key_A:
    case Qt::Key_B:
    case Qt::Key_C:
    case Qt::Key_D:
    case Qt::Key_E:
    case Qt::Key_F:
    case Qt::Key_G:
    case Qt::Key_H:
    case Qt::Key_I:
    case Qt::Key_J:
    case Qt::Key_K:
    case Qt::Key_L:
    case Qt::Key_M:
    case Qt::Key_N:
    case Qt::Key_O:
    case Qt::Key_P:
    case Qt::Key_Q:
    case Qt::Key_R:
    case Qt::Key_S:
    case Qt::Key_T:
    case Qt::Key_U:
    case Qt::Key_V:
    case Qt::Key_W:
    case Qt::Key_X:
    case Qt::Key_Y:
    case Qt::Key_Z:
        return key;

    default:
        return 0;
    }
}

Qt::Key Util::KzHelper::vkToQtKey(uint32_t vk)
{
    switch (vk)
    {
    case VK_ESCAPE:
        return Qt::Key_Escape;
    case VK_TAB:
        return Qt::Key_Tab;
    case VK_BACK:
        return Qt::Key_Backspace;
    case VK_RETURN:
        return Qt::Key_Return;
    case VK_INSERT:
        return Qt::Key_Insert;
    case VK_DELETE:
        return Qt::Key_Delete;
    case VK_PAUSE:
        return Qt::Key_Pause;
    case VK_PRINT:
        return Qt::Key_Print;
    case VK_CLEAR:
        return Qt::Key_Clear;
    case VK_HOME:
        return Qt::Key_Home;
    case VK_END:
        return Qt::Key_End;
    case VK_LEFT:
        return Qt::Key_Left;
    case VK_UP:
        return Qt::Key_Up;
    case VK_RIGHT:
        return Qt::Key_Right;
    case VK_DOWN:
        return Qt::Key_Down;
    case VK_PRIOR:
        return Qt::Key_PageUp;
    case VK_NEXT:
        return Qt::Key_PageDown;
    case VK_F1:
        return Qt::Key_F1;
    case VK_F2:
        return Qt::Key_F2;
    case VK_F3:
        return Qt::Key_F3;
    case VK_F4:
        return Qt::Key_F4;
    case VK_F5:
        return Qt::Key_F5;
    case VK_F6:
        return Qt::Key_F6;
    case VK_F7:
        return Qt::Key_F7;
    case VK_F8:
        return Qt::Key_F8;
    case VK_F9:
        return Qt::Key_F9;
    case VK_F10:
        return Qt::Key_F10;
    case VK_F11:
        return Qt::Key_F11;
    case VK_F12:
        return Qt::Key_F12;
    case VK_F13:
        return Qt::Key_F13;
    case VK_F14:
        return Qt::Key_F14;
    case VK_F15:
        return Qt::Key_F15;
    case VK_F16:
        return Qt::Key_F16;
    case VK_F17:
        return Qt::Key_F17;
    case VK_F18:
        return Qt::Key_F18;
    case VK_F19:
        return Qt::Key_F19;
    case VK_F20:
        return Qt::Key_F20;
    case VK_F21:
        return Qt::Key_F21;
    case VK_F22:
        return Qt::Key_F22;
    case VK_F23:
        return Qt::Key_F23;
    case VK_F24:
        return Qt::Key_F24;
    case VK_SPACE:
        return Qt::Key_Space;
    case VK_MULTIPLY:
        return Qt::Key_Asterisk;
    case VK_ADD:
        return Qt::Key_Plus;
    case VK_SEPARATOR:
        return Qt::Key_Comma;
    case VK_SUBTRACT:
        return Qt::Key_Minus;
    case VK_DIVIDE:
        return Qt::Key_Slash;
    case VK_MEDIA_NEXT_TRACK:
        return Qt::Key_MediaNext;
    case VK_MEDIA_PREV_TRACK:
        return Qt::Key_MediaPrevious;
    case VK_MEDIA_PLAY_PAUSE:
        return Qt::Key_MediaPlay;
    case VK_MEDIA_STOP:
        return Qt::Key_MediaStop;
    case VK_VOLUME_DOWN:
        return Qt::Key_VolumeDown;
    case VK_VOLUME_UP:
        return Qt::Key_VolumeUp;
    case VK_VOLUME_MUTE:
        return Qt::Key_VolumeMute;
    default:
        // Verifica se é um número ou uma letra
        if (vk >= Qt::Key_0 && vk <= Qt::Key_9)
        {
            return static_cast<Qt::Key>(vk);
        }
        else if (vk >= Qt::Key_A && vk <= Qt::Key_Z)
        {
            return static_cast<Qt::Key>(vk);
        }
        else
        {
            return Qt::Key_unknown;
        }
    }
}























std::map<uint32_t, uint32_t> Util::KzHelper::readQtCollection(uint32_t address)
{
    std::map<uint32_t, uint32_t> qtCollectionAddresses;

    // Reads Collection Root Node Pointer and Item Count
    char qtCollectionData[0x8];
    if (!ReadMemory(Globals::getHandle(), address, qtCollectionData, sizeof(qtCollectionData)))
        return qtCollectionAddresses;

    // If Collection is empty returns
    uint32_t totalItems = *reinterpret_cast<uint32_t*>(qtCollectionData + 0x4);
    if (totalItems == 0)
        return qtCollectionAddresses;

    //std::cout << "Total Items: " << totalItems << std::endl;

    uint32_t addrStarterItem = *reinterpret_cast<uint32_t*>(qtCollectionData + 0x0);
    uint32_t currentItemCount = 0;

    //std::cout << std::hex << "Starter Item: " << addrStarterItem << std::endl;

    // Reads Root Node's 3 Pointers (0x0, 0x4, 0x8)
    char rootNodeData[0xC];
    if (!ReadMemory(Globals::getHandle(), addrStarterItem, rootNodeData, sizeof(rootNodeData)))
        return qtCollectionAddresses;

    int totalIterationCount = 0;

    /*
    uint32_t nodeA = *reinterpret_cast<uint32_t*>(rootNodeData + 0x0);
    uint32_t nodeB = *reinterpret_cast<uint32_t*>(rootNodeData + 0x4);
    uint32_t nodeC = *reinterpret_cast<uint32_t*>(rootNodeData + 0x8);

    std::cout << std::hex << "Node A: " << nodeA << std::endl;
    std::cout << std::hex << "Node B: " << nodeB << std::endl;
    std::cout << std::hex << "Node C: " << nodeC << std::endl;
    */

    totalIterationCount += readQtCollectionNode(*reinterpret_cast<uint32_t*>(rootNodeData + 0x0), addrStarterItem, qtCollectionAddresses, currentItemCount, totalItems, addrStarterItem);
    totalIterationCount += readQtCollectionNode(*reinterpret_cast<uint32_t*>(rootNodeData + 0x4), addrStarterItem, qtCollectionAddresses, currentItemCount, totalItems, addrStarterItem);
    totalIterationCount += readQtCollectionNode(*reinterpret_cast<uint32_t*>(rootNodeData + 0x8), addrStarterItem, qtCollectionAddresses, currentItemCount, totalItems, addrStarterItem);

    //std::cout << "Total Iterations: " << totalIterationCount << std::endl;

    return qtCollectionAddresses;
}

int Util::KzHelper::readQtCollectionNode(uint32_t& addrCurrentItem, uint32_t& addrPrevItem, std::map<uint32_t, uint32_t>& addrCollection, uint32_t& currentDepth, uint32_t& maxDepth, uint32_t& adrRoot)
{
    // Reads 3 Pointers (0x0, 0x4, 0x8) and Node's Id (0x10)
    char collectionNodeData[0x14];
    if (!ReadMemory(Globals::getHandle(), addrCurrentItem, collectionNodeData, sizeof(collectionNodeData)))
        return 1;

    uint32_t currentItemId = *reinterpret_cast<uint32_t*>(collectionNodeData + 0x10);

    // Try to add Node to Collection List, if already exists returns
    if (!addrCollection.insert({currentItemId, addrCurrentItem}).second)
        return 1;

    // Increase Current Node Count
    int totalIterationCount = 1;
    currentDepth++;

    // If Current Node Count is equal or greater than Collection Size returns
    if (currentDepth >= maxDepth)
        return totalIterationCount;

    // Checks Node's 3 Child Pointers, if it's the previous Node or Root Node (which does not contain any data) ignore child
    uint32_t childA = *reinterpret_cast<uint32_t*>(collectionNodeData + 0x0);
    uint32_t childB = *reinterpret_cast<uint32_t*>(collectionNodeData + 0x4);
    uint32_t childC = *reinterpret_cast<uint32_t*>(collectionNodeData + 0x8);

    if (childA != addrPrevItem && childA != adrRoot)
        totalIterationCount += readQtCollectionNode(childA, addrCurrentItem, addrCollection, currentDepth, maxDepth, adrRoot);

    if (childB != addrPrevItem && childB != adrRoot)
        totalIterationCount += readQtCollectionNode(childB, addrCurrentItem, addrCollection, currentDepth, maxDepth, adrRoot);

    if (childC != addrPrevItem && childC != adrRoot)
        totalIterationCount += readQtCollectionNode(childC, addrCurrentItem, addrCollection, currentDepth, maxDepth, adrRoot);

    return totalIterationCount;
}













RGBQUAD* Util::KzHelper::getRGBQuad()
{
    RECT rect;
    GetClientRect(Globals::getHWnd(), &rect);
    int nScreenWidth = rect.right - rect.left;
    int nScreenHeight = rect.bottom - rect.top;

    HDC hDesktopDC = GetWindowDC(Globals::getHWnd());
    HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
    HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, nScreenWidth, nScreenHeight);
    SelectObject(hCaptureDC, hCaptureBitmap);

    BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight, hDesktopDC, 0, 0, SRCCOPY|CAPTUREBLT);

    BITMAPINFO bmi;
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = nScreenWidth;
    bmi.bmiHeader.biHeight = nScreenHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;


    RGBQUAD *pPixels = new RGBQUAD[nScreenWidth * nScreenHeight];

    GetDIBits(
        hCaptureDC,
        hCaptureBitmap,
        0,
        nScreenHeight,
        pPixels,
        &bmi,
        DIB_RGB_COLORS
        );

    ReleaseDC(Globals::getHWnd(), hDesktopDC);
    DeleteDC(hCaptureDC);
    DeleteObject(hCaptureBitmap);

    return pPixels;
}


RGBQUAD* Util::KzHelper::getRGBRightQuad()
{
    RECT rect;
    GetWindowRect(Globals::getHWnd(), &rect);
    int nScreenWidth = rect.right - rect.left;
    int nScreenHeight = rect.bottom - rect.top;
    HDC hDesktopDC = GetWindowDC(Globals::getHWnd());
    HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
    HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, 200, nScreenHeight);
    SelectObject(hCaptureDC, hCaptureBitmap);

    BitBlt(hCaptureDC, 0, 0, 200, nScreenHeight, hDesktopDC, nScreenWidth-200,0, SRCCOPY|CAPTUREBLT);

    BITMAPINFO bmi;
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = 200;
    bmi.bmiHeader.biHeight = nScreenHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD *pPixels = new RGBQUAD[200 * nScreenHeight];

    GetDIBits(
        hCaptureDC,
        hCaptureBitmap,
        0,
        nScreenHeight,
        pPixels,
        &bmi,
        DIB_RGB_COLORS
        );

    ReleaseDC(Globals::getHWnd(), hDesktopDC);
    DeleteDC(hCaptureDC);
    DeleteObject(hCaptureBitmap);

    return pPixels;
}

uint32_t Util::KzHelper::getlParam(uint key, bool up, bool extended)
{
    uint scanCode = MapVirtualKey(key, 0);
    uint lParam = (0x00000001 | (scanCode << 16));
    if (extended)
        lParam |= 0x01000000;

    if (up)
        return (lParam | 0xC0000000);

    return lParam;
}

bool Util::KzHelper::stringVKisExtended(std::string str)
{
    // System Keys
    if (str == "PgUp") return true;
    else if (str == "PgDown") return true;
    else if (str == "Ins") return true;
    else if (str == "Home") return true;
    else if (str == "End") return true;
    else if (str == "Del") return true;
    else if (str == "Num+/") return true;

    return false;
}

uint32_t Util::KzHelper::stringToVK(std::string str)
{
    if (str.length() == 1)
    {
        short keyVK = VkKeyScanEx(str[0], GetKeyboardLayout(0));
        return keyVK;
    }

    // F1-F24
    if (str == "F1") return VK_F1;
    else if (str == "F2") return VK_F2;
    else if (str == "F3") return VK_F3;
    else if (str == "F4") return VK_F4;
    else if (str == "F5") return VK_F5;
    else if (str == "F6") return VK_F6;
    else if (str == "F7") return VK_F7;
    else if (str == "F8") return VK_F8;
    else if (str == "F9") return VK_F9;
    else if (str == "F10") return VK_F10;
    else if (str == "F11") return VK_F11;
    else if (str == "F12") return VK_F12;
    else if (str == "F13") return VK_F13;
    else if (str == "F14") return VK_F14;
    else if (str == "F15") return VK_F15;
    else if (str == "F16") return VK_F16;
    else if (str == "F17") return VK_F17;
    else if (str == "F18") return VK_F18;
    else if (str == "F19") return VK_F19;
    else if (str == "F20") return VK_F20;
    else if (str == "F21") return VK_F21;
    else if (str == "F22") return VK_F22;
    else if (str == "F23") return VK_F23;
    else if (str == "F24") return VK_F24;

    // System Keys
    else if (str == "PgUp") return VK_PRIOR;
    else if (str == "PgDown") return VK_NEXT;
    else if (str == "Ins") return VK_INSERT;
    else if (str == "Home") return VK_HOME;
    else if (str == "End") return VK_END;
    else if (str == "Backspace") return VK_BACK;
    else if (str == "Del") return VK_DELETE;
    else if (str == "ScrollLock") return VK_SCROLL;
    else if (str == "Pause") return VK_PAUSE;
    else if (str == "Space") return VK_SPACE;

    // NumPad Keys
    else if (str == "Num+/") return VK_DIVIDE;
    else if (str == "Num+*") return VK_MULTIPLY;
    else if (str == "Num+-") return VK_SUBTRACT;
    else if (str == "Num++") return VK_ADD;
    else if (str == "Num+,") return VK_DECIMAL;
    else if (str == "Num+0") return VK_NUMPAD0;
    else if (str == "Num+5") return VK_NUMPAD5;
    else if (str == "Num+Ins") return VK_INSERT;
    else if (str == "Num+Clear") return VK_CLEAR;
    else if (str == "Num+Del") return VK_DELETE;

    return 0;
}
