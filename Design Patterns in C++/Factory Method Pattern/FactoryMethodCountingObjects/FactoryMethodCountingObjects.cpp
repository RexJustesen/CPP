#include <iostream>
#include <string>
#include <memory>

class IGameObject {
public:
	virtual ~IGameObject() {} //Destructor 
	virtual void Update() = 0; //purely virtual functions so derived classes must implement them. 
	virtual void Render() = 0;
};

class Plane : public IGameObject {
public:
	Plane() { std::cout << "Created Plane\n"; } //constructor
	void Update() {}
	void Render() {}
};

class Boat : public IGameObject {
public:
	Boat() { std::cout << "Created Boat\n"; } //constructor
	void Update() {}
	void Render() {}

};

//Create enum for plane and boat
enum class ObjectType { PLANE, BOAT };

// New Factory class 
class FactoryGameObjects {

public:
	// remember a key part of the singleton pattern is to make the member functions static
	// we will also rename the memeber function to be more specific to its functionality as the class is now called FactoryGameObjects
	static std::shared_ptr<IGameObject> CreateObject(ObjectType type) {
		if (ObjectType::PLANE == type) {
			//increment counter variable for plane class 
			s_plane++;
			return std::make_shared<Plane>();
		}
		else if (ObjectType::BOAT == type) {
			//increment counter variable for boat class 
			s_boat++;
			return std::make_shared<Boat>();
		}
		return nullptr; // return nullptr to supress warnings 
	}

	//function to print the counts of objects instantiated
	static void PrintCounts() {
		std::cout << "Number of Plane objects: " << s_plane << std::endl;
		std::cout << "Number of boat objects: " << s_boat << std::endl;
	}
	// private constructor for a singleton class 
private:
	FactoryGameObjects() {}
	~FactoryGameObjects() {}
	FactoryGameObjects(const FactoryGameObjects& o) {}

	// variables to keep track of the count of each object 
	static int s_plane;
	static int s_boat;

};

//initialize variables to 0 
int FactoryGameObjects::s_plane = 0;
int FactoryGameObjects::s_boat = 0;


int main() {
	// we can now use the singleton class of the factory method in the main function 
	std::shared_ptr<IGameObject> myObject = FactoryGameObjects::CreateObject(ObjectType::PLANE);
	std::shared_ptr<IGameObject> myObject2 = FactoryGameObjects::CreateObject(ObjectType::BOAT);
	std::shared_ptr<IGameObject> myObject3 = FactoryGameObjects::CreateObject(ObjectType::BOAT);

	//print the number of instances of each object
	FactoryGameObjects::PrintCounts();
	return 0;
}