#pragma once

#include <unordered_set>

namespace Object {
	class _Obj;

	extern void setup();

	extern void update();

	extern void render();

	extern void clear();

	extern void add(_Obj*);

	extern void del(_Obj*);

	class _Obj {
	public:
		_Obj() { add(this); }
		virtual void del() = 0;
		virtual void setup() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
	};

	template <class T>
	class Obj : public _Obj {
		void del() { delete (T*)this; }
	};
}
