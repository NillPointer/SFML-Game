#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class GameObject;

class Component {
public:
	Component(GameObject &obj) : m_gameObject(obj), m_active(true) {};
	virtual void Update(float timeDelta) = 0;

	void SetActive(bool active) { m_active = active; }
	bool IsActive() const { return m_active; }

protected:
	GameObject& m_gameObject;
	bool m_active;
};

#endif // !COMPONENT_HPP