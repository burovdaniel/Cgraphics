//System headers
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
//ENDGOAL: uploading an ascii figure and rotating it

//GOAL: adding shading to the figure

#define SCREEN_WIDTH  130
#define SCREEN_HEIGHT	35

#define pi 3.14

const float radius = 11;
const float thickness = 4;


//Still don't understand these
const float K1 = 55; //distance from eye to screen
const float K2 = 55;


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
			for(float theta=0; theta < 2*pi; theta+=0.001)
			{
				float circleX = radius*sin(theta)*cosA + t;
				float circleY = radius*cos(theta);

				float z = K2 + t;
				float ooz = 1/z;

				int xp = (int)(SCREEN_WIDTH/2.0 + circleX*K1*ooz);
				int yp = (int)(SCREEN_HEIGHT/2.0 - circleY*K1*ooz);

				//Lighting
			 	float L =  sin(theta); //normal vector * light vector(1,0,1)
				L = (L+1)/2; //normalize

				//debug
				//printf("%f\n", L);

				if(L>0)
				{
					//set the zbuffer
					if(ooz>Zbuffer[xp+(yp*SCREEN_WIDTH)])
					{
						Zbuffer[xp+(yp*SCREEN_WIDTH)] = ooz;
						//set the buffer
						buffer[xp+(yp*SCREEN_WIDTH)] = ".,-~:;=!*#$@"[(int) (L*8)];
					}
				}
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
