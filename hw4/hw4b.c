/*            OLYMPIA AXELOU 2161       12/1/2016
 * 
 * To programma auto ulopoiei tin apothikeusi twn stoixeiwn twn foititwn tou tmimatos 
 * se ena pinaka katakermatismou.
 * 
 * SHMEIWSH:
 *   An kai sto programma xrisimopoiw scanf,   
 *   sti sunartisi main_repeat (periexei to 'menou' kai tis antistoixes epiloges)
 *   kai sugkekrimena stin epilogi A (append) xrisimopoiw fgets gia tin eisagwgi
 *   dedomenwn giati stin ekfwnisi zitaei analutika na elegxoume tin eisodo twn 
 *   dedomenwn (aem,onoma) ws pros tin seira pou ta dinei o xristis, ta 
 *   dedomena pou prepei na dwsei kai tin egkurotita tou aem (>0). 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct student{
	char *name;
	int aem;
}studentT;

typedef struct hashTable{
	int size;
	int num_elements;
	studentT **data;
}hashTableT;

#define INIT_SIZE 7 //to arxiko megethos tou pinaka
#define FORMAT_SIZE 100 /*thewrw oti to megisto dunato string dedomenwn (aem,onoma)  
                         *tha einai 99 (gia tin fgets)*/

void main_repeat (hashTableT *table);
void destroy_table (hashTableT *table);
int insert_hashtable (hashTableT **table, char *new_name, int new_aem);
void print_hashtable (hashTableT *table);
int search_hashtable (hashTableT *table, int aem_to_search);
int delete_hashtable (hashTableT **table, int aem_to_delete);
hashTableT *rehash_table (hashTableT *table);
void init (hashTableT *table);

int main (int argc,char *argv[]){
	
	hashTableT *table;
	
	table = (hashTableT *) malloc (sizeof (hashTableT));
	if (table==NULL)
		return 1;
	
	table->size = INIT_SIZE;
	table->data = (studentT **) malloc (sizeof(studentT) * table->size);
	
	if (table->data==NULL)
		return 1;
	
	init (table);
	
	main_repeat (table);
	
	return 0;
}

/*H sunartisi diagrafei ola ta stoixeia tou pinaka katakermatismou kai apodesmeuei 
 * oli tin mnimi.
 * Pairnei ws parametro ton pinaka katakermatismou.
 * Den epistrefei kati.
 */
void destroy_table (hashTableT *table){
	
	int i;
	
	for (i=0; i<table->size; i++){
		if (table->data[i]!=NULL){
			if (table->data[i]->aem){ //!=0
// 				printf ("free: data[i]=%d\n",i);
				free (table->data[i]->name);
			}
			free (table->data[i]);
		}
	}
	free (table);
}

/*H sunartisi auti ektelei tin enthesi ston pinaka katakermatismou.
 * Pairnei ws parametrous to onoma kai to aem tou neou foititi, ti dieuthinsi tou
 * pinaka katakermatismou (pointer se pointer se struct epeidi sto teleutaio vima 
 * - ston anakatakermatismo - o deiktis table isws deixnei se kainourgia thesi 
 * mnimis h opoia prepei na diatirithei, diladi prepei na tin epistrepsei h 
 * insert_hashtable h opoia einai int).
 * Epistrefei 1 an h enthesi itan epituxis h 0 an itan aneputixis*/
int insert_hashtable (hashTableT **table, char *new_name, int new_aem){
	
	int position, i;
	
	if (search_hashtable (*table, new_aem)!=-1){
		printf ("AEM: %d already exists!\n",new_aem);
		return 0;
	}
	
	position = new_aem % (*table)->size;
	
	i=0;
	while (i<(*table)->size && (*table)->data[position]!=NULL && (*table)->data[position]->aem != 0){
		
		/*An i=size tote exei kanei ena kuklo.
		 * An einai NULL den koitaei to aem.
		 * An den einai NULL kai den einai 0 to aem tote den einai keni.
		 * An den einai NULL kai einai 0 to aem tote einai keni
		 * kai epitrepetai na eggrafei ekei o foititis. */
		
		position = (new_aem + ++i) % (*table)->size;
	}
	
	if (i == (*table)->size){
		printf ("Table is full!\n");
		return 0;
	}
	
	(*table)->data[position]=(studentT *) malloc(sizeof(studentT));
	
	if ( (*table)->data[position]==NULL ){
		(*table)->data[position]=(studentT *) malloc (sizeof (studentT));
		if ((*table)->data[position]==NULL)
			return 0;
	}
	
	(*table)->data[position]->aem = new_aem;
	(*table)->data[position]->name = strdup (new_name);
	
	printf ("Entered [%d, %s] -> %d\n",new_aem,new_name,position);
	
	(*table)->num_elements++;
	*table = rehash_table (*table); 
	return 1;
}

/*Ektupwnei ton pinaka katakermatismou.
 * Pairnei ws parametro ton pinaka.Den epistrefei kati.*/
void print_hashtable (hashTableT *table){
	
	int i;
	
	for (i=0; i<6; i++)
		printf ("-");
	printf (" Size: %d, Elements: %d, Load Factor: %lf ", 
			table->size, table->num_elements,
			(double) table->num_elements / table->size);
	for (i=0; i<6; i++)
		printf ("-");
	printf ("\n\n");
	
	for (i=0; i<table->size; i++){
		if (table->data[i] == NULL)
			printf ("%4d.\tEMPTY\n",i);
		else
			if (table->data[i]->aem == 0)
				printf ("%4d.\tDELETED\n",i);
			else
				printf ("%4d.\t%d\t%s\n",i,table->data[i]->aem,table->data[i]->name);
	}
	printf ("\n");
}

/*H sunartisi auti psaxnei (me vasi ti sunartisi katakermatismou) enan foititi.
 * Pairnei ws parametro ton pinaka kai to aem tou foititi.
 * Epistrefei akeraio pou ekfrazei ti thesi stin opoia vrerthike 
 * h -1 an den vrethei */
int search_hashtable (hashTableT *table, int aem_to_search){
	
	int position, i=0;
	
	position = aem_to_search % table->size;
	
	//elegxei tin thesi pou edwse h sunartisi katakermatismou
	if (table->data[position]==NULL)
		return -1;
	if (table->data[position]->aem==aem_to_search)
		return position;
	
	/*sunexizei tin anazitisi mexri 
	 * na to vrei, na vrei NULL, na kanei kuklo (i==table->size);*/
	for (i=1;i<table->size;i++){
		position++;
		if (position>=table->size){
			position=0;
			continue;
		}
		if (table->data[position]==NULL)
			return -1;
		if (table->data[position]->aem==aem_to_search)
			return position;
	}
	return -1;
}

/* Auti i sunartisi diagrafei enan foititi.
 * Pairnei ws parametro tin dieuthinsi tou pinaka (opws kai stin insert_hashtable, 
 * logw tou anakatakermatismou) kai to aem tou foititi gia diagrafi.
 * An vrethei kai diagrafei to stoixeio tote epistrefei 1
 * diaforetika epistrefei 0 */
int delete_hashtable (hashTableT **table, int aem_to_delete){
	
	int position;
	
	position = search_hashtable (*table, aem_to_delete);
	
	if (position == -1) 
		return 0;
	
	(*table)->data[position]->aem = 0;
	free((*table)->data[position]->name);
	
	(*table)->num_elements--;
	*table = rehash_table (*table);
	
	return 1;
}
/*Ektelei to loop tou menu tis main
 *Pairnei ws paramtro ton pinaka katakermatismou.
 * Den epistrefei kati.
 */
void main_repeat (hashTableT *table){
	
	char choice;
	char format[FORMAT_SIZE], *format_pointer; //estw oti den tha dothei onom/mo megalutero apo 50
	int aem;
	int i, position;
	
	do{
		printf ("Available Actions:\n");
		printf ("\t- Append to Table (A)\n");
		printf ("\t- Search Table (S)\n");
		printf ("\t- Remove from Table (R)\n");
		printf ("\t- Print Table (P)\n");
		printf ("\t- Destroy Table (D)\n");
		scanf (" %c",&choice);
		
		switch (choice){
			
			//Append to table
			case 'A':
				printf ("Enter \"AEM , Name\": ");
				
				getchar(); //gia na kratisei to '\n' epeidi xrisimopoiw meta fgets   
				
				/*xrisimopoiw fgets epeidi prepei na elegksw 
				 * an exoun dothei ola osa xreiazontai
				 * kai sti swsti morfi kai seira */
				fgets (format, FORMAT_SIZE-1, stdin);
				
				if (strlen(format)<FORMAT_SIZE-1)
					format[strlen(format)-1]='\0';
				
				if (!isdigit(format[0])) //diladi den tha exei dothei prwta to aem (xwris keno)
					printf ("Invalid Input!\n");
				else{
					aem = atoi (format);
					if (aem<=0) //elegxos an exei dothei arnitiko aem 
						printf ("Invalid AEM!\n");
					else{
						format_pointer = strchr(format, ',');
						if (format_pointer==NULL) //elegxos an uparxei ',' endiamesa
							printf ("Invalid Input!\n");
						else{
							i=0;
							/*h while uparxei gia na proxwrisei tosa stoixeia wste na 
							 * sunantisei to 1o gramma, diladi to onoma h to '\0' */
							while (!(isalpha(format_pointer[i])) && format_pointer[i]!='\0' )
								i++;
							/*elegxei an exei dothei onoma (an oxi eftase sto telos tou
							 * tou format prin sunartisei gramma, diladi den exei dothei onoma)*/
							if (format_pointer[i]!='\0')
								insert_hashtable(&table, &format_pointer[i], aem);
							else
								printf ("Invalid Input!\n");
						}
					}
				}
				break;
			
			//Search Table
			case 'S':
				printf ("Enter \"AEM\" ");
				scanf ("%d",&aem);
				position = search_hashtable (table, aem);
				if (position==-1)
					printf ("\nAEM: %d Not Found!\n",aem);
				else 
					printf ("\nFound AEM: %d at pos %d\n",aem,position);
				break;
			
			//Remove from table
			case 'R':
				printf ("Enter \"AEM\"\n");
				scanf ("%d", &aem);
				if (delete_hashtable (&table, aem))
					printf ("Deleted AEM: %d\n",aem);
				else 
					printf ("AEM: %d Not Found!\n",aem);
				break;
			
			//Destroy Table and Exit
			case 'D':
				destroy_table(table);
				printf ("Destroy HashTable. Exiting...\n");
				break;
			
			//Print table
			case 'P':
				print_hashtable(table);
				break;
		}
	}while (choice!='D');
}

/*H sunartisi auti allazei to megethos tou pinaka katakermatismou.
 * Pairnei ws parametro ton pinaka.
 * Epistrefei ti dieuthinsi mnimis tou paliou pinaka an uparksei kapoio provlima 
 * desmeusis mnimis. Diaforetika kanei free ton palio pinaka afou dimiourgisei ton
 * kainourgio kai epistrefei tin dieuthinsi mnimis tou kainourgiou pinaka.*/
hashTableT *rehash_table (hashTableT *table){
	
	double load_factor;
	hashTableT *new_table;
	int i, position, old_pos;
	
	load_factor = (double) table->num_elements / table->size;
	
	if (load_factor<0.5 && load_factor>=0.125)
		return table;
	
	//desmeusi mnimis gia to neo pinaka
	new_table = (hashTableT *) malloc (sizeof (hashTableT));
	if (new_table == NULL)
		return table;
	
	//elegxos tou load_factor
	if (load_factor >= 0.5){
		new_table->size = table->size * 2;
		printf ("---- Expanding table from %d/%d to %d ----\n", 
				table->size, table->num_elements, new_table->size);
	}
	else if (load_factor < 0.125){
		new_table->size = table->size / 2;
		if (new_table->size < INIT_SIZE)
			return table;
		printf ("---- Shrinking table from %d/%d to %d ----\n", 
				table->size, table->num_elements, new_table->size);
	}
	
	//desmeusi mnimis gia to new_table->data
	new_table->data = (studentT **) malloc (sizeof (studentT) * new_table->size);
	if (new_table->data == NULL)
		return table;
	
	init (new_table);
	
	/*antigrafi dedomenwn apo to table sto new_table*/
	
	new_table->num_elements = table->num_elements;
	
	for (old_pos=0;old_pos<table->size; old_pos++){
		if (table->data[old_pos] != NULL){
			if (table->data[old_pos]->aem){
				position = table->data[old_pos]->aem % new_table->size;
				i=0;
				while (i<new_table->size){
					
					position = (table->data[old_pos]->aem+i) % new_table->size;
					
					/*oi diathesimes theseis ston neo pinaka einai mono 
					 * oses exoun ton deikti new_table->data[position+i] == NULL
					 * mias kai den uparxoun diegrammena (opws sto insert_hashtable)
					 * gi'auto kai stamataei mono an vrei thesi = NULL */
					if (new_table->data[position+i]==NULL)
						break;
					i++;
				}
				
				/*Den tsekarw an einai mesa sta oria tou pinaka to position 
				 * diladi an exei vrethei thesi eleutheri epeidi 
				 * tha exei sigoura arketes theseis gia ola ta stoixeia
				 * Episis sigoura tha einai NULL i keni thesi pou tha vrei */
				new_table->data[position]=(studentT *) malloc (sizeof (studentT));
				if (new_table->data[position]==NULL)
					return table;
				
				new_table->data[position]->aem=table->data[old_pos]->aem;
				new_table->data[position]->name=strdup(table->data[old_pos]->name);
			}
		}
	}
	destroy_table (table);
	
	return new_table;
}

/*Voithitiki sunartisi. Arxikopoiei kathe deikti tou pinaka table->data me NULL*/
void init (hashTableT *table){
	
	int i;
	
	for (i=0; i<table->size; i++)
		table->data[i]=NULL;
}