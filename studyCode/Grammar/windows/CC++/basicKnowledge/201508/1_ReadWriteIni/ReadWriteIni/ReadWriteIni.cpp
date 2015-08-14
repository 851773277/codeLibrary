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
		WritePrivateProfileString("person","name","xiajun",filePath);//只写入一行

	WritePrivateProfileString("person","name","xiayang",filePath);//name键值对还是只有一行,并且键值变为"xiayang"

	for(int i = 0; i < 5; i++)
		WritePrivateProfileSection("student","student1",filePath);//写入一个student段名，然后写入5行studnet1；是向文件中写入一整个键

	GetPrivateProfileSection("student",keyValue1,sizeof(keyValue1),filePath);
	cout<<keyValue1<<endl;//只输出一行

	WritePrivateProfileStruct("school","Data",&s,sizeof(s),filePath);

	WritePrivateProfileString("person","age","29",filePath);
	age = GetPrivateProfileInt("person","age",0,filePath);//数值0代表指定条目未找到时的默认值
	cout<<"age="<<age<<endl;

	getchar();
}