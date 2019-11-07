#include "Snake.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>

extern int g_nSpeed;
extern int g_nObstacle;
extern int g_bIsReadFile;
void Snake::initSanke(int size, bool isCustomMap, Array& customMap) {
	// 构造一个点作为蛇头保存到动态数组中.
	m_win.hideCursor(); // 隐藏鼠标
	m_body.push_back(SnakeNode(25, 1, m_win)); // 初始化一个身体
	m_isCustomMap = isCustomMap;

	if (m_isCustomMap) {
		m_aMap = customMap;
		printObstacles();
	} else {
		generatorObstacle(); // 自动生成地图
	}

	generatorFood();      // 生成食物
	mathScoreAndPrint();  // 计算并打印分数
	printObstacleCount(); // 打印障碍物数量
	printSpeed();         // 打印速度
	while (--size && size > 0) { // 生成身体
		addBody();
	}
}

void Snake::initFromFile() {
	m_f.readMap(m_aMap);  // 读取地图
	m_f.readBody(m_body); // 读取身体
	m_f.readSnakeInfo(m_nFoodX, m_nFoodY, m_nEatFoodCount, m_nScore, m_nDire); // 读取蛇的信息
	printObstacles();     // 打印障碍物
	printBody();          // 打印身体
	mathScoreAndPrint();  // 计算并打印分数
	printObstacleCount(); // 打印障碍物数量
	printSpeed();         // 打印速度
	printFood();          // 打印食物
}

void Snake::addBody() {
	SnakeNode* lastNode = &m_body[m_body.size() - 1];
	short nX = lastNode->getX();
	short nY = lastNode->getY();
	short nDirec = lastNode->getDire();
	switch (nDirec) {
		case DIRE_RIGHT:
			nX -= 1;
			if (nX < LEFTG) { // 判断边界
				nX = RIGHTG + nX + 1;
			}
			break;
		case DIRE_LEFT:
			nX += 1;
			if (nX > RIGHTG) { // 判断边界
				nY += 1;
				nX = LEFTG;
			}
			break;
		case DIRE_DOWN:
			nY -= 1;
			if (nY <= LEFTG) { // 判断边界
				nY = BOTTOMG;
			}
			break;
		case DIRE_UP:
			nY += 1;
			if (nY > BOTTOMG) { // 判断边界
				nY = TOPG;
				nX -= 1;
			}
			break;
	}
	// 加入到蛇身
	m_body.push_back(SnakeNode(nX, nY, m_win));
}

void Snake::move(short dire) {
	m_nDire = dire;
	// 获取最后一个坐标
	if (m_body.size() == 0) {
		return;
	}
	SnakeNode* lastNode = &m_body[m_body.size() - 1]; // 最后一个节点
	SnakeNode* firstNode = &m_body[0]; // 第一个节点
	short nX = firstNode->getX(), nY = firstNode->getY();
	lastNode->hide();
	m_body.pop_back();

	// 根据边界重新校正坐标
	accordingToDireModifyCoor(dire, nX, nY);

	if (isEatFood(nX, nY)) { // 是否迟到了食物
		// 增加新的身体
		if (g_nSpeed <= MAXSPEED) {
			g_nSpeed = MAXSPEED;
		} else {
			g_nSpeed -= 10; // 提速
		}
		m_nEatFoodCount++;
		printSpeed();
		mathScoreAndPrint();
		m_body.push_back(SnakeNode(lastNode->getX(), lastNode->getY(), m_win, dire));
	}

	if (isEatMySelf(nX, nY)) { // 是否吃到了自己
		COORD crd = { 25 * 2, 20 };
		gameOver();
	}

	if (isEatObstacle(nX, nY)) { // 是否吃到了障碍物
		COORD crd = { 25 * 2, 20 };
		gameOver();
	}

	// 插入蛇头
	m_body.insert(m_body.begin(), SnakeNode(nX, nY, m_win, dire));
}

void Snake::generatorFood() {
	srand((int)time(0));
	int nX = 0, nY = 0;
	while (true) {
		// 生成区间食物
		nX = rand() % (RIGHTG - LEFTG + 1) + LEFTG;
		nY = rand() % (BOTTOMG - TOPG + 1) + TOPG;
		bool isContains = false;
		for (MapPointer mp : m_aMap) { // 判断障碍物集合是否包含新生成的食物坐标
			if (mp.getX() == nX && mp.getY() == nY) {
				isContains = true;
				break;
			}
		}
		if (!isContains) { // 不包含的话保存坐标并打印食物
			m_nFoodX = nX;
			m_nFoodY = nY;
			COORD crd = { short(m_nFoodX * 2), short(m_nFoodY) };
			// 打印食物
			m_win.printWord(crd, FOREGROUND_BLUE, FOOD);
			break;
		}
	}
}

bool Snake::isEatFood(int x, int y) {
	if (x == m_nFoodX && y == m_nFoodY) { // 判断是否吃到了食物
		generatorFood(); // 重新生成食物
		m_nEatFoodCount++;
		return true;
	}
	return false;
}

bool Snake::isEatMySelf(int x, int y) {
	for (auto sn : m_body) {
		if (sn.getX() == x && sn.getY() == y) { // 判断是否吃到了自己
			return true;
		}
	}
	return false;
}

void Snake::accordingToDireModifyCoor(short dire, short& nX, short& nY) {
	switch (dire) {
		case DIRE_LEFT:
			nX -= 1;
			if (nX < LEFTG) {
				nX = RIGHTG;
			}
			break;
		case DIRE_RIGHT:
			nX += 1;
			if (nX > RIGHTG) {
				nX = LEFTG;
			}
			break;
		case DIRE_UP:
			nY -= 1;
			if (nY < TOPG) {
				nY = BOTTOMG;
			}
			break;
		case DIRE_DOWN:
			nY += 1;
			if (nY > BOTTOMG) {
				nY = TOPG;
			}
			break;
	}
}

void Snake::generatorObstacle() {
	short nX, nY;
	while (m_aMap.size() != g_nObstacle) {
		nX = rand() % (RIGHTG - LEFTG + 1) + LEFTG;
		nY = rand() % (BOTTOMG - TOPG + 1) + TOPG;
		if (nX == m_nFoodX && nY == m_nFoodY) { // 判断是否是食物的坐标, 如果不是则继续
			continue;
		}
		COORD crd = { nX * 2, nY };
		m_win.printWord(crd, BACKGROUND_INTENSITY, OBSTACLE); // 打印障碍物
		m_aMap.push_back(MapPointer(nX, nY));
	}
}

void Snake::printObstacles() {
	for (auto mp : m_aMap) {
		COORD crd = { mp.getX() * 2, mp.getY() };
		m_win.printWord(crd, BACKGROUND_INTENSITY, OBSTACLE); // 打印障碍物
	}
}

bool Snake::isEatObstacle(short x, short y) {
	for (MapPointer mp : m_aMap) {
		if (mp.getX() == x && mp.getY() == y) {
			return true;
		}
	}
	return false;
}

void Snake::mathScoreAndPrint() {
	m_nScore = m_nEatFoodCount * FOODSCORE;
	COORD crd = { 13, 9 }; // 此坐标对应着 void Game::initMenu 菜单坐标
	m_win.printWord(crd, FOREGROUND_RED, std::to_string(m_nScore).data());
}

void Snake::printSpeed() {
	COORD crd = { 13, 11 }; // 此坐标对应着 void Game::initMenu 菜单坐标
	m_win.printWord(crd, FOREGROUND_RED, std::to_string(g_nSpeed).data());
}

void Snake::printObstacleCount() {
	COORD crd = { 18, 13 }; // 此坐标对应着 void Game::initMenu 菜单坐标
	m_win.printWord(crd, FOREGROUND_RED, std::to_string(MAXOSTACLESIZE).data());
}

void Snake::gameOver() {
	COORD crd = { 3, 4 };
	m_win.printWord(crd, FOREGROUND_RED, "按任意键退出~~");
	while (1) {
		if (_kbhit()) {
			exit(EXIT_SUCCESS);
		}
	}
}

void Snake::saveMap() {
	SNAKEINFO sn = { m_nFoodX, m_nFoodY, m_nEatFoodCount, m_nScore, g_nObstacle, g_nSpeed, m_nDire };
	m_f.writeFile(SNAKEMAPFIELNAME, sizeof(MapPointer), m_aMap.size(), &m_aMap[0]);
	m_f.saveMap(&m_aMap[0], m_aMap.size());
	m_f.saveBody(&m_body[0], m_body.size());
	m_f.saveSnakeInfo(sn);
}

void Snake::printBody() {
	for (auto mp : m_body) {
		COORD crd = { mp.getX() * 2, mp.getY() };
		m_win.printWord(crd, FOREGROUND_GREEN, SNAKE); // 打印身体
	}
}

void Snake::printFood() {
	m_win.printWord({ m_nFoodX * 2, m_nFoodY }, FOREGROUND_BLUE, FOOD);
}

