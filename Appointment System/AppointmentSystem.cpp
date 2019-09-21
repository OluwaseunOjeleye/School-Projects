#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define AppointmentHourStart 8
#define AppointmentHourEnd 17

class Date{
	public:
		Date(){
			day=1;
			month=1;
			year=18;
		}

		Date(const int d, const int m, const int y){
			int i, j, k; char c1, c2;
			this->day=d;
			this->month=m;
			this->year=y;
			if(!isDateCorrect()){
				std::cout<<"The Appointment Date is not correct. Input another Appointment date below: "<<std::endl;
				std::cout<<"Day:Month:Year- ";
				std::cin>>i>>c1>>j>>c2>>k;
				std::cin.clear();
				setDate(i,j,k);
			}
		}

		void setDate(const int d, const int m, const int y){
			int i, j, k; char c1, c2;
			this->day=d;
			this->month=m;
			this->year=y;
			if(!isDateCorrect()){
				std::cout<<"The Appointment Date is not correct. Input another Appointment date below: "<<std::endl;
				std::cout<<"Day:Month:Year- ";
				std::cin>>i>>c1>>j>>c2>>k;
				std::cin.clear();
				setDate(i,j,k);
			}
		}

		int dayofweek(int d, int m, int y){ 
		    static int t[]={0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; 
		    y-=m<3; 
		    return (y+y/4-y/100+y/400+t[m-1]+d)%7; 
		} 

		bool isDateCorrect(){
			if(year>=18){
				if(month>=1 && month<=12){
					if(month==2){	//if February
						if(((year%4==0) && (year%100!=0))||(year%400==0)){	//Leap Year
							if(day>=1 && day<=29){
								if(dayofweek(day, month, year)==0||dayofweek(day, month, year)==6){
									std::cout<<"Error: Appointment can't be made on weekends"<<std::endl;
								}
								else{
									return true;
								}
							}
							else{
								std::cout<<"Error: It is a Leap year. February can't have more than 29 days"<<std::endl;
							}
						}
						else{
							if(day>=1 && day<=28){
								if(dayofweek(day, month, year)==0||dayofweek(day, month, year)==6){
									std::cout<<"Error: Appointment can't be made on weekends"<<std::endl;
								}
								else{
									return true;
								}
							}
							else{
								std::cout<<"Error: It is not a Leap year. February can't have more than 28 days"<<std::endl;
							}
						}
					}
					else if(month==4||month==6||month==9|month==11){
						if(day>=1 && day<=30){
							if(dayofweek(day, month, year)==0||dayofweek(day, month, year)==6){
								std::cout<<"Error: Appointment can't be made on weekends"<<std::endl;
							}
							else{
								return true;
							}
						}
						else{
							std::cout<<"Error: month"<<month<<" have 1-30 days"<<std::endl;
						}
					}
					else{
						if(day>=1 && day<=31){
							if(dayofweek(day, month, year)==0||dayofweek(day, month, year)==6){
								std::cout<<"Error: Appointment can't be made on weekends"<<std::endl;
							}
							else{
								return true;
							}
						}
						else{
							std::cout<<"Error: month"<<month<<" have 1-31 days"<<std::endl;
						}
					}
				}
				else{
					std::cout<<"Error: Invalid month Inputted"<<std::endl;
				}
			}
			else{
				std::cout<<"Error: Invalid Year Inputted"<<std::endl;
			}
			return false;
		}

		bool isEqual(const Date &d) const{
			if((day==d.day)&&(month==d.month)&&(year==d.year)){
				return true;
			}
			else{
				return false;
			}
		}

		int getday()const{return day;}
		int getmonth()const{return month;}
		int getyear()const{return year;}

	private:
		int day;
		int month;
		int year;
};

class Time{
	public:
		Time(){
			hour=0;
			mins=0;
		}

		Time(const int h, const int m){
			int i, j; char c1;
			this->hour=h;
			this->mins=m;
			if(!isTimeCorrect()){
				std::cout<<"The Appointment Time is not correct. Input another Appointment Time below: (Hours::Mins) "<<std::endl;
				std::cout<<"Hour:Minute-";
				std::cin>>i>>c1>>j;
				std::cin.clear();
				setTime(i,j);
			}
		}

		void setTime(const int h, const int m){
			int i, j; char c1;
			this->hour=h;
			this->mins=m;
			if(!isTimeCorrect()){
				std::cout<<"The Appointment Time is not correct. Input another Appointment Time below: (Hours::Mins) "<<std::endl;
				std::cout<<"Hour:Minute-";
				std::cin>>i>>c1>>j;
				std::cin.clear();
				setTime(i,j);
			}
		}

		bool isTimeCorrect(){
			if((hour>=AppointmentHourStart && hour<12)||(hour>=13 && hour<AppointmentHourEnd)){
				if(mins>=0 && mins<60){
					return true;
				}
			}
			return false;
		}

		int gethour()const{return hour;}
		int getmins()const{return mins;}
		int getTime_min() const{return (hour*60)+mins;}//returning time in minutes only Example 16.05=965mins

	private:
		int hour;
		int mins;
};

/*************************************Appointment*****************************/
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
	int hr1, hr2, min1, min2; char c1;
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

/****************************Person***************************************/
class Person{
	public:
		Person();
		Person(const std::string Name, const std::string Surname, const std::string Email, const int phone);
		virtual ~Person();

		void setPerson(const std::string Name, const std::string Surname, const std::string Email, const int phone);
		virtual void printInfo()const=0;

		std::string getName() const;
		std::string getSurname() const;
		std::string getEmail() const;
		int getPhone() const;

	private:
		std::string Name;
		std::string Surname;
		std::string Email;
		int Phone;
};

Person::Person(){
	this->Name="";
	this->Surname="";
	this->Email="";
	this->Phone=0;
}

Person::Person(const std::string Name, const std::string Surname, const std::string Email, const int phone){
	this->Name=Name;
	this->Surname=Surname;
	this->Email=Email;
	this->Phone=phone;
}

Person::~Person(){
}

void Person::setPerson(const std::string Name, const std::string Surname, const std::string Email, const int phone){
	this->Name=Name;
	this->Surname=Surname;
	this->Email=Email;
	this->Phone=phone;
}

std::string Person::getName() const{
	return Name;
}

std::string Person::getSurname() const{
	return Surname;
}

std::string Person::getEmail() const{
	return Email;
}

int Person::getPhone() const{
	return Phone;
}


/****************************Student***************************************/
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


/****************************Lecturer***************************************/
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


/**************************Appointment System********************************************/
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

AppointmentSystem::AppointmentSystem(){
	this->no_students=0;
	this->no_lecturers=0;
	this->no_Appointments=0;
}

AppointmentSystem::~AppointmentSystem(){
}

bool AppointmentSystem::findStudent(const int StudentNo){
	for(int i=0; i<no_students; i++){
		if(Students[i].getStudentNo()==StudentNo){
			return true;
		}
	}
	return false;
}

bool AppointmentSystem::findLecturer(const int EmployeeNo){
	for(int i=0; i<no_lecturers; i++){
		if(Lecturers[i].getEmployeeNo()==EmployeeNo){
			return true;
		}
	}
	return false;
}

bool AppointmentSystem::findAppointment(const int StudentNo, const int EmployeeNo){
	for(int i=0; i<no_Appointments; i++){
		if((Appointments[i].getStudentNo()==StudentNo)&&(Appointments[i].getEmployeeNo()==EmployeeNo)){
			return true;
		}
	}
	return false;
}

bool AppointmentSystem::Appointmentoverlap(const Lecturer &L,const Date &date,const Time &StartTime,const Time &FinishTime) const{
	int len=L.getno_Lec_Appointments();
	std::vector<Appointment> Lec_Appointments=L.getLec_Appointments();	//list containing a specific lecture's appointment

	int startTime_A=StartTime.getTime_min();
	int endTime_A=FinishTime.getTime_min();

	for(int i=0; i<len; i++){
		if(date.isEqual(Lec_Appointments[i].getDate())){

			int startTime_B=Lec_Appointments[i].getStartTime().getTime_min();
			int endTime_B=Lec_Appointments[i].getFinishTime().getTime_min();

			if(((startTime_A<=endTime_B)&&(endTime_A>=startTime_B))||((startTime_A>=endTime_B)&&(endTime_A<=startTime_B))){
				return true;
			}
		}
	}
	return false;
}


void AppointmentSystem::addStudent(const std::string Name, const std::string Surname, const std::string Email, const int phone,
						const int StudentNo,const std::string Dept, const int year)
{
	Students.resize(no_students+1);
	Students[no_students].setStudent(Name, Surname, Email, phone, StudentNo, Dept, year);
	no_students++;
}

void AppointmentSystem::addLecturer(const std::string Name, const std::string Surname, const std::string Email, const int phone,
						const int EmployeeNo, const std::string Dept, const std::string AcademicChair)
{
	Lecturers.resize(no_lecturers+1);
	Lecturers[no_lecturers].setLecturer(Name, Surname, Email, phone, EmployeeNo, Dept, AcademicChair);
	no_lecturers++;
}


void AppointmentSystem::addAppointment(const int StudentNo, const int LecturerNo, const int d, const int m, const int y,
						const int s_hr , const int s_min, const int f_hr, const int f_min)
{
	Date date(d,m,y);
	Time StartTime(s_hr,s_min);
	Time FinishTime(f_hr,f_min);
	if(findStudent(StudentNo)==true){	//If student is found in record
		if(findLecturer(LecturerNo)==true){		//If lecturer is found in record
			for(int i=0; i<no_lecturers; i++){
				if(Lecturers[i].getEmployeeNo()==LecturerNo){	//Finding Lecturer's Appointment List
					if(Appointmentoverlap(Lecturers[i], date, StartTime, FinishTime)){	//If time overlap with other appointments
						std::cout<<"Appointment Overlaps"<<std::endl;
						return;
					}
					else{
						//Adding to Lecturer's appointment list
						Lecturers[i].setAppointment(StudentNo, LecturerNo, date, StartTime, FinishTime);

						//Adding to Student's appointment list
						for(int j=0; j<no_students; j++){
							if(Students[j].getStudentNo()==StudentNo){
								Students[j].setAppointment(StudentNo, LecturerNo, date, StartTime, FinishTime);
								break;
							}
						}


						//Adding to General Appointment List
						Appointments.resize(no_Appointments+1);
						int index=Lecturers[i].getno_Lec_Appointments()-1;
						this->Appointments[no_Appointments]=Lecturers[i].getLec_Appointments()[index];
						no_Appointments++;
						std::cout<<"Appointment"<<no_Appointments<<" added"<<std::endl;
					}
					break;
				}
			}
		}
		else{
			std::cout<<"Lecturer not found"<<std::endl;
		}
	}
	else{
		std::cout<<"Student not found"<<std::endl;
	}
	return;
}

void AppointmentSystem::deleteStudent(const int StudentNo){
	int i;
	if (findStudent(StudentNo)){
		//Deleting The Student from the Students Record
		for(i=0; i<no_students; i++){
			if(Students[i].getStudentNo()==StudentNo){
				break;
			}
		}
		std::cout<<"Student:"<<Students[i].getName()<<" "<<Students[i].getSurname()<<" deleted"<<std::endl;
		Students.erase(Students.begin()+i);
		no_students--;

		//Deleting all appointments made by the student in Appointment Record
		for(int j=0; j<no_Appointments; j++){
			if(Appointments[j].getStudentNo()==StudentNo){
				Appointments.erase(Appointments.begin()+j);
				no_Appointments--;
				j=-1;
			}
		}

		//Deleting all appointments made by the student in each Lecturer's Appointment Record
		for(int k=0; k<no_lecturers; k++){
			Lecturers[k].deleteStudent_all_Appointment(StudentNo);
		}

	}
	else{
		std::cout<<"Student not Found in Record"<<std::endl;
		return;
	}
}

void AppointmentSystem::deleteLecturer(const int EmployeeNo){
	int i;
	if (findLecturer(EmployeeNo)){
		//Deleting Lecturer from Lecturers Record
		for(i=0; i<no_lecturers; i++){
			if(Lecturers[i].getEmployeeNo()==EmployeeNo){
				break;
			}
		}
		std::cout<<"Lecturer:"<<Lecturers[i].getName()<<" "<<Lecturers[i].getSurname()<<" deleted"<<std::endl;
		Lecturers.erase(Lecturers.begin()+i);
		no_lecturers--;

		//Deleting all appointments made to the Lecturer
		for(int j=0; j<no_Appointments; j++){
			if(Appointments[j].getEmployeeNo()==EmployeeNo){
				Appointments.erase(Appointments.begin()+j);
				no_Appointments--;
				j=-1;
			}
		}

		//Deleting all appointments made by the student in each Student's Appointment Record
		for(int k=0; k<no_students; k++){
			Students[k].deleteall_AppointmenttoLecturer(EmployeeNo);
		}
	}
	else{
		std::cout<<"Lecturer not Found in Record"<<std::endl;
		return;
	}
}

void AppointmentSystem::deleteAppointment(const int StudentNo, const int EmployeeNo){
	int i;
	if(findAppointment(StudentNo, EmployeeNo)){
		for(i=0; i<no_Appointments; i++){
			if((Appointments[i].getStudentNo()==StudentNo)&&(Appointments[i].getEmployeeNo()==EmployeeNo)){
				for(int j=0; j<no_lecturers; j++){
					if(Lecturers[j].getEmployeeNo()==EmployeeNo){
						Lecturers[j].deleteStudentAppointment(StudentNo);
						break;
					}
				}

				for(int k=0; k<no_students; k++){
					if(Students[k].getStudentNo()==StudentNo){
						Students[k].deleteAppointmenttoLecturer(EmployeeNo);
						break;
					}
				}

				break;
			}
		}
		std::cout<<"Appointment Deleted"<<std::endl;
		Appointments.erase(Appointments.begin()+i);
		no_Appointments--;
	}
	else{
		std::cout<<"Appointment not Found in Record"<<std::endl;
	}
}

void AppointmentSystem::listStudent() const{
	if(no_students==0){
		std::cout<<"Students Record is Empty record"<<std::endl;
		return;
	}
	for(int i=0; i<no_students; i++){
		std::cout<<"Student"<<i<<std::endl;
		Students[i].printInfo();
	}
	std::cout<<"............................................."<<std::endl;
}

void AppointmentSystem::listLecturer() const{
	if(no_lecturers==0){
		std::cout<<"Lecturers Record is Empty"<<std::endl;
		return;
	}
	for(int i=0; i<no_lecturers; i++){
		std::cout<<"Lecturer"<<i<<std::endl;
		Lecturers[i].printInfo();
	}
	std::cout<<"............................................."<<std::endl;
}

void AppointmentSystem::listAppointment() const{
	if(no_Appointments==0){
		std::cout<<"Appointment Record is Empty"<<std::endl;
	}
	for(int i=0; i<no_Appointments; i++){
		std::cout<<"Appointment"<<i<<std::endl;
		Appointments[i].printAppointment();
	}
	std::cout<<"............................................."<<std::endl;
}

std::string AppointmentSystem::removeTokenFromLine(const std::string line){
	std::string output;
    for(int j=0; j<line.length(); j++){
        if(line[j]=='.'||line[j]==':'){
            output+=' ';
        }
        else{
            output+=line[j];
        }
    }
    return output;
}

void AppointmentSystem::getInfoFromDocuments(std::ifstream& studentsFile, std::ifstream& lecturersFile, std::ifstream& appointmentFile){
	std::string Name, Surname, email, Department, position;
	int phone, StudentNo, year, EmployeeNo, d, m, y, S_hr, S_min, E_hr, E_min;

	if(studentsFile.is_open()){
        while (true){
            studentsFile>>Name;
            studentsFile>>Surname;
            studentsFile>>email;
            studentsFile>>phone;
            studentsFile>>StudentNo;
            studentsFile>>Department;
            studentsFile>>year;
            if(studentsFile.eof()){break;}
            addStudent(Name, Surname, email, phone, StudentNo, Department, year);
        }
    }
    else{
        std::cout<<"Students Document not found"<<std::endl;
    }

    if(lecturersFile.is_open()){
        while (true){
            lecturersFile>>Name;
            lecturersFile>>Surname;
            lecturersFile>>email;
            lecturersFile>>phone;
            lecturersFile>>EmployeeNo;
            lecturersFile>>Department;
            lecturersFile>>position;
            if(lecturersFile.eof()){break;}
            addLecturer(Name, Surname, email, phone, EmployeeNo, Department, position);
        }
    }
    else{
        std::cout<<"Lecturers Document not found"<<std::endl;
    }

    //Removing : and . from Appointment File
    std::ofstream outData;
    outData.open("ManipulatedData",std::ios::out);

    if(appointmentFile.is_open()){
        std::string line;
        while (std::getline(appointmentFile, line)){
            line=removeTokenFromLine(line);
            outData<<line<<std::endl;
        }
    }
    else{
        std::cout<<"Document not found"<<std::endl;
    }
    //After : and . has been removed, the document is saved in a text file-ManipulatedData

    //Getting the data from the ManipulatedData File
    std::ifstream appointmentFile2;
    appointmentFile2.open("ManipulatedData",std::ios::in);
    if(appointmentFile2.is_open()){
        while (true){
            appointmentFile2>>StudentNo;
            appointmentFile2>>EmployeeNo;
            appointmentFile2>>d;
            appointmentFile2>>m;
            appointmentFile2>>y;
            appointmentFile2>>S_hr;
            appointmentFile2>>S_min;
            appointmentFile2>>E_hr;
            appointmentFile2>>E_min;
            if(appointmentFile2.eof()){break;}

            addAppointment(StudentNo, EmployeeNo, d, m, y, S_hr, S_min, E_hr, E_min);
        }
    }
    else{
        std::cout<<"Document not found"<<std::endl;
    }
}

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
    Std.open("Students",std::ios::in);
    Lec.open("Lecturers",std::ios::in);
    App.open("Appointments",std::ios::in);

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
	std::cout<<"here...."<<std::endl;

}
