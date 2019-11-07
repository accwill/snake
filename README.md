# 贪吃蛇

## 目录结构
```bash                 
│  main.cpp           # 入口函数
│  main.h             # 公共变量/全局变量/配置
│  File.h             # 文件操作类
│  Game.h             # 游戏类
│  MapPointer.h       # 节点信息/蛇的基础信息
│  Snake.h            # 蛇类
│  SnakeNode.h        # 蛇的身体类
│  tools.h            # 工具函数
│  WinApiHelper.h     # 操作windows窗口的类
│
├─icon
│      snake.ico      # 图标
│
└─sound
        bgm.wav       # 背景音乐
```

## 文件信息

### WinApiHelper

```C++
// 设置光标位置
void setCursorPosition(const COORD) const;
// 设置字体颜色等属性
void setTextAttribute(const WORD) const;
// 设置控制台标题
void setConsoleTitle(const char* title) const;
// 设置控制台大小
void setConsoleSize(const COORD) const;
// 打印文字
void printWord(const COORD, const WORD color, const char* word, const char* format = "%s") const;
// 隐藏光标
void hideCursor();
// 显示光标
void showCursor();
// 画游戏区域
void drawGameArea();
// 设置句柄
void setHandle(DWORD dw);
// 获得句柄
HANDLE& getHandle();
// 打印欢迎页面
void printWelcome();
// 编辑地图游戏说明
void printEditMapMenu();
```
#### File

```C++
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
```
#### tools

```c++
bool findForVector(std::vector<MapPointer>& arr, MapPointer& mp);
```

#### Game

```C++
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
```
#### Snake

```C++
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
```

#### SnakeNode

```C++
SnakeNode& operator=(const SnakeNode& sn); // 拷贝
short getX()const { return m_nX; }
short getY() const { return m_nY; }
short getDire() const { return m_nDire; }
void setX(const short x) { m_nX = x; }
void setY(const short y) { m_nY = y; }
void show() const; // 隐藏
void hide() const; // 显示
```
#### MapPointer

```C++
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

// 保存蛇的一些信息, 用于文件存储
typedef struct _SNAKEINFO {   
	short nFoodX;               // 食物横坐标
	short nFoodY;               // 食物纵坐标
	short nEatFoodCount;        // 食物总数
	short nScore;               // 总分数
	int nObstacle;              // 障碍物数量
	int nSpeed;                 // 速度
	short nDire;                // 方向
} SNAKEINFO, * PSNAKEINFO;
```

#### 配置文件

```C++
#pragma once
// 配置文件。。。

// 背景色
#define BGCOLOR 0x00
// 文本颜色
#define TXTCOLOR 0x0F

// 默认标题
#define DEFAULTTITLE "贪吃蛇-控制台"

// 默认缓冲区大小
#define DEFAULTPOSITION {122,41}

// 最大横坐标
#define MAXX 60
// 最大纵坐标
#define MAXY 40

// 最大速度
#define MAXSPEED 60

// 默认蛇身大小
#define DEFAULTSNAKEBODY 3

// 方向
#define DIRE_UP 'W'
#define DIRE_DOWN 'S'
#define DIRE_LEFT 'A'
#define DIRE_RIGHT 'D'

// 游戏区域的线
#define WALLBOARD "卍"
// 食物
#define FOOD "☆"
// 蛇
#define SNAKE "●"
// 障碍物
#define OBSTACLE "※"

// 生成障碍物的数量
#define MAXOSTACLESIZE 10

// 一个食物多少分?
#define FOODSCORE 5

// 游戏区域的X范围
#define LINEX 40

// 贪吃蛇活动边界
#define LEFTG 21
#define TOPG 1
#define RIGHTG 59
#define BOTTOMG 39


// 文件信息

#define SNAKEMAPFIELNAME "snake.map"               // 地图
#define SNAKEINFOFILENAME "snake.info"             // 信息: 速度, 食物
#define SNAKEBODYFILENAME "snake.body"             // 蛇的身体
```



## 总结

1. 关于控制台
   - 捕捉鼠标事件(Win10)
     - 修改方式: 右击标题栏-> 选项->取消勾选快速编辑模式
   - 鼠标移动的时候, 打印坐标, Y轴坐标异常, 通过断点步入查看Y轴坐标和打印的不一致
     - 修改方式: 直接保存数据, 打印的不用管
   - 蛇在移动/添加身体的时候坐标混乱
     - 在用push_back的时候会触发默认=号运算符, 进行对象拷贝, 重写=号运算符即可.
   - 调用system之后无法捕获鼠标事件
     - 再次调用`	SetConsoleMode(ConsoleWin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);`
   - 通过vs进行启动和双击.exe文件启动坐标异常
     - 查看是否打印信息到设定的缓冲区外, 如果有, 修正即可.
2. 关于类的职责
   - snake干了很多game该干的事情, 比如计算分数, 打印障碍物, 打印食物, 存档地图 等等.
   - 一开始写的时候每太关注, 写着写着这一块感觉出来了.

