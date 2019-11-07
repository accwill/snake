#include <windows.h>
#include <string>
#include <iostream>
#include "main.h"

class Win {
	// ���ھ��
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	~Win(){}
	Win(const char* title = DEFAULTTITLE, const COORD size = DEFAULTPOSITION);
	// ���ù��λ��
	void setCursorPosition(const COORD) const;
	// ����������ɫ������
	void setTextAttribute(const WORD) const;
	// ���ÿ���̨����
	void setConsoleTitle(const char* title) const;
	// ���ÿ���̨��С
	void setConsoleSize(const COORD) const;
	// ��ӡ����
	void printWord(const COORD, const WORD color, const char* word, const char* format = "%s") const;
	// ���ع��
	void hideCursor();
	// ��ʾ���
	void showCursor();
	// ����Ϸ����
	void drawGameArea();
	// ���þ��
	void setHandle(DWORD dw);
	// ��þ��
	HANDLE& getHandle();
	// ��ӡ��ӭҳ��
	void printWelcome();
	// �༭��ͼ��Ϸ˵��
	void printEditMapMenu();
};