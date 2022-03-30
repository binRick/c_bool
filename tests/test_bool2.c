/*******************/
#include <stdio.h>
/*******************/
#include "def.h"
#include "module.h"
#include "require.h"
/*******************/
#include "../include/module2.h"
/*******************/
#include "../../log/log.c"
/*******************/
#define MODULE_LOG_LEVEL    LOG_DEBUG
/*******************/

/*******************/
module(module2) * module2;


/*******************/


/*******************/
void pre(void) {
  log_set_level(MODULE_LOG_LEVEL);
  module2 = require(module2);
}


/*******************/


/*******************/
void test(void) {
  log_debug("module2:%d", module2);
  log_debug("module2->enabled:%d", module2->enabled);
  log_debug("module2->state:%d", module2->state);
  log_debug("module2->ok:%d", module2->ok);
  log_debug("module2->function:%d", module2->function());
  log_debug("module2->enable():%d", module2->enable());
  log_debug("module2->state:%d", module2->state);
  log_debug("module2->enabled:%d", module2->enabled);
}


/*******************/


/*******************/
void exec(void){
  log_info("EXEC>");
}


/*******************/


/*******************/
void post(void) {
  clib_module_free(module2);
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
