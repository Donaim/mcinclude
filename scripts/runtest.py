import subprocess, os, sys
from os import path

my_dir = path.normpath(path.dirname(path.abspath(sys.argv[0])))
project_dir = path.normpath(path.join(my_dir, '..'))
test_dir = path.join(project_dir, 'test', 'units')
src_dir = path.join(project_dir, 'src')
mxxfile = path.join(my_dir, 'mxxbuild.py')

includes = [src_dir, os.path.join(project_dir, 'extern', 'doctest', 'doctest')]
includes = list(map(lambda p: '-I' + p, includes))

def compile_run(main_source):
    source_without_ext = '.'.join(main_source.split('.')[:-1])
    myopts = sys.argv[2:]

    # compile /src
    subprocess.check_call(['py', mxxfile, src_dir, '++no-link', '++exclude', 'main.cpp', '++copts'] + includes + myopts) # do not compile main.cpp

    # compile this test file
    my_build_dir = path.normpath(path.join(test_dir, '..', 'build'))
    if not path.exists(my_build_dir): os.makedirs(my_build_dir)
    my_object_path = path.join(my_build_dir, path.basename(source_without_ext) + '.o')
    subprocess.check_call(['py', mxxfile, test_dir, '++no-link', '++copts'] + includes + myopts) # do not compile main.cpp

    # link this test with /src
    out_exe_path = path.join(my_build_dir, 'exe.exe')
    subprocess.check_call(['py', mxxfile, src_dir, '++no-compile', '++lopts', my_object_path, '++exclude', 'main.o', '++out', out_exe_path] + myopts) # do not include main.o
    
    # run
    subprocess.call([out_exe_path])

if __name__ == "__main__":
    target_argument = sys.argv[1]

    if target_argument == 'all':
        for f in os.listdir(test_dir):
            if f.endswith('.cpp') and not f.startswith('_'): 
                try: compile_run(path.join(test_dir, f))
                except: pass
    else:
        if not target_argument.endswith('.cpp'): target_argument += '.cpp'
        target_test_file = path.join(test_dir, target_argument)
        compile_run(target_test_file)

