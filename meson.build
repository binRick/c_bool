#//***********************************************************/
project(
    'c_bool',          ['c'],         version : '0.0.1',         
    default_options : ['warning_level=2','c_std=gnu99'],
)
#//***********************************************************/
host_system = host_machine.system()

cc = meson.get_compiler('c')
sh = find_program('sh', required : true)
passh = find_program('passh', required : true)

#//***********************************************************/
test_deps = []
#//***********************************************************/
incdir = include_directories(
  './include', 
  './deps', 
  '../',
  '../metalang99/include',
  '../ok',
)
#//***********************************************************/
test_bool1 = executable('test_bool1', [ 
    'src/bool.c', 
    'tests/test_bool1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
#//***********************************************************/
#//***********************************************************/
test_bool2 = executable('test_bool2', [ 
    'src/bool.c', 
    'tests/test_bool2.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
#//***********************************************************/
tests = [
  ['test bool 1', test_bool1, 'test-bool1.log'],
  ['test bool 2', test_bool2, 'test-bool2.log'],
]
#//***********************************************************/

#//***********************************************************/
test_env = environment()
test_env.set('__SH', sh.full_path())
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#//***********************************************************/
foreach i : tests
test(i[0], passh, args: ['-L', i[2], i[1] ], env: test_env)
endforeach
#//***********************************************************/


