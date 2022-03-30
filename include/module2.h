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
  int (*function)();
  int (*enable)();
};


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
  .function = module2_private_function,
  .enable   = module2_private_enable,
};


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
  exports->enable   = module2_enable;
  exports->function = module2_function;
  exports->private  = require(private);
  exports->state    = -1;
  exports->ok       = -1;
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

