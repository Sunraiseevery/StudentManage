// Project3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 定义学生类
class Student {
private:
    string id; // 学号，长度为12位数字字符，唯一标识，不许重复
    string name; // 姓名，长度可以是汉语拼音20位或汉字8位
    string className; // 班级，长度8位，可以带有汉字，例如“软件1141”或“rj1141”
    string gender; // 性别，取值为“男”、“女”或“M”、“F”

public:
    // 构造函数
    Student(const string& id = "", const string& name = "", const string& className = "", const string& gender = "") :
        id(id), name(name), className(className), gender(gender) {}

    // 将学生对象转换为字符串
    string toString() const {
        stringstream ss;
        ss << id << "\t" << name << "\t" << className << "\t" << gender;
        return ss.str();
    }

    // 从字符串中解析学生对象
    static Student fromString(const string& str) {
        stringstream ss(str);
        string id, name, className, gender;
        ss >> id >> name >> className >> gender;
        return Student(id, name, className, gender);
    }

    // get函数
    string getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getClassName() const {
        return className;
    }

    string getGender() const {
        return gender;
    }
};

// 读取学生信息表
vector<Student> readStudentInfo(const string& filename) {
    vector<Student> students;
    ifstream fin(filename);
    if (fin) {
        string line;
        while (getline(fin, line)) {
            students.push_back(Student::fromString(line));
        }
    }
    fin.close();
    return students;
}

void sortByStudentId(vector<Student>& students) {
    sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) { return a.getId() < b.getId(); });
}
// 写入学生信息表
void writeStudentInfo(const string& filename, const vector<Student>& students) {

    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end(),
        [](const Student& a, const Student& b) { return a.getId() < b.getId(); });

    ofstream fout(filename);
    for (const auto& student : students) {
        fout << student.toString() << endl;
    }
    fout.close();
}
void printAllStudents(const vector<Student>& students) {
    for (const auto& student : students) {
        cout << "学号：" << student.getId()
            << "\t姓名：" << student.getName()
            << "\t班级：" << student.getClassName()
            << "\t性别：" << student.getGender() << endl;
    }
}

int main() {
    const string sinfoF = "E:/CppbigWork/stuinfo.txt";
    // 读取学生信息表

    while (true) {
        
        string command;
        cout << "欢迎来到学生管理系统" << endl<<"1,学生管理\n2,课程管理\n3,成绩管理"<<endl;
        cout << "输入对应数字进入系统" << endl;
        command=getchar();
      if(command == "1") {
          vector<Student> students = readStudentInfo(sinfoF);
          cout << "学生信息表记录数：" << students.size() << endl;

          getchar();
          getchar();
      }
        
    }

    vector<Student> students = readStudentInfo(sinfoF);
    cout << "学生信息表记录数：" << students.size() << endl;
  
    printAllStudents(students);
    // 重新写入学生信息表
    writeStudentInfo("E:/CppbigWork/stuinfo.txt", students);

    return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
