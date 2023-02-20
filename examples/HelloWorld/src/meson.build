executable('hello-world', [
    'main.cpp'
  ],
  cpp_args: base_cpp_args,
  dependencies: [
    core_dep,
    main_dep,
  ])

if not meson.is_subproject()
  test_me += shared_library('hello-world-tests', [
      'main.cpp'
    ],
    cpp_args: test_cpp_args,
    dependencies: [
      core_dep,
      main_dep,
      unit_dep,
    ])
endif
