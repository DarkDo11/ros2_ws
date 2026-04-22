from setuptools import find_packages
from setuptools import setup

setup(
    name='gearbox_sim',
    version='0.0.0',
    packages=find_packages(
        include=('gearbox_sim', 'gearbox_sim.*')),
)
