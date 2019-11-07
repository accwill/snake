#pragma once
#include <vector>
#include <ctime>
#include "File.h"
#include "main.h"
#include "SnakeNode.h"
#include "MapPointer.h"

extern int g_nSpeed;

class Snake {
	std::vector<SnakeNode> m_body;
	using Array = std::vector<MapPointer>;
	Array m_aMap; // 地图
	Win m_win;
	short m_nFoodX; // 食物的横坐标
	short m_nFoodY; // 食物的纵坐标
	short m_nEatFoodCount = 0; // 吃到的食物总数
	short m_nScore = 0; // 分数
	short m_nDire = 'd'; // 方向, 用于存储不做
	bool m_isCustomMap = false; // 是否自定义地图
	File m_f;
public:
	~Snake() {};
	Snake() {};
	// 初始化这条蛇
	void initSanke(int size, bool isCustomMap, Array& customMap);

	// 从存档初始化
	void initFromFile();

	// 添加身体
	void addBody();

	// 移动
	void move(short dire);

	// 生成食物
	void generatorFood();

	// 是否吃到了食物
	bool isEatFood(int x, int y);

	// 是否吃到了自己
	bool isEatMySelf(int x, int y);

	// 根据边界修改坐标
	void accordingToDireModifyCoor(short dire, short& nX, short& nY);
	
	// 生成并打印障碍物
	void generatorObstacle();

	// 打印障碍物
	void printObstacles();

	// 判断是否吃到了障碍物
	bool isEatObstacle(short x, short y);

	// 计算分数
	void mathScoreAndPrint();

	// 打印速度
	void printSpeed();

	// 游戏结束
	void gameOver();

	// 打印障碍物数量
	void printObstacleCount();

	// 存档地图
	void saveMap();

	// 打印身体
	void printBody();

	// 打印食物
	void printFood();

	// 获得方向
	short getDire() { return m_nDire; };
};