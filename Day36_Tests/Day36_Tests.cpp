// Day36_Tests.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <process.h>
#include <Windows.h>

int len=0;
const char cNum=10;	
unsigned int *threadID;
//DWORD *threadID;
HANDLE g_hThreadSemaphore;
CRITICAL_SECTION g_csThreadTickt;

unsigned int WINAPI Thread(void* pV){

	int num=0;
	int iThreadCode=*(int*)pV;
	ReleaseSemaphore(g_hThreadSemaphore,1,NULL);
	Sleep(100);

	EnterCriticalSection(&g_csThreadTickt);
	printf("��%d��������Ʊ\n",iThreadCode+1);
	while(num<2){	
		printf("��%d��������Ʊ��%d   �߳�IDΪ��%d\n",iThreadCode+1,++len,threadID[iThreadCode]);	
		Sleep(200);
		num++;
	}

	Sleep(0);
	LeaveCriticalSection(&g_csThreadTickt);
	_endthreadex(0);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{		
	threadID=new unsigned int[cNum];
	//threadID=new DWORD[cNum];
	InitializeCriticalSection(&g_csThreadTickt);
	g_hThreadSemaphore=CreateSemaphore(NULL,0,1,NULL);
	HANDLE handle[cNum];
	int i=0;
	while(i<cNum){		
		handle[i]=(HANDLE)_beginthreadex(NULL,0,Thread,&i,0,&threadID[i]);
		//handle[i]=(HANDLE)CreateThread(NULL,0,Thread,&i,0,&threadID[i]);
		int j=0;		
		WaitForSingleObject(g_hThreadSemaphore,INFINITE);
		i++;		
	}
	
	WaitForMultipleObjects(cNum,handle,true,INFINITE);	
	
	CloseHandle(g_hThreadSemaphore);
	DeleteCriticalSection(&g_csThreadTickt);
	for(char i=0;i<cNum;i++){
		printf("��%d���߳�ID��%d\n",i+1,threadID[i]);
		CloseHandle(handle[i]);
	}
	delete threadID;
	system("pause");
	return 0;
}


//#include "StdAfx.h"
//#include <stdio.h>  
//#include <process.h>  
//#include <windows.h>  
//volatile long g_nLoginCount; //��¼����  
////unsigned int __stdcall Fun(void *pPM); //�̺߳���  
//const int THREAD_NUM = 50; //�����߳���  
//unsigned int __stdcall ThreadFun(void *pPM)  
//{  
//    Sleep(100); //some work should to do  
//    //g_nLoginCount++;  
//	InterlockedIncrement(&g_nLoginCount);
//    Sleep(50);   
//    return 0;  
//}  
//int main()  
//{  
//	int inum=30;
//	while(inum--){
//		g_nLoginCount = 0;  
//
//		HANDLE  handle[THREAD_NUM];  
//		for (int i = 0; i < THREAD_NUM; i++)  
//			handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, NULL, 0, NULL);  
//
//		WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);   
//		printf("��%d���û���¼���¼�����%d\n", THREAD_NUM, g_nLoginCount);  
//	}
//   
//    return 0;  
//}  


//�����߳�ͬ����������
//#include "StdAfx.h"
//#include <stdio.h>
//#include <process.h>
//#include <windows.h>
//
//long g_nNum; //ȫ����Դ
//unsigned int __stdcall Fun(void *pPM); //�̺߳���
//const int THREAD_NUM = 50; //���̸߳���
//HANDLE g_hThreadEvent;
//CRITICAL_SECTION g_csThreadCode;
//
//int main()
//{
//	g_nNum = 0;
//	HANDLE  handle[THREAD_NUM];
//	g_hThreadEvent=CreateEvent(NULL,false,false,NULL);
//	InitializeCriticalSection(&g_csThreadCode);
//	int i = 0;
//	while (i < THREAD_NUM) 
//	{
//		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
//		WaitForSingleObject(g_hThreadEvent,INFINITE);
//		i++;//�����߳̽��յ�����ʱ���߳̿��ܸı������i��ֵ
//	}
//	//��֤���߳���ȫ�����н���
//	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);  
//	CloseHandle(g_hThreadEvent);
//	DeleteCriticalSection(&g_csThreadCode);
//	return 0;
//}
//
//unsigned int __stdcall Fun(void *pPM)
//{
//	//���ڴ����߳���Ҫһ���Ŀ����ģ��������̲߳����ܵ�һʱ��ִ�е�����
//	int nThreadNum = *(int *)pPM; //���̻߳�ȡ����
//	SetEvent(g_hThreadEvent);
//	Sleep(50);//some work should to do
//	EnterCriticalSection(&g_csThreadCode);
//	g_nNum++;  //����ȫ����Դ
//	Sleep(0);//some work should to do
//	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
//	LeaveCriticalSection(&g_csThreadCode);
//	return 0;
//}


//#include "StdAfx.h"
//#include <stdio.h>
//#include <conio.h>
//#include <windows.h>
//
//LPCWSTR MUTEX=(LPCWSTR)"more_windows";
//
//int main(){
//	HANDLE hMutex=CreateMutex(NULL,true,MUTEX);
//	printf("������������,�����������������\n");
//	getch();
//	ReleaseMutex(hMutex);
//	printf("������������\n");
//	CloseHandle(hMutex);
//	while(1);
//}


//�����߳�ͬ����������
//#include "StdAfx.h"
//#include <stdio.h>
//#include <process.h>
//#include <windows.h>
//
//long g_nNum; //ȫ����Դ
//unsigned int __stdcall Fun(void *pPM); //�̺߳���
//const int THREAD_NUM = 10; //���̸߳���
//HANDLE g_hThreadParameter;
//CRITICAL_SECTION g_csThreadCode;
//
//int main()
//{
//	g_nNum = 0;
//	HANDLE  handle[THREAD_NUM];
//	g_hThreadParameter=CreateSemaphore(NULL,0,1,NULL);
//	InitializeCriticalSection(&g_csThreadCode);
//	int i = 0;
//	while (i < THREAD_NUM) 
//	{
//		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
//		WaitForSingleObject(g_hThreadParameter,INFINITE);
//		i++;//�����߳̽��յ�����ʱ���߳̿��ܸı������i��ֵ
//	}
//	//��֤���߳���ȫ�����н���
//	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);  
//	CloseHandle(g_hThreadParameter);
//	DeleteCriticalSection(&g_csThreadCode);
//	for(int i=0;i<THREAD_NUM;i++){
//		CloseHandle(handle[i]);
//	}
//	return 0;
//}
//
//unsigned int __stdcall Fun(void *pPM)
//{
//	//���ڴ����߳���Ҫһ���Ŀ����ģ��������̲߳����ܵ�һʱ��ִ�е�����
//	int nThreadNum = *(int *)pPM; //���̻߳�ȡ����
//	ReleaseSemaphore(g_hThreadParameter,1,NULL);
//	Sleep(50);//some work should to do
//	EnterCriticalSection(&g_csThreadCode);
//	g_nNum++;  //����ȫ����Դ
//	Sleep(0);//some work should to do
//	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
//	LeaveCriticalSection(&g_csThreadCode);
//	return 0;
//}