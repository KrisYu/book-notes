#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person{
  char *name;
  int age;
  int height;
  int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight) {
  struct Person *who = malloc(sizeof(struct Person));
  printf("%lu\n",sizeof(struct Person) );
  printf("%lu\n",sizeof(int));
  printf("%lu\n",sizeof(char *) );
  assert(who != NULL);

  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void Person_destory(struct Person *who) {
  assert(who != NULL);

  free(who->name);
  free(who);
}

void Person_print(struct Person *who) {
  printf("Name : %s\n",who->name);
  printf("\tage %d\n", who->age);
  printf("\theight %d\n", who->height);
  printf("\tweight %d\n", who->weight);
}

int main(int argc, char *argv[]) {
  // make two pople structures
  struct Person *joe = Person_create("Joe Alex", 32, 64, 140);

  struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

  // print them out and where they are in memory
  printf("Joe is at memory location %p\n", joe);
  Person_print(joe);

  printf("Frank is at memory location %p\n",frank);
  Person_print(frank);

  // make everyone age 20 years and print them again
  joe->age += 20;
  joe->height -= 2;
  joe->weight += 40;
  Person_print(joe);

  frank->age += 20;
  frank->weight += 20;
  Person_print(frank);

  // destory them both so we are clean
  Person_destory(joe);
  Person_destory(frank);

  return 0;
}
