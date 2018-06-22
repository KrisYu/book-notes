#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>



void test_debug() {
  // notice you don't need the \n
  debug("I have Brown Hair.");

  // passing in arguments like printf
  debug("I am %d years old.", 37);
}


void test_log_err() {
  log_err("I believe everything is broken.");
  log_err("There are %d problems in %s.", 0, "space");
}


void test_log_warn() {
  log_warn("You can safely ignore this.");
  log_warn("Maybe conside looking at :%s.", "/etc/password");
}

void test_log_info() {
  log_info("Well I did something mundane.");
  log_info("It happend %f times today.", 1.3f);
}

int test_check(char *file_name){
  FILE *input = NULL;
  char *block = NULL;

  block = malloc(100);
  check_mem(block);

  input = fopen(file_name, "r");
  check(input, "Failed to open %s.", file_name);

  free(block);
  fclose(input);
  return 0;

  error:
    if(block) free(block);
    if(input) fclose(input);
    return -1;
}

int test_sentinel(int code){
  char *temp = malloc(100);
  check_mem(temp);

  switch (code) {
    case 1:
        log_info("It worked.");
        break;
    default:
        sentinel("I shouldn't run.");
  }

  free(temp);
  return 0;

  error:
    if(temp) free(temp);
    return -1;
}

int test_check_mem(){
  char *test = NULL;
  check_mem(test);

  free(test);
  return 1;

  error:
    if(test) free(test);
    return -1;
}

int test_check_debug(){
  int i = 0;
  check_debug( i != 0, "Oops, I was 0.");

  return 0;

  error:
    return -1;
}


int main(int argc, char *argv[]) {
  check(argc == 2, "Need an argument.");

  // notice test_debug don't print
  // believe this is related with debug(M, ...)
  // if I define debug, it will not print
  test_debug();

  // [ERROR] (ex20.c:16: errno: None) I believe everything is broken.
  // [ERROR] (ex20.c:17: errno: None) There are 0 problems in space.
  test_log_err();

  // [WARN] (ex20.c:22: errno: None) You can safely ignore this.
  // [WARN] (ex20.c:23: errno: None) Maybe conside looking at :/etc/password.
  test_log_warn();

  // [INFO] (ex20.c:27)Well I did something mundane.
  // [INFO] (ex20.c:28)It happend 1.300000 times today.
  test_log_info();

  // This should work, so we don't have any output
  // and as for check, we don't have anyout, read dbg.h
  check(test_check("ex20.c") == 0, "failed with ex20.c");

  // [ERROR] (ex20.c:39: errno: No such file or directory) Failed to open test.
  check(test_check(argv[1]) == -1, "failed with argv");

  // [INFO] (ex20.c:57)It worked. we use log_info to print out result.
  check(test_sentinel(1) == 0, "test_sentinel failed");

  // [ERROR] (ex20.c:60: errno: None) I shouldn't run.
  check(test_sentinel(100) == -1, "test_sentinel failed");

  // [ERROR] (ex20.c:73: errno: None) Out of memory.
  check(test_check_mem() == -1, "test_check_mem failed");

  // no error, so we don't see any output
  check(test_check_debug() == -1, "test_check_debug failed");


  return 0;

error:
  return 1;
}
