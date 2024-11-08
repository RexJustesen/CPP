### What is it? 
- It is very specific as it is a method or a function that is implemented. 
- The **Factory Method Pattern** provides a generalized way to create instances of an object and can be a great way to hid implementation details for derived class 
- *Remember*: a *derived class* is a class that is created by inheriting from an existing class, called the *base class*, often related with the terminology *parent class* and *child class*. The derived class inherits the properties (data members) and behaviors (member functions) of the base class, allowing it to reuse and extend the functionality of the base class. 

### Things to keep in mind 
- The Factory method pattern is another creational design pattern
- Creational design patterns area way to abstract or make safer the creation of objects
- The idea of this generalized way to create instances of objects with the factory method is so that we are hiding implementation or details of derived classes with a method or function. 

### What problem is the factory method pattern trying to solve?

##### Example 
- Lets say we have some type like **GameObject**** as a pointer because we want to determine the type at run time and we explicitly assign it to an object
```c++
GameObject* obj = new ObjectType;
```
- This is the kind of implementation we want to avoid. We don't want clients of our interface or implementers who are working on our code to have to make this decision of allocating our objects. 
- What we want is some function where can provide an input *to a factory method* and get the correct output. Like sending raw materials to a factory in real life to get a product. You don't know how the factory has set up their assembly line, what machines they have all you care about is getting your product in a timely and correct manner. 
![[Pasted image 20241107100031.png]]

### Implementation 
- The Key part of this pattern is to use inheritance and particularly polymorphism. so inheritance based polymorphism. 
- So we create an interface and derive classes from it. 
![[Pasted image 20241107100539.png]]

##### Implementing interface
- We can start with a simple interface *IGameObject* 
  *Note*: It is standard convention to start the names of interface with **I** 

```c++
class IGameObject{
public:
	virtual ~IGameObject() {} //Destructor 
	virtual void Update() = 0; //purely virtual functions so derived classes must implement them. 
	virtual void Render() = 0;
};

int main(){

	return 0;
}
```

- We can make a **Plane** class and a **Boat** class to derive from **IGameObject** 

```c++
class IGameObject{
public:
	virtual ~IGameObject() {} //Destructor 
	virtual void Update() = 0; //purely virtual functions so derived classes must implement them. 
	virtual void Render() = 0;
};

class Plane: public IGameObject{
public:
	Plane(){} //constructor
	void Update() {}
	void Render() {}
};

class Boat: public IGameObject{
public:
	Boat(){} //constructor
	void Update() {}
	void Render() {}

};

int main(){
	// instantiate Plane and Boat 
	// remember as we move into the implementation of the factory method pattern
	// we want to avoid making decision about which object we are creating in
	// our code. We want to be going through the IGameObject interface for each
	// of our objects. 
	Boat b;
	Plane p;
	return 0;
}
```
- Lets no create the factory method so we can now abstract the creation of our objects. This removes the concern or decision about what object to create and instead we will be using the IGameObject interface for the instantiation of our objects through the factor method. 

```c++
#include <iostream>
#include <string>

class IGameObject{
public:
	virtual ~IGameObject() {} //Destructor 
	virtual void Update() = 0; //purely virtual functions so derived classes must implement them. 
	virtual void Render() = 0;
};

class Plane: public IGameObject{
public:
	Plane(){} //constructor
	void Update() {}
	void Render() {}
};

class Boat: public IGameObject{
public:
	Boat(){} //constructor
	void Update() {}
	void Render() {}

};

// create factory method that return type IGameObject or a pointer to IGameObject
// we will start off with something simple so we will make the parameter a string
IGameObject* MakeGameObjectFactory(std::string type){
	if(type =="plane"){
		return new Plane;
	}else if(type == "boat"){
		return new boat;
	}
}

int main(){
	//we can now determine at runtime what objects we want to create. 
	IGameObject* myObject = MakeGameObjectFactory("plane");
	return 0;
}
```

#### Things to think about right now 
- If you run this program you need to think about where the ownership of this object is? It is probably a good idea to delete the object at the end of the program 
```c++
#include <iostream>
#include <string>

class IGameObject{
public:
	virtual ~IGameObject() {} //Destructor 
	virtual void Update() = 0; //purely virtual functions so derived classes must implement them. 
	virtual void Render() = 0;
};

class Plane: public IGameObject{
public:
	Plane(){} //constructor
	void Update() {}
	void Render() {}
};

class Boat: public IGameObject{
public:
	Boat(){} //constructor
	void Update() {}
	void Render() {}

};

// create factory method that return type IGameObject or a pointer to IGameObject
// we will start off with something simple so we will make the parameter a string
IGameObject* MakeGameObjectFactory(std::string type){
	if(type =="plane"){
		return new Plane;
	}else if(type == "boat"){
		return new boat;
	}
}

int main(){
	//we can now determine at runtime what objects we want to create. 
	IGameObject* myObject = MakeGameObjectFactory("plane");

	delete myObject;
	return 0;
}
```

- There are still a few problems. We have completed our first factory but there are a few issues. 
- We need to return some sort of type outside of the if, else if block in the factory method.

```c++
#include <iostream>
#include <string>

class IGameObject{
public:
	virtual ~IGameObject() {} //Destructor 
	virtual void Update() = 0; //purely virtual functions so derived classes must implement them. 
	virtual void Render() = 0;
};

class Plane: public IGameObject{
public:
	Plane(){} //constructor
	void Update() {}
	void Render() {}
};

class Boat: public IGameObject{
public:
	Boat(){} //constructor
	void Update() {}
	void Render() {}

};

// create factory method that return type IGameObject or a pointer to IGameObject
// we will start off with something simple so we will make the parameter a string
IGameObject* MakeGameObjectFactory(std::string type){
	if(type =="plane"){
		return new Plane;
	}else if(type == "boat"){
		return new boat;
	}
	return nullptr; // return nullptr to supress warnings 
}

int main(){
	//we can now determine at runtime what objects we want to create. 
	IGameObject* myObject = MakeGameObjectFactory("plane");

	delete myObject;
	return 0;
}
```

- the next things to consider is the what if someone passes in "Plane" or "Boat" with a capital "P" or "B"
- This can be tricky because the runtime will throw no error because we are deleting a nullptr so there is no issue from the compiler or runtime but the object is not actually created. 
- We can improve this code by not relying on "string" we can use some C++ features like enum to create a type. 
	*Remember*: Enum (short for *enumeration*) is a user-defined data type that consists of a set of named integral constants. This helps make code more readable and manageable. Enums allows you to create a collection of related constants often used to represent a set of predefined values for variables. 

- Lets implement this for our factory method now. 

```c++
#include <iostream>
#include <string>

class IGameObject{
public:
	virtual ~IGameObject() {} //Destructor 
	virtual void Update() = 0; //purely virtual functions so derived classes must implement them. 
	virtual void Render() = 0;
};

class Plane: public IGameObject{
public:
	Plane(){} //constructor
	void Update() {}
	void Render() {}
};

class Boat: public IGameObject{
public:
	Boat(){} //constructor
	void Update() {}
	void Render() {}

};

//Create enum for plane and boat
enum class ObjectType {PLANE, BOAT};

// create factory method that return type IGameObject or a pointer to IGameObject
// use enum ObjectType as the parameter for the factory method
IGameObject* MakeGameObjectFactory(ObjectType type){
	if(ObjectType::PLANE == type){
		return new Plane;
	}else if(ObjectType::BOAT == type){
		return new boat;
	}
	return nullptr; // return nullptr to supress warnings 
}

int main(){
	//we can now determine at runtime what objects we want to create. 
	// we now have some safety for our object creation in our factory method
	IGameObject* myObject = MakeGameObjectFactory(ObjectType::PLANE);
	IGameObject* myObject2 = MakeGameObjectFactory(ObjectType::BOAT);

	delete myObject;
	delete myObject2;
	return 0;
}
```

- There is another refactoring we can make that has to deal with the implementation. Returning raw pointers is not something many people like. So we can make use of smart pointers using the *memory* library 
		*Remember*: A *smart pointer* is a class that manages a *pointer* to a dynamically allocated object, handling memory allocation and deallocation automatically. Smart pointers help prevent memory leaks and dangling pointers by ensuring that memory is properly released when it is no longer needed. 

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
	Plane(){} //constructor
	void Update() {}
	void Render() {}
};

class Boat: public IGameObject{
public:
	Boat(){} //constructor
	void Update() {}
	void Render() {}

};

//Create enum for plane and boat
enum class ObjectType {PLANE, BOAT};

// instead of returning a raw pointer lets now return a standard shared pointer
// the shared pointer is helping us avoid some of the direct calls using new
// use enum ObjectType as the parameter for the factory method
std::shared_ptr<IGameObject> MakeGameObjectFactory(ObjectType type){
	if(ObjectType::PLANE == type){
		return std::make_shared<Plane>();
	}else if(ObjectType::BOAT == type){
		return std::make_shared<Boat>();
	}
	return nullptr; // return nullptr to supress warnings 
}

int main(){
	//we can now determine at runtime what objects we want to create. 
	// we now have some safety for our object creation in our factory method
	std::shared_ptr<IGameObject> myObject = MakeGameObjectFactory(ObjectType::PLANE);
	
	std::shared_ptr<IGameObject> myObject2 = MakeGameObjectFactory(ObjectType::BOAT);

	//we can get rid of the direct delete calls as share_ptr handles that
	return 0;
}
```

- no we have a factory that creates object and handles the deallocation of memory. 
- some things to think about is the memory allocation and if you should use shared_ptr or unique_ptr or some other memory management method for your use case. 

### Recap 
- We used **Inheritance-Based Polymorphism**
- We created an interface.
- We made two different derived classes for that interface
- We made our factory method 

### Pros and Cons of the Factory Method 


| Pros                                          | Cons                                                                                       |
| --------------------------------------------- | ------------------------------------------------------------------------------------------ |
| Single Responsibility for the Factory         | You do have to make at least two updates to our code i.e., enum type and the method itself |
| It is pretty easy to update and is extensible | You may need several factories for each of the different class hierarchies                 |
- There are more update we will make to the factory method that make it even more powerful. See those in the same folder. 
