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
	float total;
	float final;
	float midterm;
	float other;
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
	MarkofCourse* markofCourse;
	int n;
};
struct Class {
	string name;
	Student* Students=NULL;
	int n=0;
};
struct SchoolLevel {
	string name;
	Class* classes=NULL;
	int n=0;
};
struct Course {
	string id="";
	string name="";
	string className="";
	string teacherName="";
	int numOfCre=0;
	int maxStu=0;
	string day="";
	string time="";
	Student* students=NULL;
	int n=0;
};
struct Semester {
	int name=0;
	string nameYear;
	string startDate;
	string endDate;
	Course* course=NULL;
	int n=0;
};
struct SchoolYear {
	string name;
	SchoolLevel* schoolLevel=NULL;
	Semester semester[3];
	int n=0;
};
struct SchoolYearArray {
	SchoolYear* schoolYears=NULL;
	int n=0;
};

UserArray userArray;
StaffInfoArray staffInfoArray;
SchoolYearArray schoolYearArray;
StaffInfo sI;
SchoolYear newSchoolYear;
Class newStudentsArray;
Semester curSemester;
User us;
int releftPadding(string text);
bool checkSubstring(const string& mainString, const string& subString);
Student* resizeStudentArray(Student* arr, int size, int newSize);
Class* resizeClassesArray(Class* arr, int size, int newSize);
SchoolYear* resizeSchoolYearArray(SchoolYear* arr, int size, int newSize);
Course* resizeCourseArray(Course* arr, int size, int newSize);
bool isFileEmpty(string& fileName);
StaffInfoArray getStaffInfoArray();
Class getstudentInfoArray();
UserArray getUserArray();
StaffInfo getCurStaffInfo(StaffInfoArray siA, User us);
Student getCurStudentInfo(Class cl, User us);
Class getClass(string ClassName, string path);
SchoolLevel getSchoolLevel(string SchoolLevelName, string path);
void initSchoolYear(SchoolYear& sY);
void getCourse(Semester sm, Course &cou);
void getSemester(Semester& sem);
SchoolYear getSchoolYear(string SchoolYearName);
SchoolYearArray getSchoolYearArray();
SchoolYear createSchoolYear(SchoolYearArray &sYA, string schoolYearName);
void addClasstoSchoolYear(SchoolYear& sY, string schoolLevel, string className);
void quickInputNewStudent(SchoolYear& schoolYear, Class newStuArr);
string returnNameofSemester(int n);
Semester createSemester();
void addSemestertoSchoolYear(SchoolYearArray& lsy, Semester sm);
Semester getCurSemester(SchoolYearArray lsy);
Course createCourse();
void addCoursetoSemester(SchoolYearArray& lsy, Semester& sm, Course cs);
void addStudenttoCourse(SchoolYear &sy);
void updateCourse(Semester& sm, int key1, int key2, string change);
void addaStudenttoCourse(Semester& sm, int key, Student stu);
void removeaStudentfromCourse(Semester& sm, int key1, int key2);
void deleteCourse(Semester& sm, int key);
Semester getCourseforStudent(Student stu);
void createScoreBoardFile(Semester sm);
void readScoreBoard(Semester& sm);
Student inputStudent();
int check_login(UserArray usA, User us);
User inputUser(int pos);
User login(UserArray usA);
void printStaffInfo(StaffInfo si, int n);
void changePassword(UserArray& usA, User& us);
void userAccount(StaffInfo si, User &us);
void Staff_menu();
void Student_menu();
void menu();
int main() {
	schoolYearArray = getSchoolYearArray();
	newStudentsArray = getClass("NewStudent", "source\\new_students.csv");
	curSemester = getCurSemester(schoolYearArray);
	//createScoreBoardFile(curSemester);
	//readScoreBoard(curSemester);
	
	menu();
	return 0;
}
int releftPadding(string text) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
	int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;

	int textWidth = text.length();
	int leftPadding = (consoleWidth - textWidth) / 2;
	return leftPadding;
}
bool checkSubstring(const string& mainString, const string& subString) {
	size_t found = mainString.find(subString);
	if (found != string::npos) {
		return true;
	}
	else {
		return false;
	}
}
Student* resizeStudentArray(Student* arr, int size, int newSize) {
	Student* newArr = new Student[newSize];
	for (int i = 0; i < size; i++) {
		*(newArr + i) = *(arr + i);
	}
	for (int i = size; i < newSize; i++) {
		newArr[i].id = "";
		newArr[i].firstName = "";
		newArr[i].lastName = "";
		newArr[i].dateofBirth = "";
		newArr[i].sex = "";
		newArr[i].socialid = "";

	}
	delete[] arr;
	return newArr;
}
Class* resizeClassesArray(Class* arr, int size, int newSize) {
	Class* newArr = new Class[newSize];
	for (int i = 0; i < size; i++) {
		*(newArr + i) = *(arr + i);
	}
	for (int i = size; i < newSize; i++) {
		newArr[i].n = 0;
		newArr[i].name = "";
		newArr[i].Students = NULL;
	}
	delete[] arr;
	return newArr;
}
SchoolYear* resizeSchoolYearArray(SchoolYear* arr, int size, int newSize) {
	SchoolYear* newArr = new SchoolYear[newSize];
	for (int i = 0; i < size; i++) {
		*(newArr + i) = *(arr + i);
	}
	for (int i = size; i < newSize; i++) {
		newArr[i].n = 0;
		newArr[i].name = "";
		newArr[i].schoolLevel = NULL;
	}
	delete[] arr;
	return newArr;
}
Course* resizeCourseArray(Course* arr, int size, int newSize) {
	Course* newArr = new Course[newSize];
	for (int i = 0; i < size; i++) {
		*(newArr + i) = *(arr + i);
	}
	for (int i = size; i < newSize; i++) {
		newArr[i].className = "";
		newArr[i].day = "";
		newArr[i].id = "";
		newArr[i].name = "";
		newArr[i].teacherName = "";
		newArr[i].time = "";
		newArr[i].maxStu = 0;
		newArr[i].numOfCre = 0;
		newArr[i].students= NULL;
		newArr[i].n = 0;
	}
	delete[] arr;
	return newArr;
}
bool isFileEmpty(string& fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		return false;
	}
	file.seekg(0, ios::end);
	streampos fileSize = file.tellg();
	if (fileSize == 0) {
		return true;
	}
	else {
		return false;
	}
}
Class getClass(string ClassName, string path) {
	Class cl;
	cl.name = ClassName;
	ifstream filein(path, ios::in);
	cl.n = 0;
	string line;
	while (getline(filein, line)) cl.n++;
	if (cl.n == 0) return cl;
	filein.close();
	cl.Students = new Student[cl.n];
	int cnt = 0;
	filein.open(path, ios::in);
	while (!filein.eof()) {
		Student st;
		getline(filein, (cl.Students + cnt)->id, ',');
		getline(filein, (cl.Students + cnt)->lastName, ',');
		getline(filein, (cl.Students + cnt)->firstName, ',');
		getline(filein, (cl.Students + cnt)->dateofBirth, ',');
		getline(filein, (cl.Students + cnt)->sex, ',');
		getline(filein, (cl.Students + cnt)->socialid);
		cnt++;
	}
	filein.close();
	return cl;
}
SchoolLevel getSchoolLevel(string SchoolLevelName, string path) {
	SchoolLevel sL;
	sL.name = SchoolLevelName;
	string path1 = path + "\\class.csv";
	ifstream filein(path1, ios::in);
	sL.n = 0;
	string line;
	while (getline(filein, line)) sL.n++;
	if (sL.n == 0) return sL;
	filein.close();
	sL.classes = new Class[sL.n];
	filein.open(path1, ios::in);
	int cnt = 0;
	while (!filein.eof()) {
		getline(filein, (sL.classes + cnt)->name);
		cnt++;
	}
	for (int i = 0; i < sL.n; i++) {
		string path2 = path + "\\" + sL.classes[i].name + ".csv";
		sL.classes[i] = getClass(sL.classes[i].name, path2);
	}
	filein.close();
	return sL;
}
void initSchoolYear(SchoolYear& sY) {
	sY.n = 4;
	sY.schoolLevel = new SchoolLevel[sY.n];
	sY.schoolLevel[0].name = "1st_year";
	sY.schoolLevel[1].name = "2nd_year";
	sY.schoolLevel[2].name = "3rd_year";
	sY.schoolLevel[3].name = "4th_year";
	sY.semester[0].name = 1;
	sY.semester[1].name = 2;
	sY.semester[2].name = 3;
	sY.semester[0].nameYear = sY.name;
	sY.semester[1].nameYear = sY.name;
	sY.semester[2].nameYear = sY.name;
	sY.semester[0].course = NULL;
	sY.semester[1].course = NULL;
	sY.semester[2].course = NULL;
}
void getCourse(Semester sm, Course &cou) {
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\" + cou.id+".csv";
	ifstream filein(path, ios::in);
	if (!filein.is_open()) return;
	string line;
	cou.n = 0;
	while (getline(filein, line)) cou.n++;
	filein.close();
	if (cou.n == 0) return;
	filein.open(path, ios::in);
	cou.students = new Student[cou.n];
	int cnt = 0;
	while (cnt != cou.n) {
		getline(filein, (cou.students + cnt)->id, ',');
		getline(filein, (cou.students + cnt)->lastName, ',');
		getline(filein, (cou.students + cnt)->firstName, ',');
		getline(filein, (cou.students + cnt)->dateofBirth, ',');
		getline(filein, (cou.students + cnt)->sex, ',');
		getline(filein, (cou.students + cnt)->socialid);
		cnt++;
	}
	filein.close();
}
void getSemester(Semester &sem) {
	sem.n = 0;
	string path = "source\\" + sem.nameYear + "\\" + returnNameofSemester(sem.name) + "\\course.csv";
	ifstream filein(path, ios::in);
	if (!filein.is_open()) return;
	string line;
	while (getline(filein, line)) sem.n++;
	filein.close();
	if (sem.n == 0) return;
	filein.open(path, ios::in);
	sem.course = new Course[sem.n];
	int cnt = 0;
	while (cnt!=sem.n) {
		getline(filein, sem.course[cnt].id,',');
		getline(filein, sem.course[cnt].name, ',');
		getline(filein, sem.course[cnt].className, ',');
		getline(filein, sem.course[cnt].teacherName, ',');
		getline(filein, sem.course[cnt].day, ',');
		getline(filein, sem.course[cnt].time, ',');
		filein >> sem.course[cnt].numOfCre;
		filein.seekg(1, 1);
		filein >> sem.course[cnt].maxStu; 
		string line1;
		getline(filein, line1);
		cnt++;
	}
	filein.close();
	for (int i = 0; i < sem.n; i++) {
		getCourse(sem, sem.course[i]);
	}
}
SchoolYear getSchoolYear(string SchoolYearName) {
	SchoolYear sY;
	sY.name = SchoolYearName;
	initSchoolYear(sY);
	for (int i = 0; i < sY.n; i++) {
		string path = "source\\" + SchoolYearName + "\\" + sY.schoolLevel[i].name;
		sY.schoolLevel[i] = getSchoolLevel(sY.schoolLevel[i].name, path);
	}
	string path = "source\\" + SchoolYearName + "\\semester.csv";
	ifstream filein(path, ios::in);
	if (!filein.is_open()) return sY;
	string line;
	int n = 0;
	while (getline(filein, line)) n++;
	if (n == 0) return sY;
	filein.close();
	filein.open(path, ios::in);
	int cnt = 0;
	while (!filein.eof()) {
		string x;
		getline(filein, x, ',');
		getline(filein, sY.semester[cnt].startDate, ',');
		getline(filein, sY.semester[cnt].endDate);
		cnt++;
	}
	for (int i = 0; i < 3; i++) {
		getSemester(sY.semester[i]);
	}
	filein.close();
	return sY;
}
SchoolYearArray getSchoolYearArray() {
	SchoolYearArray lSY={NULL,0};
	ifstream filein("source\\school_year.csv", ios::in);
	string line;
	while (getline(filein, line)) lSY.n++;
	if (lSY.n == 0) return lSY;
	filein.close();
	lSY.schoolYears = new SchoolYear[lSY.n];
	filein.open("source\\school_year.csv", ios::in);
	int cnt = 0;
	while (!filein.eof()) {

		getline(filein, (lSY.schoolYears + cnt)->name);
		cnt++;
	}
	for (int i = 0; i < lSY.n; i++) {
		lSY.schoolYears[i] = getSchoolYear(lSY.schoolYears[i].name);
	}
	filein.close();
	return lSY;
};
SchoolYear createSchoolYear(SchoolYearArray &sYA, string schoolYearName) {
	SchoolYear sY;
	sY.name = schoolYearName;
	initSchoolYear(sY);
	string path = "source\\" + schoolYearName;
	LPCSTR folderName = path.c_str();
	CreateDirectoryA(folderName, NULL);
	for (int i = 0; i < sY.n; i++) {
		path = "source\\" + schoolYearName + "\\" + sY.schoolLevel[i].name;
		folderName = path.c_str();
		CreateDirectoryA(folderName, NULL);
	}
	sY.schoolLevel[0].n = 0;
	sY.schoolLevel[0].classes = NULL;
	sY.schoolLevel[1].classes = sYA.schoolYears[schoolYearArray.n - 1].schoolLevel[0].classes;
	sY.schoolLevel[1].n = sYA.schoolYears[schoolYearArray.n - 1].schoolLevel[0].n;
	sY.schoolLevel[2].classes = sYA.schoolYears[schoolYearArray.n - 1].schoolLevel[1].classes;
	sY.schoolLevel[2].n = sYA.schoolYears[schoolYearArray.n - 1].schoolLevel[1].n;
	sY.schoolLevel[3].classes = sYA.schoolYears[schoolYearArray.n - 1].schoolLevel[2].classes;
	sY.schoolLevel[3].n = sYA.schoolYears[schoolYearArray.n - 1].schoolLevel[2].n;
	string path1 = "source\\" + schoolYearName + "\\" + sY.schoolLevel[0].name + "\\class.csv";
	ofstream fileout1(path1, ios::out);
	fileout1.close();
	for (int i = 1; i < sY.n; i++) {
		path1 = "source\\" + schoolYearName + "\\" + sY.schoolLevel[i].name + "\\class.csv";
		ofstream fileout(path1, ios::out);
		for (int j = 0; j < sY.schoolLevel[i].n; j++) {
			fileout << sY.schoolLevel[i].classes[j].name;
			if (j != sY.schoolLevel[i].n - 1) fileout << endl;
			path = "source\\" + schoolYearName + "\\" + sY.schoolLevel[i].name + "\\" + sY.schoolLevel[i].classes[j].name + ".csv";
			ofstream file(path, ios::out);
			for (int k = 0; k < sY.schoolLevel[i].classes[j].n; k++) {
				file << sY.schoolLevel[i].classes[j].Students[k].id << ","
					<< sY.schoolLevel[i].classes[j].Students[k].lastName << ","
					<< sY.schoolLevel[i].classes[j].Students[k].firstName << ","
					<< sY.schoolLevel[i].classes[j].Students[k].dateofBirth << ","
					<< sY.schoolLevel[i].classes[j].Students[k].sex << ","
					<< sY.schoolLevel[i].classes[j].Students[k].socialid;
				if (k != sY.schoolLevel[i].classes[j].n - 1) file << endl;
			}
			file.close();
		}
		fileout.close();
	}
	sYA.schoolYears = resizeSchoolYearArray(sYA.schoolYears, sYA.n, sYA.n + 1);
	sYA.n++;
	sYA.schoolYears[sYA.n - 1] = sY;
	ofstream file3("source\\school_year.csv", ios::app);
	file3 << endl;
	file3 << schoolYearName;
	file3.close();
	return sY;
}
void addClasstoSchoolYear(SchoolYear& sY, string schoolLevel, string className) {
	Class cl = { className, NULL, 0 };
	ofstream fileout;
	ofstream fileout2;
	string path1 = "source\\" + sY.name + "\\1st_year\\" + className + ".csv";
	fileout2.open(path1, ios::out);
	fileout2.close();
	if (sY.schoolLevel[0].classes == NULL) {
		sY.schoolLevel[0].n = 1;
		sY.schoolLevel[0].classes = new Class[sY.schoolLevel[0].n];
		sY.schoolLevel[0].classes[sY.schoolLevel[0].n - 1] = cl;
		string path = "source\\" + sY.name + "\\" + sY.schoolLevel[0].name + "\\class.csv";
		fileout.open(path, ios::app);
		if (!isFileEmpty(path)) fileout << endl;
		fileout << className;
		fileout.close();
		return;
	}
	sY.schoolLevel[0].classes =resizeClassesArray(sY.schoolLevel[0].classes, sY.schoolLevel[0].n, sY.schoolLevel[0].n + 1);
	sY.schoolLevel[0].n++;
	sY.schoolLevel[0].classes[sY.schoolLevel[0].n - 1] = cl;
	string path = "source\\" + sY.name + "\\" + sY.schoolLevel[0].name + "\\class.csv";
	fileout.open(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
	fileout << className;
	fileout.close();
}
Student inputStudent() {
	Student st;
	cout << setw(45) << ""<<"ID: ";
	getline(cin, st.id);
	cout << setw(45) << "" << "Last name: ";
	getline(cin, st.lastName);
	cout << setw(45) << "" << "First name: ";
	getline(cin, st.firstName);
	cout << setw(45) << "" << "Date of birth: ";
	getline(cin, st.dateofBirth);
	cout << setw(45) << "" << "Sex: ";
	getline(cin, st.sex);
	cout << setw(45) << "" << "Social ID: ";
	getline(cin, st.socialid);
	return st;
}
Semester getCourseforStudent(Student stu) {
	Semester sm;
	sm.course = NULL;
	sm.n = 0;
	for (int i = 0; i < curSemester.n; i++) {
		for (int j = 0; j < curSemester.course[i].n; j++) {
			if (stu.id == curSemester.course[i].students[j].id) {
				if (sm.course == NULL) {
					sm.n = 1;
					sm.course = new Course[sm.n];
					sm.course[sm.n - 1] = curSemester.course[i];
				}
				else {
					sm.course = resizeCourseArray(sm.course, sm.n, sm.n + 1);
					sm.n++;
					sm.course[sm.n - 1] = curSemester.course[i];
				}
			}
		}
	}
	return sm;
}
void addAStudentToSTArray(Class &cl, Student st) {
	if (cl.Students == NULL) {
		cl.n = 1;
		cl.Students = new Student[cl.n];
		cl.Students[cl.n - 1] = st;
		return;
	}
	cl.Students=resizeStudentArray(cl.Students, cl.n, cl.n + 1);
	cl.n++;
	cl.Students[cl.n - 1] = st;
}
void addStudenttoFile(Student st,string path) {
	ofstream fileout(path, ios::app);
	if(!isFileEmpty(path)) fileout << endl;
	fileout << st.id << "," << st.lastName << "," << st.firstName << "," << st.dateofBirth << "," << st.sex << "," << st.socialid;
	fileout.close();
}
void addStudenttoFileInfo(Student st, string path) {
	ofstream fileout(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
	fileout << st.id << "," << st.lastName << "," << st.firstName << "," << st.dateofBirth << "," << st.sex << "," << st.socialid;
	fileout.close();
}
void addStudenttoFileUser(Student st, string path) {
	ofstream fileout(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
	fileout << st.id << "," << 123;
	fileout.close();
}
void quickInputNewStudent(SchoolYear &schoolYear,Class newStuArr) {
	string path;
	for (int i = 0; i < newStuArr.n; i++) {
		for (int j = 0; j < schoolYear.schoolLevel[0].n; j++) {
			if (newStuArr.Students[i].id[4] == '0' && checkSubstring(schoolYear.schoolLevel[0].classes[j].name, "CTT")) {
				addAStudentToSTArray(schoolYear.schoolLevel[0].classes[j], newStuArr.Students[i]);
				path = "source\\" + schoolYear.name + "\\1st_year\\" + schoolYear.schoolLevel[0].classes[j].name + ".csv";
				addStudenttoFile(newStuArr.Students[i], path);
			}
			if (newStuArr.Students[i].id[4] == '5' && checkSubstring(schoolYear.schoolLevel[0].classes[j].name, "APCS")) {
				addAStudentToSTArray(schoolYear.schoolLevel[0].classes[j], newStuArr.Students[i]);
				path = "source\\" + schoolYear.name + "\\1st_year\\" + schoolYear.schoolLevel[0].classes[j].name + ".csv";
				addStudenttoFile(newStuArr.Students[i], path);
			}
			if (newStuArr.Students[i].id[4] == '6' && checkSubstring(schoolYear.schoolLevel[0].classes[j].name, "VP")) {
				addAStudentToSTArray(schoolYear.schoolLevel[0].classes[j], newStuArr.Students[i]);
				path = "source\\" + schoolYear.name + "\\1st_year\\" + schoolYear.schoolLevel[0].classes[j].name + ".csv";
				addStudenttoFile(newStuArr.Students[i], path);
			}
			if (newStuArr.Students[i].id[4] == '7' && checkSubstring(schoolYear.schoolLevel[0].classes[j].name, "CLC")) {
				addAStudentToSTArray(schoolYear.schoolLevel[0].classes[j], newStuArr.Students[i]);
				path = "source\\" + schoolYear.name + "\\1st_year\\" + schoolYear.schoolLevel[0].classes[j].name + ".csv";
				addStudenttoFile(newStuArr.Students[i], path);
			}
		}
	}
}
void addStudent(SchoolYear& schoolYear, string className, Student st) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < schoolYear.schoolLevel[i].n; j++) {
			if (schoolYear.schoolLevel[i].classes[j].name == className) {
				addAStudentToSTArray(schoolYear.schoolLevel[i].classes[j], st);
				string path = "source\\" + schoolYear.name + "\\" + schoolYear.schoolLevel[i].name + "\\"+schoolYear.schoolLevel[i].classes[j].name + ".csv";
				addStudenttoFile(st, path);
				path="source\\student_info.csv";
				addStudenttoFileInfo(st, path);
				path= "source\\user.csv";
				addStudenttoFileUser(st, path);
				return;
			}
		}
	}
}
Semester createSemester() {
	Semester x;
	cout << setw(50) << "" << GREEN << "School year: " << RESET;
	getline(cin, x.nameYear);
	cout << setw(50) << "" << GREEN << "Semester: " << RESET;
	cin >> x.name;
	cin.ignore();
	cout << setw(50) << "" << GREEN << "Start date: " << RESET;
	getline(cin, x.startDate);
	cout << setw(50) << "" << GREEN << "End date: " << RESET;
	getline(cin, x.endDate);
	x.course = NULL;
	x.n = 0;
	return x;
}
string returnNameofSemester(int n) {
	if (n == 1) return "semester1";
	if (n == 2) return "semester2";
	if (n == 3) return "semester3";
	return "";
}
void addSemestertoSchoolYear(SchoolYearArray &lsy,Semester sm) {
	string nameSem = returnNameofSemester(sm.name);
	string path;
	path = "source\\" + sm.nameYear + "\\semester.csv";
	ofstream fileout(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
	fileout << nameSem << "," << sm.startDate << "," << sm.endDate;
	fileout.close();
	path = "source\\" + sm.nameYear+ "\\"  + nameSem;
	LPCSTR folderName = path.c_str();
	CreateDirectoryA(folderName, NULL);
	path = path + "\\course.csv";
	fileout.open(path, ios::out);
	fileout.close();
	for (int i = 0; i < lsy.n; i++) {
		if (lsy.schoolYears[i].name == sm.nameYear) {
			lsy.schoolYears[i].semester[sm.name-1] = sm;
			break;
		}
	}
	curSemester = sm;
}
Semester getCurSemester(SchoolYearArray lsy) {
	string path = "source\\" + lsy.schoolYears[lsy.n - 1].name + "\\semester.csv";
	ifstream filein(path, ios::in);
	if (!filein.is_open()) {
		path = "source\\" + lsy.schoolYears[lsy.n - 2].name + "\\semester.csv";
		filein.open(path, ios::in);
		string line;
		while (!filein.eof()) {
			getline(filein, line);
		}
		Semester sm;
		if (line[8] == '1') sm = lsy.schoolYears[lsy.n - 2].semester[0];
		if (line[8] == '2') sm = lsy.schoolYears[lsy.n - 2].semester[1];
		if (line[8] == '3') sm = lsy.schoolYears[lsy.n - 2].semester[2];
		return sm;
	}
	string line;
	while (!filein.eof()) {
		getline(filein, line);
	}
	Semester sm;
	if (line[8] == '1') sm = lsy.schoolYears[lsy.n - 1].semester[0];
	if (line[8] == '2') sm = lsy.schoolYears[lsy.n - 1].semester[1];
	if (line[8] == '3') sm = lsy.schoolYears[lsy.n - 1].semester[2];
	return sm;
}
Course createCourse() {
	Course cou; 
	cout << setw(45) << "" << GREEN << "ID: " << RESET;
	getline(cin, cou.id);
	cout << setw(45) << "" << GREEN << "Name of course: " << RESET;
	getline(cin, cou.name);
	cout << setw(45) << "" <<GREEN << "Class: " << RESET;
	getline(cin, cou.className); 
	cout << setw(45) << "" << GREEN << "Teacher name: " << RESET;
	getline(cin, cou.teacherName);
	cout << setw(45) << "" << GREEN << "Max student: " << RESET;
	cin >> cou.maxStu;
	cout << setw(45) << "" << GREEN << "Num of credits: " << RESET;
	cin >> cou.numOfCre;
	cin.ignore();
	cout << setw(45) << "" << GREEN << "Day (MON/TUE/WED/THU/FRI/SAT):  " << RESET;
	getline(cin, cou.day);
	cout << setw(45) << "" << GREEN << "Session(S1/S2/S3/S4): " << RESET;
	getline(cin, cou.time);
	cou.students = NULL;
	cou.n = 0;
	return cou;
}
void addCoursetoSemester(SchoolYearArray& lsy,Semester &sm, Course cs) {
	ofstream fileout;
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\course.csv";
	fileout.open(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
	fileout << cs.id << "," << cs.name << "," << cs.className << "," << cs.teacherName << "," << cs.day << "," << cs.time<<"," << cs.numOfCre << "," << cs.maxStu;
	fileout.close();
	path= "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\"+ cs.id+".csv";
	fileout.open(path, ios::out);
	fileout.close();
	int pos = 0;
	if (sm.course == NULL) {
		sm.n = 1;
		sm.course = new Course[sm.n];
		sm.course[sm.n - 1] = cs;
		for (int i = 0; i < lsy.n; i++) {
			if (lsy.schoolYears[i].name == sm.nameYear) {
				lsy.schoolYears[i].semester[sm.name - 1] = sm;
				pos = i;
				break;
			}
		}
	}
	else {
		sm.course = resizeCourseArray(sm.course, sm.n, sm.n + 1);
		sm.n++;
		sm.course[sm.n - 1] = cs;
		for (int i = 0; i < lsy.n; i++) {
			if (lsy.schoolYears[i].name == sm.nameYear) {
				lsy.schoolYears[i].semester[sm.name - 1] = sm;
				pos = i;
				break;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < lsy.schoolYears[pos].schoolLevel[i].n; j++) {
			if (cs.className == lsy.schoolYears[pos].schoolLevel[i].classes[j].name) {
				sm.course[sm.n - 1].n = lsy.schoolYears[pos].schoolLevel[i].classes[j].n;
				sm.course[sm.n - 1].students = lsy.schoolYears[pos].schoolLevel[i].classes[j].Students;
				ofstream fileout(path, ios::out);
				for (int k = 0; k < sm.course[sm.n - 1].n; k++) {
					fileout << sm.course[sm.n - 1].students[k].id << ","
						<< sm.course[sm.n - 1].students[k].lastName << ","
						<< sm.course[sm.n - 1].students[k].firstName << ","
						<< sm.course[sm.n - 1].students[k].dateofBirth << ","
						<< sm.course[sm.n - 1].students[k].sex << ","
						<< sm.course[sm.n - 1].students[k].socialid;
					if (k != sm.course[sm.n - 1].n - 1) fileout << endl;
				}
				fileout.close();
			}
		}
	}

}
void addStudenttoCourse(SchoolYear &sy) {
	for (int m = 0; m < sy.n; m++) {
		for (int i = 0; i < sy.schoolLevel[m].n; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < sy.semester[j].n; k++) {
					if (sy.schoolLevel[m].classes[i].name == sy.semester[j].course[k].className) {
						sy.semester[j].course[k].n = sy.schoolLevel[m].classes[i].n;
						sy.semester[j].course[k].students = sy.schoolLevel[m].classes[i].Students;
					}
				}
			}
		}
	}
	ofstream fileout;
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < sy.semester[j].n; k++) {
			string path = "source\\" + sy.name + "\\" + returnNameofSemester(sy.semester[j].name) + "\\" + sy.semester[j].course[k].id + ".csv";
			if (!isFileEmpty(path)) {
				break;
			}
			fileout.open(path, ios::out);
				for (int i = 0; i < sy.semester[j].course[k].n; i++) {
					fileout << sy.semester[j].course[k].students[i].id << ","
						<< sy.semester[j].course[k].students[i].lastName << ","
						<< sy.semester[j].course[k].students[i].firstName << ","
						<< sy.semester[j].course[k].students[i].dateofBirth << ","
						<< sy.semester[j].course[k].students[i].sex << ","
						<< sy.semester[j].course[k].students[i].socialid;
					if (i != sy.semester[j].course[k].n - 1) fileout << endl;
				}
			
			fileout.close();
		}
	}
}
void updateCourse(Semester &sm,int key1, int key2, string change) {
	if (key2 == 1) sm.course[key1 - 1].className = change;
	if (key2 == 2) sm.course[key1 - 1].teacherName = change;
	if (key2 == 3) sm.course[key1 - 1].numOfCre = stoi(change);
	if (key2 == 4) sm.course[key1 - 1].maxStu = stoi(change);
	if (key2 == 5) sm.course[key1 - 1].day = change;
	if (key2 == 6) sm.course[key1 - 1].time = change;
	ofstream fileout;
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\course.csv";
	fileout.open(path, ios::out);
	if (!isFileEmpty(path)) fileout << endl;
	for (int i = 0; i < sm.n-1; i++) {
		fileout << sm.course[i].id << "," << sm.course[i].name << "," << sm.course[i].className << "," << sm.course[i].teacherName << "," <<sm.course[i].day << "," << sm.course[i].time <<"," << sm.course[i].numOfCre << "," << sm.course[i].maxStu << endl;
	}
	fileout << sm.course[sm.n - 1].id << "," << sm.course[sm.n - 1].name << "," << sm.course[sm.n - 1].className << "," << sm.course[sm.n - 1].teacherName << "," <<sm.course[sm.n - 1].day << "," << sm.course[sm.n - 1].time<<"," << sm.course[sm.n - 1].numOfCre << "," << sm.course[sm.n - 1].maxStu;
	fileout.close();
}
void addaStudenttoCourse(Semester &sm,int key, Student stu) {
	ofstream fileout;
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\" + sm.course[key - 1].id + ".csv";
	fileout.open(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
	fileout << stu.id << "," << stu.lastName << "," << stu.firstName << "," << stu.dateofBirth << "," << stu.sex << "," << stu.socialid;
	fileout.close();
	if (sm.course[key-1].students == NULL) {
		sm.course[key - 1].n = 1;
		sm.course[key - 1].students = new Student[sm.course[key - 1].n];
		sm.course[key - 1].students[sm.course[key - 1].n - 1] = stu;
		return;
	}
	sm.course[key - 1].students = resizeStudentArray(sm.course[key - 1].students, sm.course[key - 1].n, sm.course[key - 1].n + 1);
	sm.course[key - 1].n++;
	sm.course[key - 1].students[sm.course[key - 1].n - 1] = stu;
}
void removeaStudentfromCourse(Semester& sm, int key1, int key2) {
	for (int i = key2-1; i < sm.course[key1-1].n-1; i++) {
		sm.course[key1-1].students[i] = sm.course[key1-1].students[i + 1];
	}
	sm.course[key1-1].n--;
	string  path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\" + sm.course[key1- 1].id + ".csv";
	ofstream fileout(path, ios::out);
	for (int i = 0; i < sm.course[key1 - 1].n; i++) {
		fileout << sm.course[key1 - 1].students[i].id << "," << sm.course[key1 - 1].students[i].lastName << "," << sm.course[key1 - 1].students[i].firstName << "," << sm.course[key1 - 1].students[i].dateofBirth << "," << sm.course[key1 - 1].students[i].sex << "," << sm.course[key1 - 1].students[i].socialid;
		if (i != sm.course[key1 - 1].n - 1) fileout << endl;
	}
	fileout.close();
}
void deleteCourse(Semester& sm, int key){
	for (int i = key - 1; i < sm.n-1; i++) {
		sm.course[i] = sm.course[i + 1];
	}
	sm.n--;
	string  path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\course.csv";
	ofstream fileout(path, ios::out);
	for (int i = 0; i < sm.n; i++) {
		fileout << sm.course[i].id << "," << sm.course[i].name << "," << sm.course[i].className << "," << sm.course[i].teacherName << "," << sm.course[i].day << "," << sm.course[i].time<<"," << sm.course[i].numOfCre << "," << sm.course[i].maxStu;
		if (i != sm.n - 1) fileout << endl;
	}
	fileout.close();
}
UserArray getUserArray() {
	UserArray usA={NULL, 0};
	ifstream filein("source\\user.csv", ios_base::in);
	string line;
	while (getline(filein, line)) usA.n++;
	filein.clear();
	filein.seekg(0, ios::beg);
	usA.user = new User[usA.n];
	int cnt = 0;
	while (!filein.eof()) {
		getline(filein, (usA.user+cnt)->username, ',');
		getline(filein, (usA.user + cnt)->password);
		cnt++;
	}
	filein.close();
	return usA;
}
StaffInfoArray getStaffInfoArray() {
	StaffInfoArray siA = { NULL, 0 };
	ifstream filein("source\\staff_info.csv", ios_base::in);
	string line;
	while (getline(filein, line)) siA.n++;
	filein.clear();
	filein.seekg(0, ios::beg);
	siA.staffInfo = new StaffInfo[siA.n];
	int cnt = 0;
	while (!filein.eof()) {
		getline(filein, (siA.staffInfo + cnt)->email, ',');
		getline(filein, (siA.staffInfo + cnt)->name, ',');
		getline(filein, (siA.staffInfo + cnt)->dateofBirth, ',');
		getline(filein, (siA.staffInfo + cnt)->sex, ',');
		getline(filein, (siA.staffInfo + cnt)->id, ',');
		getline(filein, (siA.staffInfo + cnt)->position);
		cnt++;
	}
	filein.close();
	return siA;
}
Class getstudentInfoArray() {
	Class cl;
	cl.name = "StudentInfoArray";
	cl.n = 0;
	cl.Students = NULL;
	ifstream filein("source\\student_info.csv", ios_base::in);
	string line;
	while (getline(filein, line)) cl.n++;
	filein.clear();
	filein.seekg(0, ios::beg);
	cl.Students = new Student[cl.n];
	int cnt = 0;
	while (!filein.eof()) {
		getline(filein, (cl.Students + cnt)->id, ',');
		getline(filein, (cl.Students + cnt)->lastName, ',');
		getline(filein, (cl.Students + cnt)->firstName, ',');
		getline(filein, (cl.Students + cnt)->dateofBirth, ',');
		getline(filein, (cl.Students + cnt)->sex, ',');
		getline(filein, (cl.Students + cnt)->socialid);
		cnt++;
	}
	filein.close();
	return cl;
}
StaffInfo getCurStaffInfo(StaffInfoArray siA, User us) {
	StaffInfo sI;
	for (int i = 0; i < siA.n; i++) {
		if (siA.staffInfo[i].email == us.username) {
			sI = siA.staffInfo[i];
			break;
		}
	}
	return sI;
}
Student getCurStudentInfo(Class cl, User us) {
	Student stu;
	for (int i = 0; i < cl.n; i++) {
		if (cl.Students[i].id == us.username) {
			stu = cl.Students[i];
			break;
		}
	}
	return stu;
}
int check_login(UserArray usA, User us) {
	for (int i = 0; i < usA.n; i++) {
		if (us.username == usA.user[i].username) {
			if (us.password == usA.user[i].password) return 1;
			else return -1;
		}
	}
	return 0;
}
void createScoreBoardFile(Semester sm) {
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard";
	LPCSTR folderName = path.c_str();
	CreateDirectoryA(folderName, NULL);
	ofstream fileout;
	for (int i = 0; i < sm.n; i++) {
		path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard\\" + sm.course[i].id + ".csv";
		fileout.open(path, ios::out);
		for (int j = 0; j < sm.course[i].n-1; j++) {
			fileout << sm.course[i].students[j].id << "," << sm.course[i].students[j].lastName << " " << sm.course[i].students[j].firstName << endl;
		}
		fileout << sm.course[i].students[sm.course[i].n - 1].id << "," << sm.course[i].students[sm.course[i].n - 1].lastName << " " << sm.course[i].students[sm.course[i].n - 1].firstName;
		fileout.close();
	}
}
void readScoreBoard(Semester &sm) {
	string path;
	ifstream filein;
	for (int i = 0; i < sm.n; i++) {
		path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard\\" + sm.course[i].id + ".csv";
		filein.open(path, ios::in);
		if (!filein.is_open()) continue;
		int cnt = 0;
		while (!filein.eof()) {
			string temp;
			getline(filein,temp, ',');
			getline(filein, temp, ',');
			filein >> sm.course[i].students[cnt].mark.total;
			filein.seekg(1, 1);
			filein >> sm.course[i].students[cnt].mark.final;
			filein.seekg(1, 1);
			filein >> sm.course[i].students[cnt].mark.midterm;
			filein.seekg(1, 1);
			filein >> sm.course[i].students[cnt].mark.other;
			getline(filein, temp);
			cnt++;
		}
		cnt = 0;
		filein.close();
	}
}
void updateScoreBoard(Semester& sm, int key1, int key2,int key3, float change) {
	if (key3 == 1) sm.course[key1 - 1].students[key2-1].mark.total = change;
	if (key3 == 2) sm.course[key1 - 1].students[key2 - 1].mark.final = change;
	if (key3 == 3) sm.course[key1 - 1].students[key2 - 1].mark.midterm = change;
	if (key3 == 4) sm.course[key1 - 1].students[key2 - 1].mark.other = change;
	ofstream fileout;
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard\\"+sm.course[key1-1].id+".csv";
	fileout.open(path, ios::out);
	if (!isFileEmpty(path)) fileout << endl;
	for (int i = 0; i < sm.course[key1-1].n-1; i++) {
		fileout << sm.course[key1 - 1].students[i].id << "," << sm.course[key1 - 1].students[i].lastName << " " << sm.course[key1 - 1].students[i].firstName << "," << sm.course[key1 - 1].students[i].mark.total << "," << sm.course[key1 - 1].students[i].mark.final << "," << sm.course[key1 - 1].students[i].mark.midterm << "," << sm.course[key1 - 1].students[i].mark.other << endl;
	}
	int i = sm.course[key1 - 1].n - 1;
	fileout << sm.course[key1 - 1].students[i].id << "," << sm.course[key1 - 1].students[i].lastName << " " << sm.course[key1 - 1].students[i].firstName << "," << sm.course[key1 - 1].students[i].mark.total << "," << sm.course[key1 - 1].students[i].mark.final << "," << sm.course[key1 - 1].students[i].mark.midterm << "," << sm.course[key1 - 1].students[i].mark.other;
	fileout.close();
}
User inputUser(int pos) {
	User us;
	cout << "\n\n\n\n\n\n\n\n\n\n\n";
	cout << setw(pos+7) << "" << "LOGIN" << endl;
	cout << setw(pos-5) << "" << "/-------------<>-------------\\" << endl;
	cout << setw(pos-3) << "" << "Username: ";
	getline(cin, us.username);
	cout << setw(pos-3) << "" << "Password: ";
	getline(cin, us.password);
	return us;
}
User login(UserArray usA) {
	User us;
	int k;
	int pos = 57;
	do {
		system("cls");
		us = inputUser(pos);
		k = check_login(usA, us);
		cout << endl;
		if (k == 1) cout<<GREEN << setw(pos + 5 ) << "" << "Success! ";
		if (k == -1)cout<<RED << setw(pos +2) << "" << "Wrong password! ";
		if (k == 0) cout<<RED << setw(pos +2) << "" << "Wrong username! ";
		cout << RESET;
		int x=_getch();
		pos = 57;
	} while (k == -1 || k == 0);
	return us;
}
void printStaffInfo(StaffInfo si, int n) {
	cout <<setw(10) <<"" << left << setw(20) << si.name;
	cout << left << setw(20) << si.dateofBirth;
	cout << left << setw(10) << si.sex;
	cout <<left << setw(15) << si.position;
	cout <<left << setw(30) << si.email;
	cout << left << setw(15) << si.id;
	cout << right << setw(15);
	cout << endl;
}
void changePassword(UserArray& usA, User& us) {
	string curPass;
	string newPass;
	string newPass2;
	while (true) {
		cout << setw(50)<<""<<"Input current password: ";
		getline(cin, curPass);
		if (curPass != us.password) {
			cout << RED;
			cout << setw(50) << ""<< "Wrong password!" << endl;
			cout << RESET;
			int x = _getch();
		}
		else break;
	}
	while (true) {
		cout << setw(50) << "" << "Input new password: ";
		getline(cin, newPass);
		cout << setw(50) << "" << "Input again: ";
		getline(cin, newPass2);
		if (newPass == curPass) {
			cout << setw(50) << ""<<RED << "Same old password!"<<RESET << endl;
		}
		else if (newPass != newPass2) {
			cout << setw(50) << ""<<RED << "Not match!"<<RESET << endl;
		}
		else break;
	}
	cout << setw(50) << ""<<GREEN << "Success!"<<RESET;
	us.password = newPass;
	for (int i = 0; i < usA.n; i++) {
		if (usA.user[i].username == us.username) {
			usA.user[i].password = us.password;
			break;
		}
	}
	fstream fileout("source\\user.csv", ios_base::out);
	for (int i = 0; i < usA.n - 1; i++) {
		fileout << usA.user[i].username << "," << usA.user[i].password << endl;
	}
	fileout << usA.user[usA.n - 1].username << "," << usA.user[usA.n - 1].password;
	fileout.close();
}
void userAccount(StaffInfo si, User &us) {
	char menuItems[3][30] = { "View my profile", "Change password", "Exit" };
	int selectedItem = 0;
	char key;
	int pos = 61;
	do {
		system("cls");
		cout << "Call us : (028) 3835 4266" << endl;
		cout << "E-mail : info@fit.hcmus.edu.vn" << endl;
		cout << "\n\n\n\n\n";
		cout << setw(pos - 4) << "" << "USER ACCOUNT" << endl;
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		for (int i = 0; i < 3; i++) {
			if (i == selectedItem) {
				int temp = 0;
				if (i == 0) temp = 9;
				if (i == 1) temp = 9;
				if (i == 2) temp = 20; 
				cout << setw(pos - 8) << "|   " << "" << " " << GREEN << menuItems[i] << RESET << setw(temp) << "|" << endl;
				if (i != 2) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
			else {
				int temp = 0;
				if (i == 0) temp = 10;
				if (i == 1) temp = 10;
				if (i == 2) temp = 21;
				cout << setw(pos - 8) << "|   " << "" << menuItems[i] << setw(temp) << "|" << endl;
				if (i != 2) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
		}
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		key = _getch();
		switch (key) {
		case 72:
			selectedItem = (selectedItem - 1 + 3) % 3;
			break;
		case 80: // Arrow key - Down
			selectedItem = (selectedItem + 1) % 3;
			break;
		case 13:
			if (selectedItem == 0) {
				cout << YELLOW;
				cout << setw(10) << "" << left << setw(20) << "Full name";
				cout << left << setw(20) << "Date of birth";
				cout << left << setw(10) << "Sex";
				cout << left << setw(15) << "Position";
				cout << left << setw(30) << "Email";
				cout << left << setw(15) << "ID";
				cout << RESET;
				cout << endl;
				printStaffInfo(si, pos);
			}
			if (selectedItem == 1) {
				changePassword(userArray, us);
			}
			if (selectedItem == 2) return;
			int x = _getch();
			break;
		}

	} while (key != 27);
}
void showListofCourse(Semester sm) {
	cout << YELLOW;
	cout <<setw(10)<<""<< left << setw(5) << "No";
	cout << left << setw(12) << "ID";
	cout << left << setw(22) << "Name";
	cout << left << setw(12) << "Class";
	cout << left << setw(25) << "Teacher";
	cout << left << setw(10) << "Day";
	cout << left << setw(10) << "Session";
	cout << left << setw(7) << "Max";
	cout << left << setw(7) << "Credit";
	cout << right << setw(22);
	cout << RESET;
	cout << endl;
	for (int i = 0; i < sm.n; i++) {
		cout << setw(10) << "" << left << setw(5) << i+1;
		cout << left << setw(12) << sm.course[i].id;
		cout << left << setw(22) << sm.course[i].name;
		cout << left << setw(12) << sm.course[i].className;
		cout << left << setw(25) << sm.course[i].teacherName;
		cout << left << setw(10) << sm.course[i].day;
		cout << left << setw(10) << sm.course[i].time;
		cout << left << setw(7) << sm.course[i].maxStu;
		cout << left << setw(7) << sm.course[i].numOfCre;
		cout << right << setw(22);
		cout << endl;
	}
}
void showListofClasses(SchoolYearArray syA, string nameYear) {
	for (int i = 0 ; i < syA.n; i++) {
		if (syA.schoolYears[i].name == nameYear) {
			for (int j = 0; j < 4; j++) {
				cout <<setw(20)<<""<<YELLOW << syA.schoolYears[i].schoolLevel[j].name <<RESET;
			}
			cout << endl;
			cout << setw(20) << "" << "--<->--" << setw(21) << "" << "--<->--" << setw(21) << "" << "--<->--" << setw(21) << "" << "--<->--";
			cout << endl;
			for (int j = 0; j < 7; j++) {
				cout << setw(20) << "";
				for (int k = 0; k < 4; k++) {
					if (j < syA.schoolYears[i].schoolLevel[k].n)
						cout << left << setw(28) << syA.schoolYears[i].schoolLevel[k].classes[j].name;
					else cout << left << setw(28) << " ";
				}
				cout << endl;
			}
			cout << right << setw(28);
			return;
		}
	}
}
void showListStudentinCourse(Semester sm, int key) {
	cout << YELLOW;
	cout << setw(20) << "" << left << setw(10) << "No";
	cout << left << setw(15) << "ID";
	cout << left << setw(20) << "Full name";
	cout << left << setw(20) << "Date of birth";
	cout << left << setw(15) << "Sex";
	cout << left << setw(22) << "Social ID";
	cout << right << setw(22);
	cout << RESET;
	cout << endl;
	cout << setw(20) << "" << "--<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->-----";
	cout << endl;
	if (sm.course == NULL) return;
	if (sm.course[key - 1].n == 0) return;
	if (sm.course[key - 1].students == NULL) return;
	for (int i = 0; i < sm.course[key-1].n; i++) {
		cout << setw(20) << "" << left << setw(10) << i + 1;
		cout << left << setw(15) << sm.course[key-1].students[i].id;
		cout << left << setw(20) << sm.course[key-1].students[i].lastName + " " + sm.course[key-1].students[i].firstName;
		cout << left << setw(20) << sm.course[key-1].students[i].dateofBirth;
		cout << left << setw(15) << sm.course[key-1].students[i].sex;
		cout << left << setw(22) << sm.course[key-1].students[i].socialid;
		cout << right << setw(22);
		cout << endl;
	}
}
void showScoreboardinCourse(Semester sm, int key) {
	cout << YELLOW;
	cout << setw(20) << "" << left << setw(10) << "No";
	cout << left << setw(15) << "ID";
	cout << left << setw(22) << "Full name";
	cout << left << setw(15) << "Total mark";
	cout << left << setw(15) << "Final mark";
	cout << left << setw(15) << "Midterm mark";
	cout << left << setw(15) << "Other mark";
	cout << right << setw(15);
	cout << RESET;
	cout << endl;
	cout << setw(20) << "" << "--<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->--";
	cout << endl;
	if (sm.course == NULL) return;
	if (sm.course[key - 1].n == 0) return;
	if (sm.course[key - 1].students == NULL) return;
	for (int i = 0; i < sm.course[key - 1].n; i++) {
		cout << setw(20) << "" << left << setw(10) << i + 1;
		cout << left << setw(15) << sm.course[key - 1].students[i].id;
		cout << left << setw(26) << sm.course[key - 1].students[i].lastName + " " + sm.course[key - 1].students[i].firstName;
		cout << left << setw(15) << sm.course[key - 1].students[i].mark.total;
		cout << left << setw(15) << sm.course[key - 1].students[i].mark.final;
		cout << left << setw(15) << sm.course[key - 1].students[i].mark.midterm;
		cout << left << setw(15) << sm.course[key - 1].students[i].mark.other;
		cout << right << setw(15);
		cout << endl;
	}
}
void showListStudent(SchoolYearArray syA, string nameYear, string className) {
	for (int i = 0; i < syA.n; i++) {
		if (syA.schoolYears[i].name == nameYear) {
			cout << YELLOW;
			cout << setw(20) << "" << left << setw(10) << "No";
			cout << left << setw(15) << "ID";
			cout << left << setw(20) << "Full name";
			cout << left << setw(20) << "Date of birth";
			cout << left << setw(15) << "Sex";
			cout << left << setw(22) << "Social ID";
			cout << right << setw(22);
			cout << RESET;
			cout << endl;
			cout << setw(20) << "" << "--<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->-----";
			cout << endl;
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < syA.schoolYears[i].n; k++) {
					if (syA.schoolYears[i].schoolLevel[j].classes[k].name == className) {
						for (int f = 0; f < syA.schoolYears[i].schoolLevel[j].classes[k].n; f++) {
							cout << setw(20) << "" << left << setw(10) << f + 1;
							cout << left << setw(15) << syA.schoolYears[i].schoolLevel[j].classes[k].Students[f].id;
							cout << left << setw(20) << syA.schoolYears[i].schoolLevel[j].classes[k].Students[f].lastName + " " + syA.schoolYears[i].schoolLevel[j].classes[k].Students[f].firstName;
							cout << left << setw(20) << syA.schoolYears[i].schoolLevel[j].classes[k].Students[f].dateofBirth;
							cout << left << setw(15) << syA.schoolYears[i].schoolLevel[j].classes[k].Students[f].sex;
							cout << left << setw(22) << syA.schoolYears[i].schoolLevel[j].classes[k].Students[f].socialid;
							cout << right << setw(22);
							cout << endl;
						}
					}
				}
			}
			return;
		}
	}
	cout << RED << "NULL!" << RESET;
}
void classOption() {
	char menuItems[5][30] = { "Create class", "View list of classes","Input Student","Quick input" ,"Exit"};
	int selectedItem = 0;
	char key;
	int pos = 61;
	string schoolYearName;
	string className;
	string schoolLevel;
	int n = 0;
	do {
		system("cls");
		cout << "Call us : (028) 3835 4266" << endl;
		cout << "E-mail : info@fit.hcmus.edu.vn" << endl;
		cout << "\n\n\n\n\n";
		cout << setw(pos - 3) << "" <<GREEN<< "CLASS OPTION"<<RESET << endl;
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		for (int i = 0; i < 5; i++) {
			if (i == selectedItem) {
				int temp = 0;
				if (i == 0) temp = 12;
				if (i == 1) temp = 4;
				if (i == 2) temp = 11;
				if (i == 3) temp = 13;
				if (i == 4) temp = 20;
				cout << setw(pos - 8) << "|   " << "" << " " << GREEN << menuItems[i] << RESET << setw(temp) << "|" << endl;
				if (i != 4) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
			else {
				int temp = 0;
				if (i == 0) temp = 13;
				if (i == 1) temp = 5;
				if (i == 2) temp = 12;
				if (i == 3) temp = 14;
				if (i == 4) temp = 21;
				cout << setw(pos - 8) << "|   " << "" << menuItems[i] << setw(temp) << "|" << endl;
				if (i != 4) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
		}
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		key = _getch();
		switch (key) {
		case 72:
			selectedItem = (selectedItem - 1 + 5) % 5;
			break;
		case 80: // Arrow key - Down
			selectedItem = (selectedItem + 1) % 5;
			break;
		case 13:
			if (selectedItem == 0) {
				cout << setw(45) << ""<<GREEN << "Input school year: "<<RESET;
				getline(cin, schoolYearName);
				cout << setw(45) << "" << GREEN << "Input school level: " << RESET;
				getline(cin, schoolLevel);
				cout << setw(45)<<"" << GREEN << "Input number of classes: " << RESET;
				cin >> n;
				cin.ignore();
				for (int i = 0; i < schoolYearArray.n; i++) {
					if (schoolYearArray.schoolYears[i].name == schoolYearName) {
						for (int j = 0; j < n; j++) {
							cout << setw(45) << "" << GREEN << "Input class name(CTT/CLC/VP/APCS): "<<RESET;
							getline(cin, className);
							addClasstoSchoolYear(schoolYearArray.schoolYears[i], schoolLevel, className);
						}
						break;
					}
				}
				cout << setw(45) << "" << GREEN << "Success!" << RESET;
			}
			if (selectedItem == 1) {
				cout <<setw(38)<<"" << GREEN << "Input school year you want to view classes: "<<RESET;
				getline(cin, schoolYearName);
				cout << endl;
				showListofClasses(schoolYearArray, schoolYearName);
				while (true) {
					cout << setw(38) << "" << GREEN << "Input class you want to view(press 0 to stop): " << RESET;
					getline(cin, className);
					if (className == "0") break;
					cout << endl;
					showListStudent(schoolYearArray, schoolYearName, className);
				}
			}
			if (selectedItem == 2) {
				cout << setw(45) << "" << GREEN << "Input school year: " << RESET;
				getline(cin, schoolYearName);
				cout << setw(45) << "" << GREEN << "Input class: " << RESET;
				getline(cin, className);
				cout << setw(45) << "" << GREEN << "Input number of student: " << RESET;
				cin >> n;
				cin.ignore();
				for (int i = 0; i < schoolYearArray.n; i++) {
					if (schoolYearArray.schoolYears[i].name == schoolYearName) {
						for (int j = 0; j < n; j++) {
							cout << setw(45) << "" << GREEN << "Input student " << j + 1 << RESET << endl;;
							Student st = inputStudent();
							addStudent(schoolYearArray.schoolYears[i], className, st);
						}
						break;
					}
				}
				cout << setw(45) << "" << GREEN << "Success!" << RESET;
			}
			if (selectedItem == 3) {
				quickInputNewStudent(schoolYearArray.schoolYears[schoolYearArray.n - 1], newStudentsArray);
				cout << setw(50) << "" << GREEN << "Done!" << RESET;
			}
			if (selectedItem == 4) return;
			int x = _getch();
			break;
		}

	} while (key != 27);
}
void courseOption() {
	char menuItems[7][30] = {"View course" ,"Create course","Update course","Delete course","Export course","View scoreboard" ,"Exit"};
	int selectedItem = 0;
	char key;
	int pos = 61;
	Course cs;
	string schoolYearName;
	string className;
	string schoolLevel;
	string temp;
	int n = 0;
	int key1, key2, key3;
	float diem = 0;
	do {
		system("cls");
		cout << "Call us : (028) 3835 4266" << endl;
		cout << "E-mail : info@fit.hcmus.edu.vn" << endl;
		cout << setw(pos - 3) << "" <<GREEN<< "COURSE OPTION" <<RESET<< endl << endl;
		showListofCourse(curSemester);
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		for (int i = 0; i < 7; i++) {
			if (i == selectedItem) {
				int temp = 0;
				if (i == 0) temp = 13;
				if (i == 1) temp = 11;
				if (i == 2) temp = 11;
				if (i == 3) temp = 11;
				if (i == 4) temp = 11;
				if (i == 5) temp = 9;
				if (i == 6) temp = 20;
				cout << setw(pos - 8) << "|   " << "" << " " << GREEN << menuItems[i] << RESET << setw(temp) << "|" << endl;
				if (i != 6) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
			else {
				int temp = 0;
				if (i == 0) temp = 14;
				if (i == 1) temp = 12;
				if (i == 2) temp = 12;
				if (i == 3) temp = 12;
				if (i == 4) temp = 12;
				if (i == 5) temp = 10;
				if (i == 6) temp = 21;
				cout << setw(pos - 8) << "|   " << "" << menuItems[i] << setw(temp) << "|" << endl;
				if (i != 6) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
		}
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		key = _getch();
		switch (key) {
		case 72:
			selectedItem = (selectedItem - 1 + 7) % 7;
			break;
		case 80: // Arrow key - Down
			selectedItem = (selectedItem + 1) % 7;
			break;
		case 13:
			if (selectedItem == 0) {
				cout << setw(45) << "" << GREEN << "Choose a course you want to view: " << RESET;
				cin >> key1;
				showListStudentinCourse(curSemester, key1);
				cout << setw(45) << "" << GREEN << "1. Add a student to this course" << RESET << endl;
				cout << setw(45) << "" << GREEN << "2. Delete a student from this course" << RESET << endl;
				cout << setw(45) << "" << GREEN << "3. Next" << RESET << endl;
				cout << setw(45) << "" << GREEN << "Your choose: " << RESET;
				cin >> key2;
				cin.ignore();
				if (key2 == 1) {
					addaStudenttoCourse(curSemester, key1, inputStudent());
					cout << setw(45) << "" << GREEN << "Done!" << RESET;
				}
				if (key2 == 2) {
					cout << setw(45) << "" << GREEN << "Enter a student you want to remove: " << RESET;
					cin >> key3;
					cin.ignore();
					removeaStudentfromCourse(curSemester, key1, key3);
					cout << setw(45) << "" << GREEN << "Done!" << RESET;
				}
				else {
					break;
				}
			}
			if (selectedItem == 1) {
				cout << setw(45) << "" << GREEN << "Input number of courses: " << RESET;
				cin >> n;
				cin.ignore();
				for (int i = 0; i < n; i++) {
					cout << setw(45) << "" << GREEN << "Input course "<<i+1 << RESET<<endl;
					cs = createCourse();
					addCoursetoSemester(schoolYearArray, curSemester, cs);
				}
			}
			if (selectedItem == 2) {
				cout << setw(45) << "" << GREEN << "Enter a course you want to change: " << RESET;
				cin >> key1;
				cout << GREEN;
				cout << setw(45) << "" << "1. Class" << endl;
				cout << setw(45) << "" << "2. Teacher" << endl;
				cout << setw(45) << "" << "3. Credit" << endl;
				cout << setw(45) << "" << "4. Max student" << endl;
				cout << setw(45) << "" << "5. Day" << endl;
				cout << setw(45) << "" << "6. Session" << endl;
				cout << RESET;
				cout << setw(45) << "" << GREEN << "Enter a your select: " << RESET;
				cin >> key2;
				cin.ignore();
				cout << setw(45) << "" << GREEN << "You want to change to: " << RESET;
				getline(cin, temp);
				updateCourse(curSemester, key1, key2, temp);
			}
			if (selectedItem == 3) {
				cout << setw(45) << "" << GREEN << "Choose a course you want to delete: " << RESET;
				cin >> key1;
				deleteCourse(curSemester, key1);
				cout << setw(45) << "" << GREEN << "Done!" << RESET;
			}
			if (selectedItem == 4) {
				createScoreBoardFile(curSemester);
				cout << setw(45) << "" << GREEN << "Done!" << RESET;
			}
			if (selectedItem == 5) {
				readScoreBoard(curSemester);
				cout << setw(45) << "" << GREEN << "Choose a course you want to view: " << RESET;
				cin >> key1;
					cout << setw(20) << "" << YELLOW << "Course: " << RESET << curSemester.course[key1 - 1].name << endl;
					cout << setw(20) << "" << YELLOW << "Teacher: " << RESET << curSemester.course[key1 - 1].teacherName << endl;
					showScoreboardinCourse(curSemester, key1);
					cout << setw(45) << "" << GREEN << "Choose a student you want to update(0 to exit): " << RESET;
					cin >> key2;
					if (key2 != 0) {
						cout << setw(48) << "" << GREEN << "1. Total mark" << RESET << endl;
						cout << setw(48) << "" << GREEN << "2. Final mark" << RESET << endl;
						cout << setw(48) << "" << GREEN << "3. Midterm mark" << RESET << endl;
						cout << setw(48) << "" << GREEN << "4. Other mark" << RESET << endl;
						cout << setw(45) << "" << GREEN << "Your choose: " << RESET;
						cin >> key3;
						cout << setw(45) << "" << GREEN << "Your want to change to: " << RESET;
						cin >> diem;
						updateScoreBoard(curSemester, key1, key2, key3, diem);
						cout << setw(45) << "" << GREEN << "Done!" << RESET;
					}
			}
			if (selectedItem == 6) return;
			int x = _getch();
			break;
		}
	} while (key != 27);
}
void mutilTask() {
	char menuItems[5][30] = { "Create school year","Create semester", "Class option", "Course option" ,"Exit"};
	int selectedItem = 0;
	char key;
	int pos = 61;
	string schoolYearName;
	do {
		system("cls");
		cout << "Call us : (028) 3835 4266" << endl;
		cout << "E-mail : info@fit.hcmus.edu.vn" << endl;
		cout << "\n\n\n\n\n";
		cout << setw(pos-7) << "" << GREEN<<"MULTI-TASKING OPTION" <<RESET<< endl;
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		for (int i = 0; i < 5; i++) {
			if (i == selectedItem) {
				int temp = 0;
				if (i == 0) temp = 6;
				if (i == 1) temp = 9;
				if (i == 2) temp = 12;
				if (i == 3) temp = 11;
				if (i == 4) temp = 20;
				cout << setw(pos - 8) << "|   " << "" << " " << GREEN << menuItems[i] << RESET << setw(temp) << "|" << endl;
				if (i!=4) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
			else {
				int temp = 0;
				if (i == 0) temp = 7;
				if (i == 1) temp = 10;
				if (i == 2) temp = 13;
				if (i == 3) temp = 12;
				if (i == 4) temp = 21;
				cout << setw(pos - 8) << "|   " << "" << menuItems[i] << setw(temp) << "|" << endl;
				if (i!=4) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
		}
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		key = _getch();
		switch (key) {
		case 72:
			selectedItem = (selectedItem - 1 + 5) % 5;
			break;
		case 80: // Arrow key - Down
			selectedItem = (selectedItem + 1) % 5;
			break;
		case 13:
			if (selectedItem == 0) {
				cout << setw(50) << ""<<GREEN << "Input school year name: "<<RESET;
				getline(cin, schoolYearName);
				createSchoolYear(schoolYearArray, schoolYearName);
				cout << setw(50)<< "" << GREEN << "Succcess!" << RESET << endl;
			}
			if (selectedItem == 1) {
				Semester sm = createSemester();
				addSemestertoSchoolYear(schoolYearArray, sm);
				cout << setw(50) << "" << GREEN << "Succcess!" << RESET << endl;
				curSemester = sm;
			}
			if (selectedItem == 2)
				classOption();
			if (selectedItem == 3)
				courseOption();
			if (selectedItem == 4) return;
			//int x = _getch();
			break;
		}

	} while (key != 27);
}
void Staff_menu() {
	StaffInfoArray siA = getStaffInfoArray();
	StaffInfo si = getCurStaffInfo(siA,us);
	char menuItems[3][30] = { "User Account", "Multi-tasking option", "Log out" };
	int selectedItem = 0;
	char key;
	int pos = 61;
	do {
		system("cls");
		cout << "Call us : (028) 3835 4266" << endl;
		cout << "E-mail : info@fit.hcmus.edu.vn" << endl;
		cout << "\n\n";
		cout << setw(pos - 2) << "" <<GREEN<< "HOME PAGE"<<RESET << endl<<endl;
		cout << setw(pos - 12) << "" <<"Semester-"<< curSemester.name<<"/" << curSemester.nameYear << endl;
		if (si.sex == "Nam") cout << setw(pos - 12) << "" << "Staff: " << "Mr." << si.name << endl;
		else cout << setw(pos - 12) << "" << "Staff: " << "Ms." << si.name << endl;
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		for (int i = 0; i < 3; i++) {
			if (i == selectedItem) {
				int temp = 0;
				if (i == 0) temp = 12;
				if (i == 1) temp = 4;
				if (i == 2) temp = 17;
				cout << setw(pos-8) << "|   " << "" << " " << GREEN << menuItems[i] << RESET << setw(temp) << "|" << endl;
				if (i != 2) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
			else {
				int temp = 0;
				if (i == 0) temp = 13;
				if (i == 1) temp = 5;
				if (i == 2) temp = 18;
				cout << setw(pos-8) << "|   " << "" << menuItems[i] << setw(temp) << "|" << endl;
				if (i != 2) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
		}
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		key = _getch();
		switch (key) {
		case 72: 
			selectedItem = (selectedItem - 1 + 3) % 3;
			break;
		case 80: 
			selectedItem = (selectedItem + 1) % 3;
			break;
		case 13: 
	
			if (selectedItem == 0) {
				userAccount(si, us);
			}
			if (selectedItem == 1)
				mutilTask();
			if (selectedItem == 2) return;
			//int x=_getch();
			break;
		}

	} while (key != 27); 
}
void Student_menu() {
	Class cl = getstudentInfoArray();
	Student stu = getCurStudentInfo(cl, us);
	Semester couforStu;
	char menuItems[5][30] = { "View your info", "Your course","View scoreboard","Change password" ,"Log out"};
	int selectedItem = 0;
	char key;
	int pos = 61;
	do {
		system("cls");
		cout << "Call us : (028) 3835 4266" << endl;
		cout << "E-mail : info@fit.hcmus.edu.vn" << endl;
		cout << "\n\n";
		cout << setw(pos - 2) << "" << GREEN << "HOME PAGE" << RESET << endl << endl;
		cout << setw(pos - 12) << "" << "Semester-" << curSemester.name << "/" << curSemester.nameYear << endl;
		cout << setw(pos - 12) << ""  << curSemester.startDate << "-" << curSemester.endDate  << endl;
		cout << setw(pos - 3) << "Student: " << stu.lastName << " " << stu.firstName << endl;
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		for (int i = 0; i < 5; i++) {
			if (i == selectedItem) {
				int temp = 0;
				if (i == 0) temp = 10;
				if (i == 1) temp = 13;
				if (i == 2) temp = 9;
				if (i == 3) temp = 9;
				if (i == 4) temp = 17;
				cout << setw(pos - 8) << "|   " << "" << " " << GREEN << menuItems[i] << RESET << setw(temp) << "|" << endl;
				if (i != 4) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
			else {
				int temp = 0;
				if (i == 0) temp = 11;
				if (i == 1) temp = 14;
				if (i == 2) temp = 10;
				if (i == 3) temp = 10;
				if (i == 4) temp = 18;
				cout << setw(pos - 8) << "|   " << "" << menuItems[i] << setw(temp) << "|" << endl;
				if (i != 4) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
		}
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		key = _getch();
		switch (key) {
		case 72:
			selectedItem = (selectedItem - 1 + 5) % 5;
			break;
		case 80:
			selectedItem = (selectedItem + 1) % 5;
			break;
		case 13:
			if (selectedItem == 0) {
				cout << YELLOW;
				cout << setw(25) << "" << left << setw(12) << "ID";
				cout << left << setw(16) << "Last name";
				cout << left << setw(14) << "First name";
				cout << left << setw(16) << "Date of birth";
				cout << left << setw(10) << "Sex";
				cout << left << setw(15) << "Social ID";
				cout << RESET;
				cout << endl;
				cout << setw(25) << "" << left << setw(12) << stu.id;
				cout << left << setw(16) << stu.lastName;
				cout << left << setw(14) << stu.firstName;
				cout << left << setw(16) << stu.dateofBirth;
				cout << left << setw(10) << stu.sex;
				cout << left << setw(15) << stu.socialid;
				cout << right << setw(15);
				cout << endl;
			}
			if (selectedItem == 1) {
				couforStu = getCourseforStudent(stu);
				showListofCourse(couforStu);
			}
			if (selectedItem == 3) {
				changePassword(userArray, us);
			}
			if (selectedItem == 4) return;
			int x = _getch();
			break;
		}

	} while (key != 27);
}
void menu() {
	while (true) {
		userArray = getUserArray();
		bool check_login = false;
		us = login(userArray);
		for (int i = 0; i < us.username.length(); i++) {
			if (us.username[i] == '@') {
				check_login = true;
				break;
			}
		}
		if (check_login == true) Staff_menu();
		else Student_menu();
	}
}