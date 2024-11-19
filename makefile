# 定义目标
.PHONY: clean setup build all

# 删除build目录
clean:
	rm -rf build

# 创建build目录
setup: clean
	mkdir build

# 编译
build: setup
	@cd build && cmake .. && make -j4 && cd ..

# 默认执行编译
all: build