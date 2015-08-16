
// LADlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LA.h"
#include "LADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLADlg �Ի���




CLADlg::CLADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLADlg::IDD, pParent)
	, m_FilePath(_T(""))
	, m_memory(_T(""))
	, m_taskNum(0)
	, m_curtask(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	wcscpy(m_lastDateKey,_T("lastDate"));
	wcscpy(m_cycleKey,_T("cycle"));
	wcscpy(m_totalKey,_T("total"));
	m_curYear = 0;
	m_curMonth = 0;
	m_curDay = 0;
	m_clickCount = false;
}

void CLADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH, m_FilePath);
	DDX_Text(pDX, IDC_MEMORY, m_memory);
	DDX_Text(pDX, IDC_TASKNUM, m_taskNum);
	DDX_Text(pDX, IDC_CURTASK, m_curtask);
}

BEGIN_MESSAGE_MAP(CLADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADDTASK, &CLADlg::OnBnClickedShowAddtaskDlg)
	ON_BN_CLICKED(IDC_SHOWTASK, &CLADlg::OnBnClickedQuerytask)
	ON_BN_CLICKED(IDC_NewTask, &CLADlg::OnBnClickedNewtask)
	ON_BN_CLICKED(IDC_MARKTASK, &CLADlg::OnBnClickedMarktask)
	ON_BN_CLICKED(IDC_VIEWTASK, &CLADlg::OnBnClickedViewtask)
	ON_BN_CLICKED(IDC_SELECTPATh, &CLADlg::OnBnClickedSelectpath)
	ON_BN_CLICKED(IDC_NEXTTASK, &CLADlg::OnBnClickedNexttask)
END_MESSAGE_MAP()


// CLADlg ��Ϣ�������

BOOL CLADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	OnBnClickedShowAddtaskDlg();
	showTask();
	GetDlgItem(IDC_TASKNUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_CURTASK)->EnableWindow(FALSE);
	getCurTime();
	GetMemoryFileOutPath();//��ȡ�����ļ�,��ȡժҪ�ļ����·��
	getFiles(m_memoryFileOutPath);//��ȡconfPath�µ�����m_memoryFilePathVec
	SetTaskIdToFilePathMap();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLADlg::OnOK()
{

}

void charToWideChar(const char *pStr, wchar_t *pwStr)
{
	int len = strlen(pStr) + 1;
	int wLen = MultiByteToWideChar(CP_ACP,0,pStr,len,NULL,0);
	MultiByteToWideChar(CP_ACP,0,pStr,len,pwStr,wLen);
}

void WideCharToString(const TCHAR *pwStr,string &str)
{
	int wlen = wcslen(pwStr) + 1;
	int len = WideCharToMultiByte(CP_ACP,0,pwStr,wlen,NULL,0,NULL,NULL);
	char *buf = (char*)malloc(len);
	WideCharToMultiByte(CP_ACP,0,pwStr,wlen,buf,len,NULL,NULL);
	str = buf;
	free(buf);
}
void CLADlg::GetMemoryFileOutPath()
{
	TCHAR wchPath[MAXPATH];
	GetPrivateProfileString(_T("param"),_T("memoryFileOutPath"),_T(""),wchPath,MAXPATH,MEMORYFILEOUTPATH);
	WideCharToString(wchPath,m_memoryFileOutPath);
}
string CLADlg::GetFileName(string path)
{
	int pos1 = path.find_last_of('\\');
	int pos2 = path.find_last_of('\.');
	string fileName = path.substr(pos1 + 1, pos2 - (pos1 +1));
	return fileName;
}

void CLADlg::GetMemoryFileNameVec(vector<string>& path)
{
	vector<string>::iterator it;
	for(it = path.begin(); it != path.end(); it++)
	{
		string fileName = GetFileName(*it);
		int taskId = atoi(fileName.c_str());
		m_memoryFileNameVec.push_back(taskId);
		sort(m_memoryFileNameVec.begin(),m_memoryFileNameVec.end());
	}
}
int CLADlg::GetMinFileName()
{
	if(m_memoryFileNameVec.size() != 0) {
		vector<int>::iterator it= m_memoryFileNameVec.end();
		it --;
		return *it + 1;
	}
	else
		return 1;
	
}
string CLADlg::GetNewFilePath(string path)
{
	string filePath;
	int taskId = GetMinFileName();
	char ch[10];
	itoa(taskId,ch,10);
	string fileName = ch;
	filePath.assign(path).append("\\").append(ch).append(".txt");
	return filePath;
}
void CLADlg::getFiles( string path)
{	//�ļ����
	long   hFile   =   0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if   ((hFile  =  _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{			//�����Ŀ¼,����֮
			//�������,�����б�
			if ((fileinfo.attrib &  _A_SUBDIR))

			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles( p.assign(path).append("\\").append(fileinfo.name) );
			}

			else

			{
				m_memoryFilePathVec.push_back(p.assign(path).append("\\").append(fileinfo.name) );
			}
		}   while(_findnext(hFile, &fileinfo)  == 0);

		_findclose(hFile);
	}
}

void CLADlg::SetTaskIdToFilePathMap()
{
	vector<string>::iterator it;
	for(it = m_memoryFilePathVec.begin(); it != m_memoryFilePathVec.end(); it++)
	{
		int cycle = getCycleFromMemoryFile(*it);
		int lastDate = getLastDateFromMemoryFile(*it);
		if(isCurDate(cycle,lastDate))
		{
			int taskId = getTaskIdFromMemoryFile(*it);
			m_taskIdToFilePathMap[taskId] = *it;
		}
	}
	m_taskNum = m_taskIdToFilePathMap.size();
}
void CLADlg::getCurTime()
{
	CTime time = CTime::GetCurrentTime();
	m_curYear = time.GetYear();
	m_curMonth = time.GetMonth();
	m_curDay = time.GetDay();
	int date = m_curYear*10000 + m_curMonth*100 + m_curDay;
	char chDate[10];
	itoa(date,chDate,10);
	charToWideChar(chDate,m_curTime);
}
int CLADlg::newTaskFile(string filePath)
{
	string fileName = GetFileName(filePath);
	TCHAR wchPath[MAXPATH];//ժҪ�ļ�·��
	TCHAR wchFileName[MAXFILENAME];
	charToWideChar(filePath.c_str(),wchPath);
	charToWideChar(fileName.c_str(),wchFileName);
	int rlt1 = WritePrivateProfileString(_T("param"),_T("taskId"),wchFileName,wchPath);//�ļ�����taskIDֵ
	int rlt2 = WritePrivateProfileString(_T("param"),_T("firstDate"),m_curTime,wchPath);
	int rlt3 = WritePrivateProfileString(_T("param"),m_lastDateKey,m_curTime,wchPath);
	int rlt4 = WritePrivateProfileString(_T("param"),m_cycleKey,_T("1"),wchPath);
	int rlt5 = WritePrivateProfileString(_T("param"),m_totalKey,_T("1"),wchPath);
	int rlt6 = WritePrivateProfileString(_T("param"),_T("filePath"),m_FilePath,wchPath);
	int rlt7 = WritePrivateProfileSection(_T("Memory"),_T(""),wchPath);
	if(rlt1 && rlt2 && rlt3 && rlt4 && rlt5 && rlt6 && rlt7){
		std::ofstream outFile;
		string memoryBuf;
		TCHAR *buf = m_memory.GetBuffer(m_memory.GetLength() + 1);
		WideCharToString(buf,memoryBuf);
		m_memory.ReleaseBuffer();
		outFile.open(wchPath,ios::out | ios::in | ios::app);
		outFile.seekp(0,ios::end);
		outFile<<memoryBuf.c_str();
		return 1;
	}
		
	else 
		return 0;
}

void CLADlg::OnBnClickedShowAddtaskDlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CRect rectLarge;
	static CRect rectSmall;
	CRect rectSeparate;
	CString str;
	if(IsRectEmpty(&rectLarge))
		GetWindowRect(&rectLarge);
	if(IsRectEmpty(&rectSmall))
	{
		GetDlgItem(IDC_SEPARATE1)->GetWindowRect(rectSeparate);
		rectSmall.left = rectLarge.left;
		rectSmall.top = rectLarge.top;
		rectSmall.right = rectSeparate.right;
		rectSmall.bottom = rectSeparate.bottom;
	}
	if(GetDlgItemText(IDC_ADDTASK,str),str == _T("��������"))
	{
		SetDlgItemText(IDC_ADDTASK,_T("ȡ������"));

		SetDlgItemText(IDC_SHOWTASK,_T("�ر�����"));
		GetDlgItem(IDC_SHOWTASK)->EnableWindow(FALSE);
		GetDlgItem(IDC_VIEWTASK)->EnableWindow(FALSE);
		GetDlgItem(IDC_MARKTASK)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEXTTASK)->EnableWindow(FALSE);
		SetWindowPos(NULL,0,0,rectLarge.Width(),rectLarge.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetDlgItemText(IDC_ADDTASK,_T("��������"));
		
		if(m_taskNum) {
			GetDlgItem(IDC_VIEWTASK)->EnableWindow(TRUE);
			GetDlgItem(IDC_MARKTASK)->EnableWindow(TRUE);
			GetDlgItem(IDC_NEXTTASK)->EnableWindow(TRUE);
		}
		GetDlgItem(IDC_SHOWTASK)->EnableWindow(TRUE);

		SetWindowPos(NULL,0,0,rectSmall.Width(),rectLarge.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}
	if(m_taskNum) {
		m_curtask = m_taskIdToFilePathMap.begin()->first;
	}
	UpdateData(FALSE);
}

int  CLADlg::getCycleFromMemoryFile(string memoryPath)
{
	int rlt = -1;
	TCHAR path[MAXPATH];
	charToWideChar(memoryPath.c_str(),path);
	rlt = GetPrivateProfileInt(_T("param"),m_cycleKey,-1,path);
	if(rlt == -1) {
		string log = memoryPath;
		log.append("  cycle���ݶ�ȡʧ��");
		TCHAR wchLog[MAXPATH + 20];
		charToWideChar(log.c_str(),wchLog);
		MessageBox(wchLog);
		return -1;
	} else
		return rlt;
}
int CLADlg::getTaskIdFromMemoryFile(string memoryPath)
{
	int rlt = -1;
	TCHAR path[MAXPATH];
	charToWideChar(memoryPath.c_str(),path);
	rlt = GetPrivateProfileInt(_T("param"),_T("taskId"),-1,path);
	if(rlt == -1) {
		string log = memoryPath;
		log.append("  total���ݶ�ȡʧ��");
		TCHAR wchLog[MAXPATH + 20];
		charToWideChar(log.c_str(),wchLog);
		MessageBox(wchLog);
		return -1;
	} else
		return rlt;
}
int  CLADlg::getLastDateFromMemoryFile(string memoryPath)
{
	int rlt = -1;
	TCHAR path[MAXPATH];
	charToWideChar(memoryPath.c_str(),path);
	rlt = GetPrivateProfileInt(_T("param"),m_lastDateKey,-1,path);
	if(rlt == -1) {
		string log = memoryPath;
		log.append("  lastDate���ݶ�ȡʧ��");
		TCHAR wchLog[MAXPATH + 20];
		charToWideChar(log.c_str(),wchLog);
		MessageBox(wchLog);
		return -1;
	} else
		return rlt;
}
void CLADlg::getFilePathFromMemoryFile(string memoryPath,string &filePath)
{
	int rlt = -1;
	TCHAR path[MAXPATH];
	TCHAR w_filePath[MAXPATH];//���ڱ���memory�ļ��б�����ļ�·��
	charToWideChar(memoryPath.c_str(),path);
	rlt = GetPrivateProfileString(_T("param"),_T("filePath"),_T(""),w_filePath,MAXPATH,path);
	if(!rlt) {
		MessageBox(_T("�ļ�·����ȡʧ��!"));
		return;
	} else {
		WideCharToString(w_filePath,filePath);
	}
}
bool  CLADlg::isCurDate(int cycle,int lastDate){
	int rlt = false;
	int year = lastDate/10000;
	int month = (lastDate - year*10000)/100;
	int day = (lastDate - year*10000 - month*100);
	CTime timeTmp = CTime(year,month,day,0,0,0);
	timeTmp = timeTmp + CTimeSpan(cycle,0,0,0);
	if(	(m_curYear > timeTmp.GetYear()))
		rlt = true;
	else if((m_curYear == timeTmp.GetYear()) &&
		(m_curMonth > timeTmp.GetMonth()))
		rlt = true;
	if(	(m_curYear == timeTmp.GetYear())&&
		(m_curMonth == timeTmp.GetMonth()) &&
		(m_curDay >= timeTmp.GetDay()))
		rlt = true;
	return rlt;
}

int CLADlg::UpdateSpecifyMemoryFile(string memoryPath)
{
	int rlt = 0;
	char cycleStr[10],totalStr[10];
	TCHAR wcCycle[10],wcTotal[10],wcPath[MAXPATH];
	int cycle = getCycleFromMemoryFile(memoryPath) + 1;
	int total = getCycleFromMemoryFile(memoryPath) + 1;
	itoa(cycle,cycleStr,10);
	itoa(total,totalStr,10);
	charToWideChar(cycleStr,wcCycle);
	charToWideChar(totalStr,wcTotal);
	charToWideChar(memoryPath.c_str(),wcPath);
	int rlt1 = WritePrivateProfileString(_T("param"),m_cycleKey,wcCycle,wcPath);
	int rlt2 = WritePrivateProfileString(_T("param"),m_totalKey,wcTotal,wcPath);
	int rlt3 = WritePrivateProfileString(_T("param"),m_lastDateKey,m_curTime,wcPath);
	if(rlt1 && rlt2 && rlt3)
		rlt = 1;
	return rlt;
}

void CLADlg::showTask()
{
	static CRect rectLarge;
	static CRect rectMid;
	static CRect rectSmall;
	CRect rectSeparate1,rectSeparate2;
	CString str;
	if(IsRectEmpty(&rectLarge))
		GetWindowRect(&rectLarge);
	if(IsRectEmpty(&rectMid))
	{
		GetDlgItem(IDC_SEPARATE1)->GetWindowRect(rectSeparate1);
		rectMid.left = rectLarge.left;
		rectMid.top = rectLarge.top;
		rectMid.right = rectSeparate1.right;
		rectMid.bottom = rectSeparate1.bottom;
	}
	if(IsRectEmpty(&rectSmall))
	{
		GetDlgItem(IDC_SEPARATE1)->GetWindowRect(rectSeparate1);
		GetDlgItem(IDC_SEPARATE2)->GetWindowRect(rectSeparate2);
		rectSmall.left = rectLarge.left;
		rectSmall.top = rectLarge.top;
		rectSmall.right = rectSeparate2.right;
		rectSmall.bottom = rectSeparate2.bottom;
	}
	if(GetDlgItemText(IDC_SHOWTASK,str),str == _T("��ʾ����"))
	{
		SetDlgItemText(IDC_SHOWTASK,_T("�ر�����"));
		SetWindowPos(NULL,0,0,rectMid.Width(),rectMid.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetDlgItemText(IDC_SHOWTASK,_T("��ʾ����"));
		SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}
}
void CLADlg::OnBnClickedQuerytask()
{
	/*
	m_taskIdToFilePathMap(������������ID�����Ӧ��memory�ļ�·��ӳ��)�ѳ�ʼ��;
	*/
	CString str;
	GetDlgItemText(IDC_SHOWTASK,str);
	if(str == _T("��ʾ����")) {
		if(m_taskNum) {
			map<int,string>::iterator mapIt;
			mapIt = m_taskIdToFilePathMap.begin();
			m_curtask = mapIt->first;
			showTask();
		} else {
			MessageBox(_T("�������κ�����!"));
		}
	} else {
		showTask();
	}
	UpdateData(FALSE);
	
}


void CLADlg::OnBnClickedNewtask()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	string confPath;
	string newFilePath;
	m_memoryFilePathVec.clear();
	getFiles(m_memoryFileOutPath);
	GetMemoryFileNameVec(m_memoryFilePathVec);//��m_memoryFilePathVec��ȡm_memoryFileNameVec
	newFilePath = GetNewFilePath(m_memoryFileOutPath);
	UpdateData(TRUE);
	if(m_FilePath == "" || m_memory == "")
		MessageBox(_T("�ļ�·����ժҪ���ݲ���Ϊ��!"));
	else if(m_FilePath.GetLength() >= MAXPATH)
		MessageBox(_T("�ļ�·�����ܳ���255���ַ�"));
	else
	{
		if(1 == MessageBox(_T("�Ƿ񴴽��������ļ�?"),_T("�����������ļ�"),MB_OKCANCEL))
		{
			int rlt = newTaskFile(newFilePath);
			if(rlt) {
				m_FilePath = "";
				m_memory = "";
				MessageBox(_T("�ļ������ɹ�!"));
			}
			else
				MessageBox(_T("�ļ�����ʧ��!"));
			UpdateData(FALSE);
		}
	}

}


void CLADlg::OnBnClickedMarktask()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(1 == MessageBox(_T("�����������?"),_T("�������"),MB_OKCANCEL))
	{
		map<int,string>::iterator mapIt;
		for(mapIt = m_taskIdToFilePathMap.begin(); mapIt != m_taskIdToFilePathMap.end(); mapIt++)
		{
			if(mapIt->first == m_curtask)
			{
				int rlt = UpdateSpecifyMemoryFile(mapIt->second);
				if(!rlt) {
					MessageBox(_T("������ʧ��!"));
					return;
				} 
				m_taskIdToFilePathMap.erase(mapIt);
				break;
			}
		}
	}	
	m_taskNum = m_taskIdToFilePathMap.size();
	if(m_taskNum) {
		m_curtask = m_taskIdToFilePathMap.begin()->first;
	} else {
		m_curtask = 0;
		MessageBox(_T("�������������!"));
		GetDlgItem(IDC_MARKTASK)->EnableWindow(FALSE);
		GetDlgItem(IDC_VIEWTASK)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}


void CLADlg::OnBnClickedViewtask()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	string filePath;
	GetDlgItemText(IDC_VIEWTASK,str);
	map<int,string>::iterator it;
	for(it = m_taskIdToFilePathMap.begin(); it != m_taskIdToFilePathMap.end(); it++) {
		if(it->first == m_curtask) {
			/*
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			si.cb   =   sizeof(STARTUPINFO);
			GetStartupInfo(&si);
			si.wShowWindow   =   SW_HIDE;     
			si.dwFlags   =   STARTF_USESHOWWINDOW   |   STARTF_USESTDHANDLES;
			TCHAR cmd [2*MAXPATH];
			string cmdTmp = "c:\\windows\\system32\\cmd.exe /c";
			if(str == _T("�鿴����ժҪ"))
			{
				cmdTmp.append("\"").append(it->second).append("\"");
				SetDlgItemText(IDC_VIEWTASK,_T("�鿴��������"));
			}
			else
			{
				getFilePathFromMemoryFile(it->second,filePath);
				cmdTmp.append("\"").append(filePath).append("\"");
				SetDlgItemText(IDC_VIEWTASK,_T("�鿴����ժҪ"));
			}
			charToWideChar(cmdTmp.c_str(),cmd);
//			int rlt = CreateProcess(NULL, cmd, NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi);
			*/
			/*
			ERROR_FILE_NOT_FOUND = 2; {�ļ�������}
			ERROR_PATH_NOT_FOUND = 3; {·��������}
			ERROR_BAD_FORMAT = 11; {EXE �ļ���Ч}
			SE_ERR_SHARE = 26; {�����������}
			SE_ERR_ASSOCINCOMPLETE = 27; {�ļ�������ȫ����Ч}
			SE_ERR_DDETIMEOUT = 28; {��ʱ}
			SE_ERR_DDEFAIL = 29; {DDE ����ʧ��}
			SE_ERR_DDEBUSY = 30; {���ڴ������� DDE �����������ɸ� DDE ����}
			SE_ERR_NOASSOC = 31; {û���������Ӧ�ó���}
			*/
			string fileName;
			TCHAR wcFileName[MAXPATH];
			if(str == _T("�鿴����ժҪ"))
			{
				fileName.append("\"").append(it->second).append("\"");
				SetDlgItemText(IDC_VIEWTASK,_T("�鿴��������"));
			}
			else
			{
				getFilePathFromMemoryFile(it->second,filePath);
				fileName.append("\"").append(filePath).append("\"");
				SetDlgItemText(IDC_VIEWTASK,_T("�鿴����ժҪ"));
			}
			charToWideChar(fileName.c_str(),wcFileName);
			HANDLE ret = ShellExecute(NULL,_T("open"),wcFileName,NULL,_T(""),SW_SHOWNORMAL);		
			int rlt = (int)ret;
			if(rlt == 0) {
				MessageBox(_T("�ڴ治��!"));
			} else if(rlt == 2) {
				MessageBox(_T("�ļ�������!"));
			} else if(rlt <= 31) {
				MessageBox(_T("δ֪����!"));
			}
		}	
	}
}


void CLADlg::OnBnClickedSelectpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE);
	if(IDOK == dlg.DoModal())
	{
		m_FilePath = dlg.GetPathName();
	}
	UpdateData(FALSE);
}


void CLADlg::OnBnClickedNexttask()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_taskNum <= 1)
		GetDlgItem(IDC_NEXTTASK)->EnableWindow(FALSE);
	else {
		static map<int,string>::iterator mapIt;
		if(m_clickCount) {
			mapIt ++;
			if(mapIt == m_taskIdToFilePathMap.end())
				mapIt = m_taskIdToFilePathMap.begin();
		} else {
			mapIt = m_taskIdToFilePathMap.begin();
			mapIt ++;
			m_clickCount = TRUE;
		}
		m_curtask = mapIt->first;
		SetDlgItemText(IDC_VIEWTASK,_T("�鿴����ժҪ"));
		UpdateData(FALSE);
	}
}
