/*             AXELOU OLYMPIA 2161         12/1/16
 * 
 * To programma auto exei ws skopo tin ulopoihsh mias domis stin opoia 
 * apothikeuontai ta stoixeia twn foititwn pou summetexoun sta ergastiria.
 * 
 * ARXIKA
 * Pairnei ws eisodo ton arithmo twn upologistwn se kathe tmima, ton arithmo twn
 * tmimatwn kai twn mathitwn kai upologizei-ektupwnei tin katanomi twn 
 * mathitwn sta tmimata.
 * 
 * Sti sunexeia, dinei ti dunatotita ston xristi na kanei amoivaia antallagi 
 * foititwn metaksu twn tmimatwn kai oristika diagrafi foititi apo ta ergastiria.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student{
	char *name;
	int section;
	struct student *next;
	struct student *prev;
}studentT;

enum working_days {Mon,Tue,Wed,Thu,Fri};

typedef struct lab_sect{
	studentT *head_students;
	int start_time;
	enum working_days lab_day;
}lab_sectT;

enum boolean {OFF,ON};

/*otan einai ON ektupwnei KAI diagnwstika munimata
 *enw otan einai OFF ektupwnei mono ta kanonika munimata*/ 
enum boolean debug;

#define NAME_LEN 30 //thewrisa to 29 ws megisti pithani eisodos gia onoma
#define ACTION_LEN 10 //h megisti pithani eiodos einai 6 alla pairnw to 9 ws megisti (gia tin periptwsi lathous)
#define FORMAT_LEN 13 //to megethos tou format 
//stadio 0
int debug_check(int argc, char *argv[]);
//stadio 1
lab_sectT *enter_and_init (lab_sectT *lab_array, int *num_of_sections);
//stin add to section den to vazw ws parametro epeidi to periexei o komvos new_student
studentT *add_student (lab_sectT *lab_array, studentT *new_student, int section);
void deallocate (lab_sectT *lab_array, int num_of_sections);
//stadio 2
void print_sections (lab_sectT *lab_array, int num_of_sections);
//stadio 3
studentT *search_student (char *name_of_student,int num_of_sections,
						  lab_sectT *lab_array, int *section);
studentT *remove_student (lab_sectT *lab_array, studentT *student_to_remove, int section);
void swap_students (char *name_of_student1, char *name_of_student2, 
					int num_of_sections, lab_sectT *lab_array);
//stadio 4
void permanent_remove(char *name_of_student, lab_sectT *lab_array, int num_of_sections);
//voithitiki sunartisi 
void main_repeat (lab_sectT *lab_array, int num_of_sections);


int main (int argc,char *argv[]){
	
	lab_sectT *lab_array;
	int num_of_sections=0;
	
	//stadio 0
	if (debug_check(argc, argv))
		return 1;
	
	//stadio 1
	lab_array=NULL;
	lab_array=enter_and_init (lab_array, &num_of_sections);
	if (lab_array == NULL) //periptwsi provlimatos sti desmeusi mnimis
		return 1;
	
	//stadio 2
	print_sections (lab_array, num_of_sections);
	
	//stadio 3,4
	main_repeat (lab_array, num_of_sections);
	
	return 0;
}

/*(stadio 0)
 * pairnei tis idies parametrous me tin main
 * elegxei tis parametrous tou programmatos
 * kai allazei analoga tin timi tou debug 
 */
int debug_check (int argc, char *argv[]){
	
	if (argc==1){
		debug = OFF;
		return 0;
	}
	else if (argc==2){
		if ( !(strcmp(argv[1],"-d")) || !(strcmp(argv[1],"-debug")) ){ 
			debug = ON;
			return 0;
		}
		else {
			if ( argv[1][0]=='-' )
				argv[1]++;
			printf ("%s: illegal option -- %s\n", argv[0], argv[1]);
			printf ("Usage: %s [-d]\n", argv[0]);
			return 1;
		}
	}
	printf ("%s: wrong number of arguments %d\n", argv[0], argc);
	return 1;
}

/*(stadio 1)
 * h kuria sunartisi. pairnei ws parametrous ti dieuthunsi tou pinaka twn 
 * tmimatwn kai tou arithmou twn tmimatwn.
 * Dexetai ton arithmo twn foititwn kai twn upologistwn se kathe tmima
 * kai upologizei ton arithmo twn tmimatwn.
 * Sti sunexeia lamvanei ta stoixeia olwn twn foititwn kai tous eisagei stin lista
 * tou antistoixou tmimatos kuklika. Epistrefei tin dieuthinsi tou pinaka tmimatwn.
 */
lab_sectT *enter_and_init (lab_sectT *lab_array, int *num_of_sections){
	
	int num_of_students, num_of_computers,sections, i, j, k;
	char name_of_student[NAME_LEN],format[13];
	studentT *new_student;
	
	sections=*num_of_sections;
	do{
		printf ("Enter number of students: ");
		scanf ("%d",&num_of_students);
	}while (num_of_students<0);
	
	do{
		printf ("Enter maximum lab size: ");
		scanf ("%d",&num_of_computers);
	}while (num_of_computers<=0);
	
	sections=num_of_students/num_of_computers;
	if (num_of_students%num_of_computers>0)
		sections++;
	*num_of_sections=sections;
	lab_array= (lab_sectT *) malloc (sizeof(lab_sectT)*sections);
	if (lab_array==NULL)
		return NULL;
	
	i=0;
	
	
	for (j=Mon;j<=Fri; j++){
		for (k=8; k<22; k++){
			/*Otan (i>=sections) tha sunexisei na mpainei stin eswteriki for
			* mexri na teleiwsei h ekswteriki for alla den tha ektelountai oi 
			*entoles logw tis break */
			if (i>=sections)
				break;   
			lab_array[i].start_time=k;
			lab_array[i].lab_day=j;
			lab_array[i++].head_students=NULL;
		}
	}
	
	/*H ekfwnisi den leei lab omws lene ta endeiktika arxeia
	 * eksodou gi'auto kai to evala na ektupwnei ".. lab sections<<"*/
	if (debug)
		printf ("\n>>Created %d lab sections<<\n",sections);
	
	sprintf (format,"%%%ds",NAME_LEN-1);
	
	j=0; //metraei se poio tmima tha mpei o foititis
	
	for (i=0; i<num_of_students; i++){
		printf ("Enter student name: ");
		scanf (format,name_of_student);
		
		new_student= (studentT *)malloc (sizeof(studentT));
		if (new_student==NULL){
			printf ("Error allocating memory\n");
			deallocate (lab_array, sections);
			return NULL;
		}
		//ta stoixeia tou foititi (sti sunexeia h eisagwgi se lista)
		new_student->name= strdup (name_of_student);
		new_student->section=j;
		
		lab_array[j].head_students=add_student(lab_array,new_student,j);
		if (lab_array[j].head_students==NULL){
			deallocate (lab_array, sections);
			return NULL;
		}
		j++;
		//molis ftasei ton arithmo twn tmimatwn midenizetai (gia na pigainei kuklika)
		if (j==*num_of_sections) 
			j=0;
	}
	
	return lab_array;
}

/* H sunartisi gia tin eisagwgi tou komvou enos foititi se ena tmima.
 * Pairnei ws parametrous ti dieuthunsi tou pinaka twn tmimatwn,
 * ena deikti se studentT pou periexei ta stoixeia tou neou foititi
 * kai to tmima sto opoio tha mpei.
 * Vazei ton komvo stin lista tou antistoixou tmimatos.
 * Epistrefei ti dieuthinsi tis kefalis tis listas tou antistoixou tmimatos
 *h NULL an den exei ginei swsta h desmeusi mnimis (prin tin klisi tis, an einai
 * idi to new_student NULL)*/
studentT *add_student (lab_sectT *lab_array, studentT *new_student, int section){
	
	if (new_student==NULL){
		printf ("Problem allocating memory");
		return NULL;
	}
	if (debug)
		printf ("\n>>Added student \"%s\" in section %d<<\n",
			new_student->name,new_student->section +1);
	
	if (lab_array[section].head_students!=NULL)
		lab_array[section].head_students->prev=new_student;
	new_student->next=lab_array[section].head_students;
	new_student->prev=NULL;
	lab_array[section].head_students=new_student;
	
	return lab_array[section].head_students;
}

/* Sunartisi pou apodesmeuei oli ti dunamika desmeumeni mnimi.
 * Pairnei ws parametrous ti dieuthinsi tou pinaka twn tmimatwn kai ton 
 * arithmo twn tmimatwn.Den epistrefei tipota.
 */
void deallocate (lab_sectT *lab_array, int num_of_sections){
	
	studentT *current;
	int i;
	
	for (i=0; i<num_of_sections; i++){
		if (lab_array[i].head_students!=NULL)
			for (current=lab_array[i].head_students->next; current!=NULL;current=current->next)
				free (current->prev);
			free (current);
	}
	free (lab_array);
	
}

/*(stadio 2)
 * Ektupwnei ta tmimata kai tous foitites.
 * Pairnei ws parametrous tin dieuthinsi tou pinaka twn tmimatwn kai ton 
 * arithmo twn tmimatwn. (den epistrefei kati)
 */
void print_sections (lab_sectT *lab_array, int num_of_sections){
	
	int i;
	studentT *current;
	printf("\n\n");
	for (i=0; i<10; i++)
		printf ("=");
	printf ("LABS");
	for (i=0; i<10; i++)
		printf ("=");
	printf ("\n\n");
	
	for (i=0; i<num_of_sections; i++){
		printf ("*Section %d, ",i+1);
		switch (lab_array[i].lab_day){
			case Mon:
				printf ("Monday");
				break;
			case Tue:
				printf ("Tuesday");
				break;
			case Wed:
				printf ("Wednesday");
				break;
			case Thu:
				printf ("Thursday");
				break;
			case Fri:
				printf ("Friday");
				break;
		}
		printf(" %d:00*\n",lab_array[i].start_time);
		
		for (current=lab_array[i].head_students;current!=NULL;current=current->next)
			printf ("\t%s",current->name);
		printf ("\n");
	}
	for (i=0; i<24; i++)
		printf("=");
	printf ("\n");
}

/*(stadio 3)
 * H sunartisi auti psaxnei sta tmimata na vrei ena sugkekrimeno foititi.
 * Pairnei ws parametrous to onoma tou foititi, ton arithmo twn tmimatwnm, 
 * ti dieuthinsi tou pinaka twn tmimatwn kai ti dieuthinsi mias metablitis
 * kai epistrefei ti dieuthunsi tou komvou an to vrei h NULL an oxi.*/
studentT *search_student (char *name_of_student,int num_of_sections,lab_sectT *lab_array,int *section){
	
	int i;
	studentT *current;
	enum boolean found;
	
	found=OFF;
	for (i=0; i<num_of_sections; i++){
		if (debug)
			printf ("\n>>Searching section %d for %s...<<\n",i+1,name_of_student);
		for (current=lab_array[i].head_students; current!=NULL; current=current->next){
			if (debug)
				printf ("%s...",current->name);
			if (!strcmp(current->name,name_of_student)){
				found=ON;
				break;
			}
		}
		if (found==ON)
			break;
	}
	*section=i;
	
	/*to current h tha einai null (h teleutaia timi pou pairnei apo ti for)
	 *h tha exei ti dieuthunsi tou komvou an exei vrethei to onoma */
	return current;
}

/*H sunartisi auti afairei enan komvo apo ti lista tou tmimatos sto opoio anikei o
 * antistoixos foititis.
 * Pairnei ws parametrous ti dieuthunsi tou pinaka twn tmimatwn, tin dieuthinsi tou
 * komvou tou foititi pou tha diagrafei kai to tmima sto opoio anikei.
 * Epistrefei tin dieuthunsi tis kefalis tis listas, diladi (studentT *) */
studentT *remove_student (lab_sectT *lab_array, studentT *student_to_remove, int section){
	
	if (debug)
		printf ("\n>>Removed student \"%s\" from section %d<<\n",
				student_to_remove->name,section+1);
	
	if (student_to_remove==lab_array[section].head_students){
		return lab_array[section].head_students->next;
	}
	
	student_to_remove->prev->next=student_to_remove->next;
	if (student_to_remove->next!=NULL){
		student_to_remove->next->prev=student_to_remove->prev;
	}
	 
	return lab_array[section].head_students;
}

/*H sunartisi auti kanei tin amoivaia antallagi twn foititwn metaksu twn tmimatwn.
 * Pairnei ws parametrous ta onomata twn 2 foititwn, ton arithmo twn tmimatwn
 * kai tin dieuthinsi tou pinaka twn tmimatwn.
 * Den epistrefei kati. */
void swap_students (char *name_of_student1, char *name_of_student2, int num_of_sections, lab_sectT *lab_array){
	
	studentT *student1, *student2;
	int section_of_student1, section_of_student2, temp;
	
	student1=search_student (name_of_student1, num_of_sections, lab_array, &section_of_student1);
	if (student1==NULL)
		printf ("\nStudent \"%s\" not in lab.\n",name_of_student1);
	
	
	student2=search_student (name_of_student2, num_of_sections, lab_array, &section_of_student2);
	if (student2==NULL)
		printf ("\nStudent \"%s\" not in lab.\n",name_of_student2);
	
	if (student1==NULL || student2==NULL){
		printf ("Swap canceled.\n");
		return;
	}
	
	if (section_of_student1==section_of_student2){
		printf ("Students \"%s\" and \"%s\" are in the same section. Swap canceled.\n",
				name_of_student1, name_of_student2);
		return;
	}
	
	lab_array[section_of_student1].head_students= remove_student (lab_array, student1, section_of_student1);
	lab_array[section_of_student2].head_students= remove_student (lab_array, student2, section_of_student2);
	
	temp=student1->section;
	student1->section=section_of_student2;
	student2->section=temp;
	
	lab_array[section_of_student2].head_students=add_student (lab_array, student1, section_of_student2);
	lab_array[section_of_student1].head_students=add_student (lab_array, student2, section_of_student1);
	
}
/*(stadio 4)
 * H sunartisi auti afairei enan foititi oristika apo to ergastirio. 
 * Pairnei ws parametrous to onoma tou foititi, ton arithmo twn tmimatwn kai tin
 * dieuthinsi tou pinaka twn tmimatwn. Den epistrefei kati. */
void permanent_remove (char *name_of_student, lab_sectT *lab_array, int num_of_sections){
	
	studentT *student_to_remove;
	int section=0;
	student_to_remove= search_student (name_of_student, num_of_sections, lab_array, &section);
	
	if (student_to_remove==NULL){
		printf ("\nStudent \"%s\" not in lab.Remove canceled.\n",name_of_student);
		return;
	}
	lab_array[section].head_students = remove_student (lab_array, student_to_remove, section);
	free (student_to_remove);
}

/*Voithitiki sunartisi.
 * Ektelei to loop tou 'menou' tis main.
 * Pairnei ws parametro ti dieuthunsi tou pinaka twn tmimatvn kai ton arithmo twn 
 * tmimatwn, den epistrefei kati. */
void main_repeat (lab_sectT *lab_array, int num_of_sections){
	
	char name_of_student[NAME_LEN], name_of_student1[NAME_LEN];
	char name_of_student2[NAME_LEN], format[FORMAT_LEN], action[ACTION_LEN];
	
	do{
		sprintf (format,"%%%ds", ACTION_LEN-1); 
		printf ("\nEnter action: ");  
		scanf (format, action);  
		
		if (!strcmp(action, "SWAP")){ 
			sprintf (format,"%%%ds",NAME_LEN-1);
			printf ("Enter first name: ");
			scanf  (format, name_of_student1);
			printf ("Enter second name: ");
			scanf (format, name_of_student2);
			
			swap_students (name_of_student1, name_of_student2, num_of_sections, lab_array);
		}
		else if (!strcmp (action, "PRINT") )
			print_sections (lab_array, num_of_sections);
		else if (!strcmp (action, "EXIT") ){
			deallocate (lab_array, num_of_sections);
			printf ("\n");
		}
		else if (!strcmp (action, "REMOVE") ){
			sprintf (format, "%%%ds", NAME_LEN-1);
			printf ("Enter name: ");
			scanf (format, name_of_student);
			permanent_remove(name_of_student, lab_array, num_of_sections);
		}
		else
			printf ("Invalid action. Valid actions are SWAP, REMOVE, PRINT, EXIT.\n");
	}while ( strcmp(action,"EXIT") );
	
}