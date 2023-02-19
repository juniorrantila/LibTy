project('LibTy', 'cpp',
  default_options: [
    'cpp_std=c++20',
    'cpp_eh=none',
    'cpp_rtti=false',
    'default_library=static',
    'warning_level=3',
    'buildtype=release'
  ])

if not meson.is_subproject()
  add_global_arguments([
    '-Wno-gnu-case-range',
    '-Wno-c99-designator',
    '-Wno-c99-extensions',
    '-Wno-gnu-anonymous-struct',
    '-Wno-gnu-conditional-omitted-operand',
    '-Wno-gnu-statement-expression',
    '-Wno-gnu-zero-variadic-macro-arguments',
    '-Wno-user-defined-literals',
    '-fdebug-prefix-map=../=',
    '-ffile-prefix-map=../=',
  ], language: 'cpp')
endif

test_me = []

subdir('Unit')
subdir('Ty')
subdir('Core')
subdir('Mem')
subdir('CLI')
subdir('Main')
subdir('HTTP')
subdir('Net')
subdir('Web')

if not meson.is_subproject()
  subdir('TestRunner')
  run_target('run-tests', command: [
    test_runner_exe,
    test_me,
  ], depends: test_me)
endif
