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