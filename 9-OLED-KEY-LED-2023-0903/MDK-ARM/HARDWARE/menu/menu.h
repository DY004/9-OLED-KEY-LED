#ifndef __MENU_H
#define __MENU_H
#include "sys.h"
#include "stm32f4xx.h"

#define MENU_MAX_ROW 5 // 菜单最大显示行数 

//定义菜单中功能项的类型
#define TYPE_SUBMENU 101  //具有子菜单的菜单项
#define TYPE_PARAM   102  //参数项（用于执行参数设置）

typedef void (*MENU_FUN)(const char *);

//定义菜单
typedef struct menu
{
	uint8_t num;        //当前菜单功能项总数
	char * title;       //当前菜单标题
	char * label;       //功能项标题
	uint8_t type;       //当前功能项的类型
	MENU_FUN Function;  //选择某一功能后执行的功能函数
	struct menu *next;  //下一级菜单
	struct menu *prev;  //上一级菜单

} Menu;

void DrawTestPage(u8 *str);
void DispCrtMenu(void);      //绘制当前菜单项
void Display(uint8_t value);

void Str_Test(const char *str);
void SetDefaultMenuHandler(MENU_FUN pFun);

#endif

