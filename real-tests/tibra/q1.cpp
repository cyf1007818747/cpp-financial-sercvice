/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/tibra/q1.cpp -o .bin/real-tests@@tibra@@q1.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@tibra@@q1.bin
*/

#include <bits/stdc++.h>

using namespace std;


/*
 * Complete the 'valuation' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER reqArea
 *  2. LONG_INTEGER_ARRAY area
 *  3. LONG_INTEGER_ARRAY price
 */
 
long remove_outliners(map<long, vector<long>> & price_map) {
    int num_data_points = 0;
    
    for (auto& [key, value] : price_map) {
        int v_size = value.size();
        
        // skip vectors with only 1 element
        if (v_size <= 1) {
            num_data_points += value.size();
            continue;
        }

        // compute the mean and standard deviation of the vector
        double sum = 0.0, sum_sq = 0.0;
        for (const auto& element : value) {
            sum += element;
            sum_sq += pow(element, 2);
        }
        // double mean = sum / (value.size() - 1);
        // double var = (sum_sq - sum * mean) / (value.size() - 2);
        // double std_dev = sqrt(var);

        // remove elements that are more than 3 standard deviations away from the mean
        value.erase(std::remove_if(value.begin(), value.end(), [&](long element) {
            double element_mean = (double) (sum - element) / (double) (v_size - 1);
            double element_var = (sum_sq - pow(element, 2) - (v_size - 1) * pow(element_mean, 2)) / (v_size - 1);
            double element_std_dev = sqrt(element_var);
            return abs(element - element_mean) > 3 * element_std_dev;
        }), value.end());
        // cout << "key: " << key << ", value.size(): " << value.size() << endl;
        num_data_points += value.size();
    }
    // for (auto& [key, value] : price_map) {
    //     if (value.size() == 0) {
    //         price_map.erase(key);
    //     }
    // }
    return num_data_points;
 }
 
double interpolate(map<long, double>& data, long P) {
    if (data.count(P)) { // if there is a key equal to P, return its value
        return data[P];
    }
    
    auto it = data.lower_bound(P); // find the first element with key >= P
    
    // if P is smaller than all keys, use the first 2 points to extrapolate
    if (it == data.begin()) {
        double x1 = it->first, y1 = it->second;
        ++it;
        double x2 = it->first, y2 = it->second;
        return y1 + (y2 - y1) * (P - x1) / (x2 - x1);
    }
    
    // if P is larger than all keys, use the last 2 points to extrapolate
    if (it == data.end()) {
        --it;
        double x2 = it->first, y2 = it->second;
        --it;
        double x1 = it->first, y1 = it->second;
        return y2 + (y2 - y1) * (P - x2) / (x2 - x1);
    }
    
    // interpolate using the 2 nearest data points
    double x2 = it->first, y2 = it->second;
    --it;
    double x1 = it->first, y1 = it->second;
    return y1 + (y2 - y1) * (P - x1) / (x2 - x1);
}


long valuation(long reqArea, vector<long> area, vector<long> price) {
    int n = area.size();
    
    // map of <area, [prices]>
    map<long, vector<long>> price_map;
    for (int i = 0; i < n; ++i) {
        if (price_map.count(area[i]) > 0) {
            price_map[area[i]].push_back(price[i]);
        } else {
            price_map[area[i]] = {price[i]};
        }
    }
    // for (auto& [key, value] : price_map) {
    //     cout << "key: " << key << ", value: " << value.size() << endl;
    // }
    // cout << price_map.size() << endl;
    long num_dp = remove_outliners(price_map);
    // cout << num_dp << endl;
    
    map<long, double> average_prices;
    
    if (num_dp == 0) {
        return 1000;
    } else if (num_dp == 1) {
        return (price_map.begin()->second)[0];
    } else {
        for (auto& [key, value] : price_map) {
            if (value.size() == 0) {
                continue;
            }
            double mean = accumulate(value.begin(), value.end(), 0.0) / value.size();
            average_prices[key] = mean;
            // cout << "size: " << key << ", mean price: " << mean << endl;
        }
    }
    
    double prediction = interpolate(average_prices, reqArea);
    if (prediction < 1000) {
        prediction = 1000;
    } else if (prediction > 1000000) {
        prediction = 1000000;
    }
    
    return (long) prediction;
}

int main()
{
    // long reqArea = 1500;
    // vector<long> area = {1200, 1300, 1200, 1300, 1200, 2000};
    // vector<long> price = {12000, 24000, 14000, 22000, 13000, 30000};
    // long output = valuation(reqArea, area, price);
    // cout << "output: " << output << endl;

    ifstream file("real-tests/tibra/q1-input004.txt");

    long reqArea;
    file >> reqArea;

    int area_count;
    file >> area_count;
    vector<long> area(area_count);
    for (int i = 0; i < area_count; i++) {
        file >> area[i];
    }

    int price_count;
    file >> price_count;
    vector<long> price(price_count);
    for (int i = 0; i < price_count; i++) {
        file >> price[i];
    }

    file.close();

    // for (long l: area) {
    //     cout << l << endl;
    // }
    
    long output = valuation(reqArea, area, price);
    cout << "output: " << output << endl;

    return 0;
}