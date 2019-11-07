#include "WinApiHelper.h"

void Win::setCursorPosition(const COORD position) const {
	// 设置光标位置
	SetConsoleCursorPosition(hStdout, position);
}

void Win::setTextAttribute(const WORD attr) const {
	// 设置文本颜色
	SetConsoleTextAttribute(hStdout, attr);
}

Win::Win(const char* title, const COORD size) {
	setConsoleTitle(title);
	setConsoleSize(size);
}

void Win::setConsoleTitle(const char* title) const {
	// 设置控制台标题
	SetConsoleTitle(title);
}

void Win::setConsoleSize(const COORD size) const {
	// 设置控制台缓冲区大小
	SMALL_RECT sm = { 0, 0, size.X - 1, size.Y - 1 };
	SetConsoleScreenBufferSize(hStdout, size);
	SetConsoleWindowInfo(hStdout, true, &sm);
}

void Win::printWord(const COORD position, const WORD color, const char* word, const char* format) const {
	setTextAttribute(color);
	setCursorPosition(position);
	printf(format, word);
}

void Win::hideCursor() {
	CONSOLE_CURSOR_INFO cci = { 0 };
	cci.dwSize = 1;
	cci.bVisible = FALSE;//是否显示光标
	SetConsoleCursorInfo(hStdout, &cci);
}

void Win::showCursor() {
	CONSOLE_CURSOR_INFO cci = { 0 };
	cci.dwSize = 1;
	cci.bVisible = true;//是否显示光标
	SetConsoleCursorInfo(hStdout, &cci);
}

void Win::drawGameArea() {
	// 画左线
	for (short i = TOPG; i < MAXY; i++) {
		COORD crd = { LINEX, i };
		printWord(crd, BACKGROUND_BLUE, WALLBOARD);
	}
	//// 画下线
	for (short i = LINEX; i < MAXX * 2; i++) {
		COORD crd = { i, 40 };
		printWord(crd, BACKGROUND_BLUE, WALLBOARD);
	}
	// 画右线
	for (short i = TOPG; i < MAXY; i++) {
		COORD crd = { MAXX * 2, i };
		printWord(crd, BACKGROUND_BLUE, WALLBOARD);
	}
	// 画上线
	for (short i = LINEX; i < 120; i++) {
		COORD crd = { i, 0 };
		printWord(crd, BACKGROUND_BLUE, WALLBOARD);
	}
}

void Win::setHandle(DWORD dw) {
	CloseHandle(hStdout);
	hStdout = GetStdHandle(dw);
}

HANDLE& Win::getHandle() {
	return hStdout;
	// TODO: 在此处插入 return 语句
}

void Win::printWelcome() {
	printWord({ 48, 10 }, FOREGROUND_BLUE, TEXT("||欢迎来到贪吃蛇||"));
	printWord({ 44, 14 }, FOREGROUND_BLUE, TEXT("请输入游戏难度, 按回车确定"));
	printWord({ 10, 16 }, FOREGROUND_BLUE, TEXT("1. 普通          2. 中等          3.高          4. 地狱          5. 编辑地图          6. 读取存档"));
}

void Win::printEditMapMenu() {
	printWord({ 5, 14 }, 0x0F, "退格:  重新编辑");
	printWord({ 5, 18 }, 0x0F, "ESC :  保存并开始游戏");
	printWord({ 5, 10 }, 0x0F, "画图:  单击左键鼠标并拖动");
}
