#ifndef 
#define GAMEOBJECTS_HPP

class IGameObject {
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

class Plane : public IGameObject {
public:
	Plane(int x, int y) { // x and y are like a default starting position in a game
		ObjectsCreated++;
	}
	void ObjectPlayDefaultAnimation() {/* ... */ }
	void ObjectMoveInGame() {/* ... */ }
	void Update() {/* ... */ }
	void Render() {/* ... */ }
	// create object static member function that can be used as a callback
	static IGameObject* Create() {
		return new Plane(0.0)
	}
private:
	static int ObjectsCreated;
}

class Boat : public IGameObject {
public:
	Boat(int x, int y) { // x and y are like a default starting position in a game
		ObjectsCreated++;
	}
	void ObjectPlayDefaultAnimation() {/* ... */ }
	void ObjectMoveInGame() {/* ... */ }
	void Update() {/* ... */ }
	void Render() {/* ... */ }
	// create object static member function
	static IGameObject* Create() {
		return new Boat(0.0)
	}
private:
	static int ObjectsCreated;
}

#endif