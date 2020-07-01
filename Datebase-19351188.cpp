#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<map>
#include<utility>
#include<sstream>
#include<vector>
using namespace std;

class couse
{
private:
	string couseName, credits, score;                    //credits和score可通过stringstream转换为int型
public:
	couse() {}
	couse(string a, string b, string c);                 //构造函数
	couse(couse& p);                                     //复制构造函数
	~couse() {}                                          //析构函数
	couse operator=(const couse& c);                     //重载=
	void Printcouse();                                   //输出课程成绩内容
	string pcouseName() { return couseName; }
	string pscore() { return score; }
	string pcredits() { return credits; }
	friend class Student;
};

class Student
{
private:
	string id,name,sex,birthday,school_year,birthpalce;
	couse Scouse[5];
public:
	Student() {};
	Student(Student& p);
	~Student() {}
	void insertCouse(couse c);                                 //插入学生课程成绩等
	void insertinfo(string a,string b,string c,string d,string e,string f);                            //插入学生信息
	void Printcouse();                                         //输出学生的课程成绩
	void Printinfo();                                          //输出学生信息
	string printid() { return id; } 
	int sumscore();                               
	friend bool SortByTotalScore(Student& a, Student& b);      //通过总成绩排序
	bool queryscore(int a, int b, int c);                      //a代表课程序号，定义C Programming Language为0，b和c是查询分数区间
	string pID() { return id; }
	bool queryaveragescore(int a);                             //查询平均分
	bool querycredits(int a);                                  //查询学分
};

couse::couse(couse& p) 
{
	couseName = p.couseName;
	credits = p.credits; 
	score = p.score;
}

couse::couse(string a, string b, string c)
{
	couseName=a;
	credits = b; 
	score=c;
}

couse couse::operator=(const couse& c)
{
	couseName = c.couseName;
	credits = c.credits;
	score = c.score;
	return *this;
}

void couse::Printcouse()                            //输出课程成绩内容
{
	cout << setiosflags(ios_base::left) << setw(24) << couseName;
	cout<< setw(8)<< credits <<score<<endl;
}


Student::Student(Student& p)
{
	id = p.id;
	for(int i=0;i<5;i++)
	Scouse[i]=p.Scouse[i] ;
	name = p.name;
	sex = p.sex; 
	birthday = p.birthday;
	school_year = p.school_year; 
	birthpalce=p.birthday;
}

void Student::Printcouse()                           //输出学生的课程成绩
{
	for (int i = 0; i < 5; i++)
	   Scouse[i].Printcouse();
}


void Student::insertCouse(couse c)                             //插入学生课程成绩等
{
	for (int i = 0; i < 5; i++)
	{
		if ((Scouse[i].pcouseName()).empty())                     //如果课程名字不为空
		{
			//cout << "AAA" << endl;
			Scouse[i] = c;
			break;
		}
	}
}
void Student::insertinfo(string a, string b, string c, string d, string e, string f)   //插入学生信息
{
	id = a; 
	name = b;
	sex = c;
	birthday = d;
	school_year = e;
	birthpalce = f;
}

void Student::Printinfo()                                      //打印学生信息
{
	cout << setiosflags(ios_base::left) << setw(7) << id;
	cout<< setw(10) << name << setw(8) << sex << setw(10) << birthday ;
	cout << setw(13)<<school_year << birthpalce << endl;
}

int Student::sumscore()                                       //返回学生总学分
{
	stringstream is;
	int sum = 0, i,t;
	for (i = 0; i < 5; i++)
	{
		is << Scouse[i].pscore();
		is >> t;                                   //将string类型的数字转换为int型
		sum = sum + t;
	}
	return sum;
}

bool SortByTotalScore(Student& a,  Student& b)
{
	return a.sumscore() < b.sumscore();                      //按总成绩的升序排序,利用函数sort(,,SortByTotalScore)自定义排序方式
}

bool SortByID(Student& a, Student& b)                        ////按ID的升序排序,利用函数sort(,,SortByID)自定义排序方式
{
	return a.pID() < b.pID();
}

bool Student::queryscore(int a, int b, int c)              //a代表课程序号，定义C Programming Language为0，b和c是查询分数区间
{
	stringstream is;
	int t;
	is << Scouse[a].pscore();
	is >> t;
	if ((t > b) && (t < c))
		return 1;
	else 
		return 0;
}

bool Student::queryaveragescore(int a)                    //查询平均分数
{
	int aver = sumscore() / 5;
	if (aver > a)
		return 1;
	else
		return 0;
}

bool Student::querycredits(int a)                             //查询学分
{
	int t,sum=0;
	stringstream is;
	for (int i = 0; i < 5; i++)
	{
		is << Scouse[i].pcredits();                     //将string类型的credits转换为int型
		is >> t;
		sum = sum + t;
	}
	if (sum>= a)
		return 1;
	else
		return 0;
}

void text(Student *student)
{
	ofstream ou;
	ou.open("result,txt");
	vector<Student*>stu;                        //用vector容器存放学生类，方便使用自定义的sort函数
	Student* prev = student;
	int i;
	cout << "2018级选修C语言且成绩小于60分的学生信息如下：" << endl;
	ou << "2018级选修C语言且成绩小于60分的学生信息如下：";
	for (i = 0; i < 6; i++)
	{
		stu.push_back(student);
		if (student->queryscore(0, 0, 60))                      //查找2018级选修C语言且成绩小于60分的学生
		{
			cout << setiosflags(ios_base::left) << setw(7) << "#id";
			cout << setw(10) << "name" << setw(8) << "sex" << setw(10) << "birthday";
			cout << setw(13) << "school_year" << "birthplace" << endl;
			ou<< setiosflags(ios_base::left) << setw(7) << "#id"
			 << setw(10) << "name" << setw(8) << "sex" << setw(10) << "birthday"
			 << setw(13) << "school_year" << "birthplace" << endl;
			student->Printinfo();
			cout << setiosflags(ios_base::left) << setw(24) << "#course";
			cout << setw(8) << "credits" << "score" << endl;
			ou<< setiosflags(ios_base::left) << setw(24) << "#course"
			<< setw(8) << "credits" << "score" << endl;
			student->Printcouse();
			cout << endl;
		}
		student++;
	}
	student =prev;
	cout << endl << "课程平均分大于80的学生信息如下：" << endl;
	ou << "课程平均分大于80的学生信息如下：";
	for (i = 0; i < 6; i++)
	{
		if (student->queryaveragescore(80))
		{
			cout << setiosflags(ios_base::left) << setw(7) << "#id";
			cout << setw(10) << "name" << setw(8) << "sex" << setw(10) << "birthday";
			cout << setw(13) << "school_year" << "birthplace" << endl;
			ou<< setiosflags(ios_base::left) << setw(7) << "#id"
			<< setw(10) << "name" << setw(8) << "sex" << setw(10) << "birthday"
			<< setw(13) << "school_year" << "birthplace" << endl;
			student->Printinfo();
			cout << endl;
		}
		student++;
	}
	student =prev;
	for (i = 0; i < 6; i++)
	{
		cout << "id:" << student->pID();
		if (student->querycredits(20))                   //查询每个学生的学分是否修满14.5学分
			cout << "\t" << "已修满20学分" << endl;
		else
			cout << "\t" << "未修满20学分" << endl;
		student++;
	}
}

int main()
{
	Student student[6];                        //先用学生类存储学生消息
	multimap<string, string>id;
	typedef multimap<string, string>::iterator idIter;
	ifstream infile1, infile2;
	string line, part[9], str[10];
	infile1.open("StudentCourse.txt");                //打开文件StudentCourse.txt
	int pos = 1,i=0,i1=0,i2=0,i3=0,i4=0;
	while (getline(infile1, line))                       //分别存储student的课程信息到学生类
	{
		if ((pos > 1) && (pos < 8))
		{
			istringstream is(line);
			is >> part[0] >> str[0] >> str[1] >> str[2] >> part[2] >> part[3];
			part[1] = str[0] + " " + str[1] + " " + str[2];
			couse c(part[1], part[2], part[3]);
			switch (i)                                                   //通过switch语句按顺序插入信息
			{
			case 0:student[3].insertCouse(c); break;
			case 1:student[4].insertCouse(c); break;
			case 2:student[2].insertCouse(c); break;
			case 3:student[1].insertCouse(c); break;
			case 4:student[5].insertCouse(c); break;
			case 5:student[0].insertCouse(c); break;
			default:cout << "未插入" << endl;
			}
			i++;
		}
		if ((pos) > 7 && (pos < 14))
		{
			istringstream is(line);
			is >> part[0] >> str[0] >> str[1] >> part[2] >> part[3];
			part[1] = str[0] + " " + str[1] ;
			couse c(part[1], part[2], part[3]);
			switch (i1)
			{
			case 0:student[3].insertCouse(c); break;
			case 1:student[4].insertCouse(c); break;
			case 2:student[2].insertCouse(c); break;
			case 3:student[1].insertCouse(c); break;
			case 4:student[5].insertCouse(c); break;
			case 5:student[0].insertCouse(c); break;
			default:cout << "未插入" << endl;
			}
			i1++;
		}
		if ((pos) > 13 && (pos < 20))
		{
			istringstream is(line);
			is >> part[0] >> str[0] >> str[1] >> part[2] >> part[3];
			part[1] = str[0] + " " + str[1];
			couse c(part[1], part[2], part[3]);
			switch (i2)
			{
			case 0:student[3].insertCouse(c); break;
			case 1:student[4].insertCouse(c); break;
			case 2:student[2].insertCouse(c); break;
			case 3:student[1].insertCouse(c); break;
			case 4:student[5].insertCouse(c); break;
			case 5:student[0].insertCouse(c); break;
			default:cout << "未插入" << endl;
			}
			i2++;
		}
		if ((pos) > 19 && (pos < 26))
		{
			istringstream is(line);
			is >> part[0] >> str[0] >> str[1] >> part[2] >> part[3];
			part[1] = str[0] + " " + str[1];
			couse c(part[1], part[2], part[3]);
			switch (i3)
			{
			case 0:student[3].insertCouse(c); break;
			case 1:student[4].insertCouse(c); break;
			case 2:student[2].insertCouse(c); break;
			case 3:student[1].insertCouse(c); break;
			case 4:student[5].insertCouse(c); break;
			case 5:student[0].insertCouse(c); break;
			default:cout << "未插入" << endl;
			}
			i3++;
		}
		if ((pos) > 25)
		{
			istringstream is(line);
			is >> part[0] >> part[1] >> part[2] >> part[3];
			couse c(part[1], part[2], part[3]);
			switch (i4)
			{
			case 0:student[3].insertCouse(c); break;
			case 1:student[4].insertCouse(c); break;
			case 2:student[2].insertCouse(c); break;
			case 3:student[1].insertCouse(c); break;
			case 4:student[5].insertCouse(c); break;
			case 5:student[0].insertCouse(c); break;
			default:cout << "未插入" << endl;
			}
			i4++;
		}
		pos++;
	}
	infile1.close();                               //关闭文件“StudentCourse.txt”
	infile2.open("StudentInfo.txt");                 //打开文件"StudentInfo.txt"
	string id_, name_, sex_, birthday_, school_year_, birthday_1;
	int k = 0,j=0;
	while (getline(infile2, line))       //分别存储学生的消息到student类
	{
		if (j == 0)
		{
			j++;
			continue;
		}
		istringstream ist(line);
		ist >> id_>> name_>>sex_>> birthday_>> school_year_>> birthday_1;
		//cout << id_;
		student[k].insertinfo(id_, name_, sex_, birthday_, school_year_, birthday_1);
		k++;
	}
	infile2.close();                               //存储信息完毕，关闭文件“StudentInfo.txt”
	text(student);                                    //测试函数并打印
	/*pair<idIter, idIter>range = id.equal_range("10917");
	for (idIter iter = range.first; iter != range.second; ++iter)
		cout << iter->second << "";*/
	return 0;
}