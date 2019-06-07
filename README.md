# Nevergiveup
Using OpenGL to draw two-dimensional position which plane coordinates that got from MySQL database
First you should configure the OpenGL and MySQL in your computer.(My device system is macOS Sierra 10.12.4,development tool is Xcode 8.3.3)

main.c: 
The main function of this project.

DatabaseFunction.h: 
Introduce the interface of the database.

DatabaseFunction.c: 
How to implement the data interface.

paint_location.h:
Introduce the interface of OpenGL.

paint_location.c:
How to implement the data interface.

PS:  
the database SQL is followed:

create database data_1;

create table location_table 

(
	experiment_id int         null,
  
  location_time datetime(6) null,
  
  src_MAC       varchar(20) null,
  
  location_x    double      null,
  
  location_y    double      null,
  
  flag          int         null
	
);







