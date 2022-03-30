/*******************/
#include "include/module.h"
/*******************/
#include "log/log.c"
/*******************/
#include "src/bool_module.c"
/*******************/


void module_lifecycle(){
  pre();
  test();
  exec();
  post();
}


int main(void) {
  module_lifecycle();
  return(0);
}
/*******************/
