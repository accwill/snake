#include "SnakeNode.h"

SnakeNode& SnakeNode::operator=(const SnakeNode& sn) {
	m_nX = sn.getX();
	m_nY = sn.getY();
	return *this;
	// TODO: 在此处插入 return 语句
}

void SnakeNode::show() const {
	// 打印显示蛇身
	COORD crd = { 0 };
	crd.X = m_nX * 2;
	crd.Y = m_nY;

	win.printWord(crd, m_dwColor, SNAKE);
}

void SnakeNode::hide() const {
	// 打印隐藏蛇身
	COORD crd = { 0 };
	crd.X = m_nX * 2;
	crd.Y = m_nY;
	win.printWord(crd, BGCOLOR, "  ");
}