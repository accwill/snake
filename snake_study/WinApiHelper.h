#include <windows.h>
#include <string>
#include <iostream>
#include "main.h"

class Win {
	// 窗口句柄
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	~Win(){}
	Win(const char* title = DEFAULTTITLE, const COORD size = DEFAULTPOSITION);
	// 设置光标位置
	void setCursorPosition(const COORD) const;
	// 设置字体颜色等属性
	void setTextAttribute(const WORD) const;
	// 设置控制台标题
	void setConsoleTitle(const char* title) const;
	// 设置控制台大小
	void setConsoleSize(const COORD) const;
	// 打印文字
	void printWord(const COORD, const WORD color, const char* word, const char* format = "%s") const;
	// 隐藏光标
	void hideCursor();
	// 显示光标
	void showCursor();
	// 画游戏区域
	void drawGameArea();
	// 设置句柄
	void setHandle(DWORD dw);
	// 获得句柄
	HANDLE& getHandle();
	// 打印欢迎页面
	void printWelcome();
	// 编辑地图游戏说明
	void printEditMapMenu();
};