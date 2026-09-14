class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // Check if one rectangle is entirely outside the other
        bool isLeft   = rec1[2] <= rec2[0];
        bool isRight  = rec1[0] >= rec2[2];
        bool isBottom = rec1[3] <= rec2[1];
        bool isTop    = rec1[1] >= rec2[3];
        
        // If it is entirely outside on any side, they do NOT overlap
        if (isLeft || isRight || isBottom || isTop) {
            return false;
        }
        
        // Otherwise, they must overlap
        return true;
    }
};