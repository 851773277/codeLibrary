#include<iostream>
#include<Windows.h>
using namespace std;

typedef struct school
{
	char name[20];
	int time;
};

void main()
{
	char *filePath = "C:\\Users\\Administrator\\Desktop\\config.ini";
	int age;
	char keyValue[20] = "";
	char keyValue1[100] = "";
	school s;
	strcpy(s.name,"jishou");
	s.time = 1958;

	for(int i = 0; i < 5; i++)
		WritePrivateProfileString("person","name","xiajun",filePath);//ֻд��һ��

	WritePrivateProfileString("person","name","xiayang",filePath);//name��ֵ�Ի���ֻ��һ��,���Ҽ�ֵ��Ϊ"xiayang"

	for(int i = 0; i < 5; i++)
		WritePrivateProfileSection("student","student1",filePath);//д��һ��student������Ȼ��д��5��studnet1�������ļ���д��һ������

	GetPrivateProfileSection("student",keyValue1,sizeof(keyValue1),filePath);
	cout<<keyValue1<<endl;//ֻ���һ��

	WritePrivateProfileStruct("school","Data",&s,sizeof(s),filePath);

	WritePrivateProfileString("person","age","29",filePath);
	age = GetPrivateProfileInt("person","age",0,filePath);//��ֵ0����ָ����Ŀδ�ҵ�ʱ��Ĭ��ֵ
	cout<<"age="<<age<<endl;

	getchar();
}