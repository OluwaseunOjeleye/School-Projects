/****************************Lecturer***************************************/
#ifndef LECTURER_H_
#define LECTURER_H_

#include "Person.h"
#include "Date_n_Time.h"
#include "Appointment.h"
#include <string>
#include <vector>

class Lecturer:public Person{
	public:
		Lecturer();
		Lecturer(const std::string Name, const std::string Surname, const std::string Email, const int phone,
				const int EmployeeNo, const std::string Dept, const std::string AcademicChair);
		~Lecturer();

		void setLecturer(const std::string Name, const std::string Surname, const std::string Email, const int phone,
				const int EmployeeNo, const std::string Dept, const std::string AcademicChair);
		void setAppointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime);

		int getEmployeeNo() const;
		std::string getAcademicChair() const;
		std::string getDept() const;

		std::vector<Appointment> getLec_Appointments() const;
		int getno_Lec_Appointments() const;

		void deleteStudentAppointment(const int StudentNo);
		void deleteStudent_all_Appointment(const int StudentNo);

		void printInfo()const;


	private:
		int EmployeeNo;
		std::string AcademicChair;
		std::string Department;

		std::vector<Appointment> Lec_Appointments;
		int no_Lec_Appointments;	//total number of appointments for lecturer
};

#endif