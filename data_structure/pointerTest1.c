
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student{
  int id;
  char name[20];
  float percentage;
}student;
typedef student* studentPt;

void display(student record);

int main(){
  studentPt recordPt;

  recordPt = malloc(sizeof(student));
  recordPt->id = 1;
  strcpy(recordPt->name, "Raju");
  recordPt->percentage = 86.5;

  display(*recordPt);
  return 0;
}

void display(student record){
  printf(" Id is: %d \n", record.id);
  printf(" Name is: %s \n", record.name);
  printf(" Percentage is: %f \n", record.percentage);
}
