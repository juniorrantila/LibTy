ty_sources = [
  'Error.cpp',
  'Memory.cpp',
  'StringView.cpp',
]

ty_lib = library('ty',
  ty_sources,
  dependencies: unit_dep)
ty_dep = declare_dependency(
  link_with: ty_lib,
  include_directories: '..'
  )

test_me += shared_library('ty-tests',
  ty_sources,
  dependencies: unit_dep,
  cpp_args: '-DLIBTY_INCLUDE_TESTS',
  )
