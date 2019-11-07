#pragma once
#include "Snake.h"
#include <string>


class Game {
	using string = std::string;
	using List = std::vector<string>;
	int m_nScore = 0; // 分数
	char m_cInput = 'd'; // 输入的字符
	char m_cPrevInput = 'd'; // 上次输入的字符
	using Map = std::vector<MapPointer>;
	Map m_map; // 自定义地图
	bool m_isCustomerMap = false; // 是否自定义地图
	Snake* m_psnake; // 指向蛇的指针
	Win m_win; // 对Windows的操作
	List m_menu = {
		"分数: ", "速度: ", "障碍物数量: ",
		"游戏说明: ",
			"  ∷ 键入回车开始游戏",
			"  ∷ 键入ESC退出游戏",
			"  ∷ 键入空格键暂停/开始游戏",
			"  ∷ 墙壁: 卍", "  ∷ 食物: ☆", "  ∷ 障碍物: ※",
			"  ∷ W-S-A-D 分别代表上-下-左-右",
			"  ∷ 最大速度60毫秒一格"
	};
public:
	Game();
	void setIsCustomerMap(bool isCustom) { m_isCustomerMap = isCustom; };
	// 默认的开始方法
	void startGame();
	// 初始化游戏
	void initGame();
	// 初始化背景音乐
	void initBGM();
	// 暂停游戏
	void pauseGame();
	// 播放游戏
	bool playGame(Snake& snake, char ch);
	// 初始化游戏区域
	void initGameArea();
	// 初始化菜单
	void initMenu();
	// 自定义地图
	void editMap();
	// 退出游戏
	void exitGame();
};