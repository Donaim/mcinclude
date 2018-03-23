import subprocess, os, sys
from os import path

my_dir = path.normpath(path.dirname(path.abspath(sys.argv[0])))
project_dir = path.normpath(path.join(my_dir, '..'))
test_dir = path.join(project_dir, 'test', 'units')
src_dir = path.join(project_dir, 'src')
mxxlink = path.join(my_dir, 'mxxbuild.py')

includes = [src_dir, path.join(project_dir, 'extern', 'doctest', 'doctest'), path.join(project_dir, 'include')]
includes = list(map(lambda p: '-I' + p, includes))

options = sys.argv[2:]

def get_mxx():
    with open(mxxlink) as lr:
        num = 0
        while True:
            line: str = lr.readline()
            if len(line) < 1 or line.isspace(): continue
            num += 1
            if num >= 2: 
                p = path.abspath(path.expanduser(line)).strip()
                if not path.isfile(p): continue
                else:
                    if not path.exists(p):
                        subprocess.check_call(['py', mxxlink])
                        return get_mxx()
                    else:
                        return p

mxxfile = get_mxx()

sys.path.insert(0, path.dirname(mxxfile))
import mxxbuild
import cppcollector

def run_tests(names):
    args = mxxbuild.parse_args([src_dir, '++verbose', '0', '++exclude', 'main.o', '++copts'] + includes + options)
    mxx = mxxbuild.mxxbuilder(args)
    src_build_dir = path.join(project_dir, 'build')
    test_build_dir = path.join(test_dir, '..', 'build')
    
    for main_source in names:
        source_without_ext = '.'.join(main_source.split('.')[:-1])

        sources = [src_dir, path.join(test_dir, main_source)]
        mxx.compile_new(sources)

        builds = [src_build_dir, path.join(test_build_dir, source_without_ext + '.o')]
        mxx.args.out = path.join(test_build_dir, source_without_ext + '.exe')
        mxx.link_some(builds)
        mxx.runexe()

if __name__ == "__main__":
    target_argument = sys.argv[1]

    if target_argument == 'clean':
        import shutil
        try: shutil.rmtree(path.join(project_dir, 'build'))
        except:pass
        try: shutil.rmtree(path.join(project_dir, 'test', 'build'))
        except:pass
        
        print("build directories are clean")
    else:
        mxx = mxxbuild.mxxbuilder(mxxbuild.parse_args([src_dir]))
        mxx.compile_stdafx()

        if target_argument == 'all':
            run_tests(
                map(lambda f: path.join(test_dir, f),
                    filter(lambda f: f.endswith('.cpp') and not f.startswith('_'), os.listdir(test_dir)))
                )
        else:
            if not target_argument.endswith('.cpp'): target_argument += '.cpp'
            target_test_file = path.join(test_dir, target_argument)
            run_tests([target_test_file])

