/*
标准函数，无需根据openGLES和openGL变更
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "srv_views.h"

using namespace std;

//lookat 视角设置查找表
srv_coords_t srv_coords[] = {
        {0.000000, 88.167992, 291.995667, 0.000000, 25.990564, 33.987663, -0.999456, 0.000000, 0.000000}, // Front adaptive bowl view
        {0.000000, 0.000000, 300.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},     // Top down view
        {0.000000, -260.000000, 160.000000, -5.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000}, // Following eight views pan around the vehicle
        {0.000000, -260.000000, 160.000000, -5.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.897000},
        {0.000000, -260.000000, 160.000000, -5.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.794000},
        {0.000000, -260.000000, 160.000000, -5.000000, 0.000000, 0.000000, 0.000000, 0.000000, 2.691000},
        {0.000000, -260.000000, 160.000000, -5.000000, 0.000000, 0.000000, 0.000000, 0.000000, 3.588000},
        {0.000000, -260.000000, 160.000000, -5.000000, 0.000000, 0.000000, 0.000000, 0.000000, 4.485000},
        {0.000000, -260.000000, 160.000000, -5.000000, 0.000000, 0.000000, 0.000000, 0.000000, 5.382000},
        {0.000000, -260.000000, 160.000000, -5.000000, 0.000000, 0.000000, 0.000000, 0.000000, 6.280000},
        {0.000000, 88.200000, 192.000000, -1.000000, 26.000000, 34.000000, -1.500000, 0.000000, -3.1416},//Back
        {-0.000000, 200.000000, 220.000000, -7.000000, 63.000000, 0.000000, -1.500000, -0.000000, -1.570169}, //Left
        {-0.000000, 200.000000, 220.000000, -7.000000, 63.000000, 0.000000, -1.500000, 0.000000, 1.570169}, //Right
        {-0.000000, -29.049999, 440.000000, -67.374092, -39.541992, 0.000000, 0.000000, -0.000000, 0.000000}, //Left blindspot
        {-0.000000, -29.049999, 440.000000, 67.374092, -39.541992, 0.000000, 0.000000, -0.000000, 0.000000}, //Right blindspot 
        {0.000000, 0.000000, 300.000000, 0.000000, 60.000000, 0.000000, -1.000000, 0.000000, 3.100000}, //zoomed out
        {0.000000, 0.000000, 380.000000, 0.000000, 60.000000, 0.000000, -1.000000, 0.000000, 3.100000}, //zoomed out
        {0.000000, 0.000000, 440.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000}, //zoomed in
        {0.000000, 190.300049, 150.000000, -1.000000, 80.000000, 35.000000, -1.000000, 0.000000, 0.000000}, // FIle DUMP 0
        {0.000000, 190.300049, 150.000000, -1.000000, 80.000000, 35.000000, -1.750000, 0.000000, 0.000000}, // File DUMP 1
        {0.000000, 200.000000, 240.000000, -1.000000, 80.000000, 35.000000, -1.500000, 0.000000, 0.000000}, //Front
        {-15.149982, 149.549988, 257.200226, 3.312001, 38.720036, 35.000000, -1.484400, 0.008200, -3.228336},//Back
        {-0.000000, 197.199997, 240.000000, -1.000000, 66.135956, 35.000000, -1.521800, -0.000000, -1.565569}, //Left
        {-0.000000, 200.000000, 240.000000, -1.000000, 68.776001, 35.000000, -1.500000, 0.000000, 1.570169}, //Right
        {-0.000000, -29.049999, 440.000000, -67.374092, -39.541992, 0.000000, 0.000000, -0.000000, 0.000000}, //Left blindspot
        {-0.000000, -29.049999, 440.000000, 67.374092, -39.541992, 0.000000, 0.000000, -0.000000, 0.000000}, //Right blindspot
        {-15.149982, 149.549988, 257.200226, 3.312001, 38.720036, 35.000000, -1.484400, 0.008200, -3.228336},//Back
        {-0.000000, 197.199997, 240.000000, -1.000000, 66.135956, 35.000000, -1.521800, -0.000000, -1.565569}, //Left
        {-0.000000, 200.000000, 240.000000, -1.000000, 68.776001, 35.000000, -1.500000, 0.000000, 1.570169}, //Right
        {0.000000, 230.300049, 240.000000, -1.000000, 80.000000, 35.000000, -1.500000, 0.000000, 0.000000}, //
        {0.000000, 250.300049, 240.000000, -1.000000, 80.000000, 35.000000, -1.500000, 0.000000, 0.000000}
};

int num_srv_views;

void srv_views_init()
{
	ifstream file("srv_views.txt");
	int nlines = 0;
	string line;

	num_srv_views = (int)(sizeof(srv_coords)/sizeof(srv_coords_t));	

	if(!file.is_open())
	{
		printf("3DSRV: Cannot open srv_views.txt. Using default views\n");
		return;
	}

	while (!file.eof() && (nlines < MAX_SRV_VIEWS))
	{
		getline(file, line);
		sscanf(line.c_str(), "%f, %f, %f, %f, %f, %f, %f, %f, %f",
					&(srv_coords[nlines].camx),
					&(srv_coords[nlines].camy),
					&(srv_coords[nlines].camz),
					&(srv_coords[nlines].anglex),
					&(srv_coords[nlines].angley),
					&(srv_coords[nlines].anglez),
					&(srv_coords[nlines].targetx),
					&(srv_coords[nlines].targety),
					&(srv_coords[nlines].targetz));
		nlines++;
	}
	num_srv_views = nlines;
	file.close();
}
