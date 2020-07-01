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
	string couseName, credits, score;                    //credits��score��ͨ��stringstreamת��Ϊint��
public:
	couse() {}
	couse(string a, string b, string c);                 //���캯��
	couse(couse& p);                                     //���ƹ��캯��
	~couse() {}                                          //��������
	couse operator=(const couse& c);                     //����=
	void Printcouse();                                   //����γ̳ɼ�����
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
	void insertCouse(couse c);                                 //����ѧ���γ̳ɼ���
	void insertinfo(string a,string b,string c,string d,string e,string f);                            //����ѧ����Ϣ
	void Printcouse();                                         //���ѧ���Ŀγ̳ɼ�
	void Printinfo();                                          //���ѧ����Ϣ
	string printid() { return id; } 
	int sumscore();                               
	friend bool SortByTotalScore(Student& a, Student& b);      //ͨ���ܳɼ�����
	bool queryscore(int a, int b, int c);                      //a����γ���ţ�����C Programming LanguageΪ0��b��c�ǲ�ѯ��������
	string pID() { return id; }
	bool queryaveragescore(int a);                             //��ѯƽ����
	bool querycredits(int a);                                  //��ѯѧ��
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

void couse::Printcouse()                            //����γ̳ɼ�����
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

void Student::Printcouse()                           //���ѧ���Ŀγ̳ɼ�
{
	for (int i = 0; i < 5; i++)
	   Scouse[i].Printcouse();
}


void Student::insertCouse(couse c)                             //����ѧ���γ̳ɼ���
{
	for (int i = 0; i < 5; i++)
	{
		if ((Scouse[i].pcouseName()).empty())                     //����γ����ֲ�Ϊ��
		{
			//cout << "AAA" << endl;
			Scouse[i] = c;
			break;
		}
	}
}
void Student::insertinfo(string a, string b, string c, string d, string e, string f)   //����ѧ����Ϣ
{
	id = a; 
	name = b;
	sex = c;
	birthday = d;
	school_year = e;
	birthpalce = f;
}

void Student::Printinfo()                                      //��ӡѧ����Ϣ
{
	cout << setiosflags(ios_base::left) << setw(7) << id;
	cout<< setw(10) << name << setw(8) << sex << setw(10) << birthday ;
	cout << setw(13)<<school_year << birthpalce << endl;
}

int Student::sumscore()                                       //����ѧ����ѧ��
{
	stringstream is;
	int sum = 0, i,t;
	for (i = 0; i < 5; i++)
	{
		is << Scouse[i].pscore();
		is >> t;                                   //��string���͵�����ת��Ϊint��
		sum = sum + t;
	}
	return sum;
}

bool SortByTotalScore(Student& a,  Student& b)
{
	return a.sumscore() < b.sumscore();                      //���ܳɼ�����������,���ú���sort(,,SortByTotalScore)�Զ�������ʽ
}

bool SortByID(Student& a, Student& b)                        ////��ID����������,���ú���sort(,,SortByID)�Զ�������ʽ
{
	return a.pID() < b.pID();
}

bool Student::queryscore(int a, int b, int c)              //a����γ���ţ�����C Programming LanguageΪ0��b��c�ǲ�ѯ��������
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

bool Student::queryaveragescore(int a)                    //��ѯƽ������
{
	int aver = sumscore() / 5;
	if (aver > a)
		return 1;
	else
		return 0;
}

bool Student::querycredits(int a)                             //��ѯѧ��
{
	int t,sum=0;
	stringstream is;
	for (int i = 0; i < 5; i++)
	{
		is << Scouse[i].pcredits();                     //��string���͵�creditsת��Ϊint��
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
	vector<Student*>stu;                        //��vector�������ѧ���࣬����ʹ���Զ����sort����
	Student* prev = student;
	int i;
	cout << "2018��ѡ��C�����ҳɼ�С��60�ֵ�ѧ����Ϣ���£�" << endl;
	ou << "2018��ѡ��C�����ҳɼ�С��60�ֵ�ѧ����Ϣ���£�";
	for (i = 0; i < 6; i++)
	{
		stu.push_back(student);
		if (student->queryscore(0, 0, 60))                      //����2018��ѡ��C�����ҳɼ�С��60�ֵ�ѧ��
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
	cout << endl << "�γ�ƽ���ִ���80��ѧ����Ϣ���£�" << endl;
	ou << "�γ�ƽ���ִ���80��ѧ����Ϣ���£�";
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
		if (student->querycredits(20))                   //��ѯÿ��ѧ����ѧ���Ƿ�����14.5ѧ��
			cout << "\t" << "������20ѧ��" << endl;
		else
			cout << "\t" << "δ����20ѧ��" << endl;
		student++;
	}
}

int main()
{
	Student student[6];                        //����ѧ����洢ѧ����Ϣ
	multimap<string, string>id;
	typedef multimap<string, string>::iterator idIter;
	ifstream infile1, infile2;
	string line, part[9], str[10];
	infile1.open("StudentCourse.txt");                //���ļ�StudentCourse.txt
	int pos = 1,i=0,i1=0,i2=0,i3=0,i4=0;
	while (getline(infile1, line))                       //�ֱ�洢student�Ŀγ���Ϣ��ѧ����
	{
		if ((pos > 1) && (pos < 8))
		{
			istringstream is(line);
			is >> part[0] >> str[0] >> str[1] >> str[2] >> part[2] >> part[3];
			part[1] = str[0] + " " + str[1] + " " + str[2];
			couse c(part[1], part[2], part[3]);
			switch (i)                                                   //ͨ��switch��䰴˳�������Ϣ
			{
			case 0:student[3].insertCouse(c); break;
			case 1:student[4].insertCouse(c); break;
			case 2:student[2].insertCouse(c); break;
			case 3:student[1].insertCouse(c); break;
			case 4:student[5].insertCouse(c); break;
			case 5:student[0].insertCouse(c); break;
			default:cout << "δ����" << endl;
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
			default:cout << "δ����" << endl;
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
			default:cout << "δ����" << endl;
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
			default:cout << "δ����" << endl;
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
			default:cout << "δ����" << endl;
			}
			i4++;
		}
		pos++;
	}
	infile1.close();                               //�ر��ļ���StudentCourse.txt��
	infile2.open("StudentInfo.txt");                 //���ļ�"StudentInfo.txt"
	string id_, name_, sex_, birthday_, school_year_, birthday_1;
	int k = 0,j=0;
	while (getline(infile2, line))       //�ֱ�洢ѧ������Ϣ��student��
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
	infile2.close();                               //�洢��Ϣ��ϣ��ر��ļ���StudentInfo.txt��
	text(student);                                    //���Ժ�������ӡ
	/*pair<idIter, idIter>range = id.equal_range("10917");
	for (idIter iter = range.first; iter != range.second; ++iter)
		cout << iter->second << "";*/
	return 0;
}