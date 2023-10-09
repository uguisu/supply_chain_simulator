from distutils.core import setup, Extension
from pathlib import Path

# to confirm:
#     ldd -r /<PATH>/venv/lib/python3.8/site-packages/scs.cpython-38-x86_64-linux-gnu.so


# === base info ===
model_name = 'scs'
src_dirs = [
    '../../src/scs/core',
    '../../src/scs/entity',
    '../../src/scs/enums',
    '../../src/scs/function',
]


def get_sources() -> list:

    rtn = []

    for strP in src_dirs:
        path = Path(strP).resolve()
        for fi in path.glob('*.cpp'):
            rtn.append(f'{path}/{fi.name}')

    return rtn


def get_include_dir() -> list:

    return [
        '/usr/local/include',
    ]


def get_libraries() -> list:
    return [
        'python3.8',
        'glog',
        'gflags',
    ]


def get_runtime_library_dirs() -> list:
    return [
        '/usr/local/lib',
    ]


def get_extension() -> Extension:

    return Extension(
        name = model_name,
        sources = get_sources(),
        include_dirs = get_include_dir(),
        libraries=get_libraries(),
        runtime_library_dirs=get_runtime_library_dirs(),
    )


def main():
    setup(name=model_name,
          version="1.0.0",
          description="scs test",
          author="xin.he",
          author_email="xin.he@123.com",
          ext_modules=[get_extension()])


if __name__ == "__main__":
    main()
