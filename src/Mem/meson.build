mem_sources = [
  'AddressSpace.cpp',
  ]

mem_deps = [
  core_dep,
  ty_dep,
  ]

mem_lib = library('mem',
  mem_sources,
  dependencies: mem_deps,
  cpp_args: base_cpp_args
  )

mem_dep = declare_dependency(
  link_with: mem_lib,
  include_directories: '..'
  )

if not meson.is_subproject()
  test_me += shared_library('mem-tests',
    mem_sources,
    cpp_args: test_cpp_args,
    dependencies: [
      mem_deps,
      unit_dep,
  ])
endif
