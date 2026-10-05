#include<bits/stdc++.h>
using namespace std;
void my_sort(vector<int>::iterator begin, vector<int>::iterator end) {
    int n = end - begin;
    for (int i =0;i< n;i++) {
        for (int j = 0;j < n - i - 1;j++) {
            if (begin[j] > begin[j + 1]) {
                int temp = begin[j];
                begin[j] = begin[j + 1];
                begin[j + 1] = temp;
            }
        }
    }
}
vector<int> rearrangeArray(vector<int>& nums) {
    // 移除不同值重排数组
    vector<int> ans;
    while (!nums.empty()) {
        unordered_map<int,int> map;
        for (int num : nums) {
            map[num] ++;
        }
        // 得到字典中不同的key
        vector<int> vec_keys;
        for (auto &[k,v] : map) {
            vec_keys.push_back(k);
        }
        my_sort(vec_keys.begin(),vec_keys.end());
        // 把map中的key 值排序依次添加到ans中，并且map value -1
        for (int k:vec_keys) {
            ans.push_back(k);
            auto it = find(nums.begin(),nums.end(),k);
            if (it != nums.end()) {
                nums.erase(it);
            }
        }
    }
    return ans;
}
bool checkValidString(string s) {
    stack<char> stack;
    vector<char> vec;
    for (char c : s) {
        vec.push_back(c);
    }
    int index = 0;
    while (index < vec.size()) {
        if (vec[index] == '\0') {
            break;
        }
        if (vec[index] == '(' || vec[index] == '*') {
            stack.push(vec[index]);
        }else {
            while (!stack.empty()) {
                if (stack.top() == '(') {
                    stack.pop();
                    break;
                }
                stack.pop();
            }
            if (stack.empty()) return true;
        }
        index++;
        // 如果不是的话，那么就把栈中的字符取出来
    }
    return stack.empty();
}
int main() {
    std::cout << checkValidString("(((((()*)(*)*))())())(()())())))((**)))))(()())()") << std::endl;
    return 0;
}