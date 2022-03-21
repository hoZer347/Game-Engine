#pragma once

#include <vector>

namespace obj {
	class Obj {
	public:
		Obj(bool=true);
		~Obj();
		virtual void update() {};
		virtual void render() {};

		unsigned int index;
	};

	extern void update();
	extern void render();
	extern void rmv(Obj*);
	extern void close();

	template <class T>
	class Manager : public Obj {
	public:
		~Manager() {
			for (auto& o : objs)
				delete o;
		}
		T* create() {
			T* t = new T();
			objs.push_back(t);
			return t;
		}
		void del(T* t) {
			delete t;
		}
		void update() {};
		void render() {};

		std::vector<T*> objs;
	};
}
