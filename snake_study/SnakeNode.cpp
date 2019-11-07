#include "SnakeNode.h"

SnakeNode& SnakeNode::operator=(const SnakeNode& sn) {
	m_nX = sn.getX();
	m_nY = sn.getY();
	return *this;
	// TODO: �ڴ˴����� return ���
}

void SnakeNode::show() const {
	// ��ӡ��ʾ����
	COORD crd = { 0 };
	crd.X = m_nX * 2;
	crd.Y = m_nY;

	win.printWord(crd, m_dwColor, SNAKE);
}

void SnakeNode::hide() const {
	// ��ӡ��������
	COORD crd = { 0 };
	crd.X = m_nX * 2;
	crd.Y = m_nY;
	win.printWord(crd, BGCOLOR, "  ");
}