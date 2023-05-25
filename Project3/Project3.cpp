// Project3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <regex>

using namespace std;







class Course {
public:
    Course(const string& courseId = "", const string& courseName = "",
        int credit = 0, int hours = 0) :
        m_courseId(courseId), m_courseName(courseName),
        m_credit(credit), m_hours(hours) {}

    const string& getCourseId() const { return m_courseId; }
    const string& getCourseName() const { return m_courseName; }
    int getCredit() const { return m_credit; }
    int getHours() const { return m_hours; }

    void setCourseId(const string& courseId) { m_courseId = courseId; }
    void setCourseName(const string& courseName) { m_courseName = courseName; }
    void setCredit(int credit) { m_credit = credit; }
    void setHours(int hours) { m_hours = hours; }

    // 重载输入和输出运算符
    friend istream& operator>>(istream& in, Course& course);
    friend ostream& operator<<(ostream& out, const Course& course);

private:
    string m_courseId; // 课程号
    string m_courseName; // 课程名称
    int m_credit; // 学分
    int m_hours; // 学时
};

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
bool isMatch(const Student& s, const std::string& keyword) {
    std::regex reg(keyword, std::regex_constants::icase);  // 实例化一个正则表达式对象
    if (std::regex_search(s.getId(), reg) ||  // 在学生对象的任何属性中查找关键字
        std::regex_search(s.getName(), reg) ||
        std::regex_search(s.getGender(), reg) ||
        std::regex_search(s.getClassName(), reg)) {
        return true;  // 匹配成功
    }
    return false;  // 匹配失败
}
void addStudent(vector<Student>& students) {
    // 创建空的 Student 对象
    
    string id;
    string name;
    string className;
    string gender;
    cout << "依次输入学生的 ID、姓名、班级和性别\n未知信息可回车跳过，默认为空" << endl;
    cout << "请输入学生 ID：";
    getline(cin, id);
    cout << "请输入学生姓名：";
    getline(cin, name);
    cout << "请输入学生所在班级：";
    getline(cin, className);
    cout << "请输入学生性别：";
    getline(cin, gender);
    Student s(id,name,className,gender);
    // 将新的学生对象添加到学生信息表中
    students.push_back(s);

    cout << "成功添加学生：" << endl;
    s.toString();
}
int main() {
    const string sinfoF = "E:/CppbigWork/stuinfo.txt";
    // 读取学生信息表

    while (true) {
        
        string command;
        cout << "欢迎来到学生管理系统" << endl<<"1,学生管理\n2,课程管理\n3,成绩管理"<<endl;
        cout << "输入对应数字进入系统" << endl;
       command=_getch();//第三方库调用，直接读取，不同与getchar（）需要enter
       if (command == "1") {
           command = "";
          vector<Student> students = readStudentInfo(sinfoF);
        while(true){  cout << "学生信息表记录数：" << students.size() << endl;
          cout << "1,查询\n2，删除\n3,添加\n4，修改\n5,返回上一级" << endl;
         
          command = _getch();
          if (command == "1") {
              cout << "查询\tA:所有\tB:个别" << endl;
              command = _getch(); cout << command << endl;
              if (command == "A" || command=="a") {
                  printAllStudents(students);
                  continue;}
              else if(command == "B"||command=="b") {
                  cout << "输入相关信息" << endl;
                      string keyword;
                      cin >> keyword;
                      for (const auto& s : students) {
                          if (isMatch(s, keyword)) {  // 调用 isMatch() 函数对学生对象进行匹配
                              std::cout << s.getId() << ", " << s.getClassName() << ", " << s.getGender() << ", " << s.getName() << std::endl;
                          }
                      }
                      _getch();
                      continue;
              }
          }
          if(command =="2"){}
          if (command == "3") { addStudent(students); }
          if (command == "4") {  }
          if (command == "5") { writeStudentInfo(sinfoF, students); break; }
         }
          
      }
        
    }

    vector<Student> students = readStudentInfo(sinfoF);
    cout << "学生信息表记录数：" << students.size() << endl;
  
    printAllStudents(students);
    // 重新写入学生信息表
    writeStudentInfo(sinfoF, students);

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
