#include "UnitMenu.h"

void UnitOption::on() {
	if (!on_off) return; on_off = true;

}

void UnitOption::off() {
	if (on_off) return; on_off = false;

}

bool UnitOption::intersect() {
	return false;
}

void UnitMenu::add(const char* name, std::function<void(Unit*)> f) {
	
}

void UnitMenu::unload() {
	clear();
}
