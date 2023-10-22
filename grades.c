#include <stdio.h>
#include <stdlib.h>
//declarations to be used later
struct student 
{
    char name[30];
    int gradelevel;
    int age;
    
};
void makeStudent(int *a, int *gL, char n[30]);
int confirmStudent(char id[], int *gL);
char newName[30];
int newAge;
int newGrade;
int main(int argc, char **argv)
{
    if (argc > 1){ //makes sure there are arguments besides the execution
        if (*argv[1] == '-') //makes sure that a modifier is used
        {
            switch (argv[1][1]) //goes through the commmand options
            {
                case 'n': // new student
                    printf("new student\nenter the students name:");
                    scanf("%s", &newName);
                    printf("enter the students age:");
                    scanf("%d", &newAge);
                    printf("enter the students grade level(if single digit start with a 0):");
                    scanf("%d", &newGrade);
                    makeStudent(&newAge, &newGrade, newName);
                    confirmStudent(newName + newAge + newGrade, &newGrade);
                    break;
                case 'g': //getter
                    if (argc < 3) //prevents an annoying segfault idfk why it happens but this fixes it
                    {
                        printf("\nadd one of the following options: studetnt, gpa, or avg\n");
                        break;
                    }
                    if (*argv[2] == *"gpa")
                    {
                        printf("gpa placeholder txt\n");
                    }
                    else if (*argv[2] == *"student")
                    {
                        printf("get student\nenter the students name:");
                        scanf("%s", &newName);
                        printf("enter the students age:");
                        scanf("%d", &newAge);
                        printf("enter the students grade level(if single digit start with a 0):");
                        scanf("%d", &newGrade);
                        char id[34];
                        sprintf(id, "%s%d%d", newName, newAge, newGrade);
                        int conf = confirmStudent(id, &newGrade);
                        switch (conf)
                        {
                        case 0:
                            printf("%s exists\n", id);
                            break;
                        case 1:
                            printf("%s does not exist\n", id);
                            break;
                        }
                    }
                    else if (*argv[2] == *"avg")
                    {
                        printf("average gpa\n");
                    }
                    break;
                }
        }
    }else{// runs if no args are used
        printf("grades util, use -n to make a new student. -g with the options gpa, student, or avg(gets the avg gpa of a grade\n");
        void exit();
    }
}
//function that creates a new student struct and writes it to its designated grade file
void makeStudent(int *a, int *gL, char n[30]){
    char id[34];
    sprintf(id, "%s%d%d", n, *a, *gL);
    struct student newStudent = {*n, *a, *gL};
    if (confirmStudent(id, gL) == 0) //checks if the student already exists
    {
        printf(" already exists");
    }
    else
    {
        char fileName[20]; //makes sure the right syntax for the fileName is used
        switch (*gL){
        case 1:
            sprintf(fileName, "%dStGradeRecords.txt", *gL);
            break;
        case 2:
            sprintf(fileName, "%dNdGradeRecords.txt"), *gL;
            break;
        default:
            sprintf(fileName, "%dThGradeRecords.txt", *gL);
            break;
        }
        FILE *fPtr;
        fPtr = fopen(fileName, "w");
        char fileLine[34];
        fgets(fileLine, 34, fPtr); // this was added because append mode doesnt make a new file :sob:
        switch (fileLine[0]) //switch statement to check if the first line is null. added to make sure new lines are added only when needed
        {
        case '\0':
            fclose(fPtr);
            fPtr = fopen(fileName, "a");
            fprintf(fPtr, id);
            break;
        default:
            fclose(fPtr);
            fPtr = fopen(fileName, "a");
            fprintf(fPtr, "\n");
            fprintf(fPtr, id);
            break;
            
        }
        fclose(fPtr);
    }
}
//function that confirms if a student exists or not 0 means it does 1 means it does not
int confirmStudent(char id[], int *gL){
   char fileName[20];
   switch (*gL){ //makes sure the right syntax for the fileName is used
    case 1:
        sprintf(fileName, "%dStGradeRecords.txt", *gL);
        break;
    case 2:
        sprintf(fileName, "%dNdGradeRecords.txt"), *gL;
        break;
    default:
        sprintf(fileName, "%dThGradeRecords.txt", *gL);
        break;
    }
    char fileLine[34];
    FILE *fPtr;
    fPtr = fopen(fileName, "r");
    if (fPtr == NULL) //checks if the file for the grade exists
    {
        return 1;
    }
    else
    {
        while (fgets(fileLine, 34, fPtr)){ //checks to see if the student exists
            if (*fileLine == *id){
               fclose(fPtr);
                return 0;
            }
        }
    }

    return 1;
}