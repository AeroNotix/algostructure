from distutils.core import setup, Extension

module1 = Extension(
    'quicksort',
    include_dirs = ['/home/aero/algostructure/C++/sorting'],
    sources = ['quicksort.cpp'],
    extra_compile_args = ['-std=c++11']
    )

setup(
    name = 'quicksort',
    author = "Aaron France",
    author_email = "aaron.l.france@gmail.com",
    version = '0.1',
    description = "Quicksort",
    long_description = "Quicksort. Written in C++11.",
    ext_modules = [module1]
    )
