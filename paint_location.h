//
//  paint_location.h
//  nevergiveup
//
//  Created by Feiyu Han on 2018/12/20.
//  Copyright © 2018年 Feiyu Han. All rights reserved.
//

#ifndef paint_location_h
#define paint_location_h
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <mysql.h>
#include <math.h>
#include <stdio.h>
#define REDISPLAYTIMERID 1


void timerFunc(int nTimerID,MYSQL *mysql,char *query);
void createCoordinate(GLfloat x0, GLfloat y0);
void scatter(GLfloat location_x,GLfloat location_y,GLfloat x0, GLfloat y0);
void scatter_1(GLfloat *data_x,GLfloat*data_yint ,show_index,GLfloat x0, GLfloat y0);
void Display();
void Initial();
#endif 
/* paint_location_h */
