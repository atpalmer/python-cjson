from setuptools import setup, Extension


setup(
    name='cjson',
    version='0.0.0',
    author='Andrew Palmer',
    author_email='atp@sdf.org',
    description='JSON parser',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    url='https://github.com/atpalmer/python-cjson',

    ext_modules=[
        Extension('cjson', sources=[
            'src/cjson.c',
        ])
    ],

    classifiers=[
    ],

    python_requires=">=3.7",
)

