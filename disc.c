//System headers
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

//GOAL: hallow disc that rotates around the screen
//			then upload to github and mini  oled display

#define SCREEN_WIDTH  143
#define SCREEN_HEIGHT	40

#define pi 3.14

const float radius = 10;
const float thickness = 3;

char  buffer[SCREEN_WIDTH*SCREEN_HEIGHT]; //screen buffer
float Zbuffer[SCREEN_WIDTH*SCREEN_HEIGHT]; //depth buffer stores z values

float x=0;
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
		//sweep angle
		for(float theta=0; theta < 2*pi; theta+=0.01)
		{
			float circleX = radius*sin(theta);
			float circleY = radius*cos(theta);

			int xp = (int)(SCREEN_WIDTH/2  + circleX*cosA);
			int yp = (int)(SCREEN_HEIGHT/2 - circleY);


			buffer[xp+(yp*SCREEN_WIDTH)] = '.';
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
