/***********************************/
#include <stdio.h>
/***********************************/
#include "../deps/def.h"
/***********************************/
#include "log/log.h"
/***********************************/
#include "../deps/module.h"
/***********************************/
#include "../deps/require.h"
/***********************************/
#define MODULE_LOG_LEVEL    LOG_DEBUG
/***********************************/

// `module2` module definition
module(module2) {
  defaults(module2, CLIB_MODULE);
  void *private;
  bool enabled;

  int  (*enable)();
  bool (*string_to_bool)(const char *);
  bool (*is_bool)(const char *);
  char * (*bool_to_string)(const bool);
};

// `module2` module prototypes
static int  module2_init(module(module2) * exports);

static void module2_deinit(module(module2) * exports);

// `module2` module exports
exports(module2) {
  .init   = module2_init,
  .deinit = module2_deinit,
};

// `private` module definition
module(private) {
  define(private, CLIB_MODULE);
  int  (*enable)();
  bool (*string_to_bool)(const char *);
  bool (*is_bool)(const char *);
  char * (*bool_to_string)(const bool);
};


// private `private` module bool_to_string symbol
static char * module2_private_bool_to_string(const bool b) {
  log_info("module2_private_bool_to_string():%d", b);
  return(c_bool_to_str(b));
}


static bool module2_private_is_bool(const char *s) {
  log_info("module2_is_bool():%s", s);
  return(c_is_bool(s));
}


static bool module2_private_string_to_bool(const char *s) {
  log_info("module2_private_string_to_string():%s", s);
  return(c_str_to_bool(s));
}


// private `private` module enable symbol
static int module2_private_enable() {
  log_info("module2_private_enable()");
  return(0);
}


// `private` module exports
exports(private) {
  defaults(private, CLIB_MODULE_DEFAULT),
  .enable         = module2_private_enable,
  .bool_to_string = module2_private_bool_to_string,
  .string_to_bool = module2_private_string_to_bool,
};


static bool module2_is_bool(const char *s) {
  log_info("module2_is_bool(%s)", s);
  return(require(private)->is_bool(s));
}


static bool module2_string_to_bool(const char *s) {
  log_info("module2_string_to_bool(%s)", s);
  return(require(private)->string_to_bool(s));
}


// private `module2` module bool_to_string symbol
static char * module2_bool_to_string(const bool b) {
  log_info("module2_bool_to_string()");
  return(require(private)->bool_to_string(b));
}


// private `module2` module enable symbol
static int module2_enable() {
  log_info("module2_enable()");
  require(module2)->enabled = true;
  require(private)->enable();
  return(0);
}


// `module2` module initializer
static int module2_init(module(module2) *exports) {
  void debug_private(){
    if (0 != exports->private) {
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_YELLOW "init> NON PRIVATE MODE" AC_RESETALL);
    }else{
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_BLUE "init> PRIVATE MODE" AC_RESETALL);
    }
  }

  debug_private();
  exports->bool_to_string = module2_bool_to_string;
  exports->string_to_bool = module2_string_to_bool;
  exports->is_bool        = module2_is_bool;
  exports->enable         = module2_enable;
  exports->private        = require(private);
  debug_private();

  return(0);
}


// `module2` module deinitializer
static void module2_deinit(module(module2) *exports) {
  log_info("module2_deinit()");
  clib_module_free((module(private) *) exports->private);
}

