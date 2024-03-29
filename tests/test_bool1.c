/*******************/
#include <stdio.h>
/*******************/
#include "def.h"
#include "module.h"
#include "require.h"
/*******************/
#include "../include/module1.h"
/*******************/
#include "../../log/log.c"
/*******************/
#define MODULE_LOG_LEVEL    LOG_DEBUG
/*******************/

/*******************/
module(module1) * module1;


/*******************/


/*******************/
void pre(void) {
  log_set_level(MODULE_LOG_LEVEL);
  module1 = require(module1);
}


/*******************/


/*******************/
void test(void) {
  log_debug("module1:%d", module1);
  log_debug("module1->state:%d", module1->state);
  log_debug("module1->function:%d", module1->function());
  log_debug("module1->state:%d", module1->state);
}


/*******************/


/*******************/
void exec(void){
  log_info("EXEC>");
}


/*******************/


/*******************/
void post(void) {
  clib_module_free(module1);
}


/*******************/


int main(void) {
  pre();
  test();
  exec();
  post();
  return(0);
}
/*******************/
