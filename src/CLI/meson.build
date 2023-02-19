cli_sources = [
  'ArgumentParser.cpp',
]

cli_deps = [
  ty_dep,
  mem_dep,
]

cli_lib = library('cli',
  cli_sources,
  dependencies: cli_deps,
  cpp_args: base_cpp_args
  )

cli_dep = declare_dependency(
  link_with: cli_lib,
  include_directories: '..'
  )

test_me += shared_library('cli-tests',
  cli_sources,
  cpp_args: [base_cpp_args, '-DLIBTY_INCLUDE_TESTS'],
  dependencies: [
    cli_deps,
    unit_dep,
  ])
