

#include "FindFilesInAFolder_Linux.h"
#include <list>
#include <string>

using namespace std;


void FindFilesInAFolder_Linux::RecursivelyFindFiles(const char *path, list<string> &fileList, const char* ext)
{
	listDir(path,fileList,ext);
	return;
}

void  FindFilesInAFolder_Linux::listDir(const char *path,list<string> &fileList,const char* ext)
{ 
        DIR              *pDir ; 
        struct dirent    *ent  ; 
        int               i=0  ; 
        const int len = 4*512;
        char              childpath[len+1];
       string extname = ext;
        pDir=opendir(path); 
        int tt01  = sizeof(childpath);
        memset(childpath,0,sizeof(childpath) );
 
        while((ent=readdir(pDir))!=NULL) 
        { 
 
                if(ent->d_type & DT_DIR) 
                { 
 
                        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0) 
                                continue; 
 
                        sprintf(childpath,"%s/%s",path,ent->d_name); 
                        printf("path:%s\n",childpath);
 
                        listDir(childpath,fileList,ext);
 
                } 
		else
		{
			//cout<<ent->d_name<<endl;
            bool flag = extname.empty();
			if(!extname.empty()){
				string name = ent->d_name;
				int idx = name.rfind(".");
                string filenameext = name.substr(idx+1, name.size() - idx -1);
               if (strcasecmp(filenameext.c_str(), ext) == 0){
            		string tmpName = string(path) + "/"+ent->d_name;
            		fileList.push_back(tmpName);
            		cout<<fileList.size()<<" :   "<<tmpName<<endl;
               }
			}else{
         	   string tmpName = string(path) + "/"+ent->d_name;
         	    fileList.push_back(tmpName);
         	   cout<<fileList.size()<<" :   "<<tmpName<<endl;
            }// if(!extname.empty())
		}
      }//  while((ent=readdir(pDir))!=NULL)
	closedir(pDir);
 
} 
 
/*
int main(int argc,char *argv[]) 
{ 
	const char *sourceFolder = "/home/j00230615/juwenqi/ARM/tools/Hi3516A_SDK_V1.0.1.0/mpp/sample/Windows/data/bmpfaces";
        listDir(sourceFolder); 
        return 0; 
}*/
