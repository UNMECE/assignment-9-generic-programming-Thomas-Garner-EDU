#include <iostream>
#include <stdexcept> // For std::out_of_range and std::logic_error

template <typename T>
class GenericArray {
private:
    T* data;
    int current_size;

public:
    // Constructor
    GenericArray() {
        data = nullptr;
        current_size = 0;
    }

    // Destructor to clean up memory when the object is destroyed
    ~GenericArray() {
        delete[] data;
    }

    // Add an element to the end of the array
    void addElement(T param) {
        // Allocate new space in memory for the new size
        T* new_data = new T[current_size + 1];

        // Copy over the previous array to the new array
        for (int i = 0; i < current_size; ++i) {
            new_data[i] = data[i];
        }

        // Add the new element
        new_data[current_size] = param;

        // Delete the old array and point to the new one
        delete[] data;
        data = new_data;
        current_size++;
    }

    // Return the value in the array at the location param
    T at(int param) const {
        if (param < 0 || param >= current_size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[param];
    }

    // Return the size of the array
    int size() const {
        return current_size;
    }

    // Return the sum of the entire array
    T sum() const {
        if (current_size == 0) return T(); 
        T total = 0;
        for (int i = 0; i < current_size; ++i) {
            total += data[i];
        }
        return total;
    }

    // Find the maximum value of the entire array
    T max() const {
        if (current_size == 0) throw std::logic_error("Array is empty");
        T max_val = data[0];
        for (int i = 1; i < current_size; ++i) {
            if (data[i] > max_val) {
                max_val = data[i];
            }
        }
        return max_val;
    }

    // Find the minimum value of the entire array
    T min() const {
        if (current_size == 0) throw std::logic_error("Array is empty");
        T min_val = data[0];
        for (int i = 1; i < current_size; ++i) {
            if (data[i] < min_val) {
                min_val = data[i];
            }
        }
        return min_val;
    }

    // Return a slice of the array between and including elements begin to end
    T* slice(int begin, int end) const {
        // Check the bounds of the slice
        if (begin < 0 || end >= current_size || begin > end) {
            std::cerr << "Error: Invalid slice bounds." << std::endl;
            return nullptr; 
        }

        int slice_size = end - begin + 1;
        
        // Return a new array pointer (not a pointer to the underlying data)
        T* sliced_array = new T[slice_size];
        
        for (int i = 0; i < slice_size; ++i) {
            sliced_array[i] = data[begin + i];
        }
        
        return sliced_array;
    }
};

int main() {
    GenericArray<int> int_array;

    // Populating the array with some values: 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20
    for (int i = 0; i <= 10; ++i) {
        int_array.addElement(i * 2);
    }

    // Print array items to verify
    std::cout << "Original Array: [ ";
    for (int i = 0; i < int_array.size(); ++i) {
        std::cout << int_array.at(i) << " ";
    }
    std::cout << "]" << std::endl;

    // Testing core functions
    std::cout << "size of array is " << int_array.size() << std::endl;
    std::cout << "sum of the array is " << int_array.sum() << std::endl;
    std::cout << "maximum and minimum of array is " << int_array.max() << "\t" << int_array.min() << std::endl;

    // Testing slice functionality
    int slice_begin = 5;
    int slice_end = 10;
    int* sliced_array = int_array.slice(slice_begin, slice_end);

    // Print sliced array
    if (sliced_array != nullptr) {
        int slice_size = slice_end - slice_begin + 1;
        std::cout << "sliced_array (" << slice_begin << " to " << slice_end << "): [ ";
        for (int i = 0; i < slice_size; ++i) {
            std::cout << sliced_array[i] << " ";
        }
        std::cout << "]" << std::endl;

        // Clean up the dynamically allocated slice to prevent memory leaks
        delete[] sliced_array; 
    }

    return 0;
}
