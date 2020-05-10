#include "include/Lecturer.h"

Lecturer::Lecturer(){
	this->EmployeeNo=0;
	this->AcademicChair="";
	this->Department="";
	this->no_Lec_Appointments=0;
}

Lecturer::Lecturer(const std::string Name, const std::string Surname, const std::string Email, const int phone,
						const int EmployeeNo, const std::string Dept, const std::string AcademicChair)
					:Person(Name, Surname, Email, phone)
{
	this->EmployeeNo=EmployeeNo;
	this->AcademicChair=AcademicChair;
	this->Department=Dept;
}

Lecturer::~Lecturer(){
}

void Lecturer::setLecturer(const std::string Name, const std::string Surname, const std::string Email, const int phone,
						const int EmployeeNo, const std::string Dept, const std::string AcademicChair)
{
	setPerson(Name, Surname, Email, phone);
	this->EmployeeNo=EmployeeNo;
	this->AcademicChair=AcademicChair;
	this->Department=Dept;
}

void Lecturer::setAppointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime){
	Lec_Appointments.resize(no_Lec_Appointments+1);
	Lec_Appointments[no_Lec_Appointments].setAppointment(StudentNo, LecturerNo, date, StartTime, FinishTime);
	no_Lec_Appointments++;
}

int Lecturer::getEmployeeNo() const{
	return EmployeeNo;
}

std::string Lecturer::getAcademicChair() const{
	return AcademicChair;
}

std::string Lecturer::getDept() const{
	return Department;
}

int Lecturer::getno_Lec_Appointments() const{
	return no_Lec_Appointments;
}

std::vector<Appointment> Lecturer::getLec_Appointments() const{
	return Lec_Appointments;
}

void Lecturer::printInfo()const{
	std::cout<<"\t"<<getName()<<" "<<getSurname()<<std::endl;
	for(int i=0; i<no_Lec_Appointments; i++){
		std::cout<<"\t";
		Lec_Appointments[i].printAppointment();
	}
}

void Lecturer::deleteStudentAppointment(const int StudentNo){
	int i;
	for(i=0; i<no_Lec_Appointments; i++){
		if(Lec_Appointments[i].getStudentNo()==StudentNo){
			break;
		}
	}
	Lec_Appointments.erase(Lec_Appointments.begin()+i);
	no_Lec_Appointments--;
}

void Lecturer::deleteStudent_all_Appointment(const int StudentNo){
	int i;
	for(i=0; i<no_Lec_Appointments; i++){
		if(Lec_Appointments[i].getStudentNo()==StudentNo){
			Lec_Appointments.erase(Lec_Appointments.begin()+i);
			no_Lec_Appointments--;
			i=0;
		}
	}
}