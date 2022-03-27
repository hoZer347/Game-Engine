#pragma once

#include <vector>

namespace obj {
	class Obj {
	public:
		virtual void update()=0;
		virtual void render()=0;

		unsigned int index;
	};

	extern void update();
	extern void render();
	extern void add(Obj*);
	extern void rmv(Obj*);
	extern void close();

	template <class T>
	class Manager : public Obj {
	public:
		Manager() {
			add(this);
		};
		~Manager() {
			for (auto& o : objs)
				delete (T*)o;
		};
		T* create() {
			T* t = new T();
			objs.push_back(t);
			return t;
		};
		void del(T* t) {
			delete t;
		};
		void update() {
			for (auto& o : objs)
				if (o)
					o->update();
		};
		void render() {
			for (auto& o : objs)
				if (o)
					o->render();
		};

		std::vector<T*> objs;
	};
}
