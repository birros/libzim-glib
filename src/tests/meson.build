add_languages('c')
prog_c = executable(
    'prog-c',
    'prog.c',
    dependencies : [
        glib,
        gobject,
        libzim_private_dep
    ]
)
test('prog-c', prog_c)

add_languages('vala')
prog_vala = executable(
    'prog-vala',
    'prog.vala',
    dependencies : [
        glib,
        gobject,
        libzim_private_dep
    ]
)
test('prog-vala', prog_vala)


# ugly way to get LD_LIBRARY_PATH and GI_TYPELIB_PATH build environment variables
src_build_dir = join_paths(meson.build_root(), 'src')

pymodule = import('python3')
python3 = pymodule.find_python()

res = run_command(python3, '-c', 'import os; print(os.environ["LD_LIBRARY_PATH"])')
if res.returncode() == 0
    ld_library_path = src_build_dir
    ld_library_path += ':' + res.stdout().strip()
else
    ld_library_path = src_build_dir
endif
res = run_command(python3, '-c', 'import os; print(os.environ["GI_TYPELIB_PATH"])')
if res.returncode() == 0
    gi_typelib_path = src_build_dir
    gi_typelib_path += ':' + res.stdout().strip()
else
    gi_typelib_path = src_build_dir
endif


prog_py = find_program('./prog.py')
prog_py_env = environment()
prog_py_env.set('GI_TYPELIB_PATH', gi_typelib_path)
prog_py_env.set('LD_LIBRARY_PATH', ld_library_path)
test('prog-py', prog_py, env: prog_py_env)
