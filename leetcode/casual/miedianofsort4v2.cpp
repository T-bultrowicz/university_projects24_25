#include<bits/stdc++.h>
using namespace std;

    bool cond(vector<int>& tab1, vector<int>& tab2, int pos1, int pos2) {
        if(pos2 == tab2.size() - 1) {
            return max(tab1[pos1], tab2[pos2]) <= tab1[pos1 + 1];
        } else if(pos1 == tab1.size() - 1) {
            return max(tab1[pos1], tab2[pos2]) <= tab2[pos2 + 1];
        } else {
            return max(tab1[pos1], tab2[pos2]) <= min(tab1[pos1 + 1], tab2[pos2 + 1]);
        }
    }

    double solve_different_problem(vector <int>& t, int x) {
        int s = t.size();
        int damn = (s - 1) / 2;
        if((s + 1) % 2) return (x < t[damn]) ? t[damn] : min(t[damn + 1], x);
        if(x < t[damn - 1]) return (double) (t[damn - 1] + t[damn]) / 2.0;
        else if(x > t[damn + 1]) return (double) (t[damn] + t[damn + 1]) / 2.0;
        else return (double) (t[damn] + x) / 2.0;
    }

    double solve_one_way(vector<int>& nums1, vector<int>& nums2) {
        int x = nums1.size(), y = nums2.size();
        int l = 0, r = y - 1, mid1, mid2;
        int const sum_up = ((x - 1) / 2) + ((y - 1) / 2);
        while(l <= r) {
            mid2 = (l + r) / 2;
            mid1 = sum_up - mid2;
            if(cond(nums1, nums2, mid1, mid2)) {
                break;
            }
            if(nums1[mid1] < nums2[mid2]) {
                r = mid2 - 1;
            } else {
                l = mid2 + 1;
            }
        }
        if(r == -1) nums2[mid2] = min(nums1[mid1 + 1], nums2[mid2]);
        return max(nums1[mid1], nums2[mid2]);
    }

    double solve_other_way(vector<int>& nums1, vector<int>& nums2) {
        int x = nums1.size(), y = nums2.size();
        int l = 0, r = y - 1, mid1, mid2;
        int const sum_up = ((x - 1) / 2) + ((y - 1) / 2);
        while(l <= r) {
            mid2 = (l + r) / 2;
            mid1 = sum_up - mid2;
            if(cond(nums1, nums2, mid1, mid2)) {
                break;
            }
            if(nums1[mid1] < nums2[mid2]) {
                r = mid2 - 1;
            } else {
                l = mid2 + 1;
            }
        }
        if(r == -1) return (double) (min(nums1[mid1 + 2], nums2[0]) + nums1[mid1 + 1]) / 2.0;
        if(mid1 == x - 1) {
            return (double) (max(nums2[mid2],nums1[mid1]) + nums2[mid2 + 1]) / 2.0;
        } else if(mid2 == y - 1) {
            return (double) (max(nums1[mid1],nums2[mid2]) + nums1[mid1 + 1]) / 2.0;
        }
        return (double) (max(nums1[mid1], nums2[mid2]) + min(nums1[mid1 + 1], nums2[mid2 + 1])) / 2.0;     
    }

    double solve_last_way(vector<int>& nums1, vector<int>& nums2) {
        int x = nums1.size(), y = nums2.size();
        int l = 0, r = y - 1, mid1, mid2;
        int const sum_up = ((x - 1) / 2) + ((y - 1) / 2) - 1;
        while(l <= r) {
            mid2 = (l + r) / 2;
            mid1 = sum_up - mid2;
            if(cond(nums1, nums2, mid1, mid2)) {
                break;
            }
            if(nums1[mid1] < nums2[mid2]) {
                r = mid2 - 1;
            } else {
                l = mid2 + 1;
            }
        }
        if(r == -1) return (double) (min(nums1[mid1 + 2],nums2[0]) + nums1[mid1 + 1]) / 2.0;
        if(mid1 == x - 1) {
            return (double) (max(nums1[mid1],nums2[mid2]) + nums2[mid2 + 1]) / 2.0;
        } else if(mid2 == y - 1) {
            return (double) (max(nums2[mid2],nums1[mid1]) + nums1[mid1 + 1]) / 2.0;
        }
        return (double) (max(nums1[mid1], nums2[mid2]) + min(nums1[mid1 + 1], nums2[mid2 + 1])) / 2.0;            
    }    

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int x = nums1.size(), y = nums2.size();
        if(!x) return y % 2 ? nums2[(y - 1) / 2] : (double) (nums2[(y - 1) / 2] + nums2[y / 2]) / 2.0;
        if(!y) return x % 2 ? nums1[(x - 1) / 2] : (double) (nums1[(x - 1) / 2] + nums1[x / 2]) / 2.0;
        if(y == 1 && x == 1) return (double) (nums1[0] + nums2[0]) / 2.0;
        if(x < y) return findMedianSortedArrays(nums2, nums1);
        if(nums1[x - 1] <= nums2[0]) {
            if((x + y) % 2) return nums1[(x + y) / 2];
            else if(x == y) return (double) (nums1[x - 1] + nums2[0]) / 2.0;
            else return (double) (nums1[(x + y - 1) / 2] + nums1[(x + y) / 2]) / 2.0;
        }
        if(nums2[y - 1] <= nums1[0]) {
            if((x + y) % 2) return nums1[((x + y) / 2) - y];
            else if(x == y) return (double) (nums2[y - 1] + nums1[0]) / 2.0;
            else return (double) (nums1[((x + y - 1) / 2) - y] + nums1[((x + y) / 2) - y]) / 2.0;            
        }
        if(y == 1) return solve_different_problem(nums1, nums2[0]);
        if((x + y) % 2) return solve_one_way(nums1, nums2);
        if(x % 2) return solve_last_way(nums1, nums2);
        return solve_other_way(nums1, nums2);
    }

int main() {
    int x, y;
    cin >> x >> y;
    vector <int> nums1(x), nums2(y);
    for(int i = 0; i < x; i++) {
        cin >> nums1[i];
    }
    for(int i = 0; i < y; i++) {
        cin >> nums2[i];
    }
    cout << findMedianSortedArrays(nums1, nums2);
}