import os, sys
from setuptools import setup, Extension

if sys.platform == 'darwin':
    include_dirs = []
    library_dirs = []
    libraries = []
    extra_link_args = []
else:
    include_dirs = [os.path.join('..','..','include')]
    library_dirs = [os.path.join('..','..','lib')]
    libraries = ['pyweibo1']
    extra_link_args = []

_pyweibo_module = Extension('_py4weibo',
        sources=['_py4weibo.c'],
        include_dirs=include_dirs,
        library_dirs=library_dirs,
        libraries=libraries,
        extra_link_args=extra_link_args,
        )

install_requires = []

setup(name="Py4Weibo",
      version="0.1",
      ext_modules=[_pyweibo_module],
      py_moudles=['py4weibo'],
      zip_safe=False,
      install_requires=install_requires,
      )
