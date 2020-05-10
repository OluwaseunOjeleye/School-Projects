#include "include/AppointmentSystem.h"

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
