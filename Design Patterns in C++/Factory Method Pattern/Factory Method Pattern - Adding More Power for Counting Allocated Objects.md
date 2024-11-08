- We will be starting from the last example in [[Factory Method Pattern]] for this lesson.
- We will be adding on to the factory method pattern. 
- We want to add a simple addition to our factory method to give more capabilities. 
- This will involve wrapping the factory method into a singleton class. 
- You can make it a regular class if you choose to do so as there are some opinions on singletons. some people are for and other against so at the end of the day it is up to you. 
- The main thing we want to show is that we can get more power our of our factory method if we start wrapping and abstracting the factory method. 
- The type of power we will add is to count how many of the objects we have created. 
- This will add more data driven decisions and processes as we will know how many of each object exists at once. 

### Example. 
- We will create a new class in the previous code from [[Factory Method Pattern]] called **FactoryGameObjects** and we will move the **MakeGameObjectFactory** method into this class. 
- Remember from [[Singleton Pattern]] to use the singleton pattern we make the constructor private
- You can go a few levels further and make sure we do not have a copy constructor. 
```c++
#include <iostream>
#include <string>
#include <memory>

class IGameObject{
public:
	virtual ~IGameObject() {} //Destructor 
	virtual void Update() = 0; //purely virtual functions so derived classes must implement them. 
	virtual void Render() = 0;
};

class Plane: public IGameObject{
public:
	Plane(){ "Created Plane" } //constructor
	void Update() {}
	void Render() {}
};

class Boat: public IGameObject{
public:
	Boat(){ "Created Boat" } //constructor
	void Update() {}
	void Render() {}

};

//Create enum for plane and boat
enum class ObjectType {PLANE, BOAT};

// New Factory class 
class FactoryGameObjects{

public:
	// remember a key part of the singleton pattern is to make the member functions static
	// we will also rename the memeber function to be more specific to its functionality as the class is now called FactoryGameObjects
	static std::shared_ptr<IGameObject> CreateObject(ObjectType type){
		if(ObjectType::PLANE == type){
			return std::make_shared<Plane>();
		}else if(ObjectType::BOAT == type){
			return std::make_shared<Boat>();
		}
		return nullptr; // return nullptr to supress warnings 
	}
// private constructor for a singleton class 
private:
	FactoryGameObjects(){}
	~FactoryGameObjects() {}
	FactoryGameObjects(const FactoryGameObjects& o){}
	
};



int main(){
	// we can now use the singleton class of the factory method in the main function 
	std::shared_ptr<IGameObject> myObject = FactoryGameObjects::CreateObject(ObjectType::PLANE);
	return 0;
}
```

- Now that we have our factory working we can start to count our objects. 
- We will create another static function called print counts.
- In the private section of the Factory class we will create static integer variable to keep track of the count of objects instantiated through the factory. 
```c++
#include <iostream>
#include <string>
#include <memory>

class IGameObject{
public:
	virtual ~IGameObject() {} //Destructor 
	virtual void Update() = 0; //purely virtual functions so derived classes must implement them. 
	virtual void Render() = 0;
};

class Plane: public IGameObject{
public:
	Plane(){ std::cout<< "Created Plane\n"; } //constructor
	void Update() {}
	void Render() {}
};

class Boat: public IGameObject{
public:
	Boat(){ std::cout<< "Created Boat\n"; } //constructor
	void Update() {}
	void Render() {}

};

//Create enum for plane and boat
enum class ObjectType {PLANE, BOAT};

// New Factory class 
class FactoryGameObjects{

public:
	// remember a key part of the singleton pattern is to make the member functions static
	// we will also rename the memeber function to be more specific to its functionality as the class is now called FactoryGameObjects
	static std::shared_ptr<IGameObject> CreateObject(ObjectType type){
		if(ObjectType::PLANE == type){
			//increment counter variable for plane class 
			s_plane++;
			return std::make_shared<Plane>();
		}else if(ObjectType::BOAT == type){
			//increment counter variable for boat class 
			s_boat++;
			return std::make_shared<Boat>();
		}
		return nullptr; // return nullptr to supress warnings 
	}

	//function to print the counts of objects instantiated
	static void PrintCounts(){
		std::cout << "Number of Plane objects: " << s_plane << std::endl;
		std::cout << "Number of boat objects: " << s_boat << std::endl;
	}
// private constructor for a singleton class 
private:
	FactoryGameObjects(){}
	~FactoryGameObjects() {}
	FactoryGameObjects(const FactoryGameObjects& 0 ){}

	// variables to keep track of the count of each object 
	static int s_plane;
	static int s_boat;
	
};

//initialize variables to 0 
int FactoryGameObjects::s_plane = 0;
int FactoryGameObjects::s_boat = 0;


int main(){
	// we can now use the singleton class of the factory method in the main function 
	std::shared_ptr<IGameObject> myObject = FactoryGameObjects::CreateObject()bjectType::PLANE);
	std::shared_ptr<IGameObject> myObject2 = FactoryGameObjects::CreateObject(ObjectType::BOAT);
	std::shared_ptr<IGameObject> myObject3 = FactoryGameObjects::CreateObject(ObjectType::BOAT);

	//print the number of instances of each object
	FactoryGameObjects::PrintCounts();
	return 0;
}
```

- When you run this code you will get the following output:
```bash
Created Plane
Created Boat
Created Boat
Number of Plane objects: 1
Number of boat objects: 2
```

### Further thinking 
- One thing you might be wondering is figuring out how many active objects we have. 
- Right now we know how many planes or boats we have built at a specific time. 
- However since we are using *shared_ptr* we don't have a good way to know if an object has been deleted. 
- So what we can do is to check a particular object to see if it  is null at some point and reduce our count at that time. 
- this method is kind of forced and not very dynamic so we probably want to find another way to go about this by using another type of data structure. 
- We can try to use an adapter that wraps the *shared_ptr* and have it as part of the constructor or destructor and keep track of the instances of the objects and increment or decrement it
```c++
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

// implement adapter class 
class MyCountedSharedPointer{
public:
	MyCountedSharedPointer(ObjectType type){
	// implement counter logic here and wrap the object creation with this adapter 
	}
	~MyCountedSharedPointer(ObjectType type){
	}
private:
	std::shared_ptr<IGameObject> pinter;
};

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
```

- You can also make use of weak pointers and keep a list of weak pointers to the objects and iterate through the list to see where they are null and keep track that way. 
- Any additional functionality to design patterns always need to take in consideration what is best for the project. 
