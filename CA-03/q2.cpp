// i used chatGPT for creating the min heap


// i want a min heap from a vector of integers in c++ 
// ChatGPT

// Certainly! In C++, you can use the std::priority_queue container from the <queue> header to create a min heap. 
//By default, std::priority_queue creates a max heap, but you can make it behave as a min heap by providing a custom comparator.

// Here's an example of how you can create a min heap from a vector of integers:

// cpp

// #include <iostream>
// #include <vector>
// #include <queue>

// int main() {
//     // Your vector of integers
//     std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};

//     // Creating a min heap from the vector using std::priority_queue
//     std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap(vec.begin(), vec.end());

//     // Printing elements from the min heap
//     std::cout << "Min Heap elements: ";
//     while (!minHeap.empty()) {
//         std::cout << minHeap.top() << " ";
//         minHeap.pop();
//     }

//     return 0;
// }

// In this example, the third template parameter of std::priority_queue is specified as std::greater<int>, 
//which is a functor that makes the priority queue behave as a min heap. 
//The elements of the vector are then inserted into the min heap during its initialization.

// The output of this program will be:

// mathematica

// Min Heap elements: 1 1 2 3 4 5 6 9 

// This shows the elements extracted from the min heap in ascending order, demonstrating the min-heap property.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){

    int number_of_plates, temp_plate;
    int temp = 0, result = 0;

    vector<int> ingredients_number;

    cin >> number_of_plates;

    for(int i = 0 ; i < number_of_plates; i++){
        cin >> temp_plate;
        ingredients_number.push_back(temp_plate);
    }

    priority_queue<int, vector<int>, greater<int>> minHeap(ingredients_number.begin(), ingredients_number.end());

    while(minHeap.size() > 1){

        if(minHeap.size() % 2){

            for(int j = 0 ; j < 3; j++){
                temp += minHeap.top();
                minHeap.pop();
            }

            minHeap.push(temp);
        }

        else {

            for(int k = 0 ; k < 2; k++){
                temp += minHeap.top();
                minHeap.pop();
            }

            minHeap.push(temp);
        }

        result += temp;
        temp = 0;
    }

    cout << result << endl;
}