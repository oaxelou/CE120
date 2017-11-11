/*AXELOU OLYMPIA 2161 - TSAKOUMAGKOU GRAMMATIKI 2172 
 * To programma auto prosomoiwnei tin eksaplwsi mias purkagias semia perioxi*/


#include<stdlib.h>
#include <time.h>

/* grid dimensions */
#define ROWS 15
#define COLS 15

/* probability that a bush will catch fire if its neighbor is on fire */
#define BUSH_FIRE_PROBABILITY 0.75
/* probability that a tree will catch fire if its neighbor is on fire */
#define TREE_FIRE_PROBABILITY 0.50

/* time units it takes for a tree or a bush to burn completely */
#define TREE_BURN_TIME 5
#define BUSH_BURN_TIME 2


// ================================ Constants ================================

/* Set IS_RANDOM to 1 to get a different grid every time the game starts.
 * Set it to 0 to get the same grid every time */
const int IS_RANDOM = 1; 

/* The possible values of a cell in the grid */
#define BLANK -1
#define FIRE 0  
#define BUSH 1 
#define TREE 2 
#define ROCK 3
#define BURNT 4

/* The terrain grid. This is what gets drawn on the graphics window */
int grid[ROWS][COLS];

/* Helper table. For each cell, it keeps track of how long it has until it 
 * burns down completely. Cells that do not burn (e.g. rocks) have a value of -1 */
int burn_time_left[ROWS][COLS];

/* Helper table. For each cell, it keeps track of whether it should be marked
 * as BURNT at the end of the simulation step. All cells are initialized to BLANK. */
int marked_for_burning_out[ROWS][COLS];

/* AN XREIASTEITE KI ALLO BOITHITIKO PINAKA, DILWSTE TON EDW */
		
void up_low (int i,int j);
void left_right(int i,int j);
void status_change_rows (int i,int j,int neighbor);
void status_change_cols (int i,int j,int neighbor);
void fire_burning_status_change(int i,int j);
/*
 * step()
 * Executes one step (one unit of time) of the fire simulation.
 */
void step() {

	int i,j;
	
	for (i=0; i<ROWS; i++)
			for (j=0; j<COLS; j++) 
				switch (grid[i][j]){
					
					case BUSH:
					case TREE:
						up_low(i,j);
						left_right(i,j);
						break;
						
					case FIRE:
						fire_burning_status_change(i,j);
						break;
				}
		for (i=0; i<ROWS; i++)
			for (j=0; j<COLS; j++) 
				if (marked_for_burning_out[i][j]!=BLANK)
					grid[i][j]=marked_for_burning_out[i][j];
	
	return ;
}

//sunartisi gia ton elegxo twn keliwn pou vriskontai stin prwti kai stin teleutaia grammi
void up_low(int i,int j) { 
	
	if (i>0)
		status_change_cols (i,j,i-1);
	if (i<COLS-1)
		status_change_cols (i,j,i+1);
	return ;
}

//sunartisi gia ton elegxo twn keliwn pou vriskontai stin prwti kai stin teleutaia stili
void left_right(int i,int j) {     
	
	if (j>0)
		status_change_rows (i,j,j-1);
	if (j<ROWS-1)
		status_change_rows (i,j,j+1);
	return ;
}

//sunartisi gia ton elegxo an tha piasei fwtia to keli pou eksetazetai apo ta kelia pou vriskontai panw h katw tou
void status_change_cols (int i,int j,int neighbor) {  
	
	if (grid[neighbor][j]==FIRE) {
		
		if (grid[i][j]==TREE){
			if ( ((rand()%101) /(double) 100) <TREE_FIRE_PROBABILITY){  
				marked_for_burning_out[i][j]=FIRE;
				burn_time_left[i][j]=TREE_BURN_TIME; 
			}
		}
		else {
			if ( ((rand()%101) /(double) 100) <BUSH_FIRE_PROBABILITY){ 
				marked_for_burning_out[i][j]=FIRE;
				burn_time_left[i][j]=BUSH_BURN_TIME;
			}
		}
	}
	return ;
}

//sunartisi gia ton elegxo an tha piasei fwtia to keli pou eksetazetai apo ta kelia pou vriskontai deksia h aristera tou
void status_change_rows (int i,int j,int neighbor) { 
	
	if (grid[i][neighbor]==FIRE) {
		
		if (grid[i][j]==TREE){
			if ( ((rand()%101) /(double) 100) <TREE_FIRE_PROBABILITY){  
				marked_for_burning_out[i][j]=FIRE;
				burn_time_left[i][j]=TREE_BURN_TIME; 
			}
		}
		else {
			if ( ((rand()%101) /(double) 100) <BUSH_FIRE_PROBABILITY){ 
				marked_for_burning_out[i][j]=FIRE;
				burn_time_left[i][j]=BUSH_BURN_TIME;
			}
		}
	}
	return ;
}

//sunartisi pou kaleitai an to keli pou eksetazetai exei piasei fwtia.meiwnei to xrono pou apomenei kai otan ftasei sto mhden to metatrepei se BURNT
void fire_burning_status_change(int i,int j){       
	
	if (burn_time_left[i][j]!=0)
		burn_time_left[i][j]--;

	if (!(burn_time_left[i][j]))
		marked_for_burning_out[i][j]=BURNT;
	return ;
}
