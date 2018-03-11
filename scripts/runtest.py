import subprocess, os, sys

def compile_run(test_file_name):
    if not test_file_name.endswith('.cpp'): test_file_name += '.cpp'

    includes = [os.path.join('..', 'src'), os.path.join('..', 'extern', 'doctest', 'doctest')]
    includes = list(map(lambda p: '-I' + p, includes))
    output_bin_path = os.path.join('..', 'test', 'out-{}.exe'.format(test_file_name))
    options = ['-std=c++14']

    compile_args = ['-o', output_bin_path, os.path.join(test_dir, test_file_name)]
    compile_args = ['g++'] + options + includes + compile_args

    print("compiling ({})".format(" ".join(compile_args)))
    subprocess.check_call(compile_args)

    print("running {}".format(output_bin_path))
    subprocess.call(output_bin_path)

test_dir = os.path.join('..', 'test')

if sys.argv[1] == 'all':
    for f in os.listdir(test_dir):
        if f.endswith('.cpp'): 
            try: compile_run(f)
            except: pass
else:
    compile_run(os.path.basename(sys.argv[1]))



