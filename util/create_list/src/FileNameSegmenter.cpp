
#include "FileNameSegmenter.h"
#include <iostream>

using namespace std;

void FileNameSegmenter::RemoveFirstSubPath(const std::string fullName, std::string &firstpath,std::string &outputPath)
{
	int idx = fullName.find_first_of("/");
	firstpath = fullName.substr(0,idx);
	outputPath = fullName.substr(idx+1,fullName.size() - idx -1);
}

void FileNameSegmenter::SegmentFullName(std::string fullName, std::string &outputPath, std::string &outputShortName,
			std::string& outputExt)
{
	int idx = fullName.rfind("/");
	outputPath = fullName.substr(0, idx);	
	//cout<<"+++idx = "<< idx<<";   "<<outputPath<<endl;	
	outputShortName = fullName.substr(idx+1,fullName.size());
	//cout<<"+++  "<<outputShortName<<endl;

	idx = outputShortName.rfind(".");
	outputExt = outputShortName.substr(idx+1,outputShortName.size());
	outputShortName = outputShortName.substr(0,idx);
	
}
