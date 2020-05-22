#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <stdexcept>
#include <iostream>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation
	this->currentElement = map.head;
}

void SMMIterator::first(){
	//TODO - Implementation
	this->currentElement = map.head;
}

void SMMIterator::next(){
	cout << "currentElement:" << this->currentElement << "next position: " << map.positions[this->currentElement] << endl;
	if (this->valid()) {
		this->currentElement = this->map.positions[this->currentElement];
	}
	else
		throw std::exception("Invalid iterator!");
}

bool SMMIterator::valid() const {
	//TODO - Implementation
	if (this->currentElement < -1 or this->currentElement >= map.size() or map.size() == 0)
		return false;
	else
		return true;
}

TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
	if (this->valid())
		return this->map.elements[this->currentElement];
	else
		throw std::exception("Impossible operation!");
}


