// residbuilder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define RB_HEADER_W	L"/*<---------------------------RES_BUILDER:begin-----------------------------------*/"
#define RB_TAILOR_W	L"/*----------------------------RES_BUILDER:end------------------------------------->*/"

#define RB_HEADER_A	"/*<---------------------------RES_BUILDER:begin-----------------------------------*/"
#define RB_TAILOR_A	"/*----------------------------RES_BUILDER:end------------------------------------->*/"

#define LEN_HEADER_W (sizeof(RB_HEADER_W)/2-1)
#define LEN_TAILOR_W (sizeof(RB_HEADER_W)/2-1)

#define LEN_HEADER_A (sizeof(RB_HEADER_A)-1)
#define LEN_TAILOR_A (sizeof(RB_HEADER_A)-1)

struct IDMAPRECORD
{
	WCHAR szType[100];
	int	 nID;
	WCHAR szID[200];
	WCHAR szPath[MAX_PATH];
};

struct NAME2IDRECORD
{
	WCHAR szName[100];
	int   nID;
	WCHAR szRemark[300];
};

enum {POS_PREV=0,POS_INPLACE,POS_REMAIN};

void InsertBlockToFileW(FILE *f,const wstring &strOut)
{
	WCHAR szLine[1000];
	vector<wstring> strTailLines;
	int pos=POS_PREV;
	LONG lInsert=-1;
	LONG lPos=ftell(f);
	while(fgetws(szLine,1000,f))
	{
		if(pos==POS_PREV && wcsncmp(szLine,RB_HEADER_W,LEN_HEADER_W)==0)
		{
			pos=POS_INPLACE;
			lInsert=lPos;
		}
		if(pos==POS_INPLACE && wcsncmp(szLine,RB_TAILOR_W,LEN_TAILOR_W)==0)
		{
			pos=POS_REMAIN;
			continue;
		}
		if(pos==POS_REMAIN) strTailLines.push_back(szLine);
		lPos=ftell(f);
	}
	if(lInsert!=-1)
	{
		fseek(f,lInsert,SEEK_SET);
		fwrite(strOut.c_str(),2,strOut.size(),f);
		fwprintf(f,L"\n");
		vector<wstring>::iterator it=strTailLines.begin();
		while(it!=strTailLines.end())
		{
			fwrite(it->c_str(),2,it->size(),f);
			it++;
		}
		_chsize(_fileno(f),ftell(f));//write EOF
	}else
	{
		fwprintf(f,L"\n");
		fwrite(strOut.c_str(),2,strOut.size(),f);
	}
}

void InsertBlockToFileA(FILE *f,const string &strOut)
{
	CHAR szLine[1000];
	vector<string> strTailLines;
	int pos=POS_PREV;
	LONG lInsert=-1;
	LONG lPos=ftell(f);
	while(fgets(szLine,1000,f))
	{
		if(pos==POS_PREV && strncmp(szLine,RB_HEADER_A,LEN_HEADER_A)==0)
		{
			pos=POS_INPLACE;
			lInsert=lPos;
		}
		if(pos==POS_INPLACE && strncmp(szLine,RB_TAILOR_A,LEN_TAILOR_A)==0)
		{
			pos=POS_REMAIN;
			continue;
		}
		if(pos==POS_REMAIN) strTailLines.push_back(szLine);
		lPos=ftell(f);
	}
	if(lInsert!=-1)
	{
		fseek(f,lInsert,SEEK_SET);
		fwrite(strOut.c_str(),1,strOut.size(),f);
		fprintf(f,"\n");
		vector<string>::iterator it=strTailLines.begin();
		while(it!=strTailLines.end())
		{
			fwrite(it->c_str(),1,it->size(),f);
			it++;
		}
		_chsize(_fileno(f),ftell(f));//write EOF
	}else
	{
		fprintf(f,"\n");
		fwrite(strOut.c_str(),1,strOut.size(),f);
	}
}

__time64_t GetLastWriteTime(LPCSTR pszFileName)
{
	__time64_t tmRet=0;
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(pszFileName, &findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		tmRet=*(__time64_t*)&findFileData.ftLastWriteTime;
		FindClose(hFind);
	}
	return tmRet;
}


int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> vecIdMaps;
	string strRes;
	string strHead;
	string strName2ID;
	char   cYes=0;
	int c;
	;
	printf("%s\n",GetCommandLineA());
	while ((c = getopt(argc, argv, _T("i:r:h:n:y:"))) != EOF)
	{
		switch (c)
		{
		case _T('i'):vecIdMaps.push_back(optarg);break;
		case _T('r'):strRes=optarg;break;
		case _T('h'):strHead=optarg;break;
		case _T('n'):strName2ID=optarg;break;
		case _T('y'):cYes=1;optind--;break;
		}
	}

	if(vecIdMaps.size()==0 && strName2ID.length()==0)
	{
		printf("error: not specify valid idmap file\n");
		return 3;
	}

	__time64_t fs1=0;
	__time64_t fs2=0;
	string strTimeStamp;
	FILE *fts=NULL;

	if(vecIdMaps.size())
	{
		//check modify flag
		strTimeStamp=strRes+".ts";
		FILE *fts=fopen(strTimeStamp.c_str(),"r+b");
		if(fts)
		{
			fread(&fs1,1,sizeof(fs1),fts);
			fclose(fts);
		}

		vector<string>::iterator it=vecIdMaps.begin();
		while(it!=vecIdMaps.end())
		{
			fs2+=GetLastWriteTime(it->c_str());
			it++;
		}

		//build xml id map
		if(fs1==fs2 || vecIdMaps.size()==0)
		{
			if(vecIdMaps.size()) printf("idmap files have not been modified.\n");
		}else
		{
			DWORD dwAttr=GetFileAttributesA(strRes.c_str());
			if(dwAttr & FILE_ATTRIBUTE_READONLY)
			{
				if(!cYes)
				{
					printf("error: resource file is readonly. set -y to make sure to do it.\n");
					return 2;
				}
				SetFileAttributesA(strRes.c_str(),dwAttr&~FILE_ATTRIBUTE_READONLY);
			}

			fts=fopen(strTimeStamp.c_str(),"wb");
			if(fts)
			{//record time stamp
				fwrite(&fs2,1,sizeof(fs2),fts);
				fclose(fts);
			}

			vector<IDMAPRECORD> vecIdMapRecord;
			//load xml description of resource to vector
			vector<string>::iterator it=vecIdMaps.begin();
			while(it!=vecIdMaps.end())
			{
				TiXmlDocument xmlDoc;
				if(xmlDoc.LoadFile(it->c_str()))
				{
					TiXmlElement *xmlEle=xmlDoc.RootElement();
					while(xmlEle)
					{
						if(strcmp(xmlEle->Value(),"resid")==0)
						{
							IDMAPRECORD rec={0};
							const char *pszValue;
							pszValue=xmlEle->Attribute("type");
							if(pszValue) MultiByteToWideChar(CP_UTF8,0,pszValue,-1,rec.szType,100);
							pszValue=xmlEle->Attribute("id");
							if(pszValue) rec.nID=atoi(pszValue);
							pszValue=xmlEle->Attribute("id_name");
							if(pszValue) MultiByteToWideChar(CP_UTF8,0,pszValue,-1,rec.szID,200);
							pszValue=xmlEle->Attribute("file");
							if(pszValue) MultiByteToWideChar(CP_UTF8,0,pszValue,-1,rec.szPath,MAX_PATH);

							if(rec.szType[0] && rec.nID && rec.szPath[0])
							{
								if(rec.szID[0]==0) swprintf(rec.szID,L"IDC_%s_%d",rec.szType,rec.nID);
								vecIdMapRecord.push_back(rec);
							}
						}
						xmlEle=xmlEle->NextSiblingElement();
					}
				}
				it++;
			}

			//build output string by wide char
			wstring strOut;
			strOut+=RB_HEADER_W;
			strOut+=L"\n";

			vector<IDMAPRECORD>::iterator it2=vecIdMapRecord.begin();
			while(it2!=vecIdMapRecord.end())
			{
				WCHAR szRec[2000];
				swprintf(szRec,L"DEFINE_%s(%s,\t%d,\t\"%s\")\n",it2->szType,it2->szID,it2->nID,it2->szPath);
				strOut+=szRec;
				it2++;
			}
			strOut+=RB_TAILOR_W;

			//write output string to target res file
			FILE * f=fopen(strRes.c_str(),"r+b");
			if(f)
			{
				BYTE szFlag[2]={0};
				int nReaded=fread(szFlag,1,2,f);
				if(nReaded==2 && szFlag[0]==0xFF && szFlag[1]==0xFE)//detect utf32
				{
					InsertBlockToFileW(f,strOut);
				}else
				{//multibyte
					int nLen=WideCharToMultiByte(CP_ACP,0,strOut.c_str(),strOut.length(),NULL,0,NULL,NULL);
					char *pBuf=new char[nLen+1];
					WideCharToMultiByte(CP_ACP,0,strOut.c_str(),strOut.length(),pBuf,nLen,NULL,NULL);
					pBuf[nLen]=0;
					fseek(f,0,SEEK_SET);
					InsertBlockToFileA(f,pBuf);
					delete []pBuf;
				}
				fclose(f);
			}

			printf("build resouce successed!\n");
		}

	}

	//build resource head
	if(strName2ID.length())
	{
		fs1=0;
		strTimeStamp=strHead+".ts";
		fts=fopen(strTimeStamp.c_str(),"rb");
		if(fts)
		{
			fread(&fs1,sizeof(__time64_t),1,fts);
			fclose(fts);
		}

		fs2=GetLastWriteTime(strName2ID.c_str());

		if(fs1==fs2 || strName2ID.length()==0)
		{
			if(strName2ID.length()) printf("name2id xml descriptor is not changed!\n");
		}else
		{
			DWORD dwAttr=GetFileAttributesA(strHead.c_str());
			if(dwAttr & FILE_ATTRIBUTE_READONLY)
			{
				if(!cYes)
				{
					printf("error: head file is readonly. set -y to make sure to do it.\n");
					return 2;
				}
				SetFileAttributesA(strHead.c_str(),dwAttr&~FILE_ATTRIBUTE_READONLY);
			}

			fts=fopen(strTimeStamp.c_str(),"wb");
			if(fts)
			{//record time stamp
				fwrite(&fs2,1,sizeof(fs2),fts);
				fclose(fts);
			}

			vector<NAME2IDRECORD> vecName2ID;
			//load xml description of resource to vector
			TiXmlDocument xmlDoc;
			if(xmlDoc.LoadFile(strName2ID.c_str()))
			{
				TiXmlElement *xmlEle=xmlDoc.RootElement();
				while(xmlEle)
				{
					if(strcmp(xmlEle->Value(),"name2id")==0)
					{
						NAME2IDRECORD rec={0};
						const char *pszValue;
						pszValue=xmlEle->Attribute("name");
						if(pszValue) MultiByteToWideChar(CP_UTF8,0,pszValue,-1,rec.szName,100);
						pszValue=xmlEle->Attribute("id");
						if(pszValue) rec.nID=atoi(pszValue);
						pszValue=xmlEle->Attribute("remark");
						if(pszValue) MultiByteToWideChar(CP_UTF8,0,pszValue,-1,rec.szRemark,300);

						if(rec.szName[0] && rec.nID) vecName2ID.push_back(rec);
					}
					xmlEle=xmlEle->NextSiblingElement();
				}
			}

			//build output string by wide char
			wstring strOut;
			strOut+=RB_HEADER_W;
			strOut+=L"\n";

			vector<NAME2IDRECORD>::iterator it2=vecName2ID.begin();
			while(it2!=vecName2ID.end())
			{
				WCHAR szRec[2000];
				if(it2->szRemark[0])
					swprintf(szRec,L"#define\t%s\t\t%d	\t//%s\n",it2->szName,it2->nID,it2->szRemark);
				else
					swprintf(szRec,L"#define\t%s\t\t%d\n",it2->szName,it2->nID);
				strOut+=szRec;
				it2++;
			}
			strOut+=RB_TAILOR_W;

			//write output string to target res file
			FILE * f=fopen(strHead.c_str(),"r+b");
			if(f)
			{
				BYTE szFlag[2]={0};
				int nReaded=fread(szFlag,1,2,f);
				if(nReaded==2 && szFlag[0]==0xFF && szFlag[1]==0xFE)//detect utf32
				{
					InsertBlockToFileW(f,strOut);
				}else
				{//multibyte
					int nLen=WideCharToMultiByte(CP_ACP,0,strOut.c_str(),strOut.length(),NULL,0,NULL,NULL);
					char *pBuf=new char[nLen+1];
					WideCharToMultiByte(CP_ACP,0,strOut.c_str(),strOut.length(),pBuf,nLen,NULL,NULL);
					pBuf[nLen]=0;
					fseek(f,0,SEEK_SET);
					InsertBlockToFileA(f,pBuf);
					delete []pBuf;
				}
				fclose(f);
			}

			printf("build header file successed!\n");
		}
	}

	return 0;
}

