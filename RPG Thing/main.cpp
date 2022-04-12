
#include "Inputs.h"
#include "Stage.h"
#include "Spooler.h"
#include "Object.h"

#include <thread>
#include <chrono>
#include <iostream>

struct test : obj::Obj {
	void stage(size_t& t) {
		switch (t) {
		case 0:
			std::cout << "stage0" << std::endl;
			break;
		case 1:
			std::cout << "stage1" << std::endl;
			break;
		case 2:
			std::cout << "stage2" << std::endl;
			break;
		};
	};
};
                      
int main() {
	obj::OBJS.push_back(new test());
	obj::OBJS.push_back(new test());
	obj::OBJS.push_back(new test());
	obj::OBJS.push_back(new test());

	inputs::init();
	stage::init();

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	stage::close();
	inputs::close();
	spooler::close();

	return 0;
};
