#pragma once
class MapPointer { // 用于保存坐标
	short m_nX;
	short m_nY;
public:
	MapPointer(short x, short y) : m_nX(x), m_nY(y) {};
	MapPointer() {};
	short getX() { return m_nX; }
	short getY() { return m_nY; }
	bool operator==(const MapPointer& mp) { // == 运算符重载.
		if (mp.m_nX == m_nX && mp.m_nY == m_nY) {
			return true;
		}
		return false;
	}
};


typedef struct _SNAKEINFO {     // 保存蛇的一些信息, 用于文件存储
	short nFoodX;               // 食物横坐标
	short nFoodY;               // 食物纵坐标
	short nEatFoodCount;        // 食物总数
	short nScore;               // 总分数
	int nObstacle;              // 障碍物数量
	int nSpeed;                 // 速度
	short nDire;                // 方向
} SNAKEINFO, * PSNAKEINFO;
