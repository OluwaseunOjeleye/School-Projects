#include "include/Person.h"

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