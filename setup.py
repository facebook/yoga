from pathlib import Path
from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

setup(
    name="yoga-layout",
    version="1.0.0",
    description="Python bindings for the Yoga layout engine",
    ext_modules=[
        Pybind11Extension(
            "yoga",
            [*sorted(glob("yoga/**/*.cpp")), *sorted(glob("python/src/*.cc"))],
            include_dirs=["."],
        )
    ],
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    extras_require={"test": ["pytest>=6.0"], "build": ["pybind11>=2.10.3"]},
    python_requires=">=3.7",
)
