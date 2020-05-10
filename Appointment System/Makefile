##To make file type make
CC = g++
CFLAGS = -g -Wall -Iinclude

HEADER = include/Date_n_Time.h include/Appointment.h include/Person.h include/Student.h include/Lecturer.h include/AppointmentSystem.h

SRCS= Appointment.cpp Person.cpp Student.cpp Lecturer.cpp AppointmentSystem.cpp main.cpp

OBJS = $(SRCS:.c++=.o)

MAIN = main

.PHONY: depend clean

all:    $(MAIN)
		@echo  Message: executable file ...main... has been created

$(MAIN): $(OBJS) 
		$(CC) $(CFLAGS) $(HEADER) -o $(MAIN) $(OBJS)

.c++.o:
		$(CC) $(CFLAGS) $(HEADER) -cpp $<  -o $@

clean:
		$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
		makedepend $(HEADER) $^