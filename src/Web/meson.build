web_lib = library('web', [
      'File.cpp',
      'FileRouter.cpp',
      'MimeType.cpp',
    ],
    cpp_args: base_cpp_args,
    dependencies: [
      core_dep,
      ty_dep,
    ])

web_dep = declare_dependency(
  link_with: web_lib,
  include_directories: '..'
  )
