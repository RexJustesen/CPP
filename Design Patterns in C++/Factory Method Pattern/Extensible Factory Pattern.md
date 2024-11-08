### Recap
- We have been using the factory to abstract the creation of objects. This is to avoid using the *new* keyword for creating objects directly. 
- Previously we looked at ways to add power to the factory method. Please refer to [[Factory Method Pattern]] and [[Factory Method Pattern - Adding More Power for Counting Allocated Objects]] 


### The Extensible Factory
- This solves the problem of "what if your user wants to create other types"
- Through some plugin or other method a user can create a new type 

![[Pasted image 20241108093854.png]]

- How can we ensure that this user defined type is registered and the factory will perform correctly?
- For more notes on this check out [Modern C++ Design](https://amzn.to/3UIoyzO)

### Implementation Example 

- We will be starting from the last example from [[Factory Method Pattern - Adding More Power for Counting Allocated Objects]], I will paste the code below.
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

- What is different now is that our derived classed will now have a static **Create** member function which returns a new plane or new boat object. 
- What this allows us to do is if a user creates their own type is to implement the Create Member function as a callback to instruct how to create a new class. 

### Example organization

- We will now be organizing our code into separate files for this exercise. The following files will be made 
	- Factory.hpp
	- Factory.cpp
	- GameObjects.hpp
	- GameObjects.cpp
- I am using [Visual Studio Community Version](https://visualstudio.microsoft.com/downloads/) on windows. 
- To create a *.hpp* file in Visual Studio right click in the solution explorer of your C++ console application project, click Add-> New Item...
- This will bring a pop up to choose what file you want to create. Click on **Header file (.h)** 
- In the bottom of the pop up modal where it says **Name** change the name of the file to **Factory.hpp**, this will create a *.hpp* file even though it was a *.h* file to begin with. 
- Do this for creating a *.cpp* file as well for Factory and then repeat the process for the GameObjects files. 


	GameObjects.hpp 
	- Here is the code for the GameObjects.hpp file 
```c++
#define GAMEOBJECTS_HPP

class IGameObject{
	public:
	// Ensure derived classes call
	// the correct destrcutor (i.e., top of the chain)
	virtual ~IGameObject() {}
	//Pure Virtual Functions thate must be
	//implemented by the dervided classes
	//we are adding some new functions to make it seem more like a game
	//being developed
	virtual void ObjectPlayDefaultAnimation() = 0;
	virtual void ObjectMoveInGame() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
}

class Plane : public IGameObject{
	public:
	Plane(int x, int y){ // x and y are like a default starting position in a game
		ObjectsCreated++;
	}
	void ObjectPlayDefaultAnimation(){/* ... */}
	void ObjectMoveInGame(){/* ... */}
	void Update(){/* ... */}
	void Render(){/* ... */}
	// create object static member function that can be used as a callback
	static IGameObject* Create(){
		return new Plane(0.0)
	}
	private:
		static int ObjectsCreated;
}

class Boat : public IGameObject{
	public:
	Boat(int x, int y){ // x and y are like a default starting position in a game
		ObjectsCreated++;
	}
	void ObjectPlayDefaultAnimation(){/* ... */}
	void ObjectMoveInGame(){/* ... */}
	void Update(){/* ... */}
	void Render(){/* ... */}
	// create object static member function
	static IGameObject* Create(){
		return new Boat(0.0)
	}
	private:
		static int ObjectsCreated;
}

#endif
```

- We have added some new methods but they are not implemented, this is to just make it seem more like we are creating a game. 
- The Main difference is the static Create() method which is not part of the parent class IGameObject and is used as the callback method for new types to be created by users and allows the factory to be extensible. 

#### Factory.hpp
- We will now go over the method to be implemented in the extensible factory. The Factory.hpp simply has the definitions and parameters requires but not the full implementation yet. that will be done in the Factory.cpp file. 
- The first thing we do is a simple **typedef** which is a type definition or a callback function that returns **IGameObject** pointers
```c++
typedef IGameObject *(*CreateObjectCallback)();
```

- The key idea  in the **RegisterObject** Member function is to take in the type name and have a new type of object our factory can create and then take the Call back function that returns a pointer to some IGameObject as the second paramater. 

```c++
static void RegisterObject(const std::string& type, CreateObjectCallback cb);
```
- We need a callback map to help us do this which is a cool trick to make it a little easier where we have a map with our type name and our callback
```c++
//convenienc typedef
typedef std::map<std::string, CreateObjectCallback> CallBackMap;
// map of all the different types of objects that can be created
static CallBackMap s_Objects;
```

- Why do we want to structure thing this way with this map?
### Example of map 
- Map data structure

| First param | Second param |
| ----------- | ------------ |
| "Plane"     | Create()     |
| "Boat"      | Create()     |
| "New Type"  | Create()     |
- This is what is getting stored in our map so that we can call the exact function to return the new type for us. 
- This makes the functions like RegisterObject and 