#pragma once
class MapPointer { // ���ڱ�������
	short m_nX;
	short m_nY;
public:
	MapPointer(short x, short y) : m_nX(x), m_nY(y) {};
	MapPointer() {};
	short getX() { return m_nX; }
	short getY() { return m_nY; }
	bool operator==(const MapPointer& mp) { // == ���������.
		if (mp.m_nX == m_nX && mp.m_nY == m_nY) {
			return true;
		}
		return false;
	}
};


typedef struct _SNAKEINFO {     // �����ߵ�һЩ��Ϣ, �����ļ��洢
	short nFoodX;               // ʳ�������
	short nFoodY;               // ʳ��������
	short nEatFoodCount;        // ʳ������
	short nScore;               // �ܷ���
	int nObstacle;              // �ϰ�������
	int nSpeed;                 // �ٶ�
	short nDire;                // ����
} SNAKEINFO, * PSNAKEINFO;
