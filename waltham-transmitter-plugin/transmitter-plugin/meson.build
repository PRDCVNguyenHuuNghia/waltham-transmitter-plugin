
libpixman_dep = dependency('pixman-1')

deps_transmiter_plugin = [
    libwayland_dep,
    libpixman_dep,
    libweston_dep,
    libwaltham_dep,
    weston_dep,
    cc.find_library('m')
]

plugin_transmitter = shared_library(
	'waltham-transmitter',
	'input.c',
	'output.c',
	'plugin.c',
	include_directories: common_inc,
	dependencies: deps_transmiter_plugin,
	name_prefix: '',
	install: true,
	install_dir: plugin_install_dir,
)
env_modmap += 'transmitter-plugin.so=@0@;'.format(plugin_transmitter.full_path())
