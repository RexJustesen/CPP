### Topics 
- Classes 
- Constructors 
- Overloading 
- Instantiation
- Access Modifiers 
- Inheritance 
- Abstract Classes 
- Project Structure 
- The UML Class 

### Terminology and Rules 
- Functions declared within a class are known as Member Functions (methods in C# and Java)
- Variables declared within a class are known as Member Variables or Data Members 
- C++ allows the declaration of functions outside of a class. 

### Defining Classes 
The class keyword precedes the class's name which must conform to the identifier naming conventions. 
```c++
class NameOfClass {

} optional variable/s;
```
Member function and Variables belonging to the class may be placed inside the { } Note the ";" after the class's closing bracket
```c++
class BasicPlayer {
	int size;
	void DoSomething() {
		cout << "Something" << endl;
	}
};
```
Function defined inside the class are implicitly inline. 

### Defining Member Functions 
- Member function may be defined outside of the class definition as long as they are preceded by the class name and scope resolution operator "::"
- The class must include the function's declaration (prototype)
```c++
class NameOfClass{
	type MemberFunctionName();
};

type NameOfClass::MemberFunctionName(){
	//statements
}
```

### Defining Member Functions Example 
```c++
class BasicPlayer {
	int size;
	void Hello(){
		cout << "Hello" << endl;
	}
	void GoodBye()'
};

void BasicPlayer::GoodBye(){
	cout << "Good Bye" << endl;
}
```


### The Constructor 
- It is illegal to declare a member variable and initialize its value 
```c++
class Player {
	int number = 10
};
```

- This generates a compiler error (in pre C++ 11 only)
- To overcome this we can initialize the class's member variable using a constructor
- A constructor is a special member function that is automatically invoked when an object of the class is instantiated. 
- The constructor has the same name as the class 
- unlike member functions it has no return type
```c++
class NameOfClass {
	NameOfClass(){
		//statement/s
	}
};
```
- A single class can contain multiple overloaded constructors. 
- Typically used to initialize member variables. 
```c++
class Player {
public:
	int number;
	string name;
	Player(int pNumber, string pName){
		number = pNumber;
		name = pName;
	}
};
```

- Alternative syntax using an initializer list 
```c++
class Player{
public:
	int number;
	string name;
	Player(int pNumber, string pName):numer(pNumber),name(pName){}
};
```

### Overloading 
- often you may need more than one function with the same name
- this is legal if they have either different number of parameters or the parameter types are different. 
- The return type may be the same 
```c++
int Sum(inta, int b){
	return a + b;
}

float Sum(float a, float b){
	return a + b;
}

int main (){
	cout << Sum(3,5) << endl;
	cout << Sum(3.25f, 8.45f) << endl;
	return 0;
}
```

- *Note*: We explicitly put "f" at the end of the float values so that the compiler knows that these values must be passed to the Sum function that adds floats together. 

### Instantiating an Object 
- Constructor can't be explicitly invoked. 
- They are executed when a new object of the class is instantiated 
```c++
ClassName identifier(parameter/s);
```
- The brackets after the variable name are optional if no arguments are passed. 
```c++
int main(){
	BasicPlayer myBasicPlayer;
	Player myPlayer(15, "Patrick Mahomes");
	return 0;
}
```

- *Note*: These objects are created on the stack not the heap, to create on the heap you must use the *new* keyword. 

### Invoking Member Functions 
- The public member function can be invoked by placing a dot (object member access operator) after the object variable's name followed by the member function's name and the call operator 
```c++
Player myPlayer(15, "Patrick Mahomes");
myPlayer.DisplayName();
```

### Access Modifiers 
- Determine the visibility of members 
- **public** - visible to any member of any class 
- **private** - accessible from within the same class
- **protected** - as private plus its derived classes 

```c++
class NameOfClass{
private:
	/* one or more variable declarations or member functions */
protected:
	/* one or more variable declarations or member functions */
public:
	/* one or more variable declarations or member functions */
};
```

- The order of access modifiers is not important 
- they can be repeated 
- Constructors should have public access 
- Default is private if not modifier is explicitly declared. 
```c++
class Player{
private:
	int number;
	string name;
public:
	Player(in pNumber, string pName){
		number = pNumber;
		name = pName;
	}
	void DisplayName() {
		cout << "Player name is: " << name << endl;
	}
};
```

### Structures 
- similar to C++ classes apart from two small differences 
	- By default members in structures are public whilst the default in a class is private 
	- Inheritance in struct is public by default 
- Included with C++ to provide compatibility with C. 
```c++
struct NameOfStructure{

};
```

### Creating Static Objects 
- Classes can be regarded as templates from which we create (instantiate) objects. 
- To Create on object on the stack (static), first declare a variable of the class type
```c++
ClassName identifier;
ClassName identifier(paramaters/s);
```
```c++
Player myPlayer;
```
- Invoke its member functions using the member selection operator, followed by the function name and call operator (). 
```c++
myPlayer.Print();
```

### Creating Dynamic Objects 
To Create a dynamic object stored on the heap, first declare a pointer variable of the class type
```c++
Player *myPlayer;
```
Then Create the object using the new keyword and assign it to variable. 
```c++
myPlayer = new Player(); 
```

Invoke methods using the dereference operator
```c++
myPlayer->Print();
```

### Example 
```c++
class MyClass {
public:
	void Print() {
		cout << "MyClass\n";
	}
};

int main(){
	MyClass myStaticObj;
	myStaticObj.Print();
	MyClass *myDynamicObj;
	myDynamicObj = new MyClass();
	myDynamicObj->Print();
	return 0;
}
```

### Passing Objects As Pointers 
Formal Parameters can be pointers to objects 
```c++
type functionName(ClassName * identifier);
```
When Invoking the member function we can pass a pointer 
```c++
ClassName *identifier = new ClassName();
functionName(identifier);
```
Example:
```c++
void Display(Player *p){
	cout << p->name << endl;
}
```
- Instantiate the player and pass it to Display
```c++
Player *myPlayer = new Player();
Display(myPlayer);
```

### Creating Anonymous Objects 
When passing pointers as arguments to a function it may not be necessary for the invoking code to maintain a pointer to the object. 

```c++
funtionName(new type);
```

```c++
class Weapon{
private:
	Magazine *magazine;
public:
	void Load(Magazine *newMag){
		magazine = newMag;
	}
};

int main(){
	weapon *myGun = new Weapon("M14", true);
	myGun->Load(new Magazine(20));
	return 0;
}
```

### Inheritance 
- Typically classes have relationships with one another
- Some Classes being specialized version of more general classes. 
- This could be modelled as a class hierarchy. 
- Examples
	- dog is a type of animal
	- house is a type of building 
	- npc is a type of gameObject
- The general class is known as the parent and the specialized class the child 
```c++
class ChildClassName:ParentClassName{

}
```

### Inheritance example 
```c++
class Model{
public:
	void Draw(){}
};

class Car: public Model{
public:
	void ChangeGear(){}
};
```

- The car above is a type of model 
- When declaring the class we indicate car inherits the members of Model by including **:Model** after the class name.
- **public** is placed before the model to ensure public member function remain public when invoked on an object of the Car type. If private was used all member functions inherited from Model would be private. 
- Car is known as a derived (sub/child class) and Model the base class (super/parent class)
- Within the application we can crate instances of both car and model 
- Model however can only invoke the Draw() member function 
- Car can invoke both its ChangeGear() and Model's Draw() member functions 
```c++
class Model {
public: 
	void Draw){}
};

class Car:public Model {
public:
	void ChangeGear(){}
};

int main(){
	Model model;
	Car car;
	model.Draw();
	car.Draw();
	car.ChangeGear();
	return 0;
}
```


### Multiple Inheritance 
- C++ supports multiple inheritance 
- A derived class inherits from more than one parent class. 
- Can introduce unnecessary complexity. 
- Naming conflicts - Parents have members with the same name. Which should be used?
- Diamond problem - The two parent classes have a common parent.
- Multiple inheritance should be avoided if possible. 

### Example of Multiple Inheritance 
```c++
class Boat {
protected:
	int id;
public: 
	Boat(int id):id(id){}
	void Display(){cout << id << endl;}
};

class Car {
protected:
	int id;
public:
	Car(int id):id(id){}
	void Display(){cout << id << endl;}
};

class Amphibian: public Boat, public Car{ // Implement multiple inheritance
public:
	Amphibian(int id):Car(id), Boar(id) {} //The amphibian class has two id's!
};

int main() {
	Amphibian *duck = new Amphibian(1);
	duck->Car::Display(); //Prefix display with class name to avoid name conflict
	return 0;
}
```

### Encapsulation 
- Class member variables define an object's state
- Direct access to the state could lead to inconsistencies and leads to tight coupling between the class and code that uses it
- good practice to hide this state by declaring member private. Forcing the developer to access the variables through the getter / setter methods 
- There are two types of member function. 
- **Mutators** - allow changes to the object's state (default). this is known as the setter method this method sets or updates the value of a private member variable. 
- **Accessors** - do not allow changes to the object's state. this is the getter methods that retrieves the value of a private member variable but does not modify the object's state.
- a member function can be declared an accessor by appending the **const**  keyword to its declaration. 
```c++
type FunctionName()const{}
```

### Getter & Setter Member functions 
- each variable has a pair of member functions that sets and gets the variable value
- Logic inside the setter ensure the state remains consistent. 
- The getter is an **Accessor** and consequently should not change the state - hence the addition of the **const** keyword. 
```c++
class Marker {
private:
	int passMark;
public:
	void setPassMark(int pMark){
		if(pMark > 0)
			passMark = pMark;
	}
	int getPassMark() const{
		return passMark;
	}
};
```

### Abstract Member Functions 
- Also known as **pure virtual member functions** 
- A Function that has no implementation. 
- It is virtual as subclasses must override it. 
```c++
vitrual type MemberFunctionName() = 0;
```
- When declared within a class it prevents the class from being instantiated (an abstract class).
- Only derived classes that implement the pure virtual member functions can be instantiated
```c++
class Person {
public:
	virtual void Move() = 0;
};

class Soldier:public Person {
public:
	void Move(){ }
};
```
- Classes with one or more abstract member functions could be used as an alternative to Java / C# interfaces
### Interface Example 
While we can't create an instance of an abstract class, it is possible to define a pointer to the abstract class and assign a derived object to it. This restricts access to the public members of the abstract class. 

- class IPrintable is the parent and abstract class. 
- Class GameObject inherits from IPrintable
- GameObject implement Print() function from IPrintable
- We are creating a pointer to the parent IPrintable and then we are assigning an address of the child class GameObject. If this function was not abstract it would call the print of the parent but since it is abstract and is overridden by the child it is calling the member function of the child GameObject.
```c++
class IPrintable {
public:
	virtual void Print() = 0;
};

class GameObject: public IPrintable {
private:
	int id;
public:
	GameObject(int id):id(id){}
	int GetID() const {
		return id;
	}
	void Print(){
		cout << "ID: " << id << endl;
	}
};

int main(){
	GameObject *obj1 = new GameObject(1)'
	cout << obj1->GetID() << endl;
	IPrintable *obj2 = new GameObject(2)'
	obj2->Print();
}
```


### Project Organization 
- Often a developer is only interested in the class's interface.
- Not the implementation of the member functions. 
- Separate the implementation and interface elements of a class. 
- The **class's definition** (interface) including the declaration of its member function is placed in a header file (ending in .h)
- The definition of the member functions is placed in a **.cpp** file.
- Within Visual Studio these files are created for you when you select **Project->Add Class**
- It is good practice to place each class in its own .h and .cpp file. 
- By convention these files have the same name as the class. This is enforce when creating classes through Visual Studio. 

### Examples of organization 
- Header File 
```c++
//File data.h
#pragma once

class Date {
private:
	int year;
	int month;
	int day;
public:
	Date(int day, int month, int year);
	int GetYear(){ return year; }
	int GetMonth(){ return month; }
	int GetDay(){ return day; }
	void SetDate(int d, int m, int y);
};
```

- .cpp file (implementation of header file)
```c++
// File date.cpp
#include "stdafx.h"
#include "Date.h"

Date::Date(int day, int month, int year){
	SetDate(day,month,year);
}

void Date::SetDate(int d, int m, int y){
	day = d;
	month = m;
	year = y;
}
```

- Main file
```c++
#include "stdafx.h"
#include "Date.h"

int main(){
	Date *myDate = new Date(24,5,2024);
	std::cout<< myDate->GetYear() << endl; // displays 2024
	return 0;
}
```

