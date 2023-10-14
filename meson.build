project('libzim-glib', ['cpp', 'c'], version: '4.0.0')

zim_version = meson.project_version()
zim_version_digits = zim_version.split('.')
zim_major_version = zim_version_digits[0].to_int()
zim_minor_version = zim_version_digits[1].to_int()
zim_micro_version = zim_version_digits[2].to_int()

zim_api_version = '@0@.0'.format(zim_major_version)

prefix = get_option('prefix')
datadir = join_paths(prefix, get_option('datadir'))
libdir = join_paths(prefix, get_option('libdir'))
includedir = join_paths(prefix, get_option('includedir'))

glib = dependency('glib-2.0')
gobject = dependency('gobject-2.0')
zim = dependency('libzim', version : '>=7.0.0')

gnome = import('gnome')

tests = get_option('tests')

subdir('src')
