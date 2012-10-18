from distutils.core import setup, Extension
import os

ROOT = os.path.dirname(__file__)

module1 = Extension(
    'bubblesort',
    include_dirs = [os.path.realpath(os.path.join(ROOT, os.pardir, os.pardir, "C++", "sorting"))],
    sources = ['bubblesort.cpp'],
    extra_compile_args = ['-std=c++11']
    )

setup(
    name = 'bubblesort',
    author = "Aaron France",
    author_email = "aaron.l.france@gmail.com",
    version = '0.1',
    description = "Bubblesort",
    long_description = "Bubblesort. Written in C++11.",
    ext_modules = [module1]
    )
