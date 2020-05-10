/**************************Appointment System********************************************/
#ifndef APPOINTMENT_SYSTEM_H_
#define APPOINTMENT_SYSTEM_H_

#include "Student.h"
#include "Lecturer.h"
#include "Appointment.h"
#include <iostream>
#include <string>
#include <vector>


class AppointmentSystem{
	public:
		AppointmentSystem();
		~AppointmentSystem();

		bool Appointmentoverlap(const Lecturer &L,const Date &date,const Time &StartTime,const Time &FinishTime) const;

		void addStudent(const std::string Name, const std::string Surname, const std::string Email, const int phone,
						const int StudentNo,const std::string Dept, const int year);
		void addLecturer(const std::string Name, const std::string Surname, const std::string Email, const int phone,
						const int EmployeeNo, const std::string Dept, const std::string AcademicChair);
		void addAppointment(const int StudentNo, const int LecturerNo, const int d, const int m, const int y,
						const int s_hr , const int s_min, const int f_hr, const int f_min);

		void deleteStudent(const int StudentNo);
		void deleteLecturer(const int EmployeeNo);
		void deleteAppointment(const int StudentNo, const int EmployeeNo);

		void listStudent() const;
		void listLecturer() const;
		void listAppointment() const;

		void updateStudent();
		void updateLecturer();
		void updateAppointment();

		void getInfoFromDocuments(std::ifstream& studentsFile, std::ifstream& lecturersFile, std::ifstream& appointmentFile);


	private:
		bool findStudent(const int StudentNo);
		bool findLecturer(const int EmployeeNo);
		bool findAppointment(const int StudentNo, const int EmployeeNo);
		std::string removeTokenFromLine(const std::string line);

		std::vector<Student> Students;
		std::vector<Lecturer> Lecturers;
		std::vector<Appointment> Appointments;

		int no_students;
		int no_lecturers;
		int no_Appointments;
};

#endif