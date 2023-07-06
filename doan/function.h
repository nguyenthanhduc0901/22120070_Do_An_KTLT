#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
using namespace std;
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

struct User {
	string username;
	string password;
};
struct UserArray {
	User* user;
	int n;
};
struct StaffInfo {
	string email;
	string name;
	string dateofBirth;
	string sex;
	string id;
	string position;
};
struct StaffInfoArray {
	StaffInfo* staffInfo;
	int n;
};
struct Mark {
	float total=0;
	float final=0;
	float midterm=0;
	float other=0;
};
struct MarkofCourse {
	string courseName;
	Mark mark;
};
struct Student {
	string id;
	string lastName;
	string firstName;
	string sex;
	string dateofBirth;
	string socialid;
	Mark mark;
	MarkofCourse* markofCourse = NULL;
	int n=0;
};
struct Class {
	string name;
	Student* Students = NULL;
	int n = 0;
};
struct SchoolLevel {
	string name;
	Class* classes = NULL;
	int n = 0;
};
struct Course {
	string id = "";
	string name = "";
	string className = "";
	string teacherName = "";
	int numOfCre = 0;
	int maxStu = 0;
	string day = "";
	string time = "";
	Student* students = NULL;
	int n = 0;
};
struct Semester {
	int name = 0;
	string nameYear;
	string startDate;
	string endDate;
	Course* course = NULL;
	int n = 0;
};
struct SchoolYear {
	string name;
	SchoolLevel* schoolLevel = NULL;
	Semester semester[3];
	int n = 0;
};
struct SchoolYearArray {
	SchoolYear* schoolYears = NULL;
	int n = 0;
};
extern UserArray userArray;
extern StaffInfoArray staffInfoArray;
extern SchoolYearArray schoolYearArray;
extern StaffInfo sI;
extern SchoolYear newSchoolYear;
extern Class newStudentsArray;
extern Semester curSemester;
extern User us;
int releftPadding(string text);
bool checkSubstring(const string& mainString, const string& subString);
Student* resizeStudentArray(Student* arr, int size, int newSize);
Class* resizeClassesArray(Class* arr, int size, int newSize);
SchoolYear* resizeSchoolYearArray(SchoolYear* arr, int size, int newSize);
Course* resizeCourseArray(Course* arr, int size, int newSize);
bool isFileEmpty(string& fileName);
Class getClass(string ClassName, string path);
SchoolLevel getSchoolLevel(string SchoolLevelName, string path);
void initSchoolYear(SchoolYear& sY);
string returnNameofSemester(int n);
void getCourse(Semester sm, Course& cou);
void getSemester(Semester& sem);
SchoolYear getSchoolYear(string SchoolYearName);
SchoolYearArray getSchoolYearArray();
SchoolYear createSchoolYear(SchoolYearArray& sYA, string schoolYearName);
void addClasstoSchoolYear(SchoolYear& sY, string schoolLevel, string className);
Student inputStudent();
Semester getCourseforStudent(Student stu);
void addAStudentToSTArray(Class& cl, Student st);
void addStudenttoFile(Student st, string path);
void addStudenttoFileInfo(Student st, string path);
void addStudenttoFileUser(Student st, string path);
void quickInputNewStudent(SchoolYear& schoolYear, Class newStuArr);
void addStudent(SchoolYear& schoolYear, string className, Student st);
Semester createSemester();
void addSemestertoSchoolYear(SchoolYearArray& lsy, Semester sm);
Semester getCurSemester(SchoolYearArray lsy);
Course createCourse();
void addCoursetoSemester(SchoolYearArray& lsy, Semester& sm, Course cs);
void addStudenttoCourse(SchoolYear& sy);
void updateCourse(Semester& sm, int key1, int key2, string change);
void addaStudenttoCourse(Semester& sm, int key, Student stu);
void removeaStudentfromCourse(Semester& sm, int key1, int key2);
void deleteCourse(Semester& sm, int key);
UserArray getUserArray();
StaffInfoArray getStaffInfoArray();
Class getstudentInfoArray();
StaffInfo getCurStaffInfo(StaffInfoArray siA, User us);
Student getCurStudentInfo(Class cl, User us);
int check_login(UserArray usA, User us);
void createScoreBoardFile(Semester sm);
void readScoreBoard(Semester& sm);
void updateScoreBoard(Semester& sm, int key1, int key2, int key3, float change);
void createAllScoreFile(Semester sm);
void readScoreforStudent(Semester sm, Student& st);
void showClasswithScore(SchoolYear sy, string ClassName);
User inputUser(int pos);
User login(UserArray usA);
void printStaffInfo(StaffInfo si, int n);
void changePassword(UserArray& usA, User& us);
void userAccount(StaffInfo si, User& us, UserArray userArray);
void showListofCourse(Semester sm);
void showListofClasses(SchoolYearArray syA, string nameYear);
void showListStudentinCourse(Semester sm, int key);
void showScoreboardinCourse(Semester sm, int key);
void showListStudent(SchoolYearArray syA, string nameYear, string className);
void classOption();
void courseOption();
void mutilTask();
void Staff_menu();
void Student_menu();
void menu();