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
