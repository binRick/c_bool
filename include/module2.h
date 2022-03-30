/***********************************/
#include <stdio.h>
/***********************************/
#include "def.h"
/***********************************/
#include "log/log.c"
/***********************************/
#include "module.h"
/***********************************/
#include "require.h"
/***********************************/

// `module2` module definition
module(module2) {
  defaults(module2, CLIB_MODULE);
  // a private module pointer
  void *private;
  int  state;
  int  ok;
  bool enabled;

  int  (*function)();
  int  (*enable)();
  int  (*string_to_bool)();
  char * (*bool_to_string)();
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
  int  (*function)();
  int  (*enable)();
  int  (*string_to_bool)();
  char * (*bool_to_string)(bool);
};


// private `private` module bool_to_string symbol
static char * module2_private_bool_to_string(bool b) {
  log_info("module2_private_bool_to_string():%d", b);
  return(c_bool_to_str(b));
}


static int module2_private_string_to_bool() {
  char *s = "true";

  log_info("module2_private_string_to_string():%d", s);
  bool b = true;

  return(b);
}


// private `private` module enable symbol
static int module2_private_enable() {
  log_info("module2_private_enable()");
  return(0);
}


// private `private` module function symbol
static int module2_private_function() {
  log_info("module2_private_function()");
  return(0);
}

// `private` module exports
exports(private) {
  defaults(private, CLIB_MODULE_DEFAULT),
  .function       = module2_private_function,
  .enable         = module2_private_enable,
  .bool_to_string = module2_private_bool_to_string,
  .string_to_bool = module2_private_string_to_bool,
};


static int module2_string_to_bool() {
  log_info("module2_string_to_bool()");
  // require(module2)->string_to_bool();
  // require(private)->string_to_bool();
  return(true);
}


// private `module2` module bool_to_string symbol
static char * module2_bool_to_string(bool b) {
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


// private `module2` module function symbol
static int module2_function() {
  log_info("module2_function()");
  require(module2)->state = 1;
  require(module2)->ok    = 1;
  require(private)->function();
  return(0);
}


// `module2` module initializer
static int module2_init(module(module2) *exports) {
  log_info("module2_init()");
  exports->bool_to_string = module2_bool_to_string;
  exports->enable         = module2_enable;
  exports->function       = module2_function;
  exports->private        = require(private);
  exports->state          = -1;
  exports->ok             = -1;
  if (0 != exports->private) {
    log_info("exports->private");
  }
  return(0);
}


// `module2` module deinitializer
static void module2_deinit(module(module2) *exports) {
  log_info("module2_deinit()");
  clib_module_free((module(private) *) exports->private);
}

