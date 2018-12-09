#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class GameObject;

class Component {
public:
	Component(GameObject &obj) : m_gameObject(obj) {};
	virtual void Update(float timeDelta) = 0;
	
protected:
	GameObject& m_gameObject;
};

#endif // !COMPONENT_HPP

