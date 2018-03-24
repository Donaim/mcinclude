import subprocess, os, sys
from os import path

my_dir = path.normpath(path.dirname(path.abspath(sys.argv[0])))
project_dir = path.normpath(path.join(my_dir, '..'))
test_dir = path.join(project_dir, 'test', 'units')
src_dir = path.join(project_dir, 'src')
mxxlink = path.join(my_dir, 'mxxbuildlnk.py')

includes = [src_dir, path.join(project_dir, 'extern', 'doctest', 'doctest'), path.join(project_dir, 'include')]
includes = list(map(lambda p: '-I' + p, includes))

options = sys.argv[2:]

def get_mxx():
    import mxxbuildlnk
    mxxbuildlnk.parse_args()
    mxxbuildlnk.init_args()
    re = mxxbuildlnk.tag_funcs._get_first_local(mxxbuildlnk.args_list).command
    re = path.expanduser(re)
    if not path.exists(re): mxxbuildlnk.invoke_tags()
    return re
mxxfile = get_mxx()

sys.path.insert(0, path.dirname(mxxfile))
import mxxbuild

def run_tests(names):
    args = mxxbuild.parse_args([src_dir, '++verbose', '0', '++exclude', 'main.o', '++copts'] + includes + options)
    # args = mxxbuild.parse_args([src_dir, '++verbose', '0', '++copts'] + includes + options)
    mxx = mxxbuild.mxxbuilder(args)
    src_build_dir = path.join(project_dir, 'build', 'src')
    test_build_dir = path.join(project_dir, 'build', 'test', 'units')
    
    for main_source in names:
        source_without_ext = path.basename('.'.join(main_source.split('.')[:-1]))

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

