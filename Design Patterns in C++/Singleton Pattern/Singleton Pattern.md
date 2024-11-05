### Thoughts on the Singleton Pattern
- Singleton pattern has the programming community divided. 
- Some say it is a bad pattern, others think it is a great design pattern. 
- All patterns have trade offs and you need to think about what you get out of the singleton pattern and the lifetime of your program.

### What is the Singleton Pattern?

- It is a creational design pattern which means it is concerned with how we create objects 
- It allows or enforces only the creation of on instance of an object in your program
- How do we enforce this? 
- These singleton classes are typically something like a logger or a file manager, something that you want to only create once and use throughout the program. 
- If we have a constructor and a destructor we typically want a copy constructor and assignment operator as well 

### Example of Non-Singleton class

```c++
#include <iostream>
class Logger{
public:
	Logger(){ // constructor
		std::cout << "Logger was create\n";
	}
	~Logger(){
		std::cout<< "Logger was Destructed";
	}

};

int main(){
	// this will create 4 instances of the Logger so there are 4 instance of the logger class. 
	Logger logger1;
	Logger logger2;
	Logger logger3;
	Logger logger4
	return 0;
}
```

### How to enforce one instance 
- You can change the constructor and destructor methods to private. 
- Now this code will throw a bunch of errors since the constructor is private it prevents object creation but shows that we can control object creation. 
```c++
#include <iostream>
class Logger{
private:
	Logger(){ // constructor
		std::cout << "Logger was create\n";
	}
	~Logger(){
		std::cout<< "Logger was Destructed";
	}

};

int main(){
	// this will create 4 instances of the Logger so there are 4 instance of the logger class. 
	Logger logger1;
	Logger logger2;
	Logger logger3;
	Logger logger4
	return 0;
}
```

- Instead of creating the object through the constructor, we wil instead have a separate public member function where the creation is done. 
- Typically you will have a **GetInstance** function that retrieves the single instance of the object created and will enforce the creation of only one of these objects in your code. 
- The handy keyword that is helpful for handling this in C and C++ is the **Static** keyword 
- What static controls is the lifetime or duration of some variable 

### Example of Static 

```c++
#include <iostream>

void counter(){
	static int i=0;
	std::cout << "i is: " << i << std::endl;
	i++
}

void counter2(){
	int i = 0;
	std::cout << "i is: " << i << std::endl;
	i++;
}

int main(){
	counter(); // displays 0
	counter(); // displays 1
	counter(); // displays 2
	counter(); // displays 3
	counter2(); // displays 0
	counter2(); // displays 0
	counter2(); // displays 0
	counter2(); // displays 0
	return 0;
}
```

- Since we did not use static in the function *counter2* the variable *i's* value is not preserved. Static in the *counter* function initializes *i* once and updates the value every time the *counter* function is called. So the static variable remains for the duration of the program. 
- We can make use of the *static* keyword to create a singleton object .

```c++
#include <iostream>
class Logger{
public:
	Logger(){ // constructor
		std::cout << "Logger was created" << numberOfLoggers << "times \n";
		numberOfLoggers++;
	}

	~Logger(){
		std::cout<< "Logger was Destructed";
	}
	
	static int numberOfLoggers;

};

int Logger::numberOfLoggers = 0;

int main(){
	// this will create 4 instances of the Logger so there are 4 instance of the logger class. 
	Logger logger1;
	Logger logger2;
	Logger logger3;
	Logger logger4
	return 0;
}
```

#### Output of above code 
```bash
Logger was created 0 times
Logger was created 1 times
Logger was created 2 times
Logger was created 3 times
Logger was Destructed
Logger was Destructed
Logger was Destructed
Logger was Destructed
```

- We still do not have singleton but we know how to use the static variable. 
- So we can use static to create a pointer to the instance of the Logger class. 
- We make the GetInstance function static as a singleton's instance is accessible by all other classes in the program. 
- We can now make an instance of the Logger class and GetInstance and access the method printMessage
```c++
#include <iostream>
class Logger{
public:
	static Logger* GetInstance(){ //Get instance function is static as it is shared amongst all classes
		return s_instance;
	}

	//add a member function to test instance of logger singleton
	void printMessage() {
		std::cout << "Accessing the log" << std::endl;
	}

private:
	Logger(){ // constructor
		std::cout << "Logger was created" << "\n";
	}
	
	~Logger(){
		std::cout<< "Logger was Destructed";
	}
	
	static Logger* s_instance; 

};

Logger* Logger::s_instance = nullptr;

int main(){
	Logger::GetInstance()->printMessage();
	return 0;
}
```


- Now we can add more functionality to the Logger class to see the power of a the singleton. 
- We will create an addMessage method to take a string as a parameter.
- We will use a vector to add **log** the messages and store some information
- We also have to provide an allocation for the logger as the pointer to the logger is pointing to **nullptr**. We do this in the **GetInstance** function
```c++
#include <iostream>
#include <string>
#include <vector>

class Logger{
public:
	static Logger* GetInstance(){ //Get instance function is static as it is shared amongst all classes
		if(s_instance==nullptr){
			s_instance = new Logger; //allocate the logger on the heap
		}
		return s_instance;
	}

	//add a member function to test instance of logger singleton
	void printMessages() {
		std::cout << "Accessing the log" << std::endl;
		// print the messages
		for(auto& e: m_messages){
			std::cout<< e << std::endl;
		}
	}

	//store the messages in the m_messages vector
	void addMessage(std::string s){
		m_messages.push_back(s);
	}

private:
	Logger(){ // constructor
		std::cout << "Logger was created" << "\n";
	}
	
	~Logger(){
		std::cout<< "Logger was Destructed";
	}
	
	static Logger* s_instance; 
	std::vector<std::string> m_messages; // create vector  to store messages

};

Logger* Logger::s_instance = nullptr;

int main(){
	//Now we can add messages to our singleton instance of the logger and then pring the message vector. 
	Logger::GetInstance()->addMessage("Hello, Message1");
	Logger::GetInstance()->addMessage("Hello, Message2");
	Logger::GetInstance()->addMessage("Hello, Message3");
	Logger::GetInstance()->printMessages();
	return 0;
}
```

### Output of the code above
```bash
Logger was created
Accessing the log
Hello, Message1
Hello, Message2
Hello, Message3
```

### Recap of the singleton class just created 
- We have made a singleton in just a few lines of code
- Remember the key points:
	- We have a static variable **static Logger* s_instance*** 
	- We have a static member function **static Logger* GetInstance*** that accesses the static variable which is the one and only instance of our class as it can only be null once and we create the one Logger in this static member function. 

- There are some slight problem with this implementation. 
	- What if we call just **Logger::GetInstance()**? we are retrieving a Logger object here
	- Would it be possible to create another point called pointer to logger and point it to the Logger? **Logger* pointer_to_Logger = Logger::GetInstance()***
	- And if I can do this is it possible to delete my single instance of the Logger? **delete pointer_to_Logger** 
	- The Destructor is private so we cannot do this but if we did not make the destructor private we absolutely could have deleted the singleton of Logger.

### Improvements to the Logger Singleton
- You want to discourage any mischievous behavior because if the instance of the Logger can be deleted it will cause a segmentation fault. 

#### Refactor Logger Class
- Move the instantiazion of the static Logger instance inside the GetInstance member function. 

```c++
#include <iostream>
#include <string>
#include <vector>

class Logger {
public:
	static Logger& GetInstance() { //Get instance function is static as it is shared amongst all classes
		static Logger* s_instance = new Logger; // moved static instantiaion of logger to GetInstance member function, it is guaranteed to be called once
		//no derefernec the instance in the return
		return *s_instance;
	}

	//add a member function to test instance of logger singleton
	void printMessages() {
		std::cout << "Accessing the log" << std::endl;
		// print the messages
		for (auto& e : m_messages) {
			std::cout << e << std::endl;
		}
	}

	//store the messages in the m_messages vector
	void addMessage(std::string s) {
		m_messages.push_back(s);
	}

private:
	Logger() { // constructor
		std::cout << "Logger was created" << "\n";
	}

	~Logger() {
		std::cout << "Logger was Destructed";
	}

	std::vector<std::string> m_messages; // create vector  to store messages

};


int main() {
	//Now we can add messages to our singleton instance of the logger and then pring the message vector.
	//no we can use the "." operator as we already derefernced in the GetInstance function. 
	Logger::GetInstance().addMessage("Hello, Message1");
	Logger::GetInstance().addMessage("Hello, Message2");
	Logger::GetInstance().addMessage("Hello, Message3");
	Logger::GetInstance().printMessages();
	return 0;
}
```

### Future considerations 
- If you have a multithreaded program you may want to consider wrapping the instance in a mutex or some sort of locking mechanism to make sure it is thread safe. 

- Consider tradeoffs for managing large states or using a singleton as a resource manager. 

