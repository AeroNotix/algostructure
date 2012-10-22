from distutils.core import setup, Extension
import os

ROOT = os.path.dirname(__file__)

module1 = Extension(
    'prefixtrie',
    include_dirs = [
        os.path.join(ROOT, os.pardir, os.pardir, "C++", "prefixtrie"),
        ],
    sources = ['prefixtrie.cpp'],
    extra_compile_args = ['-std=c++11', '-g']
    )

setup(
    name = 'prefixtrie',
    author = "Aaron France",
    author_email = "aaron.l.france@gmail.com",
    version = '0.1',
    description = "Prefix Trie",
    long_description = "Prefix Trie. Written in C++11.",
    ext_modules = [module1]
    )
