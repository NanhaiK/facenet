#pragma once

#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <dirent.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>


class FindFilesInAFolder_Linux
{
public:
	//ext = "jpg" || "png"
	static void RecursivelyFindFiles(const char *path, std::list<std::string> &fileList, const char* ext="");

protected:
	static void  listDir(const char *path,std::list<std::string> &fileList,const char* ext);
};
