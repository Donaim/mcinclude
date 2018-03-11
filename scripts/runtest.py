import subprocess, os, sys

test_dir = os.path.join('..', 'test')
test_file_name = os.path.basename(sys.argv[1])
include = (os.path.join('..', 'extern', 'doctest', 'doctest'))
output_bin_path = os.path.join('..', 'test', 'out-{}.exe'.format(test_file_name))
options = ['-std=c++14', '-Wall']

compile_args = ['-I{}'.format(include), '-o', output_bin_path, os.path.join(test_dir, test_file_name)]
compile_args = ['g++'] + options + compile_args

print("compiling ({})".format(" ".join(compile_args)))
subprocess.check_call(compile_args)

print("running {}".format(output_bin_path))
subprocess.call(output_bin_path)
