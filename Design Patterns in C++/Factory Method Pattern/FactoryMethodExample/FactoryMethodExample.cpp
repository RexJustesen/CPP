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
	Plane() { std::cout << "made plane\n"; } //constructor
	void Update() {}
	void Render() {}
};

class Boat : public IGameObject {
public:
	Boat() { std::cout << "made boat\n"; } //constructor
	void Update() {}
	void Render() {}

};

//Create enum for plane and boat
enum class ObjectType { PLANE, BOAT };

// instead of returning a raw pointer lets now return a standard shared pointer
// the shared pointer is helping us avoid some of the direct calls using new
// use enum ObjectType as the parameter for the factory method
std::shared_ptr<IGameObject> MakeGameObjectFactory(ObjectType type) {
	if (ObjectType::PLANE == type) {
		return std::make_shared<Plane>();
	}
	else if (ObjectType::BOAT == type) {
		return std::make_shared<Boat>();
	}
	return nullptr; // return nullptr to supress warnings 
}

int main() {
	//we can now determine at runtime what objects we want to create. 
	// we now have some safety for our object creation in our factory method
	std::shared_ptr<IGameObject> myObject = MakeGameObjectFactory(ObjectType::PLANE);

	std::shared_ptr<IGameObject> myObject2 = MakeGameObjectFactory(ObjectType::BOAT);

	//we can get rid of the direct delete calls as share_ptr handles that
	return 0;
}