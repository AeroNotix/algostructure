from distutils.core import setup, Extension
import os

ROOT = os.path.dirname(__file__)

module1 = Extension(
    'sorting',
    include_dirs = [os.path.realpath(os.path.join(ROOT, os.pardir, os.pardir, "C++", "sorting"))],
    sources = ['sorting.cpp'],
    extra_compile_args = ['-std=c++11']
    )

setup(
    name = 'sorting',
    author = "Aaron France",
    author_email = "aaron.l.france@gmail.com",
    version = '0.1',
    description = "Sorting",
    long_description = "Sorting. Written in C++11.",
    ext_modules = [module1]
    )
