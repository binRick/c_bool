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
#ifndef MODULE_LOG_LEVEL
#define MODULE_LOG_LEVEL    LOG_DEBUG
#endif
/***********************************/

// `bool_module` module definition
module(bool_module) {
  defaults(bool_module, CLIB_MODULE);
  void *private;
  bool enabled;

  int  (*enable)();
  bool (*string_to_bool)(const char *);
  bool (*is_bool)(const char *);
  char * (*bool_to_string)(const bool);
};

// `bool_module` module prototypes
static int  bool_module_init(module(bool_module) * exports);

static void bool_module_deinit(module(bool_module) * exports);

// `bool_module` module exports
exports(bool_module) {
  .init   = bool_module_init,
  .deinit = bool_module_deinit,
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
static char * bool_module_private_bool_to_string(const bool b) {
  log_trace("bool_module_private_bool_to_string():%d", b);
  return(c_bool_to_str(b));
}


static bool bool_module_private_is_bool(const char *s) {
  log_trace("bool_module_is_bool():%s", s);
  return(c_is_bool(s));
}


static bool bool_module_private_string_to_bool(const char *s) {
  log_trace("bool_module_private_string_to_string():%s", s);
  return(c_str_to_bool(s));
}


// private `private` module enable symbol
static int bool_module_private_enable() {
  log_trace("bool_module_private_enable()");
  return(0);
}


// `private` module exports
exports(private) {
  defaults(private, CLIB_MODULE_DEFAULT),
  .enable         = bool_module_private_enable,
  .bool_to_string = bool_module_private_bool_to_string,
  .string_to_bool = bool_module_private_string_to_bool,
};


static bool bool_module_is_bool(const char *s) {
  log_trace("bool_module_is_bool(%s)", s);
  return(require(private)->is_bool(s));
}


static bool bool_module_string_to_bool(const char *s) {
  log_trace("bool_module_string_to_bool(%s)", s);
  return(require(private)->string_to_bool(s));
}


// private `bool_module` module bool_to_string symbol
static char * bool_module_bool_to_string(const bool b) {
  log_trace("bool_module_bool_to_string()");
  return(require(private)->bool_to_string(b));
}


// private `bool_module` module enable symbol
static int bool_module_enable() {
  log_trace("bool_module_enable()");
  require(bool_module)->enabled = true;
  require(private)->enable();
  return(0);
}


// `bool_module` module initializer
static int bool_module_init(module(bool_module) *exports) {
  void debug_private(){
    if (0 != exports->private) {
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_YELLOW "init> NON PRIVATE MODE" AC_RESETALL);
    }else{
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_BLUE "init> PRIVATE MODE" AC_RESETALL);
    }
  }

  debug_private();
  exports->bool_to_string = bool_module_bool_to_string;
  exports->string_to_bool = bool_module_string_to_bool;
  exports->is_bool        = bool_module_is_bool;
  exports->enable         = bool_module_enable;
  exports->private        = require(private);
  debug_private();

  return(0);
}


// `bool_module` module deinitializer
static void bool_module_deinit(module(bool_module) *exports) {
  log_trace("bool_module_deinit()");
  clib_module_free((module(private) *) exports->private);
}

