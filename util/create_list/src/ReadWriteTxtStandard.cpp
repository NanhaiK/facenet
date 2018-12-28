
#include "ReadWriteTxtStandard.h"
#include "FileNameSegmenter.h"

ReadWriteTxtStandard::ReadWriteTxtStandard()
{
	this->fp = NULL;
}


ReadWriteTxtStandard::~ReadWriteTxtStandard(void)
{
	Close();
}

int ReadWriteTxtStandard::Open(const char*fileName)
{
	Close();
	if((fp=fopen(fileName,"w+"))==NULL)
	{
		printf("cannot open %s\n",fileName);
		return (-1);
	}
	return 1;
}

int ReadWriteTxtStandard::OpenPlus(const char*fileName)
{
	Close();
	if((fp=fopen(fileName,"a+"))==NULL)
	{
		printf("cannot open %s\n",fileName);
		return (-1);
	}
	return 1;
}

void ReadWriteTxtStandard::Close()
{
	if(NULL != fp)
	{
		fclose(fp); 
	}
	fp=NULL;
}
	
void ReadWriteTxtStandard::Write(const char*line)
{
	fprintf(fp,"%s\n",line);
}

void ReadWriteTxtStandard::Write(int num)
{
	fprintf(fp,"%d\n",num);
}

void ReadWriteTxtStandard::Write(int x1,int y1, int w, int h)
{
	fprintf(fp,"%d,%d,%d,%d\n",x1,y1,w,h);
}
void ReadWriteTxtStandard::WriteOnlyName(std::list<std::string> filelist)
{
	std::list<std::string>::iterator it = filelist.begin();

	while(it != filelist.end()){
		std::string outputPath;
		std::string outputShortName;
		std::string outputExt;

		FileNameSegmenter::SegmentFullName(*it,outputPath,outputShortName,outputExt);
		FileNameSegmenter::SegmentFullName(outputPath,outputPath,outputShortName,outputExt);
		fprintf(fp,"%s\n",it->c_str());
		++it;
	}
}

void ReadWriteTxtStandard::Write(std::list<std::string> filelist)
{
	std::list<std::string>::iterator it = filelist.begin();

	while(it != filelist.end()){
		std::string outputPath;
		std::string outputShortName;
		std::string outputExt;
		std::string label;

		std::string tmp = *it;
		std::string tmpout;
		FileNameSegmenter::RemoveFirstSubPath(tmp,label,tmpout);
		while(label == "." ||label == ".." ){
			tmp = tmpout;
			FileNameSegmenter::RemoveFirstSubPath(tmp,label,tmpout);
		}
		//第二层是label
		tmp = tmpout;
		FileNameSegmenter::RemoveFirstSubPath(tmp,label,tmpout);
		while(label == "." ||label == ".." ){
					tmp = tmpout;
					FileNameSegmenter::RemoveFirstSubPath(tmp,label,tmpout);
				}

		fprintf(fp,"%s    %s\n",it->c_str(),label.c_str());
		++it;
	}
}
