
libpixman_dep = dependency('pixman-1')
dep_gstreamer = dependency('gstreamer-1.0')
dep_gstreamer_app = dependency('gstreamer-app-1.0')
dep_gstreamer_video = dependency('gstreamer-video-1.0')
dep_gstreamer_alloc = dependency('gstreamer-allocators-1.0')

deps_renderer_plugin = [
    libwayland_dep,
    libpixman_dep,
    libweston_dep,
    libwaltham_dep,
    weston_dep,
    dep_gstreamer, dep_gstreamer_app,
    dep_gstreamer_video, dep_gstreamer_alloc
]

plugin_renderer = shared_library(
	'waltham-renderer',
	'waltham-renderer.c',
	include_directories: common_inc,
	dependencies: deps_renderer_plugin,
	name_prefix: '',
	install: true,
	install_dir: plugin_install_dir,
)
env_modmap += 'renderer-plugin.so=@0@;'.format(plugin_renderer.full_path())
