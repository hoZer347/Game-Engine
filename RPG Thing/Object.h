#pragma once

namespace obj {
	class _Obj {
	public:
		_Obj();
		virtual void setup() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void del() = 0;
	};
	template <class T>
	class Obj : public _Obj {
	public:
		void del() {
			delete (T*)this;
		}
	};

	extern unsigned int new_attrib();
	extern void del_attrib();

	extern void setup();
	extern void update();
	extern void render();
	extern void clear();
	extern void del(_Obj* o);
}
