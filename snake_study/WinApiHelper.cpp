#include "WinApiHelper.h"

void Win::setCursorPosition(const COORD position) const {
	// ���ù��λ��
	SetConsoleCursorPosition(hStdout, position);
}

void Win::setTextAttribute(const WORD attr) const {
	// �����ı���ɫ
	SetConsoleTextAttribute(hStdout, attr);
}

Win::Win(const char* title, const COORD size) {
	setConsoleTitle(title);
	setConsoleSize(size);
}

void Win::setConsoleTitle(const char* title) const {
	// ���ÿ���̨����
	SetConsoleTitle(title);
}

void Win::setConsoleSize(const COORD size) const {
	// ���ÿ���̨��������С
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
	cci.bVisible = FALSE;//�Ƿ���ʾ���
	SetConsoleCursorInfo(hStdout, &cci);
}

void Win::showCursor() {
	CONSOLE_CURSOR_INFO cci = { 0 };
	cci.dwSize = 1;
	cci.bVisible = true;//�Ƿ���ʾ���
	SetConsoleCursorInfo(hStdout, &cci);
}

void Win::drawGameArea() {
	// ������
	for (short i = TOPG; i < MAXY; i++) {
		COORD crd = { LINEX, i };
		printWord(crd, BACKGROUND_BLUE, WALLBOARD);
	}
	//// ������
	for (short i = LINEX; i < MAXX * 2; i++) {
		COORD crd = { i, 40 };
		printWord(crd, BACKGROUND_BLUE, WALLBOARD);
	}
	// ������
	for (short i = TOPG; i < MAXY; i++) {
		COORD crd = { MAXX * 2, i };
		printWord(crd, BACKGROUND_BLUE, WALLBOARD);
	}
	// ������
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
	// TODO: �ڴ˴����� return ���
}

void Win::printWelcome() {
	printWord({ 48, 10 }, FOREGROUND_BLUE, TEXT("||��ӭ����̰����||"));
	printWord({ 44, 14 }, FOREGROUND_BLUE, TEXT("��������Ϸ�Ѷ�, ���س�ȷ��"));
	printWord({ 10, 16 }, FOREGROUND_BLUE, TEXT("1. ��ͨ          2. �е�          3.��          4. ����          5. �༭��ͼ          6. ��ȡ�浵"));
}

void Win::printEditMapMenu() {
	printWord({ 5, 14 }, 0x0F, "�˸�:  ���±༭");
	printWord({ 5, 18 }, 0x0F, "ESC :  ���沢��ʼ��Ϸ");
	printWord({ 5, 10 }, 0x0F, "��ͼ:  ���������겢�϶�");
}
