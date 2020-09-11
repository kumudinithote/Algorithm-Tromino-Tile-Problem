
#include <stdio.h>
#include <stdlib.h>
int ** board;
int ** dummy;
int** createBoard(int,int,int);
void printOutput(int);
int pasteTile(int, int, int);
void putTromino(int, int,int,int,int,int, int);
int getTrominoType(int,int);
int block=5;


int main()
{
     int board_size,
         x_missing,  /* x coordinate of missing square */
         y_missing;  /* y coordinate of missing square */
         int k;
     do {
          printf( "\n-------------------------------------" );
          printf( "\nEnter size of board (need to be 2^n) (0 to quit): " );
          scanf( "%d", &board_size );
          if ( board_size ) {
               printf( "\nEnter coordinates of missing square (separated by space): " );
               scanf( "%d%d", &x_missing, &y_missing );
               printf( "\n\nTiling\n------\n" );

               for(int i=0;i<k;i++){
		               board_size = 2*board_size;
	             }
               board = createBoard(board_size,x_missing,y_missing);
               dummy = createBoard(board_size,x_missing,y_missing);

               pasteTile(board_size,0,0);
               printf("\n\n");
	             printOutput(board_size);


          }
     } while ( board_size );

     return EXIT_SUCCESS;
}

int ** createBoard(int board_size,int x_missing,int y_missing){
	int ** array = (int**)malloc(board_size*sizeof(int *));
	int i,j;
  for(i = 0;i < board_size; i++){
    array[i] = (int*)malloc(board_size*sizeof(int));
  }

  for(j = board_size-1; j >= 0; j--){
    for(i = 0;i < board_size; i++) {
      if((i==x_missing) && (j==y_missing))
				array[i][j]= -1;
			else
	       array[i][j] = 0;
    }
  }
	return array;
}


void printOutput(int board_size){
  for(int j = board_size-1; j >= 0; j--){
		for(int i = 0;i < board_size; i++)  {
      if(dummy[i][j] == 1)
        printf(" %s ","UR");
      if(dummy[i][j] == 2)
        printf(" %s ","UL");
      if(dummy[i][j] == 3)
        printf(" %s ","LR");
      if(dummy[i][j] == 4)
        printf(" %s ","LL");
      if(dummy[i][j] == -1)
        printf(" %s ","MS");
		}
		printf("\n");
	}
}

int pasteTile(int board_size, int x_origin, int y_origin){
  int hole_hr = 0;
  int hole_vt = 0;

  if(board_size == 2){
    int temp = getTrominoType(x_origin,y_origin);
		for(int i=0;i<board_size;i++) {
			for(int j=0;j<board_size;j++){
				if(board[x_origin+i][y_origin+j]==0){
            dummy[x_origin+i][y_origin+j] = temp;
        }
			}
		}
		return 0;
	}

  for(int i=x_origin;i<x_origin+board_size;i++) {
		for(int j=y_origin;j<y_origin+board_size;j++){
			if(board[i][j]!=0) {
				hole_hr=i; hole_vt=j;
			}
		}
	}


  if(hole_hr< x_origin + board_size/2 && hole_vt < y_origin+ board_size/2) {
		putTromino(1 ,x_origin+board_size/2, y_origin+ (board_size/2) - 1,x_origin+board_size/2,y_origin+board_size/2,x_origin+board_size/2-1,y_origin+board_size/2);
	}
	else if(hole_hr>=x_origin+ board_size/2 && hole_vt < y_origin + board_size/2) {
		putTromino(2,x_origin+board_size/2-1,y_origin+ (board_size/2) ,x_origin+(board_size/2),y_origin+(board_size/2),x_origin+board_size/2-1,y_origin+board_size/2-1);
	}
	else if(hole_hr < x_origin + board_size/2 && hole_vt >= y_origin + board_size/2) {
		putTromino(3,x_origin+(board_size/2),y_origin+ (board_size/2)-1,x_origin+(board_size/2),y_origin+board_size/2,x_origin+(board_size/2)-1,y_origin+(board_size/2) -1);
	}
	else if(hole_hr >= x_origin + board_size/2 && hole_vt >= y_origin + board_size/2) {
		putTromino(4,x_origin+(board_size/2) -1, y_origin+ (board_size/2),x_origin+(board_size/2),y_origin+(board_size/2) -1,x_origin+(board_size/2)-1,y_origin+(board_size/2)-1);
	}

  pasteTile(board_size/2, x_origin+board_size/2, y_origin);
	pasteTile(board_size/2, x_origin+board_size/2, y_origin+board_size/2);
	pasteTile(board_size/2, x_origin, y_origin+board_size/2);
  pasteTile(board_size/2, x_origin, y_origin);

  return 0;
}

void putTromino(int quadrant, int x1,int y1,int x2,int y2,int x3, int y3) {
	board[x1][y1] = board[x2][y2] = board[x3][y3] = block;
  dummy[x1][y1] = dummy[x2][y2] = dummy[x3][y3] = quadrant;

}

int getTrominoType(int x_origin, int y_origin) {
  if(board[x_origin][y_origin] != 0)
  {
    return 1;
  }else if(board[x_origin+1][y_origin+1]!= 0)
  {
    return 4;
  }else if(board[x_origin][y_origin+1]!= 0)
  {
    return 3;
  }else if(board[x_origin+1][y_origin]!= 0)
  {
    return 2;
  }

  return 0;
}
