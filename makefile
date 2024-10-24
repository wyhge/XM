# 指定编译器
CC = g++

# 指定编译选项
CFLAGS = -Wall -std=c++11

# 目标文件
TARGET = main

# 源文件
SOURCES = main.cpp EpollServer/EpollServer.cpp

# 默认目标
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)