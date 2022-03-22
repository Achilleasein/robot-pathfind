#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

//******** Defines *******//
#define MAX_X 16
#define MAX_Y 16
#define LAB_SIZE 16
#define blocked_move 9
//********* END **********//

//******************* Variables *****************//
// 8-BIT variables, variables need to be changes to uint_8 to save space, cant be properly used with gcc due to it understanding them as char and failing the if()s
// Variables are created in specific order due to the nature of C and the way its compiled in low level processors.
// You lose some bytes if you place bigger var types before smaller ones: so the order is uint -> int -> float -> char etc.
int moves[16][16] = {0};
int pos_mov_1, pos_mov_2, pos_mov_3, pos_mov_4; 
int next_x = 0, next_y = 0;
int final_path[256];
int next_move;
int length = 1;//, comp_length; // length calculation
int x = 0,y = 0; // Branching vars on the table
//int branch_x, branch_y; // branching point
//Compare manhattan for ifs
int i = 0,j = 0;
// decimal numbers
float cmp_manhantan;
float calculation;
//logic variables
bool deadend_backtrack = false;
bool center_backtrack = false;
//******************* END *********************//

//*****************FUCNTIONS*******************//
//Currently unused
int choosing_path(int x_diff, int y_diff){
	calculation = abs(7.5 - x) + abs(7.5 - y - 1);
	if ( calculation <= cmp_manhantan && moves[x][y+1] != blocked_move)
	{
		next_move = 2;
		cmp_manhantan = calculation;
		next_x = 0, next_y = 1;
	}
	return 0;
}
//******************* END *********************//

int main(){
    while( abs(15-(x-1+y)) != 1000){
        cout << "Povide possible movment 1:" ;
        cin  >> pos_mov_1;
        cout << "Povide possible movment 2:" ;
        cin  >> pos_mov_2;
        cout << "Povide possible movment 3:" ;
        cin  >> pos_mov_3;
        cout << "Povide possible movment 4:" ;
        cin  >> pos_mov_4; 
        
        cmp_manhantan = 100;
		calculation = 0;
		next_move = 0;
		deadend_backtrack = false;
	if (deadend_backtrack == false)
	{
		// Basic movment pickup
		if (pos_mov_1 == 1)
		{
			if(moves[x-1][y] != blocked_move)
			{
				next_move = 1;
				cmp_manhantan = abs(7.5 - x + 1 ) + abs(7.5 - y);
				next_x = -1 , next_y = 0;
			}
		}
		if (pos_mov_2 == 1)
		{
			calculation = abs(7.5 - x) + abs(7.5 - y - 1);
			if ( calculation <= cmp_manhantan && moves[x][y+1] != blocked_move)
			{
				next_move = 2;
				cmp_manhantan = calculation;
				next_x = 0, next_y = 1;
			}
		}
		if (pos_mov_3 == 1)
		{
			calculation = abs(7.5 - x - 1) + abs(7.5 - y);
			if (calculation <= cmp_manhantan && moves[x+1][y] != blocked_move)
			{
				next_move = 3;
				cmp_manhantan = calculation;
				next_x = 1, next_y = 0;
			}
		}
		if (pos_mov_4 == 1)
		{
			calculation = abs(7.5 - x) + abs(7.5 - y + 1);
			if (calculation <= cmp_manhantan && moves[x][y-1] != blocked_move)
			{
				next_move = 4;
				cmp_manhantan = calculation;
				next_x = 0, next_y = -1;
			}
		}
		// Checking if the movment can be picked, otherways enable backtrack
		if (next_move != 0)
		{
			// Enabling center_backtrack if the center has been found
			// diferentiate the functions becuase it doesnt erase the path that it created.
			// when in the center, there is always a visible movement, e.g. the path that led us there!
			if(abs(15-(x-1+y)) == 0){
				center_backtrack = true;
				next_move = 0;
			}
			else{
				moves[x][y] = next_move;
				final_path[length] = next_move;
				x = x + next_x, y = y + next_y;
				length++;
			}
		}
		// If there is no next movment the deadend backtrack is enabled. 
		// Center and deadend can be true at the same time, which doesnt make sense since in the center we always have movment.
		else{
			deadend_backtrack = true;
			if(center_backtrack == false){moves[x][y] = blocked_move;}
			switch (final_path[length-1]){
				case 1:
					next_move = 3;
					next_x = 1, next_y = 0;
					break;
				case 2:
					next_move = 4;
					next_x = 0, next_y = -1;
					break;
				case 3:
					next_move = 1;
					next_x = -1, next_y = 0;
					break;
				case 4:
					next_move = 2;
					next_x = 0, next_y = 1;
					break;
			}
			final_path[length-1] = 0;
			x = x + next_x, y = y + next_y ;
			length--;
			deadend_backtrack = false;
		}

//***************** Primitive virtualization *******************//
		cout << "    |";
		cout<< "1" << " " << "|";
		for(j=1;j<MAX_Y;j++){
			cout<< " " << j+1;
			if(j< 9){cout << " " << "|";}
			else{cout <<"|";}			// "
		}
		cout  << "\n" << "    ";
		for(j=0;j<MAX_Y;j++){
			cout<<" # |";
		}
		for(i=0;i<MAX_X;i++){
			cout << "\n" ;
			if( i < 9){ cout << " "; }
			cout << i+1 << "# |" ; 
			for(j=0;j<MAX_Y;j++){
					cout << moves[i][j] << " | ";
				}
			}
			cout << "\n" ;
//***************** END *******************//
	}
	}
}
