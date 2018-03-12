import subprocess, os, sys

my_dir = os.path.dirname(os.path.abspath(sys.argv[0]))
project_dir = os.path.abspath(os.path.join(my_dir, '..'))
test_dir = os.path.join(project_dir, 'test')

def compile_run(files):
    if not files[0].endswith('.cpp'): files[0] += '.cpp'
    test_file_name = os.path.basename(files[0])

    includes = [os.path.join(project_dir, 'src'), os.path.join(project_dir, 'extern', 'doctest', 'doctest')]
    includes = list(map(lambda p: '-I' + p, includes))
    output_bin_path = os.path.abspath(os.path.join(test_dir, 'out-{}.exe'.format(test_file_name)))
    options = ['-std=c++14']

    compile_args = ['g++'] + options + includes
    compile_args += files
    compile_args += ['-o', output_bin_path]

    print("compiling ({})".format(" ".join(compile_args)))
    subprocess.check_call(compile_args)

    print("running {}".format(output_bin_path))
    subprocess.call(output_bin_path)
def get_cpps():
    import subprocess
    proc = subprocess.Popen(['py', os.path.join(my_dir, 'get_cpps.py')], stdout=subprocess.PIPE)
    proc.wait()
    text = proc.stdout.read()
    text = text.decode('utf-8')
    lines = text.split(os.linesep)
    lines = filter(lambda f: len(f) > 1 and not f.isspace() and os.path.basename(f) != 'main.cpp', lines)

    lines = map(lambda f: os.path.abspath(f), lines)
    return list(lines)

cpps = get_cpps()
if sys.argv[1] == 'all':
    for f in os.listdir(test_dir):
        if f.endswith('.cpp') and not f.startswith('_'): 
            try: compile_run( [os.path.join(test_dir, f)] + cpps)
            except: pass
else:
    target_test_file = os.path.abspath(os.path.join(test_dir, sys.argv[1]))
    compile_run([target_test_file] + cpps)


