main_lib = static_library('main', [
      'Main.cpp'
    ],
    cpp_args: base_cpp_args,
    dependencies: [core_dep, ty_dep])

main_dep = declare_dependency(
  link_with: main_lib,
  include_directories: '..'
  )
