import os
from setuptools import setup, Extension

module = Extension('cartesianMesher2d', sources=['ccartesianmesher2dmodule.cpp', 'ccartesianmesher2d.cpp', 'cpolyutils2d.cpp', 'typeconverter.cpp'],
                   include_dirs=['.'], language='c++')

setup(name='cartesianMesher2d', ext_modules = [module])