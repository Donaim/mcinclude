import subprocess, os, sys
from os import path

my_dir = path.normpath(path.dirname(path.abspath(sys.argv[0])))
project_dir = path.normpath(path.join(my_dir, '..'))
builddir = path.join(project_dir, 'build')

test_dir = path.join(project_dir, 'test', 'units')
src_dir = path.join(project_dir, 'src')
src_build_dir = path.join(builddir, 'src')
test_build_dir = path.join(builddir, 'test', 'units')

includes = [src_dir, path.join(project_dir, 'extern', 'doctest', 'doctest'), path.join(project_dir, 'include')]
includes = list(map(lambda p: '-I' + p, includes))
exclude = [path.join(src_build_dir, 'main.o')]

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
import buildmethods

log = mxxbuild.Log(0)
if '++verbose' in sys.argv:
    log.level = 1

def run_tests(names: list):
    for main_source in names:
        source_without_ext = path.basename('.'.join(main_source.split('.')[:-1]))

        sources = [src_dir, path.join(test_dir, main_source)]
        buildmethods.compile_new(sources, rootdir=project_dir, builddir=builddir, copts=includes, exclude=exclude, log=log)

        builds = [src_build_dir, path.join(test_build_dir, source_without_ext + '.o')]
        output_exe = path.join(test_build_dir, source_without_ext + '.exe')
        buildmethods.linksome(builds, output_exe, rootdir=project_dir, lopts=[], exclude=exclude, log=log)

        subprocess.check_call([output_exe])

if __name__ == "__main__":
    target_argument = sys.argv[1]

    if target_argument == 'clean':
        import shutil
        try: shutil.rmtree(path.join(project_dir, 'build'))
        except:pass

        print("/build directory is clean")
    else:
        buildmethods.compile_stdafxes([src_dir, test_dir], copts=includes, log=log)

        if target_argument == 'all':
            run_tests(
                map(lambda f: path.join(test_dir, f),
                    filter(lambda f: f.endswith('.cpp') and not f.startswith('_'), os.listdir(test_dir)))
                )
        else:
            if not target_argument.endswith('.cpp'): target_argument += '.cpp'
            target_test_file = path.join(test_dir, target_argument)
            run_tests([target_test_file])

