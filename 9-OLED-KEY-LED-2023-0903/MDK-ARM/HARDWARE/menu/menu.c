#include "menu.h"
#include <stdio.h>
#include "string.h"
#include "lcd.h"
#include "key.h"
#include "led.h"
#include "delay.h"

//各级菜单页面结构体声明  
Menu menu1_main[5]; 
Menu menu2_file[4]; 
Menu menu2_edit[4]; 
Menu menu2_view[4]; 
Menu menu2_set[3]; 
Menu menu3_test[2];  

//结构体初始化//菜单定义,在这里将每一个菜单的关联设置好
Menu menu1_main[5] = // 第1级 主菜单 
{
	{5, "主菜单", "文件          >>", TYPE_SUBMENU, NULL, menu2_file, NULL}, 
	{5, "", "编辑          >>", TYPE_SUBMENU, NULL, menu2_edit, NULL}, 
	{5, "", "视图          >>", TYPE_SUBMENU, NULL, menu2_view, NULL}, 
	{5, "", "设置          >>", TYPE_SUBMENU, NULL, menu2_set, NULL}, 
	{5, "", "帮助          --", TYPE_PARAM, NULL, NULL, NULL}, 
}; 

Menu menu2_file[4] =  // 第2级 文件菜单 
{
	{4, "文件", "open            ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{4, "",     "close           ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{4, "",     "save            ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{4, "",     "exit            ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
};

Menu menu2_edit[4] =  // 第2级 编辑菜单 
{
	{4, "编辑", "cut             ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{4, "",     "copy            ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{4, "",     "paste           ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{4, "",     "delete          ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
};

Menu menu2_view[4] =  // 第2级 视图菜单 
{
	{4, "视图", "open            ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{4, "",     "close           ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{4, "",     "save            ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{4, "",     "ColorText       ", TYPE_PARAM, NULL, NULL, menu1_main}, 
};

Menu menu2_set[3] =  // 第2级 设置菜单 
{
	{3, "设置", "option          ", TYPE_SUBMENU, NULL, NULL, menu1_main}, 
	{3, "",     "set             ", NULL, NULL, NULL, menu1_main}, 
	{3, "",     "on/off test     ", TYPE_SUBMENU, NULL, menu3_test, menu1_main}, 
};

Menu menu3_test[2] =  // 第3级菜单,menu_tool子菜单
{
	{2, "Text", "ON              ", TYPE_PARAM, NULL, NULL, menu2_set}, 
	{2, "",     "OFF             ", TYPE_PARAM, NULL, NULL, menu2_set}, 
};

//颜色测试函数，作为菜单中一个子功能，移植时可以删除
void Test_Color()
{
	u16 ColorTab[8]= {WHITE,BRED,BROWN,YELLOW,BLUE,RED,GREEN,GRAY};//定义颜色数组
	char *ColorText[] = {"WHITE","BRED","BROWN","YELLOW","BLUE","RED","GREEN","GRAY"};
	//绘制显示区域
	LCD_Fill(0,40,lcddev.width,lcddev.height-40,BLACK);
	for(u8 i=0;i<=7;i++)
	{
		LCD_Fill(90,250,390,550,ColorTab[i]);
		Gui_StrCenter(0,220,(u8 *)ColorText[i],24,1);delay_ms(1000);
		LCD_Fill(0,40,lcddev.width,lcddev.height-40,BLACK);
	}
}
//各项功能函数
void Str_Test(const char *str) 
{
	POINT_COLOR = WHITE;
	if(strstr((char *)str,"帮助"))
	{
		LCD_Fill(0,lcddev.height-40,lcddev.width,lcddev.height,BLUE);
		Gui_StrCenter(0,lcddev.height-32,"菜单测试程序",24,1);//居中显示
	}
	if(strstr((char *)str,"ColorText"))
	{
		LCD_Fill(0,lcddev.height-40,lcddev.width,lcddev.height,BLUE);
		Gui_StrCenter(0,lcddev.height-32,"ColorText",24,1);//居中显示
		Test_Color();	
	}
	
	if(strstr((char *)str,"ON"))
	{
		LCD_Fill(0,lcddev.height-40,lcddev.width,lcddev.height,BLUE);
		LED01_ON();  //实际功能函数
		Gui_StrCenter(0,lcddev.height-32,"LED已打开",24,1);//居中显示
	}
	if(strstr((char *)str,"OFF"))
	{
		LCD_Fill(0,lcddev.height-40,lcddev.width,lcddev.height,BLUE);
		LED01_OFF(); //实际功能函数 LED0 LED1关闭
		Gui_StrCenter(0,lcddev.height-32,"LED已关闭",24,1);//居中显示
	}
}

//设置相应项按确定键后执行的函数
//将上面的功能函数 赋值到各功能项
void SetDefaultMenuHandler(MENU_FUN pFun)
{
	menu1_main[4].Function = pFun;
	menu2_view[3].Function = pFun;
	
	menu3_test[0].Function = pFun;
	menu3_test[1].Function = pFun;
}


//定义菜单操作需要的全局变量
Menu *cur_item = menu1_main;  //初始化当前菜单为第一级(main_menu)
Menu *prev_item = NULL;	    //初始化上一级菜单为空
uint8_t item_index = 0;//当前菜单项索引

//绘制测试界面
//str :字符串指针
void DrawTestPage(u8 *str)
{
	//绘制固定栏up
	LCD_Fill(0,0,lcddev.width,40,BLUE);
	//绘制固定栏down
	LCD_Fill(0,lcddev.height-40,lcddev.width,lcddev.height,BLUE);
	POINT_COLOR=WHITE;
	Gui_StrCenter(0,9,str,24,1);  //菜单顶部标题 居中显示
	Gui_StrCenter(0,lcddev.height-32,"",24,1);//菜单底部 居中显示
	POINT_COLOR=RED;
	LCD_ShowString(10,lcddev.height-32,100,30,24, "右键确定",0);
	LCD_ShowString(374,lcddev.height-32,100,30,24, "左键取消",0);
	//绘制显示区域
	LCD_Fill(0,40,lcddev.width,lcddev.height-40,BLACK);
}

void DispCrtMenu(void)//绘制当前菜单项
{
	uint8_t menu_num = cur_item[0].num;//获取当前菜单的项目数量 
	uint8_t i, num = menu_num>MENU_MAX_ROW ? MENU_MAX_ROW : menu_num;//绘制数量不能超过每一屏的最大绘制数量
	if(item_index>=MENU_MAX_ROW || item_index>=menu_num)//菜单项上下选择是否越界 
	{ 
		if(item_index==0XFF)  //此情况为 item_index=0 再按上键，0-1=0XFF
		{
			item_index = menu_num - 1;   //循环，回到最后一个功能索引值
		}
		if(item_index>=menu_num)  //此情况为到达最下面一个功能索引值
		{
			item_index = 0;  //循环，回到第一个功能索引值
		}
		if(item_index>=MENU_MAX_ROW) 
		{
			item_index = 0;
		}
	} 
	DrawTestPage((u8 *)cur_item[0].title);
	
	for (i=0; i<num; i++)//绘制某一级菜单下的功能键 
	{
		POINT_COLOR = RED;
		//Show_Str_1(0, (i+1)*40, (u8 *)cur_item[i].label, 32, i==item_index ? 0:1);//绘制单个菜单项
		LCD_ShowString(144,150+(i+1)*40,200,30,24, (u8 *)cur_item[i].label,i==item_index ? 0:1);
	}
}

#define KEY_ENTER_PRESS  3 //对应原子开发板的左键
#define KEY_RETURN_PRESS 4 //对应原子F4板的右键


void Display(uint8_t value) 
{
	if(value==KEY_UP_PRESS || value==KEY_DOWN_PRESS || value==KEY_ENTER_PRESS || value==KEY_RETURN_PRESS)
	{
		switch(value)//检测按键，进入相应动作
		{
			case KEY_UP_PRESS: 
				item_index--; 
				DispCrtMenu();
				break; 
			case KEY_DOWN_PRESS: 
				item_index++; 
				DispCrtMenu();
				break; 
			case KEY_ENTER_PRESS:
				switch(cur_item[item_index].type)//检测功能项的类型，进入相应动作
				{
					case TYPE_SUBMENU: //具有子菜单的菜单项
						if(cur_item[item_index].next != NULL)
						{ 
							prev_item = cur_item;//此级菜单变成了上一级菜单 
							cur_item = cur_item[item_index].next;//将指向的下一级菜单设置为当前菜单 
							item_index = 0;//重置子菜单项索引 
							DispCrtMenu();
						}
						else
						{
							POINT_COLOR = WHITE;
							LCD_Fill(0,lcddev.height-40,lcddev.width,lcddev.height,BLUE);
							Gui_StrCenter(0,lcddev.height-32,"待设置~~~",24,1);//居中显示
						}
						break; 
					case TYPE_PARAM:  //具有参数设置的菜单项
						if(cur_item[item_index].Function != NULL)
						{ 
							//调用相应的动作函数,并传递参数
							cur_item[item_index].Function((const char *)cur_item[item_index].label);
						}
						else
						{
							POINT_COLOR = WHITE;
							LCD_Fill(0,lcddev.height-40,lcddev.width,lcddev.height,BLUE);
							Gui_StrCenter(0,lcddev.height-32,"待设置~~~",24,1);//居中显示
						}
						break; 
					default: 
						break;
				}
				break; 
			case KEY_RETURN_PRESS: 
				if (prev_item != NULL)//返回上一级菜单的操作 
				{
					cur_item = prev_item;  //设置上一级菜单为当前菜单 
					prev_item = cur_item[0].prev;  //设置当前菜单的上一级菜单 
					item_index = 0;  //重置子菜单项索引
					DispCrtMenu();
				} 
				else
				{
					POINT_COLOR = WHITE;
					LCD_Fill(0,lcddev.height-40,lcddev.width,lcddev.height,BLUE);
					Gui_StrCenter(0,lcddev.height-32,"已是主菜单",24,1);//居中显示
				}
				break; 
		    default: 
		        break;
		}
	}
} 





