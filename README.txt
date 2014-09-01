##compile instructions

the project uses cmake to compile do on the top folder:

mkdir build
cd build
cmake ..
make

Executable will be created on build/bin, this executable will
search for resources at ../../Resources

Executables for linux and mac are provided into executables folder

you can also generate xcode file with cmake doing:

cmake -G Xcode ..

HAVE FUN!!
