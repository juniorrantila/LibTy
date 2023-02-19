project('LibTy', 'cpp',
  default_options: [
    'cpp_std=c++20',
    'cpp_eh=none',
    'cpp_rtti=false',
    'default_library=static',
    'warning_level=3',
    'buildtype=release'
  ])

base_cpp_args = [
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
]

test_me = []

subdir('src')

if not meson.is_subproject()
  run_target('run-tests', command: [
    test_runner_exe,
    test_me,
  ], depends: test_me)
endif
