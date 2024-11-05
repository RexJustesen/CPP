In C++, if you have a constructor and a destructor, it is often necessary to define a copy constructor and assignment operator as well. Primarily because of the **Rule of Three**. This rule states that if a class requires a custom destructor, copy constructor, or copy assignment, it likely requires all three of these special functions. 

### Why do you need to follow the Rule of Three?
1. Resource Management 
	- If your class manages resources like dynamically allocated memory, file handles, or network connections, the default copy constructor and assignment operator (which perform shallow copies) may not suffice. a shallow copy only duplicates the pointer, not the data it points to. This can lead to issues like double deleted (where both copies try to free the same resource), memory leaks, or undefined behavior. 
2. Copy Constructor
	- A Custom copy constructor is necessary to perform a deep copy of the resource, creating a new resource for the copy rather than sharing the original resource's address. This ensures that each object manages its own instance of the resource. 
3. Assignment Operator
	- The assignment operator (**operator=**) needs to handle cases where the object already has resources, as in **a = b;**. A Well-implemented assignment operator would first free the existing resource of **a** (if any), then make a copy if **b's** resources. This prevents memory leaks and ensures both objects manage their own resources independently.
4. Destructor
	- The destructor is crucial for cleaning up resources when the object is no longer needed. Without it, you'd have memory leaks, dangling pointers, or incomplete resource deallocation. 

### Example
```c++


#include <iostream>
// This is an example of the Rule of Three

class MyClass{
private:
    int* data; // pointer to dynamically allocated memory 
public:
    //constructor 
    MyClass(int value) : data(new int(value)) {
        std::cout << "Constructor called. Memory allocated for value: " << *data << std::endl;
    }

    //copy constructor
    MyClass(const MyClass& other) : data(new int(*other.data)) {
        std::cout << "Copy constructor called, value copied: " << *data << std::endl;
    }

    //Assignment operator 
    MyClass& operator=(const MyClass& other) {
        std::cout << "assignment operator called.\n";
        if (this == &other) {
            std::cout << "Self assignment, skipping assignement. \n";
            return *this; // handles self assignment
        }
        delete data; //clean up existing resource
        data = new int(*other.data); //deep copy of resource
        std::cout << "Assigned new value: " << *data << "\n";
        return *this;

    }

    //destructor
    ~MyClass() {
        std::cout << "Destrcutor called. Releasing memory for " << *data << "\n";
        delete data; // free memory 
    }

    void display() const {
        std::cout << "Value " << *data << "\n";
    }

    void setData(int value) {
        *data = value;
    }
};

int main()
{
    //create an object of MyClass 
    MyClass obj1(10);
    obj1.display();

    // use copy constructor to create second object as a copy of the first 
    MyClass obj2 = obj1;
    obj2.display();

    // Modify obj2 and see how it affects obj1 (deep copy)
    obj2.setData(20);
    std::cout << "after modifying obj2:\n";
    obj1.display();
    obj2.display();

    // assignment operator to assign obj2 to obj3
    MyClass obj3(30);
    obj3 = obj2;
    obj3.display();
}

```

