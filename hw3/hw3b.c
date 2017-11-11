/*AXELOU OLYMPIA - 2161 - 15/12/2015 
 * To programma auto apothikeuei ta stoixeia kai tous vathmous enos arithmou foititwn se 	* pinaka apo structs, 
 * ta taksinomei me vasi to onoma kai se periptwsi sunonimias to aem,
 * xrisimopoiei kapoious sugkekrimenous algorithmous (insertion, selection sort,binary search),
 * vriskei kapoio atomo me vasi to onoma kai ektupnwei ta apotelesmata. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STUDENTS 100+1 //einai +1 giati exw rithmisi na dexetai to string k meta na to tsekarei an aem<0
#define NAME_SIZE 26
#define SIZE 39      //to max plithos xaraktirwn einai 37 + 2 apo tin fgets
#define NAME_POS 6   //i thesi ston pinaka apo opou ksekina to onoma
#define GRADE_POS 32 //i thesi apo opou ksekia o vathmos

struct studentData {
	int aem;
	char name[NAME_SIZE];
	double grade;
};
typedef struct studentData studentDataT;

//functions' prototypes
int insert_info(studentDataT *all_students);
void initialize_students(studentDataT *all_students, int num_of_students);
void print_students(studentDataT *all_students, int num_of_students);
void separator_output();
void selection_sort(studentDataT *all_students, int num_of_students);
void insertion_sort(studentDataT *all_students, int num_of_students);
int find_name_aem(studentDataT *all_students, int num_of_students,char *name_to_search,int aem_to_search);
void find_all_records(studentDataT *all_students, int num_of_students,char *name_to_search);

int main (int argc,char *argv[]){
	
	char name_to_search[NAME_SIZE];
	int num_of_students,aem_to_search,pos_found;
	studentDataT all_students[MAX_STUDENTS];
	
	//Eisodos Dedomenwn
	num_of_students=insert_info(all_students);
	
	printf ("\n");
	print_students ( all_students, num_of_students);
	
	initialize_students( all_students, num_of_students);
	
	//Taksinomisi
	separator_output ();
	printf("\n");
	
// 	selection_sort (all_students,num_of_students);
	
	insertion_sort (all_students,num_of_students);
	
	print_students (all_students,num_of_students);
	
	//Anazitisi
	separator_output ();
	
	printf ("Enter name: ");
	scanf ("%26s",name_to_search);
	
	printf ("Enter ID: ");
	scanf ("%d",&aem_to_search);
	
	printf ("\n");
	
	pos_found=find_name_aem(all_students,num_of_students,name_to_search,aem_to_search);
	
	if (pos_found==-1)
		printf ("%s, %d Not found\n",name_to_search,aem_to_search);
	else
		printf ("%.1lf\n",all_students[pos_found].grade);
	
	printf ("Enter name: ");
	scanf ("%s",name_to_search); //idia metavliti me to binary search 
	
	printf ("\n");
	find_all_records(all_students,num_of_students,name_to_search);
	printf ("\n");
	
	return 0;
}

/* Auti i sunartisi pairnei ws parametrous ton pinaka,
 * diavazei ta dedomena, ta apothikeuei katallila,
 * epistrefei to plithos twn foititwn */
int insert_info(studentDataT *all_students){
	
	int i=-1,num_of_students;
	char str_input[MAX_STUDENTS][SIZE];
	char *pointer;
	
	do{
		i++;
		fgets(str_input[i],SIZE-1,stdin);
		if (atoi(str_input[i])<0)
			break;
	}while(i<MAX_STUDENTS-1 );
	
	num_of_students=i;
	
// 	 DIMIOURGIA TWN PEDIWN
	for (i=0; i<num_of_students; i++){
		
// 		GIA TO NAME
		str_input[i][strlen(str_input[i])-1]='\0';
		str_input[i][GRADE_POS-1]='\0';
		
		pointer=&str_input[i][NAME_POS];
		
		strcpy(all_students[i].name,&str_input[i][NAME_POS]);
		pointer=strchr(all_students[i].name,' ');
		if (pointer!=NULL)
			*pointer='\0';
		
// 		GIA TO AEM
		all_students[i].aem=atoi(str_input[i]);
		
// 		GIA TO GRADE
		all_students[i].grade=atof(&str_input[i][GRADE_POS]);
	}
	return num_of_students;
}

/*Auti i sunartisi arxikopoiei ta kena pedia me arnitiko aem*/
void initialize_students (studentDataT *all_students, int num_of_students){
	
	int i;
// 	arxikopoihsh twn aem me arnitiko arithmo gia ta kena pedia
	for (i=num_of_students; i<MAX_STUDENTS; i++)
		all_students[i].aem=-1;
}

/*Auti i sunartisi ektupwnei katallila kathe struct tou pinaka student */
void print_students (studentDataT *all_students, int num_of_students){
	
	char *pointer;
	int i,j;
	
	for (i=0; i<num_of_students; i++){
		pointer=strchr(all_students[i].name,',')+1;
		printf ("%c. ",*pointer);
		for (j=0; isalpha(all_students[i].name[j]);j++)
			printf ("%c",all_students[i].name[j]);
		printf(" ");
		printf ("%d ",all_students[i].aem);
		printf ("%.1lf\n",all_students[i].grade);
	}
}

/* Ektupwnei to diaxwristiko metaksu twn stadiwn */
void separator_output (){
	
	int i;
	
	printf ("\n");
	for (i=0; i<20; i++)
		printf ("-");
	printf ("\n");
}

/* Taksinomisi tou pinaka me selection sort koitwntas prwta to onoma & meta t aem */
void selection_sort (studentDataT *all_students, int num_of_students){
	
	studentDataT temp;
	int i,j,min;
// 	int comparison_counter=0;  (stadio 4)
	
	for (i=0; i<num_of_students; i++){
		min=i;
		for (j=i+1; j<num_of_students; j++){
			
// 			comparison_counter++;
			if (strcmp(all_students[j].name,all_students[min].name)<0)
				min=j;
			else if (strcmp(all_students[j].name,all_students[min].name)==0)
				if (all_students[j].aem<all_students[min].aem)
					min=j;
		}
// 		comparison_counter++;
		if (i!=min){
			temp=all_students[i];
			all_students[i]=all_students[min];
			all_students[min]=temp;
		}
	}
	// GIA TO STADIO 4
// 	printf ("*** SELECITON SORT *** Comparison_counter= %d\n",comparison_counter);
}

/* Taksinomisi tou pinaka me insertion sort koitwntas prwta to onoma & meta t aem */
void insertion_sort (studentDataT *all_students, int num_of_students){
	
	studentDataT temp;
	int i,j;
// 	int comparison_counter=0;
	for (i=1; i<num_of_students; i++){
		temp=all_students[i];
		j=i-1;
		while (j>=0 && strcmp(all_students[j].name,temp.name)>=0){
// 			comparison_counter++;
			if (strcmp(all_students[j].name,temp.name)==0){
// 				comparison_counter++;
				if (all_students[j].aem<temp.aem)
					break;
			}
			
			all_students[j+1]=all_students[j];
			j--;
		}
		all_students[j+1]=temp;
	}
	// GIA TO STADIO 4
// 	printf ("*** INSERTION SORT *** Comparison_counter= %d\n",comparison_counter);
}

/* Auti i sunartisi pairnei ws parametro mia sumvoloseira gia to onoma kai enan
 * akeraio gia to aem gia tin anazitisi, ton pinaka kai to megisto arithmo stoixeiwn. Xrisimopoihtai o algorithmos binary search
 * kai epistrefei ti thesi tou ston pinaka an to vrei, alliws -1 */
int find_name_aem (studentDataT *all_students, int num_of_students,char *name_to_search,int aem_to_search){
	
	int max,min,middle;
	
	min=0;
	max=num_of_students-1; // last of the students 
	
	while (min<=max){
		middle=(min+max)/2;
		
	if (strcmp(all_students[middle].name , name_to_search)==0){
		if (all_students[middle].aem==aem_to_search)
			return middle;
		else if (all_students[middle].aem>aem_to_search){
			max=middle-1;
			continue;
		}
		else if (all_students[middle].aem<aem_to_search){
			min=middle+1;
			continue;
		}
	}
	else if (strcmp(all_students[middle].name,name_to_search)<0)
		min=middle+1;
	else if (strcmp(all_students[middle].name,name_to_search)>0)
		max=middle-1;
	}
	return -1;
}

/*Auti i sunartisi pairnei ws parametro mia sumvoloseira gia to onoma, ton pinaka kai
 * to megisto arithmo stoixeiwn.
 * Psaxnei olous tous foitites me auto to onoma.
 * Gia kathe enan pou vriskei ektupwnei to aem kai to vathmo tou. */
void find_all_records(studentDataT *all_students, int num_of_students,char *name_to_search){
	
	int i,all_found=0;
	
	/* O pinakas students einai taksinomenos se auksousa sumfwna me to onoma.
	 * Ara tha einai oloi osoi exoun to idio onoma dipla.Gia auto xrisimopoiw
	 * ena flag (all_found) mexri na vrei to 1o einai all_found=0 meta ginetai 1
	 * kai molis vrei to prwto pali pou den einai iso vgainei apo to loop me break*/
	for (i=0; i<num_of_students; i++){
		if (strcmp(all_students[i].name,name_to_search)){ //an strcmp=0 den ekteleitai
			if (all_found) //ekteleitai an strcmp!=0 & all_found=1, vgainei apo loop 
				break;
			else //ekteleitai an strcmp!=0 & all_found=1,den exei ftasei sta onomata
				continue;
		}
		printf ("%d, %.1lf\n",all_students[i].aem,all_students[i].grade);
		all_found=1; //toulax. 1 vrethike & afou einai taksinomimena an to epomeno onoma
	}				//den einai to idio tote den uparxei allo idio onoma
}