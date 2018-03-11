
import os

srcdir = os.path.join('..', 'src')

allf = [os.path.join(dp, f) for dp, dn, fn in os.walk(srcdir) for f in fn]
for f in allf:
    if f.endswith('.cpp'):
        print(f)

