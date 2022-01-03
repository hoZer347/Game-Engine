#pragma once

#include "Mesh.h"

#include <vector>
#include <functional>

template<class T>
class Menu : public MeshObj<Menu<T>> {
public:
	~Menu() { delete (T*)this; }
	class Option {
	public:
		friend class Menu<T>;

		virtual void on() = 0;
		virtual void off() = 0;
		virtual bool intersect() = 0;

	protected:
		std::function<void(T)> f;
	};

	void set(T o) {
		obj = o;
	}

	void update() {
		hovered = NULL;

		for (auto& o : O)
			if (o->intersect()) {
				hovered = o;
				o->on();
			}
			else
				o->off();
	};

	void select() {
		if (hovered) {
			hovered->f(obj);
			unload();
		}
	};
	
	void clear() { O.clear(); };

	virtual void unload()=0;

protected:
	T obj = NULL;
	Option* hovered = NULL;
	std::vector<Option*> O;
};
