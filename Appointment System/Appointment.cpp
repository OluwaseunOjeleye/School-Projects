#include "include/Appointment.h"

Appointment::Appointment(){
	this->StudentNo=0;
	this->LecturerNo=0;
}

Appointment::Appointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime){
	int hr1, hr2, min1, min2; char c1;
	this->StudentNo=StudentNo;
	this->LecturerNo=LecturerNo;
	this->date=date;
	this->StartTime=StartTime;
	this->FinishTime=FinishTime;
	while(!isAppointmentTimeCorrect()){
		std::cout<<"Finish Time is Lesser than Start Time"<<std::endl;
		std::cout<<"Input Starting Time Hour:Minute:- ";
		std::cin>>hr1>>c1>>min1;
		std::cin.clear();
		std::cout<<"Input Finishing Time Hour:Minute:- ";
		std::cin>>hr2>>c1>>min2;
		std::cin.clear();

		this->StartTime.setTime(hr1, min1);
		this->FinishTime.setTime(hr2, min2);
	}
}

bool Appointment::isAppointmentTimeCorrect(){
	if(this->StartTime.gethour()<this->FinishTime.gethour()){
		return true;
	}
	if(this->StartTime.gethour()==this->FinishTime.gethour()){
		if(this->StartTime.getmins()<this->FinishTime.getmins()){
			return true;
		}
	}
	return false;
}

Appointment::~Appointment(){

}

void Appointment::setAppointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime){
	int hr1, hr2, min1, min2; char c1;
	this->StudentNo=StudentNo;
	this->LecturerNo=LecturerNo;
	this->date=date;
	this->StartTime=StartTime;
	this->FinishTime=FinishTime;
	while(!isAppointmentTimeCorrect()){
		std::cout<<"Finish Time is Lesser than Start Time"<<std::endl;
		std::cout<<"Input Starting Time Hour:Minute:- ";
		std::cin>>hr1>>c1>>min1;
		std::cin.clear();
		std::cout<<"Input Finishing Time Hour:Minute:- ";
		std::cin>>hr2>>c1>>min2;
		std::cin.clear();

		this->StartTime.setTime(hr1, min1);
		this->FinishTime.setTime(hr2, min2);
	}
}

//Here The Time Info is surely correct
void Appointment::createAppointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime){
	this->StudentNo=StudentNo;
	this->LecturerNo=LecturerNo;
	this->date=date;
	this->StartTime=StartTime;
	this->FinishTime=FinishTime;
}

int Appointment::getStudentNo() const{
	return StudentNo;
}

int Appointment::getEmployeeNo() const{
	return LecturerNo;
}

Date Appointment::getDate() const{
	return date;
}

Time Appointment::getStartTime() const{
	return StartTime;
}

Time Appointment::getFinishTime() const{
	return FinishTime;
}

void Appointment::printAppointment() const{
	std::cout<<StudentNo<<" "<<LecturerNo<<" "<<date.getday()<<"."<<date.getmonth()<<
	"."<<date.getyear()<<" "<<StartTime.gethour()<<":"<<StartTime.getmins()<<" "<<
	FinishTime.gethour()<<":"<<FinishTime.getmins()<<std::endl;
}