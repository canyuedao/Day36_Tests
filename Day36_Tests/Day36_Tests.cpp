// Day36_Tests.cpp : 定义控制台应用程序的入口点。
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
	printf("第%d个窗口卖票\n",iThreadCode+1);
	while(num<2){	
		printf("第%d个窗口卖票：%d   线程ID为：%d\n",iThreadCode+1,++len,threadID[iThreadCode]);	
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
		printf("第%d个线程ID：%d\n",i+1,threadID[i]);
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
//volatile long g_nLoginCount; //登录次数  
////unsigned int __stdcall Fun(void *pPM); //线程函数  
//const int THREAD_NUM = 50; //启动线程数  
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
//		printf("有%d个用户登录后记录结果是%d\n", THREAD_NUM, g_nLoginCount);  
//	}
//   
//    return 0;  
//}  


//经典线程同步互斥问题
//#include "StdAfx.h"
//#include <stdio.h>
//#include <process.h>
//#include <windows.h>
//
//long g_nNum; //全局资源
//unsigned int __stdcall Fun(void *pPM); //线程函数
//const int THREAD_NUM = 50; //子线程个数
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
//		i++;//等子线程接收到参数时主线程可能改变了这个i的值
//	}
//	//保证子线程已全部运行结束
//	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);  
//	CloseHandle(g_hThreadEvent);
//	DeleteCriticalSection(&g_csThreadCode);
//	return 0;
//}
//
//unsigned int __stdcall Fun(void *pPM)
//{
//	//由于创建线程是要一定的开销的，所以新线程并不能第一时间执行到这来
//	int nThreadNum = *(int *)pPM; //子线程获取参数
//	SetEvent(g_hThreadEvent);
//	Sleep(50);//some work should to do
//	EnterCriticalSection(&g_csThreadCode);
//	g_nNum++;  //处理全局资源
//	Sleep(0);//some work should to do
//	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
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
//	printf("互斥量被创建,按任意键触发互斥量\n");
//	getch();
//	ReleaseMutex(hMutex);
//	printf("互斥量被触发\n");
//	CloseHandle(hMutex);
//	while(1);
//}


//经典线程同步互斥问题
//#include "StdAfx.h"
//#include <stdio.h>
//#include <process.h>
//#include <windows.h>
//
//long g_nNum; //全局资源
//unsigned int __stdcall Fun(void *pPM); //线程函数
//const int THREAD_NUM = 10; //子线程个数
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
//		i++;//等子线程接收到参数时主线程可能改变了这个i的值
//	}
//	//保证子线程已全部运行结束
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
//	//由于创建线程是要一定的开销的，所以新线程并不能第一时间执行到这来
//	int nThreadNum = *(int *)pPM; //子线程获取参数
//	ReleaseSemaphore(g_hThreadParameter,1,NULL);
//	Sleep(50);//some work should to do
//	EnterCriticalSection(&g_csThreadCode);
//	g_nNum++;  //处理全局资源
//	Sleep(0);//some work should to do
//	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
//	LeaveCriticalSection(&g_csThreadCode);
//	return 0;
//}