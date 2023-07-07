#include "function.h"
UserArray userArray;
StaffInfoArray staffInfoArray;
SchoolYearArray schoolYearArray;
StaffInfo sI;
SchoolYear newSchoolYear;
Class newStudentsArray;
Semester curSemester;
User us;
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
		newArr[i].students = NULL;
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
string returnNameofSemester(int n) {
	if (n == 1) return "semester1";
	if (n == 2) return "semester2";
	if (n == 3) return "semester3";
	return "";
}
void getCourse(Semester sm, Course& cou) {
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\" + cou.id + ".csv";
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
void getSemester(Semester& sem) {
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
	while (cnt != sem.n) {
		getline(filein, sem.course[cnt].id, ',');
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
	SchoolYearArray lSY = { NULL,0 };
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
SchoolYear createSchoolYear(SchoolYearArray& sYA, string schoolYearName) {
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
	sY.schoolLevel[0].classes = resizeClassesArray(sY.schoolLevel[0].classes, sY.schoolLevel[0].n, sY.schoolLevel[0].n + 1);
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
	cout << setw(45) << "" << "ID: ";
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
void addAStudentToSTArray(Class& cl, Student st) {
	if (cl.Students == NULL) {
		cl.n = 1;
		cl.Students = new Student[cl.n];
		cl.Students[cl.n - 1] = st;
		return;
	}
	cl.Students = resizeStudentArray(cl.Students, cl.n, cl.n + 1);
	cl.n++;
	cl.Students[cl.n - 1] = st;
}
void addStudenttoFile(Student st, string path) {
	ofstream fileout(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
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
void quickInputNewStudent(SchoolYear& schoolYear, Class newStuArr) {
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
				string path = "source\\" + schoolYear.name + "\\" + schoolYear.schoolLevel[i].name + "\\" + schoolYear.schoolLevel[i].classes[j].name + ".csv";
				addStudenttoFile(st, path);
				path = "source\\student_info.csv";
				addStudenttoFileInfo(st, path);
				path = "source\\user.csv";
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
void addSemestertoSchoolYear(SchoolYearArray& lsy, Semester sm) {
	string nameSem = returnNameofSemester(sm.name);
	string path;
	path = "source\\" + sm.nameYear + "\\semester.csv";
	ofstream fileout(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
	fileout << nameSem << "," << sm.startDate << "," << sm.endDate;
	fileout.close();
	path = "source\\" + sm.nameYear + "\\" + nameSem;
	LPCSTR folderName = path.c_str();
	CreateDirectoryA(folderName, NULL);
	path = path + "\\course.csv";
	fileout.open(path, ios::out);
	fileout.close();
	for (int i = 0; i < lsy.n; i++) {
		if (lsy.schoolYears[i].name == sm.nameYear) {
			lsy.schoolYears[i].semester[sm.name - 1] = sm;
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
	cout << setw(45) << "" << GREEN << "Class: " << RESET;
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
void addCoursetoSemester(SchoolYearArray& lsy, Semester& sm, Course cs) {
	ofstream fileout;
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\course.csv";
	fileout.open(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
	fileout << cs.id << "," << cs.name << "," << cs.className << "," << cs.teacherName << "," << cs.day << "," << cs.time << "," << cs.numOfCre << "," << cs.maxStu;
	fileout.close();
	path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\" + cs.id + ".csv";
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
void addStudenttoCourse(SchoolYear& sy) {
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
void updateCourse(Semester& sm, int key1, int key2, string change) {
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
	for (int i = 0; i < sm.n - 1; i++) {
		fileout << sm.course[i].id << "," << sm.course[i].name << "," << sm.course[i].className << "," << sm.course[i].teacherName << "," << sm.course[i].day << "," << sm.course[i].time << "," << sm.course[i].numOfCre << "," << sm.course[i].maxStu << endl;
	}
	fileout << sm.course[sm.n - 1].id << "," << sm.course[sm.n - 1].name << "," << sm.course[sm.n - 1].className << "," << sm.course[sm.n - 1].teacherName << "," << sm.course[sm.n - 1].day << "," << sm.course[sm.n - 1].time << "," << sm.course[sm.n - 1].numOfCre << "," << sm.course[sm.n - 1].maxStu;
	fileout.close();
}
void addaStudenttoCourse(Semester& sm, int key, Student stu) {
	ofstream fileout;
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\" + sm.course[key - 1].id + ".csv";
	fileout.open(path, ios::app);
	if (!isFileEmpty(path)) fileout << endl;
	fileout << stu.id << "," << stu.lastName << "," << stu.firstName << "," << stu.dateofBirth << "," << stu.sex << "," << stu.socialid;
	fileout.close();
	if (sm.course[key - 1].students == NULL) {
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
	for (int i = key2 - 1; i < sm.course[key1 - 1].n - 1; i++) {
		sm.course[key1 - 1].students[i] = sm.course[key1 - 1].students[i + 1];
	}
	sm.course[key1 - 1].n--;
	string  path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\" + sm.course[key1 - 1].id + ".csv";
	ofstream fileout(path, ios::out);
	for (int i = 0; i < sm.course[key1 - 1].n; i++) {
		fileout << sm.course[key1 - 1].students[i].id << "," << sm.course[key1 - 1].students[i].lastName << "," << sm.course[key1 - 1].students[i].firstName << "," << sm.course[key1 - 1].students[i].dateofBirth << "," << sm.course[key1 - 1].students[i].sex << "," << sm.course[key1 - 1].students[i].socialid;
		if (i != sm.course[key1 - 1].n - 1) fileout << endl;
	}
	fileout.close();
}
void deleteCourse(Semester& sm, int key) {
	for (int i = key - 1; i < sm.n - 1; i++) {
		sm.course[i] = sm.course[i + 1];
	}
	sm.n--;
	string  path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\course.csv";
	ofstream fileout(path, ios::out);
	for (int i = 0; i < sm.n; i++) {
		fileout << sm.course[i].id << "," << sm.course[i].name << "," << sm.course[i].className << "," << sm.course[i].teacherName << "," << sm.course[i].day << "," << sm.course[i].time << "," << sm.course[i].numOfCre << "," << sm.course[i].maxStu;
		if (i != sm.n - 1) fileout << endl;
	}
	fileout.close();
}
UserArray getUserArray() {
	UserArray usA = { NULL, 0 };
	ifstream filein("source\\user.csv", ios_base::in);
	string line;
	while (getline(filein, line)) usA.n++;
	filein.clear();
	filein.seekg(0, ios::beg);
	usA.user = new User[usA.n];
	int cnt = 0;
	while (!filein.eof()) {
		getline(filein, (usA.user + cnt)->username, ',');
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
	path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard\\allscore.csv";
	fileout.open(path, ios::out);
	fileout.close();
	for (int i = 0; i < sm.n; i++) {
		path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard\\" + sm.course[i].id + ".csv";
		fileout.open(path, ios::out);
		for (int j = 0; j < sm.course[i].n - 1; j++) {
			fileout << sm.course[i].students[j].id << "," << sm.course[i].students[j].lastName << " " << sm.course[i].students[j].firstName << endl;
		}
		fileout << sm.course[i].students[sm.course[i].n - 1].id << "," << sm.course[i].students[sm.course[i].n - 1].lastName << " " << sm.course[i].students[sm.course[i].n - 1].firstName;
		fileout.close();
	}
}
void readScoreBoard(Semester& sm) {
	string path;
	ifstream filein;
	for (int i = 0; i < sm.n; i++) {
		path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard\\" + sm.course[i].id + ".csv";
		filein.open(path, ios::in);
		if (!filein.is_open()) continue;
		int cnt = 0;
		while (!filein.eof()) {
			string temp;
			getline(filein, temp, ',');
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
void updateScoreBoard(Semester& sm, int key1, int key2, int key3, float change) {
	if (key3 == 1) sm.course[key1 - 1].students[key2 - 1].mark.total = change;
	if (key3 == 2) sm.course[key1 - 1].students[key2 - 1].mark.final = change;
	if (key3 == 3) sm.course[key1 - 1].students[key2 - 1].mark.midterm = change;
	if (key3 == 4) sm.course[key1 - 1].students[key2 - 1].mark.other = change;
	ofstream fileout;
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard\\" + sm.course[key1 - 1].id + ".csv";
	fileout.open(path, ios::out);
	if (!isFileEmpty(path)) fileout << endl;
	for (int i = 0; i < sm.course[key1 - 1].n - 1; i++) {
		fileout << sm.course[key1 - 1].students[i].id << "," << sm.course[key1 - 1].students[i].lastName << " " << sm.course[key1 - 1].students[i].firstName << "," << sm.course[key1 - 1].students[i].mark.total << "," << sm.course[key1 - 1].students[i].mark.final << "," << sm.course[key1 - 1].students[i].mark.midterm << "," << sm.course[key1 - 1].students[i].mark.other << endl;
	}
	int i = sm.course[key1 - 1].n - 1;
	fileout << sm.course[key1 - 1].students[i].id << "," << sm.course[key1 - 1].students[i].lastName << " " << sm.course[key1 - 1].students[i].firstName << "," << sm.course[key1 - 1].students[i].mark.total << "," << sm.course[key1 - 1].students[i].mark.final << "," << sm.course[key1 - 1].students[i].mark.midterm << "," << sm.course[key1 - 1].students[i].mark.other;
	fileout.close();
}
void createAllScoreFile(Semester sm) {
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard\\allscore.csv";
	ofstream fileout;
	fileout.open(path, ios::out);
	for (int i = 0; i < sm.n; i++) {
		for (int j = 0; j < sm.course[i].n - 1; j++) {
			fileout << sm.course[i].students[j].id << "," << sm.course[i].name << "," << sm.course[i].students[j].mark.total << "," << sm.course[i].students[j].mark.final << "," << sm.course[i].students[j].mark.midterm << "," << sm.course[i].students[j].mark.other << endl;
			cout << sm.course[i].students[j].id << "," << sm.course[i].name << "," << sm.course[i].students[j].mark.total << "," << sm.course[i].students[j].mark.final << "," << sm.course[i].students[j].mark.midterm << "," << sm.course[i].students[j].mark.other << endl;
		}
	}
	fileout.close();
}
void readScoreforStudent(Semester sm, Student& st) {
	st.markofCourse = new MarkofCourse[10];
	st.n = 0;
	string path = "source\\" + sm.nameYear + "\\" + returnNameofSemester(sm.name) + "\\scoreboard\\allscore.csv";
	ifstream filein;
	filein.open(path, ios::in);
	if (!filein.is_open()) return;
	int cnt = 0;
	while (!filein.eof()) {
		string temp;
		getline(filein, temp, ',');
		if (temp == st.id) {
			getline(filein, st.markofCourse[cnt].courseName, ',');
			filein >> st.markofCourse[cnt].mark.total;
			filein.seekg(1, 1);
			filein >> st.markofCourse[cnt].mark.final;
			filein.seekg(1, 1);
			filein >> st.markofCourse[cnt].mark.midterm;
			filein.seekg(1, 1);
			filein >> st.markofCourse[cnt].mark.other;
			getline(filein, temp);
			cnt++;
			st.n++;
		}
		else {
			getline(filein, temp);
		}
	}
}
void showClasswithScore(SchoolYear sy, string ClassName) {
	double diem = 0;
	cout << YELLOW;
	cout << setw(15) << "" << left << setw(10) << "No";
	cout << left << setw(15) << "ID";
	cout << left << setw(30) << "Full name";
	cout << RESET;
	cout << right << setw(30);
	cout << endl;
	for (int i = 0; i < sy.n; i++) {
		for (int j = 0; j < sy.schoolLevel[i].n; j++) {
			if (ClassName == sy.schoolLevel[i].classes[j].name) {
				for (int k = 0; k < sy.schoolLevel[i].classes[j].n; k++) {
					cout << setw(10) << "" << left << setw(10) << GREEN << k + 1 << ".";
					cout << left << setw(13) << GREEN << sy.schoolLevel[i].classes[j].Students[k].id;
					cout << left << setw(12) << GREEN << sy.schoolLevel[i].classes[j].Students[k].lastName << " " << sy.schoolLevel[i].classes[j].Students[k].firstName << RESET;
					cout << right << setw(12);
					cout << endl;
					readScoreforStudent(curSemester, sy.schoolLevel[i].classes[j].Students[k]);
					for (int h = 0; h < sy.schoolLevel[i].classes[j].Students[k].n; h++) {
						cout << setw(15) << "" << YELLOW << "-->" << sy.schoolLevel[i].classes[j].Students[k].markofCourse[h].courseName << RESET << ": " << sy.schoolLevel[i].classes[j].Students[k].markofCourse[h].mark.final << endl;
						diem = diem + sy.schoolLevel[i].classes[j].Students[k].markofCourse[h].mark.final;
					}
					cout << setw(15) << "" << YELLOW << "-->GPA: " << RESET << diem / sy.schoolLevel[i].classes[j].Students[k].n << endl;
					diem = 0;
				}
				break;
			}
		}
	}
};
User inputUser(int pos) {
	User us;
	cout << "\n\n\n\n\n\n\n\n\n\n\n";
	cout << setw(pos + 7) << "" << "LOGIN" << endl;
	cout << setw(pos - 5) << "" << "/-------------<>-------------\\" << endl;
	cout << setw(pos - 3) << "" << "Username: ";
	getline(cin, us.username);
	cout << setw(pos - 3) << "" << "Password: ";
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
		if (k == 1) cout << GREEN << setw(pos + 5) << "" << "Success! ";
		if (k == -1)cout << RED << setw(pos + 2) << "" << "Wrong password! ";
		if (k == 0) cout << RED << setw(pos + 2) << "" << "Wrong username! ";
		cout << RESET;
		int x = _getch();
		pos = 57;
	} while (k == -1 || k == 0);
	return us;
}
void printStaffInfo(StaffInfo si, int n) {
	cout << setw(10) << "" << left << setw(20) << si.name;
	cout << left << setw(20) << si.dateofBirth;
	cout << left << setw(10) << si.sex;
	cout << left << setw(15) << si.position;
	cout << left << setw(30) << si.email;
	cout << left << setw(15) << si.id;
	cout << right << setw(15);
	cout << endl;
}
void changePassword(UserArray& usA, User& us) {
	string curPass;
	string newPass;
	string newPass2;
	while (true) {
		cout << setw(50) << "" << "Input current password: ";
		getline(cin, curPass);
		if (curPass != us.password) {
			cout << RED;
			cout << setw(50) << "" << "Wrong password!" << endl;
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
			cout << setw(50) << "" << RED << "Same old password!" << RESET << endl;
		}
		else if (newPass != newPass2) {
			cout << setw(50) << "" << RED << "Not match!" << RESET << endl;
		}
		else break;
	}
	cout << setw(50) << "" << GREEN << "Success!" << RESET;
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
void userAccount(StaffInfo si, User& us) {
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
	cout << setw(10) << "" << left << setw(5) << "No";
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
		cout << setw(10) << "" << left << setw(5) << i + 1;
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
	for (int i = 0; i < syA.n; i++) {
		if (syA.schoolYears[i].name == nameYear) {
			for (int j = 0; j < 4; j++) {
				cout << setw(20) << "" << YELLOW << syA.schoolYears[i].schoolLevel[j].name << RESET;
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
	for (int i = 0; i < sm.course[key - 1].n; i++) {
		cout << setw(20) << "" << left << setw(10) << i + 1;
		cout << left << setw(15) << sm.course[key - 1].students[i].id;
		cout << left << setw(20) << sm.course[key - 1].students[i].lastName + " " + sm.course[key - 1].students[i].firstName;
		cout << left << setw(20) << sm.course[key - 1].students[i].dateofBirth;
		cout << left << setw(15) << sm.course[key - 1].students[i].sex;
		cout << left << setw(22) << sm.course[key - 1].students[i].socialid;
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