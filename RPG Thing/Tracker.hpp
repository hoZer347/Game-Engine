#pragma once

#include <cstddef>

class _Tracker {
public:
	_Tracker
		*next = NULL,
		*prev = NULL;
};

extern _Tracker* TRACKER;

class TrackList {

};

template <class T>
class Tracker : public _Tracker {
public:

};

template <class T>
static void track(T* t) {
	
};

template <class T>
static void letgo(T* t) {

}
