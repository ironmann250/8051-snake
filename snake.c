#include <reg52.h>
#define LEFT 4
#define RIGHT 5
#define UP 6
#define DOWN 7
#define TIME 100
#define WIDTH 8
#define HEIGHT 8

sbit selectionLatch=P2^7;
sbit dataLatch=P2^6;

void delay(char x);
char calc_p0 (char n,char r);
void display();
char can_move(char direction);
void move(char direction);
void translate_board_to_mat();
void shedBody();
void transpose();

sbit col0 = P2^0;
sbit col1 = P2^1;
sbit col2 = P2^2;
sbit col3 = P2^3;
sbit col4 = P2^4;
sbit col5 = P2^5;
sbit col6 = P2^6;
sbit col7 = P2^7;
sbit row0 = P0^0;
sbit row1 = P0^1;
sbit row2 = P0^2;
sbit row3 = P0^3;
sbit row4 = P0^4;
sbit row5 = P0^5;
sbit row6 = P0^6;
sbit row7 = P0^7;

//machine state / framerate
xdata long double machineState=0;
xdata long double dispWait=15;
//xdata long double moveWait=150;
xdata long double previousState=0;


pdata char mat[8][8]={
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1},
};

xdata char board[8][8]={
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,8,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,2,2},
};
//snake attributes
pdata char snake[20][2]={{7,5},{7,6},{7,7}};
char snakeSize=3;
char direction=LEFT;

//controls
sbit up_button=P3^4;
sbit down_button=P3^5;
sbit left_button=P3^6;
sbit right_button=P3^7;
void main()
{
//turns[0]=-1;
	//invert();//invert mat
	transpose();
	transpose();
	transpose();
	//invert();
	while(1)
	{
		//=0xff;
		//P2=0;
		display();
		machineState++;
	    delay(1);
		
		//=0xff;
		//P2=0;
		if(up_button==0)
		{
			direction=UP;
		}
		if (left_button==0)
		{
			direction=LEFT;
		}
		if (right_button==0)
		{
			direction=RIGHT;
		}
		if (down_button==0)
		{
			direction=DOWN;
		}
		display();
		
		if (machineState - previousState> dispWait)
        {
		//shedBody();
		move(direction);
		previousState=machineState;
		transpose();
		transpose();
		transpose();
        }
	}
}

void delay(char x)
{
	char y;
	while(x--)
		for(y = 0; y<120; y++);

}

void display()
{
	char i;
	
for(i =0; i<8; i++)
		{
			
			row0 = mat[i][0];
			row1 = mat[i][1];
			row2 = mat[i][2];
			row3 = mat[i][3];
			row4 = mat[i][4];
			row5 = mat[i][5];
			row6 = mat[i][6];
			row7 = mat[i][7];
			col7 = calc_p0(i,0);
			col6 = calc_p0(i,1);
			col5 = calc_p0(i,2);
			col4 = calc_p0(i,3);
			col3 = calc_p0(i,4);
			col2 = calc_p0(i,5);
			col1 = calc_p0(i,6);
			col0 = calc_p0(i,7);
			//delay(t);
		}
}

char calc_p0 (char n,char r)//n is current mat row, r is loop i
{
char j,sum=0;
for (j=0;j<8;j++)
{
	sum+=mat[n][j];
}
 if ((n == r) && sum>0)
 {
     return 0;
 }
 else
 {
     return 1;
 }

}
void transpose()
{
	char i,j,temp,n=8;
	for (i=0;i<n/2;i++) 
  { 
    for (j=i;j<n-i-1;j++) 
    { 
        // Swapping elements after each iteration in Clockwise direction
            temp=mat[i][j]; 
            mat[i][j]=mat[n-1-j][i]; 
            mat[n-1-j][i]=mat[n-1-i][n-1-j]; 
            mat[n-1-i][n-1-j]=mat[j][n-1-i]; 
            mat[j][n-1-i]=temp; 
    } 
  }
}

char can_move(char direction)
{
	char snakeHeadx=snake[0][0];
	char snakeHeady=snake[0][1];
    //printf("%d",board[snakeHeadx-1][snakeHeady]);
	switch(direction)
	{
	case (UP):
	if (board[snakeHeadx-1][snakeHeady] != 0)
	{
		return 0;
	}
    return 1;
	break;

	case (DOWN):
	if (board[snakeHeadx+1][snakeHeady] != 0)
	{
		return 0;
	}
    return 1;
	break;

	case (LEFT):
	if (board[snakeHeadx][snakeHeady-1] != 0)
	{
		return 0;
	}
    return 1;
	break;

	case (RIGHT):
	if (board[snakeHeadx][snakeHeady+1] != 0)
	{
		return 0;
	}
	break;
    return 1;
	default:
	return 1;
	break;
	}
}

void get_dir_coord(char *coord,char x, char y, char direction) //send x,y of where to go
{
switch(direction)
	{
	case (UP):
	coord[0]=x-1;coord[1]=y;
	return;
	break;

	case (DOWN):
	coord[0]=x+1;coord[1]=y;
	return;
	break;

	case (LEFT):
	coord[0]=x;coord[1]=y-1;
	return;
	break;

	case (RIGHT):
	coord[0]=x;coord[1]=y+1;
	return;
	break;
	}
}

void where_s_empty(char *coord)
{
	char x,y;//x,y in reference to mat/board
	for (x=0;x<8;x++)
	{
		for (y=0;y<8;y++)
		{

			if (board[x][y]==9)
			{
				coord[0]=x;coord[1]=y;
				return;
			}
		}
	}
	return;
}

void translate_board_to_mat()// output a matrix of 1s and 0s 
{
	char x,y;
	for (x=0;x<8;x++)
	{
		for(y=0;y<8;y++)
		{
			if (board[x][y]!=0)
			{
				mat[x][y]=1;
			}
			else
			{
				mat[x][y]=0;
			}

		}
	}
}

void shedBody() //a pun :) recalculate body
{
	char x,y,pnt=0;
	for(x=0;x<8;x++)
	{
		for(y=0;y<8;y++)
		{

			if (board[x][y]==1)
			{
				snake[pnt][0]=x;
				snake[pnt][1]=y;
				pnt++;
			}
		}
	}
	for(x=0;x<8;x++)
	{
		for(y=0;y<8;y++)
		{

			if (board[x][y]==2)
			{
				snake[pnt][0]=x;
				snake[pnt][1]=y;
				pnt++;
			}
		}
	}
    snakeSize=pnt;
}

void move(char direction)
{
	char i,next[2]={0,0},ec[2]={-1,-1},curx=snake[0][0],cury=snake[0][1];

	if (can_move(direction))
	{

    	get_dir_coord(next,curx,cury,direction); //see where to go
	board[next[0]][next[1]]=1;//put a 2 in the desired x,y
    	board[curx][cury]=9;//leave where we are (put 9)

	for (i=0;i<snakeSize;i++)
	{

    where_s_empty(ec);
    board[ec[0]][ec[1]]=2;
    board[snake[i][0]][snake[i][1]]=9;
	}
	board[snake[i-1][0]][snake[i-1][1]]=0;//put zero at the tail
	shedBody();//get new snake array
	translate_board_to_mat();
	
    return;
	}
	else
	{
		return;
	}
}