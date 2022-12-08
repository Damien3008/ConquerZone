#pragma once

#include <iostream>
    using namespace std;
#include <string>
#include <fstream>


// ILoggable abstract class, all derived classes must implement stringToLog()
class ILoggable
{
public:
	ILoggable(); // Default constructor 
	ILoggable(const ILoggable& s); // Copy constructor 
	ILoggable& operator=(const ILoggable& s); // Assignment operator
	friend ostream& operator<<(ostream& os, const ILoggable& s); // Stream insertion operator 
	virtual string stringToLog() = 0; // pure virtual class. Implemented by a derived class, must return a string that represents the class
};

// Observer abstract class
class Observer
{
public:
	Observer(); // Default constructor 
	Observer(const Observer& s); //Copy constructor 
	Observer& operator=(const Observer& s); // Assignment operator 
	friend ostream& operator<<(ostream& os, const Observer& s); // Stream insertion operator 
	virtual void Update(ILoggable* _loggable_object) = 0; // Abstract Update method to be defined by LogObserver
};

// Observer implementation class which outputs to the log file
class LogObserver : public Observer
{
public:
	LogObserver(); // Default constructor 
	LogObserver(const LogObserver& s); // Copy constructor 
	LogObserver& operator=(const LogObserver& s); // Assignment operator 
	friend ostream& operator<<(ostream& os, const LogObserver& s); // Stream insertion operator 
	void Update(ILoggable* _loggable_object); // Will output the stringToLog implementation from a derived class of ILoggable into the log file
};

// Subject class, all derived classes can Attach() or Detach() itself from the observer
// Houses Notify() which calls the Observer's (implemented) update method
class Subject
{
public:
	Subject(); // Default constructor 
	~Subject(); // Destructor .. should NOT delete Observer, only set local observer object to nullptr
	Subject(const Subject &s); // Copy constructor 
	Subject& operator=(const Subject& s); // Assignment operator 
	friend ostream& operator<<(ostream& os, const Subject& s); // Stream insertion operator 
	void Attach(Observer* _logger); // Attaches this class to the observer object
	void Detach(); // Detaches this class from the observer object
	void Notify(ILoggable* _loggable_object); // Calls the update method in Observer/LogObserver
private:
	Observer* _observer = nullptr; // Observer object
};