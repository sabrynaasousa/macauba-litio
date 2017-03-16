# Instalação da biblioteca gráfica SDL 2
sudo apt-get install libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev

# Instalação da engine
CURRENT=`pwd`
BASENAME=`basename "$CURRENT"`

git clone https://github.com/fgagamedev/ijengine.git ../ijengine
cd ../ijengine
make dist-clean
make
sudo make install
cp kernel/sdl2/kernel.so.0.1.0 ../$BASENAME/libs
cd ../$BASENAME

# Execução do simulador
make dist-clean
make
make run
