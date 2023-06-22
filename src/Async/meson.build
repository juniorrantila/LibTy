os = target_machine.system()
arch = target_machine.cpu_family()
context_src = 'system' / arch / os / 'context.S'

async_lib = library('async', [
    context_src
  ], dependencies: [
    ty_dep,
  ],
  cpp_args: base_cpp_args
)

async_dep = declare_dependency(
  link_with: async_lib,
  include_directories: '..'
)

test_me += shared_library('async-tests', [
    'Tests.cpp'
  ], dependencies: [
    async_dep,
    unit_dep,
  ],
  cpp_args: test_cpp_args
)
