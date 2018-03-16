import subprocess, os, sys
from os import path

my_dir = path.normpath(path.dirname(path.abspath(sys.argv[0])))
project_dir = path.normpath(path.join(my_dir, '..'))
test_dir = path.join(project_dir, 'test', 'units')
src_dir = path.join(project_dir, 'src')

includes = [src_dir, os.path.join(project_dir, 'extern', 'doctest', 'doctest')]
includes = list(map(lambda p: '-I' + p, includes))

def compile_run(main_source):
    # compile /src
    subprocess.check_call(['py', 'mxxbuild.py', src_dir, '++no-link', '++exclude', 'main.cpp', '++copts'] + includes) # do not compile main.cpp

    # compile this test file
    my_build_dir = path.normpath(path.join(test_dir, '..', 'build'))
    if not path.exists(my_build_dir): os.makedirs(my_build_dir)
    my_object_path = path.join(my_build_dir, path.basename(main_source) + '.o')
    subprocess.check_call(['g++', '-c', main_source, '-o', my_object_path] + includes) # compile only this file

    # link this test with /src
    out_exe_path = path.join(my_build_dir, 'exe.exe')
    subprocess.check_call(['py', 'mxxbuild.py', src_dir, '++no-compile', '++lopts', my_object_path, '++exclude', 'main.o', '++out', out_exe_path]) # do not include main.o
    
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
        target_test_file = path.join(test_dir, target_argument)
        compile_run(target_test_file)

