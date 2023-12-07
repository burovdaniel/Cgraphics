//System headers
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
//ENDGOAL: uploading an ascii figure and rotating it

//GOAL: adding depth to the disc

//different approach: draw the circle in 3d space, then project it onto the screen
//x^2 + y^2 = r^2
//How about draw the circle in buffer, then rotate the buffer, then print the buffer

#define SCREEN_WIDTH  110
#define SCREEN_HEIGHT	31

#define pi 3.14

const float radius = 10;
const float thickness = 4;

const float K2 = 5; //constant for zoom
const float K1 = SCREEN_WIDTH*K2*3/(18); //constant for zoom

char  buffer[SCREEN_WIDTH*SCREEN_HEIGHT]; //screen buffer
float Zbuffer[SCREEN_WIDTH*SCREEN_HEIGHT]; //depth buffer stores z values

float A=0; //angle to rotate

int main(void)
{
	printf("\x1b[2J"); //clear screen

	//infinite loop
	for(;;)
	{
		//set buffers
		memset(buffer, ' ', SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(char));
		memset(Zbuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(float));

		//calculate the trigs
		float sinA = sin(A), cosA = cos(A);

		//draw circle
		//sweep thickness
		for(float t=1; t<=thickness; t++)
		{
			//sweep angle
			for(float theta=0; theta < 2*pi; theta+=0.01)
			{
				float circleX = radius*sin(theta)*cosA + t;
				float circleY = radius*cos(theta);

				int xp = (int)(SCREEN_WIDTH/2.0 + circleX);
				int yp = (int)(SCREEN_HEIGHT/2.0 - circleY);

				//debug
				//printf("x: %f, y: %f\n", circleX, circleY);
				//printf("ooz: %f\n", ooz);
				//printf("x: %d, y: %d\n", xp, yp);


				buffer[xp+(yp*SCREEN_WIDTH)] = ':';

			}
		}

		//print the circle
		printf("\x1b[H"); //cursor home
		for(int k=0; k<SCREEN_HEIGHT*SCREEN_WIDTH; k++)
		{
			putchar(k%SCREEN_WIDTH ? buffer[k] : '\n');
		}
		A+=0.01;
		usleep(6000);
	}
	return 0;
}
