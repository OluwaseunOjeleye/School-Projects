/*************************************Appointment*****************************/
#ifndef APPOINTMENT_H_
#define APPOINTMENT_H_

#include "Date_n_Time.h"

class Appointment{
	public:
		Appointment();
		Appointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime);
		~Appointment();

		bool isAppointmentTimeCorrect();

		void setAppointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime);
		//The createAppointment methods Time is correct
		void createAppointment(const int StudentNo, const int LecturerNo, const Date &date, const Time &StartTime, const Time &FinishTime);

		int getStudentNo() const;
		int getEmployeeNo() const;
		Date getDate() const;
		Time getStartTime() const;
		Time getFinishTime() const;

		void printAppointment() const;

	private:
		int StudentNo;
		int LecturerNo;
		Date date;
		Time StartTime;
		Time FinishTime;
};

#endif