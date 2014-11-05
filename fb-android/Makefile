export NDK=/opt/android-ndk
export NDK_TOOLCHAIN=${NDK}/toolchains/x86-4.9/prebuilt/linux-x86_64/bin/i686-linux-android-
export NDK_SYSROOT=${NDK}/platforms/android-15/arch-x86

LD=${NDK_TOOLCHAIN}ld.gold
CXX=${NDK_TOOLCHAIN}g++
CXXFLAGS=--sysroot=${NDK_SYSROOT} -g -I ${NDK_SYSROOT}/usr/include -fno-exceptions -Werror -Wextra -Wall -w -pedantic --std=c++14
LDFLAGS=-L${NDK_SYSROOT}/usr/lib -lstdc++ -lm
SRC=painter.cpp
INC=$(SRC,.cpp=.h)

all: $(SRC) $(INC)
	$(CXX) $(CXXFLAGS) $(SRC) main.cpp -o prog $(LDFLAGS)

run: all deploy
	adb shell /data/prog

clean:
	rm -f prog

deploy:
	adb connect localhost:55001
	adb push prog /data/
