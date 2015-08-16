
// LADlg.h : 头文件
//

#pragma once
#include <string>
#include<ctime>
#include <io.h>
#include<vector>
#include <algorithm> 
#include <map>
#include <fstream>
using namespace std;

#define  MAXPATH 256
#define  MAXFILENAME 100
#define MEMORYFILEOUTPATH  _T("..\\conf\\conf.ini")
// CLADlg 对话框
class CLADlg : public CDialogEx
{
// 构造
private:
	TCHAR m_lastDateKey[10];//构造初始值"lastDate"
	TCHAR m_cycleKey[10];//构造初始值"cycle"
	TCHAR m_totalKey[10];//构造初始值"total"

	TCHAR m_curTime[10];
	int m_curYear;
	int m_curMonth;
	int m_curDay;
	vector<int> m_memoryFileNameVec;//所有摘要文件名(文件名为taskId)
	vector<string>m_memoryFilePathVec;//所有摘要文件名全路径
	map<int,string>m_taskIdToFilePathMap;
	string m_memoryFileOutPath;

	bool m_clickCount;//用来判断"查看下一任务按钮"是否点击"
public:
	CLADlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	//初始化设置
	void getCurTime();//设置成员变量m_curTime为当前时间
	void getFiles( string path);//获取输出目录下所有的memory文件名,即m_memoryFilePathVec
	void SetTaskIdToFilePathMap();//设置成员变量m_taskIdToFilePathMap值

	//新增文件
	void GetMemoryFileNameVec(vector<string>& path);//获取成员变量m_memoryFileName
	int GetMinFileName();//从m_memoryFileNameVec获取最小值，用以做为新的文件名
	string GetNewFilePath(string path);//获取新增文件名的全路径(以taskId作为文件名)
	int newTaskFile(string fileName);//新增任务文件
	
	//查询任务
	void showTask();//显示任务框

	//查看具体任务
	void getFilePathFromMemoryFile(string memoryPath,string &filePath);

	//标记任务
	int getCycleFromMemoryFile(string memoryPath);
	int getTaskIdFromMemoryFile(string memoryPath);
	int getLastDateFromMemoryFile(string memoryPath);
	int UpdateSpecifyMemoryFile(string memoryPath);//修改指定memory文件的信息

	
	string GetFileName(string filePath);//从一个文件路径中获取文件名（除去扩展名)
	void GetMemoryFileOutPath();//从程序配置文件中读取摘要文件的输出路径
	

	bool isCurDate(int cycle,int lastDate);
	
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShowAddtaskDlg();//用于显示或关闭新建任务对话框
	void OnOK();
	CString m_FilePath;
	CString m_memory;
	afx_msg void OnBnClickedQuerytask();//若m_taskNum不为0，将其和m_curtask显示在对话编辑框中
	int m_taskNum;
	int m_curtask;
	afx_msg void OnBnClickedNewtask();
	afx_msg void OnBnClickedMarktask();
	afx_msg void OnBnClickedViewtask();
	afx_msg void OnBnClickedSelectpath();
	afx_msg void OnBnClickedNexttask();
};
