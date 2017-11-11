/*                            AXELOU OLYMPIA 2161 
 *to programma auto zwgrafizei ena nao parametrika ws pros tous kiones tou
 * 
 * epilegw o arithmos twn kionwn na einai artios (ara number_pillar artios)
 * kai o megistos arithmos kionwn na einai 16 (PILLAR_MAX)
 *
 * STATHERES:
 * SPACE_PILLAR:oi 4 theseis keno endiamesa apo kathe kiona
 * WIDTH_PILLARS:oi 4 theseis pou katalambanei kathe kionas
 * LENGTH_PILLARS: to upsos twn kionwn (8)
 * NUMBER_CHARS:posoi diaforetikoi xaraktires apo teloun to aetoma
 * WIDTH_CHAR:poses theseis pianoun dyo synexomenoi idioi xaraktires
 */

#include <stdio.h>
#define PILLAR_MAX 16 

int main (int argc , char *argv[] ) {
	
	
	int number_pillar,i,j,k;
	const int WIDTH_CHAR=2,NUMBER_CHARS=4,SPACE_PILLAR=4; 
	const int LENGTH_PILLARS=8,WIDTH_PILLARS=4;
	char symbol[]={'_','.','-','\''};
	
	printf ("Number of pillars:");
	scanf ("%d",&number_pillar);
	
	while (!((number_pillar>0)&&(number_pillar%2!=1)&&(number_pillar<=PILLAR_MAX))){
		printf ("Invalid number of pillars.Try again. \n");
		scanf ("%d",&number_pillar);
	}
	
	//first part (aetoma)
	for (i=1 ; i<=number_pillar/2 ; i++) {
		
		/*first half
		 *sto 1o miso to aetoma exei ti morfi tis deuteris diagwniou enos    
		 *tetragwnikou pinaka.Ara oi sunthikes stis 'for' gia ta kena 
		 *prin apo ta sumbola tha akolouthoun
		 *tin kinisi j(i)=N-i, gia i=1,..,N opou N to megethos tou pinaka
		 *( number_pillar/2 diladi)*/
		for (j=0 ; j<number_pillar/2-i ; j++)
			for (k=0 ; k<WIDTH_CHAR*NUMBER_CHARS ; k++)
				printf (" ");
		for (j=0 ; j<NUMBER_CHARS ; j++)
			for (k=0 ; k<WIDTH_CHAR ; k++)
				printf ("%c",symbol[j]);
		
		//gap between the first and the second half
		for (j=0;j<2*(i-1);j++)
			for (k=0 ; k<WIDTH_CHAR*NUMBER_CHARS ; k++)
				printf (" ");
		
		//second half
		for (j=NUMBER_CHARS-1 ; j>=0 ; j--)
			for (k=0 ; k<WIDTH_CHAR ; k++)
				printf ("%c",symbol[j]);
		printf ("\n");
	}

	//second part (kiones)
	
	for (i=0 ; i<number_pillar*(SPACE_PILLAR+WIDTH_PILLARS) ; i++)
		printf ("=");
	printf ("\n");
	
	for (i=0;i<number_pillar;i++)
		for (j=0;j<WIDTH_PILLARS;j++)
			printf ("[]");
	printf ("\n ");
	
	for (i=0;i<number_pillar;i++){
		printf ("@.==.@");
		for (j=0; j<2;j++)
			printf (" ");
	}
	printf ("\n");
	
	for (i=0;i<LENGTH_PILLARS-1;i++){
		for (j=0;j<2; j++)
			printf (" ");
		for (j=0;j<number_pillar ; j++){
			printf ("|''|");
			if (i<LENGTH_PILLARS)	
				for (k=0;k<SPACE_PILLAR;k++)
					printf (" ");
			else {
				if (j==number_pillar-1)
					break;
				for (k=0;k<WIDTH_PILLARS;k++)
					printf ("_");
			}
		}
		printf ("\n");
	}

	//third part (skales)
	for (j=2 ; j>=0 ; j--) {
		for (i=0; i<j;i++)
			printf (" ");      
		for (i=0 ; i<WIDTH_PILLARS*(number_pillar*2-1)+(2-j)*2  ; i++)
			printf ("=");
		printf ("\n");
	}

	return 0;
}