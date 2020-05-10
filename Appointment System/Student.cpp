#include "include/Student.h"

Student::Student(){
	this->StudentNo=0;
	this->Department="";
	this->no_Std_Appointments=0;
}

Student::Student(const std::string Name, const std::string Surname, const std::string Email, const int phone,
					const int StudentNo,const std::string Dept, const int Year)
				:Person(Name, Surname, Email, phone)
{
	this->StudentNo=StudentNo;
	this->Department=Dept;
	this->Year=Year;
}

Student::~Student(){
}

void Student::setStudent(const std::string Name, const std::string Surname, const std::string Email, const int phone,
					const int StudentNo,const std::string Dept, const int Year)
{
	setPerson(Name, Surname, Email, phone);
	this->StudentNo=StudentNo;
	this->Department=Dept;
	this->Year=Year;
}

int Student::getStudentNo() const{
	return StudentNo;
}

std::string Student::getDept() const{
	return Department;
}

int Student::getStartDate() const{
	return Year;
}

void Student::printInfo()const{
	std::cout<<"\t"<<getName()<<" "<<getSurname()<<std::endl;
	for(int i=0; i<no_Std_Appointments; i++){
		std::cout<<"\t";
		Std_Appointments[i].printAppointment();
	}
}

void Student::setAppointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime){
	Std_Appointments.resize(no_Std_Appointments+1);
	Std_Appointments[no_Std_Appointments].createAppointment(StudentNo, LecturerNo, date, StartTime, FinishTime);
	no_Std_Appointments++;
}
int Student::getno_Std_Appointments() const{
	return no_Std_Appointments;
}

std::vector<Appointment> Student::getStd_Appointments() const{
	return Std_Appointments;
}
void Student::deleteAppointmenttoLecturer(const int Lecturer){
	int i;
	for(i=0; i<no_Std_Appointments; i++){
		if(Std_Appointments[i].getEmployeeNo()==Lecturer){
			break;
		}
	}
	Std_Appointments.erase(Std_Appointments.begin()+i);
	no_Std_Appointments--;
}

void Student::deleteall_AppointmenttoLecturer(const int Lecturer){
	int i;
	for(i=0; i<no_Std_Appointments; i++){
		if(Std_Appointments[i].getEmployeeNo()==Lecturer){
			Std_Appointments.erase(Std_Appointments.begin()+i);
			no_Std_Appointments--;
			i=0;
		}
	}
}