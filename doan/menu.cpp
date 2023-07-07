#include "menu.h"
void classOption() {
	char menuItems[5][30] = { "Create class", "View list of classes","Input Student","Quick input" ,"Exit" };
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
		cout << setw(pos - 3) << "" << GREEN << "CLASS OPTION" << RESET << endl;
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
				cout << setw(45) << "" << GREEN << "Input school year: " << RESET;
				getline(cin, schoolYearName);
				cout << setw(45) << "" << GREEN << "Input school level: " << RESET;
				getline(cin, schoolLevel);
				cout << setw(45) << "" << GREEN << "Input number of classes: " << RESET;
				cin >> n;
				cin.ignore();
				for (int i = 0; i < schoolYearArray.n; i++) {
					if (schoolYearArray.schoolYears[i].name == schoolYearName) {
						for (int j = 0; j < n; j++) {
							cout << setw(45) << "" << GREEN << "Input class name(CTT/CLC/VP/APCS): " << RESET;
							getline(cin, className);
							addClasstoSchoolYear(schoolYearArray.schoolYears[i], schoolLevel, className);
						}
						break;
					}
				}
				cout << setw(45) << "" << GREEN << "Success!" << RESET;
			}
			if (selectedItem == 1) {
				cout << setw(38) << "" << GREEN << "Input school year you want to view classes: " << RESET;
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
	char menuItems[7][30] = { "View course" ,"Create course","Update course","Delete course","Export course","View scoreboard" ,"Exit" };
	int selectedItem = 0;
	char key;
	int pos = 61;
	Course cs;
	SchoolYear curSchoolYear;
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
		cout << setw(pos - 3) << "" << GREEN << "COURSE OPTION" << RESET << endl << endl;
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
					cout << setw(45) << "" << GREEN << "Input course " << i + 1 << RESET << endl;
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
				cout << setw(45) << "" << GREEN << "1. View scoreboard of course" << endl << RESET;
				cout << setw(45) << "" << GREEN << "2. View scoreboard of class" << endl << RESET;
				cout << setw(45) << "" << GREEN << "Your choose: " << RESET;
				cin >> key1;
				cin.ignore();
				if (key1 == 1) {
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
				else {
					for (int i = 0; i < schoolYearArray.n; i++) {
						if (schoolYearArray.schoolYears[i].name == curSemester.nameYear) {
							curSchoolYear = schoolYearArray.schoolYears[i];
							break;
						}
					}
					cout << setw(45) << "" << GREEN << "Input a class you want to view: " << RESET;
					getline(cin, className);
					showClasswithScore(curSchoolYear, className);
				}
			}
			if (selectedItem == 6) return;
			int x = _getch();
			break;
		}
	} while (key != 27);
}
void mutilTask() {
	char menuItems[5][30] = { "Create school year","Create semester", "Class option", "Course option" ,"Exit" };
	int selectedItem = 0;
	char key;
	int pos = 61;
	string schoolYearName;
	do {
		system("cls");
		cout << "Call us : (028) 3835 4266" << endl;
		cout << "E-mail : info@fit.hcmus.edu.vn" << endl;
		cout << "\n\n\n\n\n";
		cout << setw(pos - 7) << "" << GREEN << "MULTI-TASKING OPTION" << RESET << endl;
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
				if (i != 4) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
			else {
				int temp = 0;
				if (i == 0) temp = 7;
				if (i == 1) temp = 10;
				if (i == 2) temp = 13;
				if (i == 3) temp = 12;
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
				cout << setw(50) << "" << GREEN << "Input school year name: " << RESET;
				getline(cin, schoolYearName);
				createSchoolYear(schoolYearArray, schoolYearName);
				cout << setw(50) << "" << GREEN << "Succcess!" << RESET << endl;
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
	StaffInfo si = getCurStaffInfo(siA, us);
	char menuItems[3][30] = { "User Account", "Multi-tasking option", "Log out" };
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
		if (si.sex == "Nam") cout << setw(pos - 12) << "" << "Staff: " << "Mr." << si.name << endl;
		else cout << setw(pos - 12) << "" << "Staff: " << "Ms." << si.name << endl;
		cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
		for (int i = 0; i < 3; i++) {
			if (i == selectedItem) {
				int temp = 0;
				if (i == 0) temp = 12;
				if (i == 1) temp = 4;
				if (i == 2) temp = 17;
				cout << setw(pos - 8) << "|   " << "" << " " << GREEN << menuItems[i] << RESET << setw(temp) << "|" << endl;
				if (i != 2) cout << setw(pos - 12) << "" << "+---------------------------+" << endl;
			}
			else {
				int temp = 0;
				if (i == 0) temp = 13;
				if (i == 1) temp = 5;
				if (i == 2) temp = 18;
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
	char menuItems[5][30] = { "View your info", "Your course","View scoreboard","Change password" ,"Log out" };
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
		cout << setw(pos - 12) << "" << curSemester.startDate << "-" << curSemester.endDate << endl;
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
			if (selectedItem == 2) {
				double dtb = 0;
				readScoreforStudent(curSemester, stu);
				cout << YELLOW;
				cout << setw(20) << "" << left << setw(10) << "No";
				cout << left << setw(30) << "Course";
				cout << left << setw(15) << "Total mark";
				cout << left << setw(15) << "Final mark";
				cout << left << setw(15) << "Midterm mark";
				cout << left << setw(15) << "Other mark";
				cout << right << setw(15);
				cout << RESET;
				cout << endl;
				cout << setw(20) << "" << "--<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->----<->--";
				cout << endl;
				if (stu.markofCourse == NULL) return;
				for (int i = 0; i < stu.n; i++) {
					cout << setw(20) << "" << left << setw(10) << i + 1;
					cout << left << setw(34) << stu.markofCourse[i].courseName;
					cout << left << setw(15) << stu.markofCourse[i].mark.total;
					cout << left << setw(15) << stu.markofCourse[i].mark.final;
					cout << left << setw(15) << stu.markofCourse[i].mark.midterm;
					cout << left << setw(15) << stu.markofCourse[i].mark.other;
					cout << right << setw(15);
					cout << endl;
					dtb += stu.markofCourse[i].mark.total;
				}
				cout << YELLOW;
				dtb = dtb / stu.n;
				cout << setw(20) << "" << "-------->GPA: " << RESET << dtb << endl;

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