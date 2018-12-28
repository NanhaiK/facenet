//============================================================================
// Name        : RandomGenerateTrainTest01.cpp
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<stdlib.h>
#include <iostream>
#include "FindFilesInAFolder_Linux.h"
#include "ReadWriteTxtStandard.h"
#include "assert.h"
#include <algorithm>
#include <vector>
#include <sys/stat.h>
#include "FileNameSegmenter.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#define FILEPATH_MAX 2000
using namespace std;

void RandomGenerateOnlyName(string srcpath,string tgtpath, float trainFileRate, string fileExt = "")
{


	assert(trainFileRate <=1.0 && trainFileRate>=0);
	std::list<std::string> filelist;
	FindFilesInAFolder_Linux::RecursivelyFindFiles(srcpath.c_str(),filelist,fileExt.c_str());
   printf("--------------------------------------------\n");
	std::vector<std::string> filevector;
	int tt = filelist.size();
	if(tt==0) return;
   filevector.reserve(filelist.size()+1);
	////////////////////////////
	std::list<std::string>::iterator it = filelist.begin();
	while(it != filelist.end()){
		filevector.push_back(*it);
		++it;
	}
	filelist.clear();
	///////////////////////////////
	std::random_shuffle(filevector.begin(),filevector.end());//迭代器
	int testTotal = filevector.size() * (1- trainFileRate);

	  printf("---------------------01-----------------------\n");
    std::list<std::string> filelistTrain;
    std::list<std::string> filelistTest;

    std::vector<std::string>::iterator it01 = filevector.begin();
    int idx = 0;
   	while(it01 != filevector.end()){
   	  string name = *it01;
   	  int idxnum = name.find_last_of("/");
      string newname = name.substr(0,idxnum);
      idxnum = newname.find_last_of("/");
      string numlabel = newname.substr(idxnum+1,newname.size()-idxnum -1);

   	  string prename = string(tgtpath);
   	name = prename +name;
   	  if(idx < testTotal){

        	   printf("001test: %s\n",name.c_str());
        	   filelistTest.push_back(name + "   " + numlabel);
           }else{

        	   printf("001train: %s\n",name.c_str());
        	   filelistTrain.push_back(name + "   " + numlabel);
           }
    		++it01;
    		++idx;
    	}


	ReadWriteTxtStandard writer;
	printf("------------------------train--------------------\n");
	string trainfilename = tgtpath + "train.txt";
    writer.Open(trainfilename.c_str());
    writer.WriteOnlyName(filelistTrain);
    writer.Close();
    printf("----------------------test----------------------\n");
	string testfilename = tgtpath + "test.txt";
    writer.Open(testfilename.c_str());
    writer.WriteOnlyName(filelistTest);
    writer.Close();
	return;
}



void RandomGenerateAndCopyPics(string srcpath,string tgtpath, float trainFileRate)
{
	assert(trainFileRate <=1.0 && trainFileRate>=0);
	std::list<std::string> filelist;
	FindFilesInAFolder_Linux::RecursivelyFindFiles(srcpath.c_str(),filelist);
   printf("--------------------------------------------\n");
	std::vector<std::string> filevector;
   filevector.reserve(filelist.size());
	//////////////////////////////
	std::list<std::string>::iterator it = filelist.begin();
	while(it != filelist.end()){
		filevector.push_back(*it);
		++it;
	}
	filelist.clear();
	///////////////////////////////随机排序
	srand((unsigned int)time((time_t *)NULL));
	std::random_shuffle(filevector.begin(),filevector.end());//迭代器
	int testTotal = filevector.size() * (1- trainFileRate);


    std::list<std::string> filelistTrain;
    std::list<std::string> filelistTest;

    std::vector<std::string>::iterator it01 = filevector.begin();
    int idx = 0;
   	while(it01 != filevector.end()){
           if(idx < testTotal){
        	   string name = *it01;
        	   printf("001test: %s\n",name.c_str());
        	   filelistTest.push_back(name);
           }else{
        	   string name = *it01;
        	   printf("001train: %s\n",name.c_str());
        	   filelistTrain.push_back(name);
           }
    		++it01;
    		++idx;
    	}


	ReadWriteTxtStandard writer;
	printf("------------------------train--------------------\n");
	string trainfilename = tgtpath + "train.txt";
    writer.Open(trainfilename.c_str());
    writer.Write(filelistTrain);
    writer.Close();

    string testFolder = "./test";
    string trainFolder =  "./train";
    int ret =  mkdir(testFolder.c_str(), 0777);
    if(ret == -1){
    	 printf("ret = %d;the folder  %s  exists! \n",ret,testFolder.c_str());
    }else{
    	 printf("ret = %d, successfully create the folder:%s \n",ret,testFolder.c_str());
    }
    ret =  mkdir(trainFolder.c_str(), 0777);
    if(ret == -1){
        	 printf("ret = %d;the folder  %s  exists! \n",ret,trainFolder.c_str());
        }else{
        	 printf("ret = %d, successfully create the folder:%s \n",ret,trainFolder.c_str());
        }

    std::list<std::string>::iterator ittrain = filelistTrain.begin();
     while(ittrain != filelistTrain.end()){
    		std::string outputPath;
    		std::string outputShortName;
    		std::string outputExt;

    		string tmpname;
    		string tmptxt;
    		string tmpname01;
    		string tmptxt01;
    	FileNameSegmenter::SegmentFullName(*ittrain,outputPath,outputShortName,outputExt);
    	FileNameSegmenter::SegmentFullName(outputPath,outputPath,tmpname,tmptxt);
     	FileNameSegmenter::SegmentFullName(outputPath,outputPath,tmpname01,tmptxt01);

    	string newfolder =  trainFolder + "/"+ tmpname ;
      	string newname =newfolder+"/" +outputShortName + "." + outputExt;
      	//判断目录是否存在，不存在建立
    	if( access(newfolder.c_str(), F_OK) == -1)
    	{
    		printf("create folder %s\n",newfolder.c_str());
    		printf("%d\n", mkdir(newfolder.c_str(), 0777));
    	}

    	 string cmd = string("cp  ") + *ittrain + "  " + newname;
    	 printf("%s\n",cmd.c_str());
    	 system(cmd.c_str());
    	 ++ittrain;
     }

///////////////////////////////////////////////////////////
    printf("----------------------test----------------------\n");
	string testfilename = tgtpath + "test.txt";
    writer.Open(testfilename.c_str());
    writer.Write(filelistTest);
    writer.Close();

    std::list<std::string>::iterator ittest = filelistTest.begin();
         while(ittest != filelistTest.end()){
        		std::string outputPath;
        		std::string outputShortName;
        		std::string outputExt;

        		string tmpname;
        		string tmptxt;
        		string tmpname01;
        		string tmptxt01;
        	FileNameSegmenter::SegmentFullName(*ittest,outputPath,outputShortName,outputExt);
        	FileNameSegmenter::SegmentFullName(outputPath,outputPath,tmpname,tmptxt);
         	FileNameSegmenter::SegmentFullName(outputPath,outputPath,tmpname01,tmptxt01);

        	string newfolder = testFolder + "/"+ tmpname ;
          	string newname =newfolder+"/" +outputShortName + "." + outputExt;
        	if( access(newfolder.c_str(), F_OK) == -1)
        	{
        		printf("create folder %s\n",newfolder.c_str());
        		printf("%d\n", mkdir(newfolder.c_str(), 0777));
        	}

        	 string cmd = string("cp  ") + *ittest + "  " + newname;
        	 printf("%s\n",cmd.c_str());
        	 system(cmd.c_str());
        	 ++ittest;
         }
	return;
}



int main(int argc,char **argv) {
//system("ls");
//	string path = "./data/0/sss/fff/1.jpg";
//	string tt01,tt02;
//	FileNameSegmenter::RemoveFirstSubPath(path,tt01,tt02);
	  char *file_path_getcwd;
	    file_path_getcwd=(char *)malloc(FILEPATH_MAX);
	    getcwd(file_path_getcwd,FILEPATH_MAX);


	    strcat(file_path_getcwd,"/");
	    printf("%s\n",file_path_getcwd);
	 for(int i=0;i<argc;i++)
	        cout<<"Argument "<<i<<" is "<<argv[i]<<endl;
	float number;
	number = atof ( argv[1]  );

    if(number > 1.0 ||number< 0) {
    	printf("train rate must be 0~1!!!\n");
    	return -1;
    }
	cout << "Begin Process 02!!!" << endl; // prints !!!Hello World!!!
	//RandomGenerateAndCopyPics("./data","./",0.0);

	//RandomGenerateOnlyName("./data",file_path_getcwd,number);
	RandomGenerateOnlyName("./data","./",number);
	//RandomGenerateOnlyName("/home/user/PictureDataBases/hand/train_file","./handYolo/",0.8,"jpg");

	//RandomGenerateOnlyName("./data1","./handYolo/",0.8,"jpg");
	cout << "Process is over!!!" << endl;
	return 0;
}
