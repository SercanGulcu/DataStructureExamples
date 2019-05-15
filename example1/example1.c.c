#include <stdio.h>


int Floor[20][20] = { {0} };
int xpos = 0;
int ypos = 0;
enum Pen { DOWN, UP };
int startflag = 0;

void move(const int degree, const int pen);
void print();
int normal_degr(int degree);

int main()
{
    int input;
    int pen = UP;
    int degree = 0;		
    while (1) {
	scanf("%d", &input);
	switch (input) {
	case 1:
	    pen = UP;
	    break;
	case 2:
	    pen = DOWN;
	    break;
	case 3:
	    degree += 90;
	    degree = normal_degr(degree);
	    break;
	case 4:
	    degree -= 90;
	    degree = normal_degr(degree);
	    break;
	case 5:
	    move(degree, pen);
	    break;
	case 6:
	    print();
	    break;
	case 9:
	    return 0;
	}		
    }				
}

int normal_degr(int degree)
{
    int temp;
    if (degree < 0)
	temp = 360 + degree;
    else if (degree >= 360)
	temp = degree - 360;
    else
	temp = degree;
    return temp;
}

void move(const int degree, const int pen)
{
    int step;
    int i;
    int x_pos;
    int y_pos;

    if (degree == 0) { // right
	x_pos = 0;
	y_pos = 1;
    } else if (degree == 90) { // down
	x_pos = 1;
	y_pos = 0;	
    } else if (degree == 180) { // left
	x_pos = 0;
	y_pos = -1;
    } else if (degree == 270) { //up
	x_pos = -1;
	y_pos = 0;	
    }

    scanf("%d", &step);

    for (i = 0; i < (step-1); i++) {

	xpos += x_pos;
	if (xpos < 0) {
	    xpos = 0;
	} else if (xpos > 20) {
	    xpos = 20;
	}

	if(startflag == 0 && pen == DOWN) {
		Floor[xpos][ypos] = 1;
		step++;
		startflag++;
	} else ypos += y_pos;
	
	if (ypos < 0) {
	    ypos = 0;
	} else if (ypos > 20) {
	    ypos = 20;
	}

	if (pen == DOWN) {
	    Floor[xpos][ypos] = 1;
	}
    }


}
void print()
{
    int i, j;
    for (i = 0; i < 20; i++) {
	for (j = 0; j < 20; j++)
	printf("%d",Floor[i][j]);
	printf("\n");
    }
}
