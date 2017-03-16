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
