#include <vector>
#include <memory>
#include <fstream>
#include <string>

#include "Factory.hpp"
#include "GameObjects.hpp"


// as a user I want to create a new type
class Ant : public IGameObject {
public:
	Ant(int x, int y) {
		ObjectsCreated++;
	}
	void ObjectPlayDefaultAnimation(){/* ... */ }
	void ObjectMoveInGame(){/* ... */ }
	void Update(){/* ... */ }
	void Render(){/* ... */ }
	// the static member function create is not part of the interface 
	// so this is where good documentation comes in for users and other developers using your code
	static IGameObject* Create() {
		return new Ant(0, 0);
	}
};

int Ant::ObjectsCreated = 0;

int main() {
	// Register 3 different types 
	MyGameObjectFactory::RegisterObject("plane", Plane::Create);
	MyGameObjectFactory::RegisterObject("boat", Boat::Create);
	MyGameObjectFactory::RegisterObject("Ant", Ant::Create);

	std::_Adjust_manually_vector_aligned<IGameObject*> gameObjectCollection;
	// we cann add the correct object to our collection using a .txt file
	// based on the .txt file 
	std::string line;
	std::ifstream myFile("")
}