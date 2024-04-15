#include <iostream>

using namespace std;

template <class AbstractClass>
class Container {
private:
	int size;
	AbstractClass* array;
public:
	Container() : size(0), array(nullptr) {}
	Container(int size) : size(size), array(new AbstractClass[size]) {}
	Container(const Container& с) : size(с.size), array(new AbstractClass[с.size]) {
		for (int i = 0; i < size; i++) {
			array[i] = с.array[i];
		}
	}
	~Container() {
		delete[] array;
	}
};


int main() {

}
