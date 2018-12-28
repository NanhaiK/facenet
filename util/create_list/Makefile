
DEBUGDIR = debug
RELEASEDIR = release

MKDIRS := $(shell find ./src  -path ./$(DEBUGDIR)   -prune -o   -path ./$(RELEASEDIR)   -prune -o -type d)
MKDIRS := $(subst ./$(DEBUGDIR),, $(MKDIRS))
MKDIRS := $(subst ./$(RELEASEDIR),, $(MKDIRS))


ver = debug
ifeq ($(ver), $(DEBUGDIR))
	CXXFLAGS =-O0 -g -ggdb
	DIR = $(DEBUGDIR)
endif
ifeq ($(ver), $(RELEASEDIR))
	DIR =  $(RELEASEDIR)
	CXXFLAGS =  -O2  
endif


MKDIRS := $(subst  ./,./$(DIR)/, $(MKDIRS))
#$(info $(MKDIRS))

$(shell mkdir  -p  $(MKDIRS))

#CXXFLAGS +=  -c  -Wall -Wextra -D_LINUX    -fPIC -fpermissive -DCPU_ONLY   -fvisibility=hidden   -DLINUX  -DUSE_OPENCV  -std=c++11 -lpthread
#CXXLinkFlags+=  -lpthread   -std=c++11 -shared -fPIC
CXXFLAGS +=  -c  -Wall -Wextra -D_LINUX    -fPIC -fpermissive -DCPU_ONLY   -fvisibility=hidden   -DLINUX  -DUSE_OPENCV  -std=c++98   -lpthread  \
 -DAPI_FACERECOGNITION01Projec_INTERFACES_EXPORTS  -Wno-unused-parameter -Wno-unused-variable
CXXLinkFlags+=    -std=c++11   -lpthread 

##################ori################
#srccplus = $(wildcard  ./src/caffe/proto/*.cc)  $(wildcard  ./src/caffe/util/*.cpp)  $(wildcard  ./src/caffe/layers/*.cpp) $(wildcard  ./src/caffe/solvers/*.cpp) $(wildcard  ./src/caffe/*.cpp) $(wildcard  ./src/*.cpp) 
#objcplus01= $(patsubst %.cpp,%.o, $(srccplus))
#objcplus =  $(patsubst %.cc,%.o, $(objcplus01))
##################################

srccplus:=$(shell find  ./  -name "*.cpp")
#nodirsrccplus = $(notdir $(srccplus))
#$(info $(nodirsrccplus))
objcplus01:= $(patsubst %.cpp,%.o, $(srccplus))
objcplus :=  $(patsubst %.cc,%.o, $(objcplus01))
DIRobjcplus :=  $(subst ./,./$(DIR)/, $(objcplus))


#$(info $(srccplus))
#$(info $(objcplus))
#$(info $(DIRobjcplus))


#exportFlag = normal
#ifeq ($(exportFlag), so)
#	SoTarget = ColorDetectionSO
#	CXXFLAGSSHARED  +=  -shared -fPIC
#	CXXLinkFlags = -L$(SoTarget);
#endif



Include := -I/usr/include  -I/usr/include/opencv \
-I/usr/include/opencv2  \
-I/usr/include\
-I./src \
-I./include 




#note: -DCPU_ONLY 否则下载cublas library

LIBS += 



#
# Compiler flags
#

CC     = g++
#CFLAGS = -Wall -Werror -Wextra -D_LINUX 

Target = ./$(DIR)/GenerateTrainTest
#$(info $(CXXFLAGS))
FolderOBJS = $(addprefix $(DIR)/,   $(oriobj) )
FolderTarget= $(addprefix $(DIR)/, $(Target))
#FolderSOTarget= $(addprefix $(DIR)/lib$(Target).so, $(SoTarget))

.PHONY: all 
# Default build
all:  $(Target) $(SoTarget)

#编译，注意不要移动编译后的o文件，后面修改某个.cpp时候则不需要全部重新编译。
./$(DIR)/%.o:./%.cpp
	$(CC)     $(CXXFLAGS)  $(Include)   $^    -o $@

	
#注意.o的位置都在依赖项
#链接！注意不要移动编译后的o文件，后面修改某个.cpp时候则不需要全部重新编译。	

$(Target):  $(DIRobjcplus) $(LIBS)  
	$(CC) $(CXXLinkFlags) $(Include)  $^   -o $@ 

prep:

	
remake: clean all

clean:
	rm -f $(DIRobjcplus) $(Target) $(FolderTarget) $(FolderOBJS)
