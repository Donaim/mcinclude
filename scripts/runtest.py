import subprocess, os, sys
from os import path

my_dir = path.normpath(path.dirname(path.abspath(sys.argv[0])))
project_dir = path.normpath(path.join(my_dir, '..'))
test_dir = path.join(project_dir, 'test', 'units')
src_dir = path.join(project_dir, 'src')

def compile_run(main_source):

    includes = [src_dir, os.path.join(project_dir, 'extern', 'doctest', 'doctest')]
    includes = list(map(lambda p: '-I' + p, includes))
    subprocess.check_call(['py', 'mxxbuild.py', src_dir, '++no-link', '++exclude', 'main.cpp', '++copts'] + includes) # compile only, but not main.cpp

    mybuild_path = path.normpath(path.join(test_dir, '..', 'build'))
    if not path.exists(mybuild_path): os.makedirs(mybuild_path)
    my_object_path = path.join(mybuild_path, path.basename(main_source) + '.o')
    subprocess.check_call(['g++', '-c', main_source, '-o', my_object_path] + includes) # compile only this file

    subprocess.check_call(['py', 'mxxbuild.py', src_dir, '++autorun', '++no-compile', '++lopts', my_object_path, '++exclude', 'main.o']) # link only, but not main.o

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

