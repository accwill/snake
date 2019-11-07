
#include <iostream>
#include "Game.h"
#include <conio.h>
#include <windows.h>
#include "File.h"

int g_nSpeed = 200; // ȫ������, �ٶ�
int g_nObstacle = MAXOSTACLESIZE; // �ϰ�������
int g_bIsReadFile = false; // �Ƿ��ȡ�ļ�
int main() {
	using std::cout;
	using std::cin;
	using std::endl;
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
	Win win;
	win.printWelcome(); // ��ӡ��ӭҳ��

	Game game; // ��ʼ����Ϸ����
	char difficulty; // �Ѷȵȼ�
	bool bIsCustomMap = false; // �Ƿ����Զ����ͼ

	win.showCursor();
	win.setCursorPosition({ 53, 17 });
	cin >> difficulty;
	system("cls");

	switch (difficulty) {
		case '1': // �Ѷ�Ϊ1
			g_bIsReadFile = false;
			bIsCustomMap = false;
			break;
		case '2': // �Ѷ�Ϊ2
			g_nSpeed = 150;
			g_nObstacle = 20;
			g_bIsReadFile = false;
			bIsCustomMap = false;
			break;
		case '3': // �Ѷ�Ϊ3
			g_nSpeed = 100;
			g_nObstacle = 50;
			g_bIsReadFile = false;
			bIsCustomMap = false;
			break;
		case '4': // �Ѷ�Ϊ4
			g_nSpeed = 30;
			g_nObstacle = 60;
			g_bIsReadFile = false;
			bIsCustomMap = false;
			break;
		case '5': // �༭��ͼ
			game.editMap();
			g_bIsReadFile = true;
			g_bIsReadFile = false;
			bIsCustomMap = true;
			break;
		case '6': // ��ȡ�浵
			g_bIsReadFile = true;
			break;
	}

	win.hideCursor(); // �������
	game.setIsCustomerMap(bIsCustomMap); // ��������
	game.startGame(); // ��ʼ��Ϸ
	return 1;
}
