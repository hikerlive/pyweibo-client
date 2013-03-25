import os, sys
from setuptools import setup, Extension

if sys.platform == 'darwin':
    include_dirs = []
    library_dirs = []
    libraries = []
    extra_link_args = []
else:
    include_dirs = [os.path.join('..','..','include')]
    library_dirs = [os.path.join('..','..','release')]
    libraries = []
    extra_link_args = []

example_module = Extension('_py4example',
        sources=['_sinaweibo.c', 'sinaweibo.c'],
        include_dirs=include_dirs,
        library_dirs=library_dirs,
        libraries=libraries,
        extra_link_args=extra_link_args,
        )

install_requires = []

setup(name="Py4Example",
      version="0.1",
      ext_modules=[example_module],
      py_moudles=['py4example'],
      zip_safe=False,
      install_requires=install_requires,
      )
