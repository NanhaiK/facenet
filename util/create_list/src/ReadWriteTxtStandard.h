#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>

class ReadWriteTxtStandard
{
public:
	ReadWriteTxtStandard();
	~ReadWriteTxtStandard(void);

	int Open(const char*fileName);
	void Close();
	int OpenPlus(const char*fileName);
	void Write(const char*line);
	void Write(int num);
	void Write(int x1, int y1, int w, int h);
	void Write(std::list<std::string> filelist);
	void WriteOnlyName(std::list<std::string> filelist);
protected:
	FILE *fp;
};

