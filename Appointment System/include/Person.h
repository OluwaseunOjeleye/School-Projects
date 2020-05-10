/****************************Person***************************************/
#ifndef PERSON_H_
#define PERSON_H_

#include <string>

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

#endif
