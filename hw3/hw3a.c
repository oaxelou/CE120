/*AXELOU OLYMPIA - 2161 - 15/12/2015 
 * To programma auto apothikeuei ta stoixeia kai tous vathmous enos arithmou foititwn se 	* pinaka kai upologizei kapoia statistika. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STUDENTS 100+1 //einai +1 giati exw rithmisi na dexetai to string k meta na to tsekarei an aem<0
#define SIZE 39      //to max plithos xaraktirwn einai 37 + 2 apo tin fgets
#define NAME_POS 6   //i thesi ston pinaka apo opou ksekina to onoma
#define GRADE_POS 32 //i thesi apo opou ksekia o vathmos

void print_histogram( int histogram_grade);

int main (int argc,char *argv[]){
	
	//name_pointer: voithitiki metavliti pointer
	char student[MAX_STUDENTS][SIZE], *name_pointer;
	int i=-1;  //to auksanw stin arxi tis do..while gi'auto to arxikopoiw me -1 
	int j, aem, num_of_students, histogram_grades[11]={0}; 
	double grade, sum_grades=0, average;
	
	do{
		i++;
		fgets(student[i],SIZE-1,stdin);
		if (atoi(student[i])<0) //o prwtos akeraios pou tha vrei einai to aem
			break;
	}while(i<MAX_STUDENTS-1 );
	
	num_of_students=i;
	
	for (j=0; j<num_of_students; j++){
		
		student[j][strlen(student[j])-1]='\0';
		student[j][GRADE_POS-1]='\0';
		
		name_pointer=strchr(student[j],',')+1;
		printf ("%c. ",*name_pointer);
		
		//gia tin ektupwsi tou epithetou allazw to , me \0 kai to ksanakanw ,
		//
		name_pointer[-1]='\0';
		printf ("%s",&student[j][NAME_POS]);
		printf (" ");
		name_pointer[-1]=',';
		
		aem=atoi(student[j]);
		printf ("%d ",aem);
		
		grade=atof(&student[j][GRADE_POS]);
		printf ("%.1lf\n",grade);
		
		sum_grades+=grade;
		histogram_grades[(int)ceil(grade)]++;
	}
	
	//dimiourgia istrogrammatos
	printf ("[ 0,  0]: ");
	print_histogram (histogram_grades[0]);
	
	for (i=1; i<11; i++){
		printf ("(%2d, %2d]: ",i-1,i);
		print_histogram (histogram_grades[i]);
	}
	
	//evresi mesou orou
	if (num_of_students)
		average=sum_grades/num_of_students;
	printf ("\nAVERAGE: %.2lf\n",average);
	
	return 0;
}

/*tupwnei mia grammi tou istogrammatos 
 *kai pairnei ws parametro ton arithmo atomwn 
 * pou eixan tous sugkekrimenous vathmous */
void print_histogram( int histogram_grade) {
	
	int i;
	
	for (i=0; i<histogram_grade/10; i++)
			printf ("*");
		histogram_grade%=10;
		for (i=0; i<histogram_grade; i++)
			printf ("-");
		printf("\n"); 
}