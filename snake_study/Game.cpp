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
	initMenu(); // ��ʼ���˵�˵��
	initBGM(); // ��ʼ����������
	initGameArea(); // ��ʼ����Ϸ����
	while (true) {
		if (_kbhit()) {
			char temp = _getch();
			if (temp == '\r') {
				break;
			}
		}
	}

	initGame(); // ��ʼ����Ϸ
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
		if (_kbhit()) { // �ж��Ƿ��а���
			m_cInput = _getch();
			int temp = m_cInput + m_cPrevInput;
			if (temp == 202 || temp == 170 || temp == 165 || temp == 133 || temp == 234 || temp == 197) { // ��ֹ���෴�ļ�
				m_cInput = m_cPrevInput;
			}
		}
		if (playGame(snake, m_cInput)) { // �������Ч����,�򱣴水��
			m_cPrevInput = m_cInput;
		} else { // ���������Ч, ������ִ���ϴεİ���
			playGame(snake, m_cPrevInput);
		}
		Sleep(g_nSpeed);
	}
}

void Game::initBGM() {
	// ��������
	PlaySound(TEXT("sound/bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Game::pauseGame() {
	COORD crd = { 3, 4 };
	m_win.printWord(crd, FOREGROUND_RED, "��Ϸ��ͣ�� �ٰ�һ�οո����������");
	// ��ͣ��Ϸ
	while (true) {
		if (_kbhit()) {
			char temp;
			temp = _getch();
			if (temp == ' ') {
				m_win.printWord(crd, FOREGROUND_RED, "��Ϸ������ ���ո����ͣ����       ");
				m_cInput = m_cPrevInput;
				fflush(stdin); // ��ջ�����
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
	m_win.drawGameArea(); // ������Ϸ����
	m_win.hideCursor(); // �������
	HANDLE ConsoleWin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD eventMsg;
	DWORD Pointer;
	SetConsoleMode(ConsoleWin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	m_win.printEditMapMenu(); // ��ӡ��ͼ�˵�(˵��)
	while (true) {
		ReadConsoleInput(ConsoleWin, &eventMsg, 1, &Pointer); // Read input msg
		MOUSE_EVENT_RECORD mer = eventMsg.Event.MouseEvent;
		bool isMouseEvent = eventMsg.EventType == MOUSE_EVENT; // �Ƿ��������¼�
		bool isKeyEvent = eventMsg.EventType == KEY_EVENT; // �Ƿ��������¼�
		bool isClick = mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED; // �Ƿ񵥻���������
		bool isMove = mer.dwEventFlags == MOUSE_MOVED; // �Ƿ��ƶ������

		if (isMouseEvent && isClick) { // �ж�����¼�
			if (isMove) {
				short nX = mer.dwMousePosition.X;
				short nY = mer.dwMousePosition.Y;
				if (nX > LEFTG * 2 && nX < RIGHTG * 2 && nY >= TOPG && nY <= BOTTOMG) { // �жϱ߽�
					MapPointer mp(nX / 2, nY);
					if (!findForVector(m_map, mp)) { // �ж��Ƿ��Ѿ�������������, �����ͼ������
						m_map.push_back(mp); // ���
						m_win.printWord({ nX , nY }, FOREGROUND_GREEN, "��"); // ��ӡ�ϰ���
					}
				}
			}
		} else if (isKeyEvent) { // �Ƿ��Ǽ��̰���
			if (eventMsg.Event.KeyEvent.uChar.UnicodeChar == VK_ESCAPE) { // �ж��Ƿ����� esc
				m_win.printWord({ 10, 20 }, FOREGROUND_RED, "������ESC��");
				system("cls");
				break;
			}
			if (eventMsg.Event.KeyEvent.uChar.UnicodeChar == VK_BACK) { // �ж��Ƿ����� esc
				system("cls");
				system("color A");
				SetConsoleMode(ConsoleWin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
				m_map.clear();  // ��յ�ͼ
				m_win.drawGameArea(); // ��ӡ��Ϸ����
				m_win.printEditMapMenu(); // ��ӡ��ͼ�˵�(˵��)
			}
		}


	}

}

void Game::exitGame() {
	m_win.printWord({ 3, 4 }, FOREGROUND_RED, "��Ϸ�����˳�, �Ƿ�浵? (y/n)");
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
