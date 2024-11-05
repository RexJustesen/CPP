#include <iostream>
#include <string>
#include <vector>

class Logger {
public:
	static Logger& GetInstance() { //Get instance function is static as it is shared amongst all classes
		static Logger* s_instance = new Logger; // moved static instantiaion of logger to GetInstance member function, it is guaranteed to be called once
		//now derefernece the instance in the return
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