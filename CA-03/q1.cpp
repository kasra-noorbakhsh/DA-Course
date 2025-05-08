#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

    long long ingredients_number, foods_number, temp;
    long long count = 0, result = 0;

    vector<long long> ingredients_value;
    vector<long long> ingredients_number_in_foods;

    cin >> ingredients_number;
    cin >> foods_number;

    for(long long i = 0 ; i < ingredients_number; i++){
        cin >> temp;
        ingredients_value.push_back(temp);
    }

    for(long long j = 0 ; j < foods_number; j++){
        cin >> temp;
        ingredients_number_in_foods.push_back(temp);
    }

    sort(ingredients_value.begin(), ingredients_value.end());
    sort(ingredients_number_in_foods.begin(), ingredients_number_in_foods.end());

    for(long long k = 0 ; k < foods_number; k++){
        if(ingredients_number_in_foods[k] == 1){
            count++;
        }
        else{
            break;
        }
    }

    long long max_ingredients_value_index = ingredients_value.size() - 1;
    long long max_ingredients_number_in_foods_index = ingredients_number_in_foods.size() - 1;
    long long min_ingredients_value_index = 0;
    long long temp_count = count;

    while(temp_count != 0){
        result += ingredients_value[max_ingredients_value_index] * 2;
        max_ingredients_value_index--;
        temp_count--;
    }

    for(long long x = max_ingredients_number_in_foods_index ; x >= count; x--){
        result += ingredients_value[max_ingredients_value_index] + ingredients_value[min_ingredients_value_index];
        max_ingredients_value_index--;
        min_ingredients_value_index += ingredients_number_in_foods[x] - 1;
    }

    cout << result << endl;
}