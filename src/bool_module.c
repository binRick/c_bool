/*******************/
#include <stdio.h>
/*******************/
#include "../deps/def.h"
#include "../deps/module.h"
#include "../deps/require.h"
/*******************/
#include "bool_module.h"
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
module(bool_module) * cm_bool;
/*******************/


/*******************/
void pre(void) {
  log_set_level(MODULE_LOG_LEVEL);
  cm_bool = require(bool_module);
}


/*******************/
void test(void) {
  char *s0 = "true", *s1 = "false", *bs0, *bs1;
  bool sb0, sb1, b0 = bools[0], b1 = bools[1], ib0, ib1;


  void bool_to_string(){
    bs0 = cm_bool->bool_to_string(b0);
    bs1 = cm_bool->bool_to_string(b1);

    log_error("cm_bool->bool_to_string(%d):%s", b0, bs0);
    log_error("cm_bool->bool_to_string(%d):%s", b1, bs1);
  }


  void string_to_bool(){
    sb0 = cm_bool->string_to_bool(s0);
    sb1 = cm_bool->string_to_bool(s1);

    log_debug("cm_bool->string_to_bool(%s):%d", s0, sb0);
    log_debug("cm_bool->string_to_bool(%s):%d", s1, sb1);
  }


  void is_bool(){
    ib0 = cm_bool->is_bool(s0);
    ib1 = cm_bool->is_bool(s1);

    log_debug("cm_bool->is_bool(%s):%d", s0, ib0);
    log_debug("cm_bool->is_bool(%s):%d", s1, ib1);
  }

  bool_to_string();
  string_to_bool();
  //is_bool();
}


/*******************/


/*******************/
void exec(void){
  log_info("bool exec>");
}


/*******************/


/*******************/
void post(void) {
  log_debug("bool unload>");
  clib_module_free(cm_bool);
}


/*******************/


/*******************/
