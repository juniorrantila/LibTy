unit_lib = static_library('unit', [
  'TestCase.cpp',
  'TestContext.cpp',
], cpp_args: base_cpp_args)

unit_dep = declare_dependency(
  link_with: unit_lib,
  include_directories: '..'
  )
