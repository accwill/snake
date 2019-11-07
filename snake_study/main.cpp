
#include <iostream>
#include "Game.h"
#include <conio.h>
#include <windows.h>
#include "File.h"

int g_nSpeed = 200; // 全局属性, 速度
int g_nObstacle = MAXOSTACLESIZE; // 障碍物数量
int g_bIsReadFile = false; // 是否读取文件
int main() {
	using std::cout;
	using std::cin;
	using std::endl;
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
	Win win;
	win.printWelcome(); // 打印欢迎页面

	Game game; // 初始化游戏对象
	char difficulty; // 难度等级
	bool bIsCustomMap = false; // 是否是自定义地图

	win.showCursor();
	win.setCursorPosition({ 53, 17 });
	cin >> difficulty;
	system("cls");

	switch (difficulty) {
		case '1': // 难度为1
			g_bIsReadFile = false;
			bIsCustomMap = false;
			break;
		case '2': // 难度为2
			g_nSpeed = 150;
			g_nObstacle = 20;
			g_bIsReadFile = false;
			bIsCustomMap = false;
			break;
		case '3': // 难度为3
			g_nSpeed = 100;
			g_nObstacle = 50;
			g_bIsReadFile = false;
			bIsCustomMap = false;
			break;
		case '4': // 难度为4
			g_nSpeed = 30;
			g_nObstacle = 60;
			g_bIsReadFile = false;
			bIsCustomMap = false;
			break;
		case '5': // 编辑地图
			game.editMap();
			g_bIsReadFile = true;
			g_bIsReadFile = false;
			bIsCustomMap = true;
			break;
		case '6': // 读取存档
			g_bIsReadFile = true;
			break;
	}

	win.hideCursor(); // 隐藏鼠标
	game.setIsCustomerMap(bIsCustomMap); // 设置属性
	game.startGame(); // 开始游戏
	return 1;
}
