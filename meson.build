project('LibJR', 'cpp',
  default_options: [
    'cpp_std=c++20',
    'cpp_eh=none',
    'cpp_rtti=false',
    'default_library=static',
    'warning_level=3',
    'buildtype=release'
  ])

if not meson.is_subproject()
  add_global_arguments('-Wno-c99-designator', language: 'cpp')
  add_global_arguments('-Wno-c99-extensions', language: 'cpp')
  add_global_arguments('-Wno-gnu-zero-variadic-macro-arguments', language: 'cpp')
  add_global_arguments('-Wno-keyword-macro', language: 'cpp')
  add_global_arguments('-Wno-gnu-conditional-omitted-operand', language: 'cpp')
  add_global_arguments('-Wno-format-pedantic', language: 'cpp')
  add_global_arguments('-Wno-nullability-extension', language: 'cpp')
  add_global_arguments('-Wno-gnu-statement-expression', language: 'cpp')
  add_global_arguments('-Wno-gnu-anonymous-struct', language: 'cpp')
  add_global_arguments('-Wno-c++2b-extensions', language: 'cpp')

  add_global_arguments('-fdebug-prefix-map=../=', language: 'cpp')
  add_global_arguments('-ffile-prefix-map=../=', language: 'cpp')
  
  add_global_arguments('-Wno-user-defined-literals', language: 'cpp')
endif

test_me = []
subdir('Unit')
subdir('Ty')
subdir('Core')
subdir('Mem')
subdir('CLI')
subdir('Main')

subdir('TestRunner')
run_target('run-tests', command: [
  test_runner_exe,
  test_me,
], depends: test_me)
