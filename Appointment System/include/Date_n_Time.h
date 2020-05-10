#ifndef DATE_N_TIME_H_
#define DATE_N_TIME_H_

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
					else if(month==4||month==6||month==9||month==11){
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

#endif