#ifndef MEMORY_H
#define MEMORY_H

#include <unordered_map>
#include <windows.h>
#include <vector>
#include <string>
#include <filesystem>
#include <Qt>
#include <vector>
#include <map>
#include "../Settings/globals.h"

namespace Util {
namespace KzHelper {

extern void WriteMemoryUInt32(HANDLE &handle, uint32_t address, uint32_t value);
extern void WriteMemoryByte(HANDLE &handle, uint32_t address, uint8_t value);
extern void WriteMemoryInt32(HANDLE &handle, uint32_t address, int32_t value);
extern void WriteMemoryString(HANDLE &handle, uint32_t address, std::string value);
extern void WriteMemoryStringUnicode(HANDLE &handle, uint32_t address, std::string value);

extern bool ReadMemory(HANDLE &handle, uint32_t address, LPVOID lpBuffer, DWORD_PTR dwSize);
extern uint8_t ReadMemoryByte(HANDLE &handle, uint32_t address);
extern int16_t ReadMemoryInt16(HANDLE &handle, uint32_t address);
extern int32_t ReadMemoryInt32(HANDLE &handle, uint32_t address);
extern int64_t ReadMemoryInt64(HANDLE &handle, uint32_t address);
extern uint16_t ReadMemoryUInt16(HANDLE &handle, uint32_t address);
extern uint32_t ReadMemoryUInt32(HANDLE &handle, uint32_t address);
extern uint64_t ReadMemoryUInt64(HANDLE &handle, uint32_t address);
extern float ReadMemoryFloat(HANDLE &handle, uint32_t address);
extern double ReadMemoryDouble(HANDLE &handle, uint32_t address);
extern std::string ReadMemoryString(HANDLE &handle, uint32_t address);
extern std::string ReadMemoryStringUnicode(HANDLE &handle, uint32_t address);
extern uint32_t GetProcessBaseAddress( DWORD processID, HANDLE& processHandle );


extern BOOL CALLBACK EnumWindowsCallback(HWND hWnd, LPARAM lParam);

extern std::vector<HWND> getWindows();
extern std::vector<HWND> getWindowsByTitle(std::string title, bool startsWith);
extern HWND getWindowById(DWORD pId);

extern std::string getWindowTitle(HWND hwnd);
extern DWORD getWindowProcessId(HWND hwnd);
extern std::filesystem::path getWindowPath(HWND hwnd);

extern uint32_t qtKeyToVK(uint32_t key, bool& extended);
extern Qt::Key vkToQtKey(uint32_t vk);
extern void SendKey(uint32_t key, bool extended = false);
extern void LeftClick(int x, int y);
extern void LeftClick(Point* p);
extern void RightClick(int x, int y);
extern void RightClick(Point* p);
extern void SendText(std::string text, bool lockKeyboard = false);

extern std::map<uint32_t, uint32_t> readQtCollection(uint32_t address);
extern std::map<uint32_t, uint32_t> readQtCollection(HANDLE& handle, uint32_t address);
extern int readQtCollectionNode(HANDLE& handle, uint32_t& addrCurrentItem, uint32_t& addrPrevItem, std::map<uint32_t, uint32_t>& addrCollection, uint32_t& currentDepth, uint32_t& maxDepth, uint32_t& adrRoot);

extern uint32_t getlParam(uint key, bool up = false, bool extended = false);
extern bool stringVKisExtended(std::string str);
extern uint stringToVK(std::string str);

extern RGBQUAD* getRGBQuad();
extern RGBQUAD* getRGBRightQuad();
};
};

#endif // MEMORY_H
