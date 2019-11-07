#pragma once
#include <vector>
#include "MapPointer.h"
#include "SnakeNode.h"


class File {
public:
	// 读取文件
	void readFile(const char* fileName, int nEleSize, void* p);
	// 写入文件
	void writeFile(const char* fileName, int nEleSize, int nCount, const void* p);
	// 保存地图
	void saveMap(const MapPointer* mp, int nCount);
	// 读取地图
	void readMap(std::vector<MapPointer>& mps);
	// 读取身体
	void readBody(std::vector<SnakeNode>& body);
	// 保存身体
	void saveBody(const SnakeNode* psn, int nCount);
	// 保存蛇的信息, 速度, 食物, 吃了多少个等信息
	void saveSnakeInfo(SNAKEINFO& snakeInfo);
	// 读取蛇的信息
	void readSnakeInfo(short& nFoodX, short& nFoodY, short& nEatFoodCount, short& nScore, short& nDire);
};