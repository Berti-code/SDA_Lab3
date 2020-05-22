#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->relation = r;
	this->capacity = 10;
	this->elements = new TElem[this->capacity];
	this->positions = new int[this->capacity];
	this->head = -1;
	this->firstEmpty = 0;
	this->mapSize = 0;
	// initialising the list of empty positions
	for (int i = 0; i < this->capacity - 1; i++) {
		this->positions[i] = i + 1;
		this->elements[i] = NULL_TELEM;
	}
	this->positions[this->capacity - 1] = -1;
}

void SortedMultiMap::add(TKey c, TValue v) {
	TElem newElement = pair<TKey, TValue>(c, v);

	if (this->firstEmpty == -1)
	{
		// in case the capacity is reached we double the capacity
		TElem* newElements = new TElem[2 * this->capacity];
		int* newPositions = new int[2 * this->capacity];

		for (int i = 0; i < capacity ; i++)
		{
			newElements[i] = this->elements[i];
			newPositions[i] = this->positions[i];
		}
		for (int i = capacity - 1; i < 2 * capacity - 1; i++)
		{
			if (i != capacity - 1)
				newElements[i] = NULL_TELEM;
			newPositions[i] = i + 1;
		}
		newPositions[2 * capacity - 1] = -1;
		newElements[2 * capacity - 1] = NULL_TELEM;

		// we deallocate the previously used memory
		delete[] this->elements;
		delete[] this->positions;

		this->elements = newElements;
		this->positions = newPositions;
		this->firstEmpty = capacity;
		this->capacity *= 2;
	}
	// if the map is empty
	if (this->size() == 0) 
	{
		this->elements[this->firstEmpty] = newElement;
		this->head = this->firstEmpty;
		this->firstEmpty = this->positions[this->firstEmpty];
	}
	else
	{
		int currentIndex = this->head;
		while (this->positions[currentIndex] != -1 && this->relation(this->elements[this->positions[currentIndex]].first, this->elements[currentIndex].first))
		{
			currentIndex = this->positions[currentIndex];
		}

		int newElementPosition = this->firstEmpty;
		this->firstEmpty = this->positions[this->firstEmpty];
		this->elements[newElementPosition] = newElement;
		this->positions[newElementPosition] = this->firstEmpty;
	}
	this->mapSize++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	// Theta(size)
	std::vector<TValue> TValueVector;
	int i = this->head;
	while (i != -1)
	{
		//cout << " i: " << i;
		cout << this->elements[i].first << " " << c << " TValue " << this->elements[i].second << endl;
		if (this->elements[i].first == c) {
			TValueVector.push_back(this->elements[i].second);
			cout << "Matched:" << " key: " << this->elements[i].first << " to match: "<< c << " TValue: " << this->elements[i].second << endl;
		}
		i = this->positions[i];
	}

	return TValueVector;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	TElem removeElement = pair<TKey, TValue>(c, v);
	int currentNode = this->head, previousNode = -1;

	while (currentNode != -1 and this->elements[currentNode] != removeElement)
	{
		previousNode = currentNode;
		currentNode = this->positions[currentNode];
	}
	if (currentNode != -1)
	{
		if (currentNode == this->head)
			this->head = this->positions[this->head];
		else
		{
			this->positions[previousNode] = this->positions[currentNode];
			this->positions[currentNode] = this->firstEmpty;
			this->firstEmpty = currentNode;
		}
		this->mapSize--;
		return true;
	}

	return false;
}


int SortedMultiMap::size() const {
	//Theta(1)
	return this->mapSize;
}

bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	if (this->mapSize == 0)
		return true;
	else
		return false;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	delete[] this->elements;
	delete[] this->positions;
}
