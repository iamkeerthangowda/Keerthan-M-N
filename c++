// 1.Two sum probelms

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> numToIndex;

    for (int i = 0; i < nums.size(); ++i) {
      if (const auto it = numToIndex.find(target - nums[i]);
          it != numToIndex.cend())
        return {it->second, i};
      numToIndex[nums[i]] = i;
    }

    throw;
  }
};

//2. Add two numbers 

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr || carry > 0) {
      if (l1 != nullptr) {
        carry += l1->val;
        l1 = l1->next;
      }
      if (l2 != nullptr) {
        carry += l2->val;
        l2 = l2->next;
      }
      curr->next = new ListNode(carry % 10);
      carry /= 10;
      curr = curr->next;
    }

    return dummy.next;
  }
};

//3.Longest substring without repeptition

class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    int ans = 0;
    vector<int> count(128);

    for (int l = 0, r = 0; r < s.length(); ++r) {
      ++count[s[r]];
      while (count[s[r]] > 1)
        --count[s[l++]];
      ans = max(ans, r - l + 1);
    }

    return ans;
  }
};

//4.median of two sorted Arrays

class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    const int n1 = nums1.size();
    const int n2 = nums2.size();
    if (n1 > n2)
      return findMedianSortedArrays(nums2, nums1);

    int l = 0;
    int r = n1;

    while (l <= r) {
      const int partition1 = (l + r) / 2;
      const int partition2 = (n1 + n2 + 1) / 2 - partition1;
      const int maxLeft1 = partition1 == 0 ? INT_MIN : nums1[partition1 - 1];
      const int maxLeft2 = partition2 == 0 ? INT_MIN : nums2[partition2 - 1];
      const int minRight1 = partition1 == n1 ? INT_MAX : nums1[partition1];
      const int minRight2 = partition2 == n2 ? INT_MAX : nums2[partition2];
      if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1)
        return (n1 + n2) % 2 == 0
                   ? (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) * 0.5
                   : max(maxLeft1, maxLeft2);
      else if (maxLeft1 > minRight2)
        r = partition1 - 1;
      else
        l = partition1 + 1;
    }

    throw;
  }
};

//5.longest palindromic substring

class Solution {
 public:
  string longestPalindrome(string s) {
    if (s.empty())
      return "";

    // (start, end) indices of the longest palindrome in s
    pair<int, int> indices{0, 0};

    for (int i = 0; i < s.length(); ++i) {
      const auto [l1, r1] = extend(s, i, i);
      if (r1 - l1 > indices.second - indices.first)
        indices = {l1, r1};
      if (i + 1 < s.length() && s[i] == s[i + 1]) {
        const auto [l2, r2] = extend(s, i, i + 1);
        if (r2 - l2 > indices.second - indices.first)
          indices = {l2, r2};
      }
    }

    return s.substr(indices.first, indices.second - indices.first + 1);
  }

 private:
  // Returns the (start, end) indices of the longest palindrome extended from
  // the substring s[i..j].
  pair<int, int> extend(const string& s, int i, int j) {
    for (; i >= 0 && j < s.length(); --i, ++j)
      if (s[i] != s[j])
        break;
    return {i + 1, j - 1};
  }
};

//6.zigzag conversion

class Solution {
 public:
  string longestPalindrome(string s) {
    if (s.empty())
      return "";

    // (start, end) indices of the longest palindrome in s
    pair<int, int> indices{0, 0};

    for (int i = 0; i < s.length(); ++i) {
      const auto [l1, r1] = extend(s, i, i);
      if (r1 - l1 > indices.second - indices.first)
        indices = {l1, r1};
      if (i + 1 < s.length() && s[i] == s[i + 1]) {
        const auto [l2, r2] = extend(s, i, i + 1);
        if (r2 - l2 > indices.second - indices.first)
          indices = {l2, r2};
      }
    }

    return s.substr(indices.first, indices.second - indices.first + 1);
  }

 private:
  // Returns the (start, end) indices of the longest palindrome extended from
  // the substring s[i..j].
  pair<int, int> extend(const string& s, int i, int j) {
    for (; i >= 0 && j < s.length(); --i, ++j)
      if (s[i] != s[j])
        break;
    return {i + 1, j - 1};
  }
};

//7.Reverse integer
class Solution {
 public:
  int reverse(int x) {
    long ans = 0;

    while (x != 0) {
      ans = ans * 10 + x % 10;
      x /= 10;
    }

    return (ans < INT_MIN || ans > INT_MAX) ? 0 : ans;
  }
};

//8.string to integer

class Solution {
 public:
  int myAtoi(string s) {
    trim(s);
    if (s.empty())
      return 0;

    const int sign = s[0] == '-' ? -1 : 1;
    if (s[0] == '+' || s[0] == '-')
      s = s.substr(1);

    long num = 0;

    for (const char c : s) {
      if (!isdigit(c))
        break;
      num = num * 10 + (c - '0');
      if (sign * num < INT_MIN)
        return INT_MIN;
      if (sign * num > INT_MAX)
        return INT_MAX;
    }

    return sign * num;
  }

 private:
  void trim(string& s) {
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
  }
};

// palindromic Number

class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0)
      return false;

    long reversed = 0;
    int y = x;

    while (y > 0) {
      reversed = reversed * 10 + y % 10;
      y /= 10;
    }

    return reversed == x;
  }
};

