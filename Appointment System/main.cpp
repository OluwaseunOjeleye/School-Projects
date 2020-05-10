#include "include/AppointmentSystem.h"

bool PrintMenu(AppointmentSystem *S){
	int Choice = 0;

	std::cout << "********** Main Menu **********" << std::endl;
	std::cout << "(1): Add Student" << std::endl;
	std::cout << "(2): Add Lecturer" << std::endl;
	std::cout << "(3): Add Appointment" << std::endl;
	std::cout << "(4): Delete Student" << std::endl;
	std::cout << "(5): Delete Lecturer" << std::endl;
	std::cout << "(6): Delete Appointment" << std::endl;
	std::cout << "(7): List Student" << std::endl;
	std::cout << "(8): List Lecturer" << std::endl;
	std::cout << "(9): List Appointment" << std::endl;
	std::cout << "(99): Exit" << std::endl;
	std::cin >> Choice;

	std::string name, surname, email, dept, position, Date, startTime, endTime, token;
	int phone, employeeNo, stuNo, year, d, m, y, start_hr, start_min, end_hr, end_min;
	char c1, c2;

	switch(Choice){
	case 1:
		std::cout<<"***********Add Student**********"<<std::endl;
		std::cout<<"Name: ";
		std::cin>>name;
		std::cout<<"Surname: ";
		std::cin>>surname;
		std::cout<<"Email: ";
		std::cin>>email;
		std::cout<<"Telephone: ";
		std::cin>>phone;
		std::cout<<"Student Number: ";
		std::cin>>stuNo;
		std::cout<<"Department: ";
		std::cin>>dept;
		std::cout<<"Year: ";
		std::cin>>year;

		S->addStudent(name, surname, email, phone, stuNo, dept, year);
		break;
	case 2:
		std::cout<<"**********Add Lecturer**********"<<std::endl;
		std::cout<<"Name: ";
		std::cin>>name;
		std::cout<<"Surname: ";
		std::cin>>surname;
		std::cout<<"Email: ";
		std::cin>>email;
		std::cout<<"Telephone: ";
		std::cin>>phone;
		std::cout<<"Employee Number: ";
		std::cin>>employeeNo;
		std::cout<<"Department: ";
		std::cin>>dept;
		std::cout<<"Position: ";
		std::cin>>position;
		S->addLecturer(name, surname, email, phone, employeeNo, dept, position);
		break;
	case 3:
		std::cout<<"**********Add Appointment**********"<<std::endl;
		std::cout<<"Student Number: ";
		std::cin>>stuNo;
		std::cout<<"Employee Number: ";
		std::cin>>employeeNo;
		std::cout<<"Date: ";
		std::cin>>d>>c1>>m>>c2>>y;
		std::cin.clear();
		//std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
		std::cout<<"Start Time: ";
		std::cin>>start_hr>>c1>>start_min;
		std::cin.clear();
		//std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
		std::cout<<"End Time: ";
		std::cin>>end_hr>>c1>>end_min;
		std::cin.clear();
		//std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		S->addAppointment(stuNo, employeeNo, d, m, y, start_hr, start_min, end_hr, end_min);
		break;
	case 4:
		std::cout<<"**********Delete Student**********"<<std::endl;
		std::cout<<"Input Student Number: ";
		std::cin>>stuNo;
		S->deleteStudent(stuNo);
		break;
	case 5:
		std::cout<<"**********Delete Lecturer**********"<<std::endl;
		std::cout<<"Input Employee Number: ";
		std::cin>>employeeNo;
		S->deleteLecturer(employeeNo);
		break;
	case 6:
		std::cout<<"**********Delete Appointment**********"<<std::endl;
		std::cout<<"Input Student Number: ";
		std::cin>>stuNo;
		std::cout<<"Input Employee Number: ";
		std::cin>>employeeNo;
		S->deleteAppointment(stuNo, employeeNo);
		break;
	case 7:
		std::cout<<"**********Students List**********"<<std::endl;
		S->listStudent();
		break;
	case 8:
		std::cout<<"**********Lecturers List**********"<<std::endl;
		S->listLecturer();
		break;
	case 9:
		std::cout<<"**********Appointments List**********"<<std::endl;
		S->listAppointment();
		break;
	case 99:
		std::cout<<"Shutting Down Database..."<<std::endl;
		std::cout<<"Goodbye :)"<<std::endl;
		return false;
	default:
		std::cout<<"ERROR! You have selected an invalid choice." << std::endl;
		std::cout<<"Choose again.\n";
        std::cin>>Choice;
		break;
	}
}

int main(){
	AppointmentSystem SAS;
	std::ifstream Std, Lec, App;
    Std.open("./Database/Students",std::ios::in);
    Lec.open("./Database/Lecturers",std::ios::in);
    App.open("./Database/Appointments",std::ios::in);

    SAS.getInfoFromDocuments(Std, Lec, App);
    bool state=true;
	while (state != false){
		state=PrintMenu(&SAS);
	}

	/*SAS.addStudent("Seun","Ojeleye","jimmystar14@yahoo.com", 803375,359704,"Computer Engineering", 2016);
	SAS.addStudent("Jimmy","Ojeleye","star14@yahoo.com", 803375,359703,"Computer Engineering", 2016);
	SAS.addStudent("Oluwaseun","Ojeleye","jimmystar14@yahoo.com", 8033,359702,"Computer Engineering", 2016);
	SAS.addLecturer("Seun","Ojeleye","jimmystar14@yahoo.com", 803375,88392,"Computer Engineering", "Prof. Dr.");
	SAS.addLecturer("J-STar","Ojeleye","jimmystar14@yahoo.com", 803375,88999,"Computer Engineering", "Prof. Dr.");

	SAS.addAppointment(359703,88392, 12,12,18, 16,30, 16, 45);
	SAS.addAppointment(359704,88392, 12,12,18, 16,10, 16, 15);
	SAS.addAppointment(359703,88999, 12,12,18, 16,30, 16, 45);
	SAS.addAppointment(359704,88999, 12,12,18, 16,10, 16, 15);*/

	/*SAS.listAppointment();
	SAS.listStudent();
	SAS.deleteStudent(359704);
	SAS.listStudent();
	SAS.listLecturer();
	SAS.deleteLecturer(88392);
	SAS.listLecturer();
	SAS.deleteLecturer(88999);
	SAS.listLecturer();
	SAS.deleteAppointment(359703,88999);
	SAS.listAppointment();
	SAS.listLecturer();*/
}
