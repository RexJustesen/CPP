#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <memory>
#include <map>
#include <string>

// Declare the one interface type 

class IGameObject;

// One change is we have removed the enum for plane and boat classes 
// we want to be able to create different types at runtime so that is why the enum is removed
class MyGameObjectFactory {
	// callback function for creating an object 
	typedef IGameObject* (*CreateObjectCallback)();
public:
	//register a new user created type 
	// they also have to pass in how to create an object 
	static void RegisterObject(const std::string& type, CreateObjectCallback cb);
	// unregister a user created object type
	// remove from the map
	static void UnregisterObject(const std::string& type);

	//previous factory method created in other examples 
	static IGameObject* CreateSingleObject(const std::string& type);

private:
	
};