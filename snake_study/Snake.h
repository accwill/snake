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
	Array m_aMap; // ��ͼ
	Win m_win;
	short m_nFoodX; // ʳ��ĺ�����
	short m_nFoodY; // ʳ���������
	short m_nEatFoodCount = 0; // �Ե���ʳ������
	short m_nScore = 0; // ����
	short m_nDire = 'd'; // ����, ���ڴ洢����
	bool m_isCustomMap = false; // �Ƿ��Զ����ͼ
	File m_f;
public:
	~Snake() {};
	Snake() {};
	// ��ʼ��������
	void initSanke(int size, bool isCustomMap, Array& customMap);

	// �Ӵ浵��ʼ��
	void initFromFile();

	// �������
	void addBody();

	// �ƶ�
	void move(short dire);

	// ����ʳ��
	void generatorFood();

	// �Ƿ�Ե���ʳ��
	bool isEatFood(int x, int y);

	// �Ƿ�Ե����Լ�
	bool isEatMySelf(int x, int y);

	// ���ݱ߽��޸�����
	void accordingToDireModifyCoor(short dire, short& nX, short& nY);
	
	// ���ɲ���ӡ�ϰ���
	void generatorObstacle();

	// ��ӡ�ϰ���
	void printObstacles();

	// �ж��Ƿ�Ե����ϰ���
	bool isEatObstacle(short x, short y);

	// �������
	void mathScoreAndPrint();

	// ��ӡ�ٶ�
	void printSpeed();

	// ��Ϸ����
	void gameOver();

	// ��ӡ�ϰ�������
	void printObstacleCount();

	// �浵��ͼ
	void saveMap();

	// ��ӡ����
	void printBody();

	// ��ӡʳ��
	void printFood();

	// ��÷���
	short getDire() { return m_nDire; };
};