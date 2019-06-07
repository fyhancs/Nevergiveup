//
//  DatabaseFunction.h
//  nevergiveup
//
//  Created by Feiyu Han on 2018/12/20.
//  Copyright © 2018年 Feiyu Han. All rights reserved.
//

#ifndef DatabaseFunction_h
#define DatabaseFunction_h
#include <stdio.h>
#include <mysql.h>
#include "paint_location.h"
#include <stdio.h>

MYSQL connecttoDatabase();
void showDatabase(MYSQL *mysql,char *query);
double * readData(MYSQL *mysql);
void updataDatabase(MYSQL *mysql,char *query);
double *readData(MYSQL *mysql);
#endif /* DatabaseFunction_h */
