#include <iostream>

using namespace std;

template <class AbstractClass>
class Container {
private:
	int size;
	AbstractClass** array;
public:
	Container() : size(0), array(new AbstractClass * []) {}
	Container(int size) : size(size), array(new AbstractClass * [size]) {
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass();
		}
	}
	Container(const Container& с) : size(с.size), array(new AbstractClass * [с.size]) {
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass(*(с.array[i]));
		}
	}
	~Container() {
		for (int i = 0; i < size; i++) {
			delete array[i];
		}
		delete[] array;
	}
	int get_size() {
		return size;
	}
	AbstractClass get_object(int index) {
		//Return element in container
		if (index >= 0 && index < size) return *array[index];
		else if (index < 0 && -index <= size) return *array[size + index];
	}
	void push_back(AbstractClass element) {
		size += 1;
		AbstractClass** temp_arr = new AbstractClass * [size];
		for (int i = 0; i < size - 1; i++) {
			temp_arr[i] = new AbstractClass(*array[i]);
			delete array[i];
		}
		temp_arr[size - 1] = new AbstractClass(element);
		delete[] array;
		array = new AbstractClass * [size];
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass(*temp_arr[i]);
			delete temp_arr[i];
		}
		delete[] temp_arr;
	}
};


int main() {

	Container<int> c(4);
	c.push_back(1);
	for (int i = 0; i < c.get_size(); i++) {
		cout << c.get_object(i) << endl;
	}

	return 0;
}