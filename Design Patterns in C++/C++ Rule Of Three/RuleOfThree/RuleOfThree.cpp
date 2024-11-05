

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

