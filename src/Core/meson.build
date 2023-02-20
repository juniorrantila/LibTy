core_sources = [
  'File.cpp',
  'MappedFile.cpp',
  'System.cpp',
]

core_deps = [
  ty_dep,
]

core_lib = library('core',
  core_sources,
  dependencies: core_deps,
  cpp_args: base_cpp_args
  )

core_dep = declare_dependency(
  link_with: core_lib,
  include_directories: '..'
  )

test_me += shared_library('core-tests',
  core_sources,
  cpp_args: test_cpp_args,
  dependencies: [
    core_deps,
    unit_dep,
  ])
