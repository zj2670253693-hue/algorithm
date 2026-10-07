#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 二叉树的最近公共祖先
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

}
// 相交链表
// 链表节点
struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(nullptr) {}
};
// 创建一段链表，并把末尾连接到 tail
// nodes 负责管理内存，程序结束时自动释放节点
ListNode* buildList(
    const vector<int>& values,
    ListNode* tail,
    vector<unique_ptr<ListNode>>& nodes
) {
    ListNode* head = tail;

    for (int i = static_cast<int>(values.size()) - 1; i >= 0; --i) {
        nodes.push_back(make_unique<ListNode>(values[i]));
        nodes.back()->next = head;
        head = nodes.back().get();
    }

    return head;
}

void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "nullptr\n";
}
// 算法思想：
// 1. 首先记录链表的长度
// 2. 然后找到那个比较长的链表，让这个链表优先走 lana - lanb 步
// 3. 然后两个链表的指针一块走，如果两个指针指向的节点相同，那么就返回，如果遍历到了某个链表的末尾，那么此时就返回null
int getLength(ListNode *cur) {
    int length = 0;
    while (cur != nullptr) {
        length++;
        cur = cur->next;
    }
    return length;
}
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    // 在这里写你的解题代码
    ListNode *curA = headA, *curB = headB;
    int lenA = getLength(headA), lenB = getLength(headB);
    ListNode *list_long;
    ListNode *list_short;
    if (lenA > lenB) {
        list_long = curA;
        list_short = curB;
    }else {
        list_long = curB;
        list_short = curA;
    }
    int diff = abs(lenA - lenB);
    while (diff) {
        list_long = list_long->next;
        diff--;
    }
    while (list_long != nullptr && list_short != nullptr) {
        if (list_long == list_short) {
            return list_short;
        }
        list_long = list_long->next;
        list_short = list_short->next;
    }
    return nullptr;
}
// 三数之和
// 算法思想：
// 1. 首先把vec中的所有元素 全部重排序
// 2. 设置三个指针 分别是 i j k 并且在遍历vec的基础上实现去重
// 3. i 指针是普通指针， j 和 k 指针是对撞指针
// 4。 如果能凑到的最小值已经大于0，那么在这个vec中就没有任何三个元素相加起来等于0的
// 5. 如果i遍历的这个位置上的元素，i指针指向的是这三个指针最小的元素，另外和vec中两个最大的元素相加，如果大于0 那么就进入到下一次循环中
// 6. 因为 j 和 k 指针移动 缩小那两个值
vector<vector<int>> threeSum(vector<int>& nums) {
    // 把vec中的所有元素 排序
    vector<vector<int>> ans;
    sort(nums.begin(),nums.end()); // 升序排序
    int n = nums.size();
    int i = 0;
    for (i = 0;i < n - 2;i++) {
        int j = i + 1,k = n - 1;
        // 固定 nums[i] 时能凑到的最大和仍然 < 0，这个 i 无解，跳下一个
        if(nums[i] + nums[n - 1] + nums[n - 2] < 0){
            continue;
        }
        // 能凑到的最小和已经 > 0，后面的 i 更大，全部无解，直接收工
        if(nums[i] + nums[i + 1] + nums[i + 2] > 0){
            break;
        }
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        while (j < k) {
            // target 必须每轮重算，因为 j、k 一直在变
            int target = nums[i] + nums[j] + nums[k];
            if (target == 0) {
                vector<int> res = {nums[i],nums[j],nums[k]};
                ans.push_back(res);
                j++;
                while (j < k && nums[j] == nums[j - 1]) { // 跳过 j 方向的重复值
                    j++;
                }
                k--;
                while (j < k && nums[k] == nums[k + 1]) { // 跳过 k 方向的重复值
                    k--;
                }
            }else if (target > 0) {
                k--;
            }else {
                j++;
            }
        }
    }
    return ans;
}
// 两数之和 有序版 二分
vector<int> twoSum(vector<int>& numbers, int target) {
    int l = 0, r = numbers.size() - 1;
    while (l < r) {
        int sum = numbers[l] + numbers[r];
        if (sum == target) {
            return {l,r};
        }else if (sum > target) {
            r--;
        }else {
            l++;
        }
    }
    return {};
}
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
    // 创建节点，程序结束时自动释放
    TreeNode n3(3), n5(5), n1(1);
    TreeNode n6(6), n2(2), n0(0), n8(8);
    TreeNode n7(7), n4(4);

    // 连接成题目中的二叉树
    //
    //          3
    //        /   \
    //       5     1
    //      / \   / \
    //     6   2 0   8
    //        / \
    //       7   4

    n3.left  = &n5;
    n3.right = &n1;

    n5.left  = &n6;
    n5.right = &n2;

    n1.left  = &n0;
    n1.right = &n8;

    n2.left  = &n7;
    n2.right = &n4;

    TreeNode* root = &n3;

    // p、q 必须指向树中已有的节点
    TreeNode* p = &n5;
    TreeNode* q = &n1;
    TreeNode* expected = &n3;  // 预期答案：节点 3


    TreeNode* result = lowestCommonAncestor(root, p, q);

    if (result != nullptr) {
        cout << "最近公共祖先：" << result->val << '\n';
    } else {
        cout << "返回 nullptr\n";
    }

    cout << (result == expected ? "测试通过\n" : "测试失败\n");
    std::cout << checkValidString("(((((()*)(*)*))())())(()())())))((**)))))(()())()") << std::endl;
    vector<int> vec = {-100,-70,-60,110,120,130,160};
    threeSum(vec);
    vector<unique_ptr<ListNode>> nodes;

    // 公共部分：只创建一次，两个链表共享这些节点
    ListNode* common = buildList({8, 4, 5}, nullptr, nodes);

    // A 的独立部分：4 -> 1，然后连接公共部分
    ListNode* headA = buildList({4, 1}, common, nodes);

    // B 的独立部分：5 -> 6 -> 1，然后连接同一个公共部分
    ListNode* headB = buildList({5, 6, 1}, common, nodes);

    cout << "A: ";
    printList(headA);

    cout << "B: ";
    printList(headB);

    ListNode* result = getIntersectionNode(headA, headB);

    if (result != nullptr) {
        cout << "返回节点的值：" << result->val << '\n';
    } else {
        cout << "返回 nullptr\n";
    }

    // 比较地址，确保返回的是相交节点本身
    cout << (result == common ? "测试通过\n" : "测试失败\n");
    return 0;
}