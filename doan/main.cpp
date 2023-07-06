#include "function.h"
int main() {
	schoolYearArray = getSchoolYearArray();
	newStudentsArray = getClass("NewStudent", "source\\new_students.csv");
	curSemester = getCurSemester(schoolYearArray);
	menu();
	return 0;
}
