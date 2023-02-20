project('hello-world', 'cpp',
  default_options: [
    'cpp_std=c++20',
    'cpp_eh=none',
    'cpp_rtti=false',
    'default_library=static',
    'warning_level=3',
    'buildtype=release'
  ])

libty_proj = subproject('LibTy')
core_dep = libty_proj.get_variable('core_dep')
main_dep = libty_proj.get_variable('main_dep')
unit_dep = libty_proj.get_variable('unit_dep')
test_runner_exe = libty_proj.get_variable('test_runner_exe')

base_cpp_args = libty_proj.get_variable('base_cpp_args')
test_cpp_args = libty_proj.get_variable('test_cpp_args')

test_me = []
subdir('src')

if not meson.is_subproject()
  run_target('run-tests', command: [
    test_runner_exe,
    test_me,
  ], depends: test_me)
endif
