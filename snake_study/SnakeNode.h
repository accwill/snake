#pragma once
#include "WinApiHelper.h"
#include "main.h"
class SnakeNode {
	short m_nX; // X 坐标
	short m_nY; // Y 坐标
	WORD m_dwColor; // 颜色
	Win win;
	short m_nDire; // 方向
public:
	~SnakeNode() {};
	SnakeNode(short nX, short nY, Win& w, short nDire = DIRE_RIGHT, WORD dwC = FOREGROUND_GREEN) : m_nX(nX), m_nY(nY), m_dwColor(dwC), m_nDire(nDire) { show(); };
	SnakeNode(){};
	SnakeNode& operator=(const SnakeNode& sn);
	short getX()const { return m_nX; }
	short getY() const { return m_nY; }
	short getDire() const { return m_nDire; }
	void setX(const short x) { m_nX = x; }
	void setY(const short y) { m_nY = y; }
	void show() const;
	void hide() const;
};