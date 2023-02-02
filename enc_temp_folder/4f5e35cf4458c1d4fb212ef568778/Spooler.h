#pragma once

#include <time.h>
#include <queue>
#include <thread>
#include <atomic>

namespace spooler {
	extern const size_t MAX_CORES;

	struct _thread {
		virtual ~_thread() { };
		std::atomic<bool>
			ON = true,
			PAUSE = false;
		std::thread _t;
	};

	template <class T>
	struct thread : _thread {
		~thread() {
			ON = false;
			_t.join();
			delete obj;
		};
		virtual void push(void(*)(thread<T>*)) { };
		T* obj = NULL;
	};

	// Vector thread
	// Iterates over a vector of tasks
	template <class T>
	struct v_thread : thread<T> {
		v_thread() {
			this->obj = new T();
			this->_t = std::thread(manage, this);
		};
		v_thread(T* t) {
			this->obj = t;
			this->_t = std::thread(manage, this);
		};
		void push(void(*t)(thread<T>*)) { push_cont(t); };
		void push_cont(void(*f)(thread<T>*)) { v.push_back(f); };
		static void manage(v_thread<T>* t) {
			while (t->ON)
				if (t->v.size() && !t->PAUSE) {
					t->v[t->index](t);

					t->index++;
					if (t->index >= t->v.size()) t->index = 0;
				}
		};

	protected:
		size_t index = 0;
		std::vector<void(*)(thread<T>*)> v;
	};

	// Queue thread
	// Continually pops tasks off of a queue
	template <class T>
	struct q_thread : thread<T> {
		q_thread() {
			this->obj = new T();
			this->_t = std::thread(manage, this);
		};
		q_thread(T* t) {
			this->obj = t;
			this->_t = std::thread(manage, this);
		};
		void push(void(*t)(thread<T>*)) { push_once(t); };
		void push_once(void(*f)(thread<T>*)) { q.push(f); };
		static void manage(q_thread<T>* t) {
			while (t->ON)
				if (t->q.size() && !t->PAUSE) {
					t->q.front()(t);
					t->q.pop();
				}
		};

	protected:
		std::queue<void(*)(thread<T>*)> q;
	};

	// Timed Thread
	// Runs a Queue thread every interval of time until it is empty
	template <class T>
	struct t_thread : v_thread<T> {
		t_thread() {
			this->interval = 1000;
			this->obj = new T();
			this->_t = std::thread(manage, this);
		};
		t_thread(T* t, long i) {
			this->interval = i;
			this->obj = t;
			this->_t = std::thread(manage, this);
		};
		static void manage(t_thread<T>* t) {
			t->c = clock();

			while (t->ON) {
				t->c += t->interval;

				while (clock() - t->c < t->interval);

				this->v_thread<T>::manage(t);
			};
		};

		clock_t c;
		long interval = 0;
	};

	void close();
	void wait_for_close();
};
