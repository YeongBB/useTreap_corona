#include<iostream>

using namespace std;

int count_ = 0;  // search 의 횟수 카운트

struct treap
{
	string name = "empty";
	int occur = 0;
	int death = 0;
	double death_n = 0;
	treap* left = NULL, * right = NULL;
};

treap* RightRotate(treap* y)
{
	treap* x = y->left, * T2 = x->right;
	x->right = y;
	y->left = T2;
	return x;
}

treap* LeftRotate(treap* x)
{
	treap* y = x->right, * T2 = y->left;
	y->left = x;
	x->right = T2;
	return y;
}

treap* newnode(string name, int occur, int death)
{
	treap* temp = new treap;
	temp->name = name;
	temp->occur = occur;
	temp->death = death;
	temp->death_n = (double)death / occur * 100;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

treap* search(treap* root, string name)
{
	if (root == NULL)
	{
		cout << " 발견 X" << endl;
		return root;
	}
	else if (root->name == name)
	{
		cout << root->name;
		cout << "  발견 : " << count_ << "번 search" << endl;
		return root;
	}
	cout << root->name << " -> ";
	count_++;
	if (root->name < name)
		return search(root->right, name);
	else
		return search(root->left, name);

}

treap* Add(treap* root, string name, int occur, int death)
{
	if (root == NULL)
		return newnode(name, occur, death);

	if (name <= root->name)
	{
		root->left = Add(root->left, name, occur, death);

		if (root->left->death_n > root->death_n)
			root = RightRotate(root);
	}
	else
	{
		root->right = Add(root->right, name, occur, death);
		if (root->right->death_n > root->death_n)
			root = LeftRotate(root);
	}
	return root;
}

treap* Erase(treap* root)
{
	if (root == NULL)
		return root;


	root->death_n = -100;

	for (root; root->left == NULL && root->right == NULL;)
	{
		root = RightRotate(root);
	}
	if (root->left == NULL)
	{
		cout << "root Node : " << root->name << endl;
		treap* Nod = root->right;
		delete(root);
		root = Nod;
	}
	else if (root->right == NULL)
	{
		cout << "root Node : " << root->name << endl;
		treap* Nod = root->left;
		delete(root);
		root = Nod;
	}
	else if (root->left->death_n < root->right->death_n)
	{
		root = LeftRotate(root);
		root->left = Erase(root->left);
	}
	else
	{
		root = RightRotate(root);
		root->right = Erase(root->right);
	}
	return root;
}

void Oput(treap* root)
{
	if (root)
	{
		Oput(root->left);
		cout << "name : " << root->name << "	occur : " << root->occur << "	death : " << root->death << "	death_n : " << root->death_n << " ";
		cout << endl;

		Oput(root->right);
	}
}

int main()
{
	struct treap* root = NULL;
	string search_name;
	//				  나라    발병수    사망
	root = Add(root, "USA", 1786593, 104319);	//				  FRANCE						
	root = Add(root, "FRANCE", 151753, 28802);	//                /   ＼
	root = Add(root, "KOREA", 11503, 271);		//			  CHINA   ITALY
	root = Add(root, "U.K", 274762, 38489);		//					  /  ＼
	root = Add(root, "RUSSIA", 405843, 4693);	//				  INDIA  U.K
	root = Add(root, "CHINA", 83017, 4634);		//						 /  ＼
	root = Add(root, "TAIWAN", 442, 7);			//					  JAPAN USA
	root = Add(root, "JAPAN", 16884, 892);		//					     ＼
	root = Add(root, "ITALY", 233019, 33415);	//					  	 KOREA 
	root = Add(root, "INDIA", 182143, 5164);	//						   ＼
	//						  TAIWAN
	Oput(root);								// OutPut                       /
	cout << endl;							//                           RUSSIA

	cout << "root Node delete\n" << endl;
	root = Erase(root);						// root->pri값이 가장 큰거 삭제 
	cout << endl;
	Oput(root);								// OutPut
	cout << endl;

	cout << "검색할 나라를 입력 : ";
	cin >> search_name;
	search(root, search_name);		//search
	return 0;
}
