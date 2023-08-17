# 设置默认的c++编译器为g++
CXX ?= g++

# 设置是否开启调试模式， 默认值为1
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	#如果DUBGE为1，就将调试标志（-g）添加到编译选项中
	CXXFLAGS += -g
else
	#如果DUBGE不为1，就将优化标志（-02）添加到编译选项中
	CXXFLAGS += -02
endif

# 目标规则： 构建名为server的可执行文件
# 依赖于 main.cpp
#		./timer/lst_timer.cpp
#		./http/http_conn.cpp
#		./log/log.cpp
#		./CGImysql/sql_connection_pool.cpp 
#		webserver.cpp 
#		config.cpp
server: main.cpp ./timer/lst_timer.cpp ./http/http_conn.cpp ./log/log.cpp ./CGImysql/sql_connection_pool.cpp webserver.cpp config.cpp
	# 使用$(CXX)编译器，也就是g++编译器，将所有依赖文件（源文件）编译为server可执行文件
	$(CXX) -o server $^ $(CXXFLAGS) -lpthread -lmysqlcient

#目标规则:清理构建生成的文件
clean:
	#使用rm 命令递归地删除生成server时的中间文件
	rm -r server