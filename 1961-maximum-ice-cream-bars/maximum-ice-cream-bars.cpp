class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        int maxCost = *max_element(costs.begin(), costs.end());

        vector<int> count(maxCost + 1, 0);

        for (int cost : costs) {
            count[cost]++;
        }

        int ans = 0;

        for (int price = 1; price <= maxCost; price++) {
            if (count[price] == 0) continue;

            int canBuy = min(count[price], coins / price);

            ans += canBuy;
            coins -= canBuy * price;

            if (coins < price) continue;
        }

        return ans;
    }
};