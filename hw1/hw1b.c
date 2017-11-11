/*                              AXELOU OLYMPIA 2161
 *Ypologismos nikiti se mia psifoforia  
 *METAVLHTES 
 *max_person:o upopsifios me tis perissoteres psifous
 *max_votes:oi megistoi psifoi pou exei parei kapoios upopsifios
 *
 * Stathera DIAIRETIS : 32768=2^15=10000000 000000000 
 *tin xrisimopoiw gia na vrw an ena atomo psifise ton sugkekrimeno upopsifio h oxi */

#include <stdio.h>
#define DIAIRETIS 32768 

int main (int argc, char *argv[] ) {
	
	unsigned short votes;
	int canditates,i,j,sum_votes,max_person,max_votes=0;
	
	printf ("Enter number of canditates:");
	scanf ("%d",&canditates);
	
	//elegxos eisagwgis dedomenwn apo ton xristi
	while (canditates<=0) {
		printf ("ERROR: The number of canditates must be positive!\n");
		printf ("Enter number of canditates:");
		scanf ("%d",&canditates);
	}
	
	for (i=0 ; i<canditates ; i++) {
		sum_votes=0;
		printf ("Enter votes for canditate %d:",i);
		scanf ("%hx",&votes);
		
		for (j=0 ; j<16 ; j++){ 
		sum_votes+=votes/DIAIRETIS; //votes/DIAIRETIS=0 h =1 analoga me to MSB    
		votes=votes<<1;         
		}
		printf ("\t%d votes\n",sum_votes);
		
		if (sum_votes>max_votes){
			max_person=i;
			max_votes=sum_votes;
		}
	}
	printf ("The winner is canditate %d with %d votes\n",max_person,max_votes);
	
	return 0;
}