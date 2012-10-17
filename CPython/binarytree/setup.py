from distutils.core import setup, Extension
import os

ROOT = os.path.dirname(__file__)

module1 = Extension(
    'binarytree',
    include_dirs = [
        os.path.join(ROOT, os.pardir, os.pardir, "C++", "binarytree"),
        ],
    sources = ['binarytree.cpp'],
    extra_compile_args = ['-std=c++11','-O3']
    )

setup(
    name = 'binarytree',
    author = "Aaron France",
    author_email = "aaron.l.france@gmail.com",
    version = '0.1',
    description = "Binary Tree",
    long_description = "Binary Tree. Written in C++11.",
    ext_modules = [module1]
    )
