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

base_cpp_args = libty_proj.get_variable('base_cpp_args')

subdir('src')
