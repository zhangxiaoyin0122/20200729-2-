/ 方法一:一次左移一个元素
class Solution {
public:
	void LeftRotateStringHelper(string& str) {
		char temp = str[0];
		for (int i = 0; i < str.size() - 1; i++) {
			str[i] = str[i + 1];
		}
		str[str.size() - 1] = temp;
	}
	string LeftRotateString(string str, int n) {
		if (str.size() == 0 || n == 0)
			return str;
		int step = n % str.size();
		while (step--)
			LeftRotateStringHelper(str);
		return str;
	}
};
//方法二:字符串三次逆置
class Solution {
public:
	void reverse(string& str, int start, int end) {
		while (start < end) {
			char temp = str[start];
			str[start] = str[end];
			str[end] = temp;
			start++;
			end--;
		}
	}
	string LeftRotateString(string str, int n) {
		if (str.length() == 0 || n == 0)
			return str;
		int step = n % str.size();
		reverse(str, 0, step - 1); //逆置前半部分
		reverse(str, step, str.size() - 1); //逆置后半部分
		reverse(str, 0, str.size() - 1); //整体逆置
		return str;
	}
};
(2).公司近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish 写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student.a am I”。后来 才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。Cat对一一的翻 转这些单词顺序可不在行，你能帮助他么？

class Solution {
public:
	void reverse(string& str, int start, int end) {
		while (start < end) {
			char temp = str[start];
			str[start] = str[end];
			str[end] = temp;
			start++;
			end--;
		}
	}
	string ReverseSentence(string str) {
		if (str.length() == 0)
			return str;
		int i = 0;
		int j = i;
		int len = str.length();
		//逆置每个单词
		while (j < len) {
			while (j < len && str[j] != ' ') {
				j++;
			}
			reverse(str, i, j - 1);
			while (j < len && str[j] == ' ') {
				j++;
			}
			i = j;
		}
		//逆置最后一个单词
		reverse(str, i, len - 1);
		//整体逆置
		reverse(str, 0, len - 1);
		return str;
	}
};
(3).请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺 序打印，第三行按照从左到右的顺序打印，其他行以此类推。

class Solution {
public:
	vector<vector<int> > Print(TreeNode* pRoot) {
		vector<vector<int> > result;
		if (pRoot == nullptr)
			return result;
		stack<TreeNode*> st; //保存要遍历的节点
		queue<TreeNode*> q; //辅助队列
		st.push(pRoot);
		int dir = 1; //dir == 1,left->right;dir == 2,right->left
		while (!st.empty()) {
			vector<int> v;
			int size = st.size();
			for (int i = 0; i < size; i++) {
				TreeNode* node = st.top();
				v.push_back(node->val);
				st.pop();
				TreeNode* first = (dir == 1) ? node->left : node->right;
				TreeNode* second = (dir == 1) ? node->right : node->left;
				if (first)
					q.push(first);
				if (second)
					q.push(second);
			}
			result.push_back(v);
			//下一轮节点入栈进行逆序
			while (!q.empty()) {
				st.push(q.front());
				q.pop();
			}
			dir = (dir == 1) ? 2 : 1;
		}
		return result;
	}
};


(4).给定一棵二叉搜索树, 请找出其中的第k小的结点。例如， （5，3，7，2，4，6，8）    中，按结点数 值大小顺序第三小结点的值为4。
二叉搜索树中序遍历是递增序列(元素不重复), 即第k小节点就是中序遍历第k个结点.

class Solution {
public:
	TreeNode* KthNode(TreeNode* pRoot, int k) {
		if (pRoot == nullptr || k <= 0)
			return nullptr;
		stack<TreeNode*> st; //定义一个栈,利用栈实现中序遍历
		TreeNode* cur = pRoot;
		//当栈不为空或根节点存在
		while (cur || !st.empty()) {
			//左节点全部入栈
			while (cur) {
				st.push(cur);
				cur = cur->left;
			}
			TreeNode* node = st.top();
			st.pop();
			k--;
			if (k == 0)
				return node;
			cur = node->right;
		}
		return nullptr;
	}
