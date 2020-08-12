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
// OLA TA VARIABLES EINAI GLOBAL, DEN EXO KSEKATHARISEI TI XREIAZETAI KAI TI OXI//
// 8-BIT variables, den tis usaro akoma san uint_8 giati tis katalavainei san char kai den kanei sosta tis if()
int moves[16][16] = {0}; //apothikeuoume tis kiniseis gia to traversal tou lavirinthou
int pos_mov_1, pos_mov_2, pos_mov_3, pos_mov_4; //pithanes metakiniseis dosmenes apo to PID
int next_x = 0, next_y = 0; //ti tha prostheso sto x,y gia na ipologiso to epomeno
int final_path[256]; //to teliko monopati
int next_move; //i epomeni kinisi pou tha ekteleso
// normal variables
int length = 1;//, comp_length; // metrisi mikous monopatiou
int x = 0,y = 0; //metavlites metakinisis pano ston pinaka
//int branch_x, branch_y; // simeio diakladosis
//Compare manhattan gia elegxo ton if kai ekxorisi timis stin moves
int i = 0,j = 0;
// decimal numbers
float cmp_manhantan;
float calculation;
//logic variables
bool deadend_backtrack = false;
bool center_backtrack = false;
//******************* END *********************//

//*****************FUCNTIONS*******************//
//mporei na xreiastei gia melontiki xrisi veltistopoiisis
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
        cout << "Dose to possible movment 1:" ;
        cin  >> pos_mov_1;
        cout << "Dose to possible movment 2:" ;
        cin  >> pos_mov_2;
        cout << "Dose to possible movment 3:" ;
        cin  >> pos_mov_3;
        cout << "Dose to possible movment 4:" ;
        cin  >> pos_mov_4; 
        
        cmp_manhantan = 100;
		calculation = 0;
		next_move = 0;
		deadend_backtrack = false;
	if (deadend_backtrack == false)
	{
		// vasiki for epilogi kinisis
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
		//elegxo an mporesa na epilekso kinisi, an den ta katafera tote energopoio to backtrack
		if (next_move != 0)
		{
			//energopoio to center_backtrack an exo vrei to kentro
			//diaforopoiei tis sinartiseis kathos den svinei to monopati to opoio exo idi diasxisei
			//panta otan eimai sto kentro tha exo epomeni kinisi, ara panta tha vlepei auto to komati
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
		//an den vrisko epomeni kinisi energopoio to deadend backtrack, 
		//to center kai to deadend mporoun na einai true tautoxrona
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

//*****************OPTIKOPOIISI*******************//
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
//*****************TELOS*******************//
	}
	}
}
