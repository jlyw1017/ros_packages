## ! DO NOT MANUALLY INVOKE THIS setup.py, USE CATKIN INSTEAD

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

# fetch values from package.xml
setup_args = generate_distutils_setup(
    packages=['python_imapro_package'],
    package_dir={'': 'src'})

setup(**setup_args)#这就是把上马那个setup_args里的东西塞到这个函数里，也可以直接在setup()里写
