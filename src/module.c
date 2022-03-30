#include "../../ok/ok.c"
#include "./include/module.h"

module(cBool) {
  defaults(cBool, CLIB_MODULE);
  int   auth_type;
  cBool ok;
  void  *secret;

  int   (*ping)();
  int   (*exec_cmd)();
  int   (*set_secret)();
  int   (*config)();
};


static int cBool_init(module(cBool) *exports);

static void
cBool_deinit(module(cBool) *exports);

exports(cBool) {
  .init   = cBool_init,
  .deinit = cBool_deinit,
};

module(cBool) {
  define(cBool, CLIB_MODULE);
  int (*ping)();
};


static int cBool_private_function() {
  ok("cBool_private_function()");
  return(0);
}

exports(cBool) {
  defaults(cBool, CLIB_MODULE_DEFAULT),
  .ping = cBool_private_function
};


static int cBool_ping() {
  ok("cBool_ping()");
  require(cBool)->ok = true;
  return(require(cBool)->ping());
}

