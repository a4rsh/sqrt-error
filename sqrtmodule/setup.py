from setuptools import setup, Extension

# Define the extension module
sqrt_module = Extension(
    'sqrt',           # Module name
    sources=['sqrtmodule.c']  # C source file(s)
)

# Setup script
setup(
    name='sqrt',
    version='1.0',
    description='Approximate square root using Taylor\'s theorem',
    ext_modules=[sqrt_module]
)

