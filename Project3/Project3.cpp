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
#include <iomanip>

using namespace std;





class Course {
public:
    Course(const string& courseId = "", const string& courseName = "", float credit = 0.0f, int hours = 0) :
        m_courseId(courseId), m_courseName(courseName), m_credit(credit), m_hours(hours) {}

    const string& getCourseId() const { return m_courseId; }
    const string& getCourseName() const { return m_courseName; }
    float getCredit() const { return m_credit; }
    int getHours() const { return m_hours; }

    bool setCourseId(const string& courseId) {
        if (courseId.empty() || courseId.length() > 10) {
            return false;
        }
        m_courseId = courseId;
        return true;
    }

    bool setCourseName(const string& courseName) {
        m_courseName = courseName;
        return true;
    }

    bool setCredit(float credit) {
        if (credit < 0.0f || credit > 10.0f) {
            return false;
        }
        m_credit = credit;
        return true;
    }

    bool setHours(int hours) {
        if (hours <= 0 || hours > 999) {
            return false;
        }
        m_hours = hours;
        return true;
    }

private:
    string m_courseId;
    string m_courseName;
    float m_credit;
    int m_hours;
};

bool writeToFile(const string& fileName, const vector<Course>& courses) {
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "无法打开文件 \"" << fileName << "\"!" << endl;
        return false;
    }

    for (const auto& course : courses) {
        outFile << course.getCourseId() << ' ' << course.getCourseName() << ' ' << course.getCredit() << ' ' << course.getHours() << endl;
    }

    outFile.close();
    return true;
}

vector<Course> readFromFile(const string& fileName) {
    vector<Course> courses;
    ifstream inFile(fileName);

    if (!inFile) {
        cerr << "无法打开文件 \"" << fileName << "\"!" << endl;
        return courses;
    }

    string courseId;
    string courseName;
    float credit;
    int hours;

    while (inFile >> courseId >> courseName >> credit >> hours) {
        courses.emplace_back(courseId, courseName, credit, hours);
    }

    inFile.close();
    return courses;
}

void showAllCourses(const vector<Course>& courses) {
    cout << "所有课程信息如下：" << endl << endl;
    cout << left << setw(15) << "课程编号" << setw(20) << "课程名称" << setw(10) << "学分" << setw(10) << "学时" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (const auto& course : courses) {
        cout << left << setw(15) << course.getCourseId() << setw(20) << course.getCourseName()
            << setw(10) << course.getCredit() << setw(10) << course.getHours() << endl;
    }
}



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

    string courseFileName = "E:/CppbigWork/courseInfo.txt";
    string sortedCourseFileName = "sortedCourseInfo.txt";

    // 读取课程信息
    vector<Course> courses = readFromFile(courseFileName);

  /*  _getch();

    if (writeToFile(courseFileName, courses)) {
        cout << "课程信息已经成功写入文件 courses.txt。" << endl;
    }
    else {
        cerr << "无法将课程信息写入文件 courses.txt！" << endl;
    }

    showAllCourses(courses);

    return 0;*/
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
       if (command == "2") {
           vector<Course> courses = readFromFile(courseFileName);
           while (true) {
               cout <<"1. 退出程序" << endl
                   << "2. 查询所有课程信息" << endl
                   << "3. 查询单个课程信息" << endl
                   << "4. 修改课程信息" << endl
                   << "5. 添加新的课程" << endl
                   << "6. 删除课程" << endl
                   << "请输入要执行的操作编号：";

               string command;
               cin >> command;

               if (command == "1") {
                   break;
               }
               else if (command == "2") {
                   showAllCourses(courses);
               }
               else if (command == "3") {
                   string courseId;
                   cout << "请输入要查询的课程编号：";
                   cin >> courseId;

                   cout << left << setw(15) << "课程编号" << setw(20) << "课程名称" << setw(10) << "学分" << setw(10) << "学时" << endl;
                   cout << "--------------------------------------------------------" << endl;

                   for (const auto& course : courses) {
                       if (course.getCourseId().find(courseId) != string::npos) {
                           cout << left << setw(15) << course.getCourseId() << setw(20) << course.getCourseName() << setw(10) << course.getCredit() << setw(10) << course.getHours() << endl;
                       }
                   }
               }
               else if (command == "4") {
                   string courseId;
                   cout << "请输入要修改的课程编号：";
                   cin >> courseId;

                   for (auto& course : courses) {
                       if (course.getCourseId() == courseId) {
                           string courseName;
                           float credit;
                           int hours;

                           cout << "请输入新的课程名称：";
                           cin >> courseName;
                           cout << "请输入新的课程学分：";
                           cin >> credit;
                           cout << "请输入新的课程学时：";
                           cin >> hours;

                           course.setCourseName(courseName);
                           course.setCredit(credit);
                           course.setHours(hours);

                           if (writeToFile(courseFileName, courses)) {
                               cout << "课程信息已更新！" << endl;
                           }
                           else {
                               cerr << "无法将课程信息写入文件 " << courseFileName << "！" << endl;
                           }

                           break;
                       }
                   }

                   cout << endl;
               }
               else if (command == "5") {
                   string courseId;
                   string courseName;
                   float credit;
                   int hours;

                   cout << "请输入新课程的编号：";
                   cin >> courseId;
                   cout << "请输入新课程的名称：";
                   cin >> courseName;
                   cout << "请输入新课程的学分：";
                   cin >> credit;
                   cout << "请输入新课程的学时：";
                   cin >> hours;

                   Course newCourse(courseId, courseName, credit, hours);
                   courses.push_back(newCourse);

                   if (writeToFile(courseFileName, courses)) {
                       cout << "新课程已添加！" << endl;
                   }
                   else {
                       cerr << "无法将课程信息写入文件 " << courseFileName << "！" << endl;
                   }

                   cout << endl;
               }
               else if (command == "6") {
                   string courseId;
                   cout << "请输入要删除的课程编号：";
                   cin >> courseId;

                   for (auto it = courses.begin(); it != courses.end(); ++it) {
                       if (it->getCourseId() == courseId) {
                           courses.erase(it);

                           if (writeToFile(courseFileName, courses)) {
                               cout << "课程信息已删除！" << endl;
                           }
                           else {
                               cerr << "无法将课程信息写入文件 " << courseFileName << "！" << endl;
                           }

                           break;
                       }
                   }

                   cout << endl;
               }
               else {
                   cout << "无效的输入！请输入有效的操作编号。" << endl;
               }
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
