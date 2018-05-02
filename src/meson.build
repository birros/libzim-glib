public_headers = [
    'file.h',
    'article.h',
    'misc.h',
    'fileheader.h',
    'search.h',
    'search-iterator.h'
]

sources = [
    'file.cpp',
    'article.cpp',
    'misc.cpp',
    'fileheader.cpp',
    'search.cpp',
    'search-iterator.cpp'
]

libzim = shared_library(
    'zim-glib-@0@'.format(zim_api_version),
    sources,
    version : zim_version,
    soversion : '0',
    dependencies : [
        glib,
        gobject,
        zim
    ],
    install: true
)

install_headers(
    public_headers,
    subdir: 'zim-glib-@0@'.format(zim_api_version)
)

zim_gir = gnome.generate_gir(
    libzim,
    sources: [
        public_headers,
        sources
    ],
    namespace: 'Zim',
    nsversion: zim_api_version,
    identifier_prefix: 'Zim',
    symbol_prefix: 'zim',
    export_packages: 'zim-glib-@0@'.format(zim_api_version),
    includes: ['GLib-2.0', 'GObject-2.0'],
    install: true
)

cp = find_program('cp')
zim_metadata = custom_target(
    'zim-metadata',
    input: 'Zim.metadata',
    output: 'Zim-@0@.metadata'.format(zim_api_version),
    install: false,
    command: [cp, '@INPUT@', '@OUTPUT@']
)

# the move command and metadatadir's src argument are for fixing the destination
# path of the output file
vapigen = find_program('vapigen')
zim_vapi = custom_target(
    'zim-vapi',
    depends: zim_metadata,
    input: zim_gir,
    output: 'zim-glib-@0@.vapi'.format(zim_api_version),
    command: [
        vapigen,
            '--library', 'zim-glib-@0@'.format(zim_api_version),
            '--metadatadir', './src',
            '@INPUT@',
        '&&',
        'mv',
            'zim-glib-@0@.vapi'.format(zim_api_version),
            '@OUTPUT@'
    ],
    install: true,
    install_dir: join_paths(datadir, 'vala/vapi')
)

pkg = import('pkgconfig')
pkg.generate(
    filebase : 'zim-glib-@0@'.format(zim_api_version),
    name : 'Zim',
    description : 'GObject Bindings of Zim library',
    version : zim_version,
    libraries : [
        libzim
    ],
    subdirs : ['zim-glib-@0@'.format(zim_api_version)],
    requires: ['glib-2.0', 'gobject-2.0']
)

if enable_tests
    libzim_private = static_library(
        'zim-glib-private',
        sources: sources,
        dependencies : [
            glib,
            gobject,
            zim
        ],
        install: false
    )
    libzim_private_inc = include_directories('.')
    libzim_private_dep = declare_dependency(
        include_directories: libzim_private_inc,
        link_with : libzim_private,
        sources: zim_vapi
    )

    subdir('tests')
endif
