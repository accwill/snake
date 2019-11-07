#include "Game.h"
#include <conio.h>
#include <stdio.h>
#include "tools.h"
#pragma comment(lib,"WinMM.Lib")
extern int g_nSpeed;
extern int g_bIsReadFile;

Game::Game() {
}

void Game::startGame() {
	initMenu(); // 初始化菜单说明
	initBGM(); // 初始化背景音乐
	initGameArea(); // 初始化游戏区域
	while (true) {
		if (_kbhit()) {
			char temp = _getch();
			if (temp == '\r') {
				break;
			}
		}
	}

	initGame(); // 初始化游戏
}

void Game::initGame() {
	Snake snake;
	if (g_bIsReadFile) {
		snake.initFromFile();
		m_cInput = (char)snake.getDire();
		m_cPrevInput = (char)snake.getDire();
	} else {
		snake.initSanke(DEFAULTSNAKEBODY, m_isCustomerMap, m_map);
	}
	m_psnake = &snake;
	while (true) {
		if (_kbhit()) { // 判断是否有按键
			m_cInput = _getch();
			int temp = m_cInput + m_cPrevInput;
			if (temp == 202 || temp == 170 || temp == 165 || temp == 133 || temp == 234 || temp == 197) { // 防止按相反的键
				m_cInput = m_cPrevInput;
			}
		}
		if (playGame(snake, m_cInput)) { // 如果是有效按键,则保存按键
			m_cPrevInput = m_cInput;
		} else { // 如果按键无效, 则重新执行上次的按键
			playGame(snake, m_cPrevInput);
		}
		Sleep(g_nSpeed);
	}
}

void Game::initBGM() {
	// 播放音乐
	PlaySound(TEXT("sound/bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Game::pauseGame() {
	COORD crd = { 3, 4 };
	m_win.printWord(crd, FOREGROUND_RED, "游戏暂停， 再按一次空格键继续！！");
	// 暂停游戏
	while (true) {
		if (_kbhit()) {
			char temp;
			temp = _getch();
			if (temp == ' ') {
				m_win.printWord(crd, FOREGROUND_RED, "游戏继续， 按空格键暂停！！       ");
				m_cInput = m_cPrevInput;
				fflush(stdin); // 清空缓冲区
				break;
			};
		}
	}
}

bool Game::playGame(Snake& snake, char ch) {
	switch (ch) {
		case 'W': case 'w':
			snake.move(DIRE_UP);
			break;
		case 'S': case 's':
			snake.move(DIRE_DOWN);
			break;
		case 'A':case 'a':
			snake.move(DIRE_LEFT);
			break;
		case 'D': case 'd':
			snake.move(DIRE_RIGHT);
			break;
		case ' ':
			pauseGame();
			break;
		case '\x1b':
			exitGame();
			break;
		default:
			return false;
	}
	return true;
}

void Game::initGameArea() {
	m_win.drawGameArea();
}

void Game::initMenu() {
	for (unsigned short i = 0; i < m_menu.size(); i++) {
		COORD crd = { 5, 9 + (i * 2) };
		m_win.printWord(crd, 0x0F, m_menu[i].data());
	}
}

void Game::editMap() {
	m_isCustomerMap = true;
	m_win.drawGameArea(); // 画出游戏区域
	m_win.hideCursor(); // 隐藏鼠标
	HANDLE ConsoleWin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD eventMsg;
	DWORD Pointer;
	SetConsoleMode(ConsoleWin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	m_win.printEditMapMenu(); // 打印画图菜单(说明)
	while (true) {
		ReadConsoleInput(ConsoleWin, &eventMsg, 1, &Pointer); // Read input msg
		MOUSE_EVENT_RECORD mer = eventMsg.Event.MouseEvent;
		bool isMouseEvent = eventMsg.EventType == MOUSE_EVENT; // 是否是鼠标的事件
		bool isKeyEvent = eventMsg.EventType == KEY_EVENT; // 是否是鼠标的事件
		bool isClick = mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED; // 是否单击了鼠标左键
		bool isMove = mer.dwEventFlags == MOUSE_MOVED; // 是否移动了鼠标

		if (isMouseEvent && isClick) { // 判断鼠标事件
			if (isMove) {
				short nX = mer.dwMousePosition.X;
				short nY = mer.dwMousePosition.Y;
				if (nX > LEFTG * 2 && nX < RIGHTG * 2 && nY >= TOPG && nY <= BOTTOMG) { // 判断边界
					MapPointer mp(nX / 2, nY);
					if (!findForVector(m_map, mp)) { // 判断是否已经包含此做坐标, 包含就继续添加
						m_map.push_back(mp); // 添加
						m_win.printWord({ nX , nY }, FOREGROUND_GREEN, "※"); // 打印障碍物
					}
				}
			}
		} else if (isKeyEvent) { // 是否是键盘按键
			if (eventMsg.Event.KeyEvent.uChar.UnicodeChar == VK_ESCAPE) { // 判断是否按下了 esc
				m_win.printWord({ 10, 20 }, FOREGROUND_RED, "按下了ESC键");
				system("cls");
				break;
			}
			if (eventMsg.Event.KeyEvent.uChar.UnicodeChar == VK_BACK) { // 判断是否按下了 esc
				system("cls");
				system("color A");
				SetConsoleMode(ConsoleWin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
				m_map.clear();  // 清空地图
				m_win.drawGameArea(); // 打印游戏区域
				m_win.printEditMapMenu(); // 打印画图菜单(说明)
			}
		}


	}

}

void Game::exitGame() {
	m_win.printWord({ 3, 4 }, FOREGROUND_RED, "游戏即将退出, 是否存档? (y/n)");
	while (true) {
		if (_kbhit()) {
			m_win.showCursor();
			char isSaveFile = _getch();
			if (isSaveFile == 'y' || isSaveFile == 'Y') {
				m_psnake->saveMap();
			}
			exit(EXIT_SUCCESS);
		}
	}
}
