ty_lib = library('ty', [
    'Error.cpp',
    'Memory.cpp',
    'StringView.cpp',
    'Parse.cpp',
  ], cpp_args: base_cpp_args)

ty_dep = declare_dependency(
  link_with: ty_lib,
  include_directories: '..'
  )
