//
//  paint_location.c
//  nevergiveup
//
//  Created by Feiyu Han on 2018/12/20.
//  Copyright © 2018年 Feiyu Han. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "paint_location.h"
#include "DatabaseFunction.h"
#pragma comment(lib,"glut32.lib")


void timerFunc(int nTimerID,MYSQL *mysql,char *query)
{
    switch(nTimerID)
    {
        case REDISPLAYTIMERID:
            //g_c++;
            //标注着窗口需要重新绘制，等到执行glutMainLoop下一次循环时，窗口显示将被回调以重新显示窗口的正常面板
            glutPostRedisplay();
            glutTimerFunc(800,timerFunc,REDISPLAYTIMERID);
            break;
    }
}

//建立一个图的坐标系
//以窗口(10,10)位置处为图的坐标原点，向右是x正方向，向上是y正方向,x和y轴上均以10为刻度
void createCoordinate(GLfloat x0, GLfloat y0)
{
    
    int i = 0, k_x = 800,k_y=500;
    //设置颜色
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    GLfloat lineWidth = 2.0f;
    glLineWidth(lineWidth);
    //画出x y坐标轴
    glBegin(GL_LINES);
    glVertex2f(10.0f, 5.0f);   //纵轴
    glVertex2f(10.0f, 147.0f);
    glVertex2f(9.0f, 143.0f);
    glVertex2f(10.0f, 147.0f);
    glVertex2f(11.0f, 143.0f);
    glVertex2f(10.0f, 147.0f);
    glVertex2f(5.0f, 10.0f);   //横轴
    glVertex2f(197.0f, 10.0f);
    glVertex2f(193.0f, 9.0f);
    glVertex2f(197.0f, 10.0f);
    glVertex2f(193.0f, 11.0f);
    glVertex2f(197.0f, 10.0f);
    glEnd();
    lineWidth = 1.0f;
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    for (i = 1; i <=k_x/10; i++){
        glVertex2f(i*10, x0 + 3.0);
        glVertex2f(i*10, x0);
    }
    for (i = 1; i <= k_y/10; i++){
        glVertex2f(y0 + 3.0, i*10);
        glVertex2f(y0, i*10);
    }
    glEnd();
    
    //绘制四个AP信息
    glColor3f(0.0f, 0.0f, 1.0f);    //设置绘图颜色
    glRectf(10.0f, 10.0f, 20.0f, 20.0f);
    glRasterPos2f(0.0f, 0.0f);
    glRectf(10.0f, 130.0f, 20.0f, 140.0f);
    glRectf(180.0f, 10.0f, 190.0f, 20.0f);
    glRectf(180.0f, 130.0f, 190.0f, 140.0f);
    
}

//绘制位置信息
void scatter(GLfloat location_x,GLfloat location_y,GLfloat x0, GLfloat y0)
{
    // printf("%s\n","lalala");
    location_x=location_x+10;
    location_y=location_y+10;
    GLfloat pointSize = 8.0f;
    glPointSize(pointSize);
    glBegin(GL_POINTS);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(location_x, location_y );
    glEnd();
}
void scatter_1(GLfloat*data_x,GLfloat*data_y,int show_index,GLfloat x0, GLfloat y0)
{
    // printf("%s\n","lalala");
    
    GLfloat location_x=data_x[show_index]+10;
    GLfloat location_y=data_y[show_index]+10;
    GLfloat pointSize = 8.0f;
    glPointSize(pointSize);
    glBegin(GL_POINTS);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(location_x, location_y );
    
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i=1;i<=9;i++)
        if(i!=show_index)
            glVertex2f(data_x[i],data_y[i] );
    
    glEnd();
}
void Display()
{
    extern MYSQL mysql_paint;
    extern GLfloat *data_x;
    extern GLfloat *data_y;
    extern int show_index;
    double *location_data;
    GLfloat x0 = 10.0f, y0 = 10.0f;
    createCoordinate(x0, y0);
    location_data=readData(&mysql_paint);
    if(show_index%10==0)
        show_index=0;
    data_x[show_index]=location_data[0];
    data_y[show_index]=location_data[1];
    show_index++;
    
    scatter(location_data[0],location_data[1],x0, y0);
    //scatter1(data_x,data_y,show_index-1, x0,y0);
    
    //printf("dasdad");
    glFlush();
}
void Initial()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  //清屏颜色
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);   //投影到裁剪窗大小：世界
}

