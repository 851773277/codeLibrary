
// LADlg.h : ͷ�ļ�
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
// CLADlg �Ի���
class CLADlg : public CDialogEx
{
// ����
private:
	TCHAR m_lastDateKey[10];//�����ʼֵ"lastDate"
	TCHAR m_cycleKey[10];//�����ʼֵ"cycle"
	TCHAR m_totalKey[10];//�����ʼֵ"total"

	TCHAR m_curTime[10];
	int m_curYear;
	int m_curMonth;
	int m_curDay;
	vector<int> m_memoryFileNameVec;//����ժҪ�ļ���(�ļ���ΪtaskId)
	vector<string>m_memoryFilePathVec;//����ժҪ�ļ���ȫ·��
	map<int,string>m_taskIdToFilePathMap;
	string m_memoryFileOutPath;

	bool m_clickCount;//�����ж�"�鿴��һ����ť"�Ƿ���"
public:
	CLADlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//��ʼ������
	void getCurTime();//���ó�Ա����m_curTimeΪ��ǰʱ��
	void getFiles( string path);//��ȡ���Ŀ¼�����е�memory�ļ���,��m_memoryFilePathVec
	void SetTaskIdToFilePathMap();//���ó�Ա����m_taskIdToFilePathMapֵ

	//�����ļ�
	void GetMemoryFileNameVec(vector<string>& path);//��ȡ��Ա����m_memoryFileName
	int GetMinFileName();//��m_memoryFileNameVec��ȡ��Сֵ��������Ϊ�µ��ļ���
	string GetNewFilePath(string path);//��ȡ�����ļ�����ȫ·��(��taskId��Ϊ�ļ���)
	int newTaskFile(string fileName);//���������ļ�
	
	//��ѯ����
	void showTask();//��ʾ�����

	//�鿴��������
	void getFilePathFromMemoryFile(string memoryPath,string &filePath);

	//�������
	int getCycleFromMemoryFile(string memoryPath);
	int getTaskIdFromMemoryFile(string memoryPath);
	int getLastDateFromMemoryFile(string memoryPath);
	int UpdateSpecifyMemoryFile(string memoryPath);//�޸�ָ��memory�ļ�����Ϣ

	
	string GetFileName(string filePath);//��һ���ļ�·���л�ȡ�ļ�������ȥ��չ��)
	void GetMemoryFileOutPath();//�ӳ��������ļ��ж�ȡժҪ�ļ������·��
	

	bool isCurDate(int cycle,int lastDate);
	
	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShowAddtaskDlg();//������ʾ��ر��½�����Ի���
	void OnOK();
	CString m_FilePath;
	CString m_memory;
	afx_msg void OnBnClickedQuerytask();//��m_taskNum��Ϊ0�������m_curtask��ʾ�ڶԻ��༭����
	int m_taskNum;
	int m_curtask;
	afx_msg void OnBnClickedNewtask();
	afx_msg void OnBnClickedMarktask();
	afx_msg void OnBnClickedViewtask();
	afx_msg void OnBnClickedSelectpath();
	afx_msg void OnBnClickedNexttask();
};
