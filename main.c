//
//  main.c
//  nevergiveup
//
//  Created by Feiyu Han on 2018/12/20.
//  Copyright © 2018年 Feiyu Han. All rights reserved.
//

#include <stdio.h>
#include <mysql.h>
#include <GLUT/GLUT.h>
#include "paint_location.h"
#include "DatabaseFunction.h"

MYSQL mysql_paint;
GLfloat *data_x;
GLfloat *data_y;
int show_index=0;
int main(int argc, const char * argv[])
{
    data_x=malloc( sizeof(GLfloat)*10);
    data_y= malloc( sizeof(GLfloat)*10);
    if(data_x==NULL ||data_y==NULL)
    {
        printf("%s\n","malloc error");
        return 0;
    }
    
    memset(data_x,0,sizeof(float)*10);
    memset(data_y,0,sizeof(float)*10);
   // 与远程数据库连接
    MYSQL mysql=connecttoDatabase();
    mysql_paint = mysql;
    char *query="select * from location_data_1";
    //查询语句
    char *query_init="update location_data set flag = 0";
    updataDatabase(&mysql, query_init);
    //显示远程数据库中的全部数据
    showDatabase(&mysql,query);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("Where Are You ？");
    glutDisplayFunc(Display);
    glutTimerFunc(1000,timerFunc,REDISPLAYTIMERID);
    Initial();
    glutMainLoop();
    //关闭数据库
    mysql_close(&mysql);
    
    free (data_x);
    free (data_y);
    
    return 0;
    
    
}
