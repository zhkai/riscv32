all: before apt conf install linux
.PHONY: all

before:
	git clone https://github.com/riscv/riscv-qemu
	git clone --recursive https://github.com/riscv/riscv-gnu-toolchain

conf:
	cd riscv-qemu; git submodule update --init pixman; ./configure --target-list=riscv32-softmmu,riscv32-linux-user
	cd riscv-gnu-toolchain; git submodule update --init --recursive; ./configure --prefix=/opt/riscv --with-xlen=32 --with-arch=RV32IMA

apt:
	apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc gcc libc6-dev pkg-config bridge-utils uml-utilities zlib1g-dev libglib2.0-dev libsdl1.2-dev

install:
	cd riscv-qemu; make
	cd riscv-gnu-toolchain; make; make linux

run:
	echo '#include <stdio.h>\n int main(void) { printf("Hello world!\\n"); return 0; }' > hello.c
	riscv32-unknown-linux-gnu-gcc hello.c -o hello
	./riscv-qemu/riscv32-linux-user/qemu-riscv32 -L /opt/riscv/sysroot hello

linux:
	curl -L https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.6.2.tar.xz | tar -xJ
	cd linux-4.6.x; git init; git remote add -t master origin https://github.com/riscv/riscv-linux.git; git fetch; git checkout -f -t origin/master

clean:
	cd riscv-qemu; clean
	cd riscv-gnu-toolchain; clean	
