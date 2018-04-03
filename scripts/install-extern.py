# this will download external dependencies

import inspect, os # https://stackoverflow.com/questions/50499/how-do-i-get-the-path-and-name-of-the-file-that-is-currently-executing
thisfile = inspect.getfile(inspect.currentframe()) # script filename (usually with path)
thisdir = os.path.dirname(os.path.abspath(thisfile)) # script directory
externdir = os.path.join(thisdir, '..', 'extern')

import subprocess
def clone(repo):
    name = "".join((repo.split('/')[-1]).split('.')[0:-1])
    try: subprocess.check_call(['git', 'clone', repo, os.path.join(externdir, name)])
    except:
        print("Couln't download [{}]. Make sure you have git installed.".format(repo))
        raise

clone('https://github.com/onqtam/doctest.git')
