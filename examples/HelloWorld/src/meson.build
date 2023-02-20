executable('hello-world', [
    'main.cpp'
  ],
  cpp_args: base_cpp_args,
  dependencies: [
    core_dep,
    main_dep,
  ])

test_me += shared_library('hello-world-test', [
    'main.cpp'
  ],
  cpp_args: test_cpp_args,
  dependencies: [
    core_dep,
    main_dep,
    unit_dep,
  ])
