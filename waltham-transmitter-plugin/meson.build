project('waltham-transmitter',
  'c',
  version: '0.0.1',
  default_options: [
    'warning_level=3',
    'c_std=gnu99',
  ],
  meson_version: '>= 0.50',
  license: 'MIT/Expat',
)

pkgconfig = import('pkgconfig')
cc = meson.get_compiler('c')

add_project_arguments(
  cc.get_supported_arguments([
    '-Wno-unused-parameter',
    '-Wno-pedantic',
    '-Wextra',
    '-Werror'
  ]),
  language: 'c'
)

add_project_arguments([
    '-DPACKAGE_STRING="waltham-transmitter @0@"'.format(meson.project_version()),
    '-D_GNU_SOURCE',
    '-D_ALL_SOURCE',
  ],
  language: 'c'
)

optional_libc_funcs = [ 'memfd_create', 'strchrnul' ]
foreach func: optional_libc_funcs
    if cc.has_function(func)
        add_project_arguments('-DHAVE_@0@=1'.format(func.to_upper()), language: 'c')
    endif
endforeach


env_modmap = ''
libweston_major_version = '8'
libweston_version = 'libweston-@0@'.format(libweston_major_version)
libweston_dep = dependency(libweston_version)

libwayland_dep = dependency('wayland-server')
libwaltham_dep = dependency('waltham')
weston_dep = dependency('weston')

prefix_path = get_option('prefix')
plugin_dir = join_paths(prefix_path, get_option('libdir'))
plugin_install_dir = join_paths(plugin_dir, libweston_version)
common_inc = include_directories('include')

dir_include_waltham_transmiter_install = 'waltham-transmitter'

subdir('transmitter-plugin')
subdir('include')
