/* TSAKOUMAGKOU GRAMMATIKI 2172 - AXELOU OLYMPIA 2161 
 * To programma auto ulopoiei enan apokwdikopoihti aplis morfis.
 */

#include <stdio.h>

#define MAX_SIZE 1024
#define FIRST_PRINTABLE 32  //to ' '
#define NUMBER_OF_PRINTABLES '~'-' '+1  //to diastima twn ektupwsimwn xaraktirwn

int main (int argc, char *argv[]){
	
	int i=0,size,freq[NUMBER_OF_PRINTABLES]={0},max_freq,key; 
	char encoded[MAX_SIZE],max_freq_char,decoded[MAX_SIZE];
	
	encoded[i]=getchar();
	while ((i<MAX_SIZE)&&(encoded[i]!=EOF)) {
		i++;
		encoded[i]=getchar();
	}
	size=i;
	
	//euresi tis suxnotitas olwn twn xaraktirwn
	for (i=0; i<size; i++)
		if (encoded[i]>=FIRST_PRINTABLE)
			freq[encoded[i]-FIRST_PRINTABLE]++;
	
	//euresi tou max_freq
	i=0;
	max_freq=freq[i];
	max_freq_char=i+FIRST_PRINTABLE;
	for (i=1; i<NUMBER_OF_PRINTABLES; i++)
		if (freq[i]>max_freq) {
			max_freq=freq[i];
			max_freq_char=i+FIRST_PRINTABLE;  // to teliko max_freq_char einai to keno kwdikopoihmeno
		}
	key=max_freq_char-' '; //to kleidi einai h diafora tou kenou (ws kwdikopoihmenou xaraktira) apo ton antistoixo mh-kwdikopoihmeno
	
	printf ("KEY: %d\n\n",key);
	printf ("TEXT: ");
	
	for (i=0;i<size;i++){
		if (encoded[i]=='\n'){ //to \n den einai ektupwsimos xaraktiras ara den exei kwdikopoihthei.Sunepws den xreiazetai apokwdikopoihsh
			decoded[i]='\n';   
			continue;          
		} 
		decoded[i]=encoded[i]-key;
		if (decoded[i]<FIRST_PRINTABLE)
			decoded[i]=NUMBER_OF_PRINTABLES+decoded[i];
	}
	for (i=0; i<size; i++)
		printf ("%c",decoded[i]);
	printf ("\n");
	
	return 0;
}