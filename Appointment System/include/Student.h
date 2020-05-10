/****************************Student***************************************/
#ifndef STUDENT_H_
#define STUDENT_H_

#include "Person.h"
#include "Date_n_Time.h"
#include "Appointment.h"
#include <string>
#include <vector>

class Student:public Person{
	public:
		Student();
		Student(const std::string Name, const std::string Surname, const std::string Email, const int phone,
				const int StudentNo,const std::string Dept, const int Year);
		~Student();

		void setStudent(const std::string Name, const std::string Surname, const std::string Email, const int phone,
				const int StudentNo,const std::string Dept, const int Year);

		int getStudentNo() const;
		std::string getDept() const;
		int getStartDate() const;

		void printInfo()const;

		void setAppointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime);
		int getno_Std_Appointments() const;
		std::vector<Appointment> getStd_Appointments() const;

		void deleteAppointmenttoLecturer(const int Lecturer);

		void deleteall_AppointmenttoLecturer(const int Lecturer);

	private:
		int StudentNo;
		std::string Department;
		int Year;

		std::vector<Appointment> Std_Appointments;
		int no_Std_Appointments;	//total number of appointments student made
};

#endif