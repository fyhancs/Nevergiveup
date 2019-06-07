//
//  DatabaseFunction.c
//  nevergiveup
//
//  Created by Feiyu Han on 2018/12/20.
//  Copyright © 2018年 Feiyu Han. All rights reserved.
//

#include "DatabaseFunction.h"
#include "paint_location.h"
#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//与远程数据库建立连接
MYSQL  connecttoDatabase()
{
    MYSQL * connection,  mysql;
    mysql_init(&mysql);
    //user->用户名;psd->密码;db->数据库名称
    //connection = mysql_real_connect(&mysql,"localhost","root","meiyoumima","data_1",3306,NULL,0); 
    connection = mysql_real_connect(&mysql,"localhost",user,psd,db,3306,NULL,0); 
    if (connection == NULL)
    { printf("连接失败:%s\n", mysql_error(&mysql));}
    else
    { printf("连接成功, 服务器版本: %s, 客户端版本: %s.\n", MYSQL_SERVER_VERSION, mysql_get_client_info());}
    return  mysql;
}

void updataDatabase(MYSQL *mysql,char *query)
{
    int flag=mysql_query(mysql, query);
    MYSQL_RES* res = mysql_store_result(mysql);
    if(flag)
    {
        printf("查询失败:%s",mysql_error(mysql));
        return;
    }
    
    mysql_free_result(res);
}

//获取将远程数据库中的数据
//query：SQL语
void showDatabase(MYSQL *mysql,char *query)
{
    mysql_query(mysql, query);        //查询query表示的SQL语句
    //printf("%d\n",status);
    MYSQL_RES* res = mysql_store_result(mysql);    //获得结果,查询的结果将存储在MYSQL_RES结构体中
    if (res) // success
    {
        int num_fields = mysql_num_fields(res); //返回查询结果中的列的数量
        int num_rows = mysql_num_rows(res); //返回查询结果中的行的数量
        printf("\n");
        printf("result: %d rows  %d fields\n", num_rows, num_fields);
        printf("----------------------------\n");
        
        //1. 获得列属性（名称）
        MYSQL_FIELD* fields; //数组，包含所有field的元数据
        fields = mysql_fetch_fields(res);
        for (int i = 0; i < num_fields; ++i)
        {
            printf("%s\t", fields[i].name);
        }
        printf("\n");
        
        //2. 获得每行的数据
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)))
        {
            
            for (int i = 0; i < num_fields; ++i)
            {
                printf("%s\t",  row[i] ? row[i] : "NULL");
            }
            printf("\n");
            
        }
        printf("----------------------------\n");
        mysql_free_result(res);
       
    }
    else
        printf("%s\n","Query result failed！");

}
double *readData(MYSQL *mysql)
{
    char *query="select * from location_data";
    //存储从数据库中取出的位置数据
    double location_data[2],flag=0;
    mysql_query(mysql, query);        //查询query表示的SQL语句
    MYSQL_RES* res = mysql_store_result(mysql);    //获得结果,查询的结果将存储在MYSQL_RES结构体中
    if (res) // success
    {
        //获得每行的数据
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)))
        {
            flag=atoi(row[3]);
            if(!flag)
            {
                printf("%s","location data is:");
                location_data[0]= atoi(row[1]);
                location_data[1]= atoi(row[2]);
                printf("%f %f\n",location_data[0],location_data[1]);
                char *id=row[0];
                id=strcat(id,"'");
                char query_updata[100]="update location_data set flag=1 where id ='";
                char *result=strcat(query_updata,id);
                updataDatabase(mysql, result);
                break;
            }
            
        }
        mysql_free_result(res);
    }
    else
        printf("%s\n","Query result failed！");
    
    return location_data;
    
}


