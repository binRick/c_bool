/*******************/
#include <stdio.h>
/*******************/
#include "../deps/def.h"
#include "../deps/module.h"
#include "../deps/require.h"
/*******************/
#include "module2.h"
/*******************/
#include "log/log.c"
/*******************/
/*******************/
const char *chars[] = {
  "true",
  "false",
  NULL,
};
const bool bools[] = {
  true,
  false,
  NULL,
};
/*******************/
module(module2) * module2;
/*******************/


/*******************/
void pre(void) {
  log_set_level(MODULE_LOG_LEVEL);
  module2 = require(module2);
}


/*******************/
void test(void) {
  char *s0 = "true", *s1 = "false", *bs0, *bs1;
  bool sb0, sb1, b0 = bools[0], b1 = bools[1], ib0, ib1;

  bs0 = module2->bool_to_string(b0);
  bs1 = module2->bool_to_string(b1);

  log_error("module2->bool_to_string(%d):%s", b0, bs0);
  log_error("module2->bool_to_string(%d):%s", b1, bs1);

  sb0 = module2->string_to_bool(s0);
  sb1 = module2->string_to_bool(s1);

  log_debug("module2->string_to_bool(%s):%d", s0, sb0);
  log_debug("module2->string_to_bool(%s):%d", s1, sb1);
/*
 * ib0 = module2->is_bool(s0);
 * ib1 = module2->is_bool(s1);
 * log_debug("module2->is_bool(%s):%d", s0, ib0);
 * log_debug("module2->is_bool(%s):%d", s1, ib1);
 */
}


/*******************/


/*******************/
void exec(void){
  log_info("bool exec>");
}


/*******************/


/*******************/
void post(void) {
  log_info("bool unload>");
  clib_module_free(module2);
}


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
