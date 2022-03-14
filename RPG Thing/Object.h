#pragma once

#include <unordered_set>

namespace obj {
	
	class Obj {
	public:
		Obj(bool=true);
		~Obj();
		virtual void setup()=0;
		virtual void update()=0;
		virtual void render()=0;
	};

	extern void setup();
	extern void update();
	extern void render();

	extern void rmv(Obj*);
	extern void close();

	extern std::unordered_set<Obj*> OBJS;

	template <class T>
	class Manager : public Obj {
	public:
		~Manager() {
			for (auto& o : objs)
				delete o;
		}
		T* create() {
			T* t = new T();
			objs.insert(t);
			return t;
		}
		void del(T* t) {
			objs.erase(t);
			delete t;
		}
		void setup() {};
		void update() {};
		void render() {};

		std::unordered_set<T*> objs;
	};
}
