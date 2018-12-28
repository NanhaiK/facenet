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

class FileNameSegmenter
{
public:
	static void SegmentFullName(const std::string fullName, std::string &outputPath, std::string &outputShortName,
			std::string &outputExt);
	static void RemoveFirstSubPath(const std::string fullName, std::string &firstpath,std::string &outputPath);

};
