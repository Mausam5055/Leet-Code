#include <vector>
#include <algorithm>

class Solution {
public:
    int minimumEffort(std::vector<std::vector<int>>& tasks) {
        // Sort the tasks based on the difference (minimum - actual) in descending order.
        // This greedy approach ensures we pick tasks that require a high starting energy 
        // but consume less, leaving us with more residual energy for the next tasks.
        std::sort(tasks.begin(), tasks.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });
        
        int min_initial_energy = 0;
        int current_energy = 0;
        
        for (const auto& task : tasks) {
            int actual = task[0];
            int minimum = task[1];
            
            // If we don't have enough current energy to start this task, 
            // we must have started with more energy initially.
            if (current_energy < minimum) {
                min_initial_energy += (minimum - current_energy);
                current_energy = minimum;
            }
            
            // Deduct the actual energy spent on this task
            current_energy -= actual;
        }
        
        return min_initial_energy;
    }
};