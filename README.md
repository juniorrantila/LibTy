# LibTy

**LibTy** is modern C++ library

## Build instructions

This project is only tested to compile with the `clang` compiler on
linux. You will need to install it along with `meson` and `ninja`.
For faster rebuilds you may install `ccache` as well.

### Setup:

```sh
meson build
```

### Build:

```sh
ninja -C build
```

### Want to depend on this library?

Since this project uses meson as a build system you can easily add
this library as a dependency by creating a file called `LibTy.wrap`
in your `subprojects` folder with this content:

```wrap
[wrap-git]
url = https://github.com/juniorrantila/libty.git
revision = main
depth = 1
```

After the file is created you can add the LibTy dependencies by
adding something similar to the following in your `meson.build`:

```meson
libty_proj = subproject('LibTy')
libty_core_dep = libty_proj.get_variable('core_dep')
libty_main_dep = libty_proj.get_variable('main_dep')

libty_cpp_args = libty_proj.get_variable('base_cpp_args')

executable('my-program', [
      'my-source.cpp',
    ],
    cpp_args: libty_cpp_args,
    dependencies: [
      libty_core_dep,
      libty_main_dep,
    ])
```

A more extensive example can be found in `examples/HelloWorld/`.
