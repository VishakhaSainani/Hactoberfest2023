#include<iostream>
using namespace std;
#include<string>

struct AVLnode
{
	string word;
	string meaning;
	AVLnode* left,*right;
	//int bf;
	int ht;
};

class AVLtree
{
	public:
    	AVLnode *root;

		AVLtree()
		{
			root=NULL;
		}
		AVLnode* insert(AVLnode*,string,string);
		int height(AVLnode *T);
		AVLnode *rotate_right(AVLnode*);
		AVLnode *rotate_left(AVLnode*);
		AVLnode* LL(AVLnode*);
		AVLnode *RR(AVLnode*);
		AVLnode* LR(AVLnode*);
		AVLnode* RL(AVLnode*);
        AVLnode* update(AVLnode* root, string targetKey, string newMeaning);
        AVLnode* remove(AVLnode* root, string targetKey);
		int BF(AVLnode *T);
		void ascending(AVLnode *T);
		void descending(AVLnode *T);
		void create();
        AVLnode* search(AVLnode* root, string targetKey,int comparisons );
        void printLevelOrder(AVLnode* root);
        void printCurrentLevel(AVLnode* root, int level);


};

AVLnode* AVLtree::insert(AVLnode *root,string newkey,string mean)
{
	AVLnode *curr;
	int lh,rh;
	if(root==NULL)
	{
		curr=new AVLnode;
		curr->word=newkey;
		curr->meaning=mean;
		curr->ht=0;
		curr->left=curr->right=NULL;
        root=curr;
	}
	else
	{
		if(newkey<root->word)
		{
			root->left=insert(root->left,newkey,mean);
			if(BF(root)==2)
			{
				if(newkey<root->left->word)
					root=LL(root);
				else
					root=LR(root);
			}
		}
		else if(newkey>root->word)
		{
			root->right=insert(root->right,newkey,mean);
			if(BF(root)==-2)
			{
				if(newkey>root->right->word)
					root=RR(root);
				else
					root=RL(root);
			}
		}
		else
			cout<<"Duplicate";
	}               
	root->ht=height(root);
	return root;
}

void AVLtree::create()
{
	string w,m;
	char ch;
	do
	{
	cout<<"Enter word : ";
	cin>>w;
	cout<<"Enter meaning : ";
	cin>>m;
	root=insert(root,w,m);
	cout<<"Do you want to add more(y/n) : ";
	cin>>ch;
	}while(ch=='y' || ch=='Y');

}


int AVLtree::height(AVLnode *T)
{
	int hl,hr;
	if(T==NULL) 
		return 0;
	if(T->left==NULL && T->right==NULL)
		return 1;
	hl=height(T->left);
	hr=height(T->right);
	if(hl<hr)
		return hr+1;
	else
		return hl+1;
}

AVLnode* AVLtree::rotate_right(AVLnode* x)
{
	AVLnode *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	return y;
}

AVLnode* AVLtree:: rotate_left(AVLnode *x)
{
	AVLnode *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	return y;
}

AVLnode*AVLtree::LL(AVLnode *T)
{
	cout<<"\nLL rotation\n";
	T=rotate_right(T);
	return T;
}

AVLnode*AVLtree::LR(AVLnode *T)
{
	cout<<"\nLR rotation\n";
	T->left=rotate_left(T->left);
	T=rotate_right(T);
	return T;
}

AVLnode*AVLtree::RR(AVLnode *T)
{
	cout<<"\nRR rotation\n";
	T=rotate_left(T);
	return T;
}

AVLnode*AVLtree::RL(AVLnode *T)
{
	cout<<"\nRL rotation\n";
	T->right=rotate_right(T->right);
	T=rotate_left(T);
	return T;
}

int AVLtree::BF(AVLnode *T)
{
	int l,r;
	l=height(T->left);
	r=height(T->right);
	return l-r;
}

void AVLtree::ascending(AVLnode *T)
{
	if(T==NULL)
		return ;
	ascending(T->left);
	cout<<T->word<<" : "<<T->meaning<<endl;
	ascending(T->right);
}

void AVLtree::descending(AVLnode *T)
{
	if(T==NULL)
		return ;
    descending(T->right);
    cout<<T->word<<" : "<<T->meaning<<endl;
	descending(T->left);
	
	
}

void AVLtree ::printLevelOrder(AVLnode* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}
 
/* Print nodes at a current level */
void AVLtree::printCurrentLevel(AVLnode* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        cout << root->word << " ";
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}




AVLnode* AVLtree::update(AVLnode* root, string targetKey, string newMeaning)
{
    if (root == NULL)
    {
        cout << "Key not found: " << targetKey << endl;
        return root;
    }

    if (targetKey < root->word)
    {
        root->left = update(root->left, targetKey, newMeaning);
    }
    else if (targetKey > root->word)
    {
        root->right = update(root->right, targetKey, newMeaning);
    }
    else
    {
        root->meaning = newMeaning;
        cout << "Updated meaning for key " << targetKey << endl;
    }

    root->ht = height(root);
    return root;
}

AVLnode* AVLtree::remove(AVLnode* root, string targetKey)
{
    if (root == NULL)
    {
        cout << "Key not found: " << targetKey << endl;
        return root;
    }

    if (targetKey < root->word)
    {
        root->left = remove(root->left, targetKey);
    }
    else if (targetKey > root->word)
    {
        root->right = remove(root->right, targetKey);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            cout << "Deleted key: " << targetKey << endl;
        }
        else if (root->left == NULL)
        {
            AVLnode* temp = root;
            root = root->right;
            delete temp;
            cout << "Deleted key: " << targetKey << endl;
        }
        else if (root->right == NULL)
        {
            AVLnode* temp = root;
            root = root->left;
            delete temp;
            cout << "Deleted key: " << targetKey << endl;
        }
        else
        {
            AVLnode* minNode = root->right;
            while (minNode->left != NULL)
            {
                minNode = minNode->left;
            }
            root->word = minNode->word;
            root->meaning = minNode->meaning;
            root->right = remove(root->right, minNode->word);
        }
    }

    if (root != NULL)
    {
        root->ht = height(root);
        if (BF(root) == 2)
        {
            if (BF(root->left) >= 0)
                root = LL(root);
            else
                root = LR(root);
        }
        else if (BF(root) == -2)
        {
            if (BF(root->right) <= 0)
                root = RR(root);
            else
                root = RL(root);
        }
    }

    return root;
}
// AVLnode* AVLtree::search(AVLnode* root, string targetKey,int comparisons )
// {
//     if (root == NULL || root->word == targetKey)
//     {
//         comparisons++; // Increment the comparison count
//         cout<<"\nWord prsent\nNumber of comparisons required: "<<comparisons<<endl;
//         return root;
//     }

//     comparisons++; // Increment the comparison count

//     if (targetKey < root->word)
//     {
//         return search(root->left, targetKey,comparisons);
//     }
//     else
//     {
//         return search(root->right, targetKey,comparisons);
//     }
// }


AVLnode* AVLtree::search(AVLnode* root, string targetKey, int comparisons)
{
    if (root == NULL)
    {
        cout << "\nWord not found\nNumber of comparisons: " << comparisons << endl;
        return root;
    }

    if (root->word == targetKey)
    {
        comparisons++; // Increment the comparison count
        cout << "\nWord found\nNumber of comparisons: " << comparisons << endl;
        return root;
    }

    comparisons++; // Increment the comparison count

    if (targetKey < root->word)
    {
        return search(root->left, targetKey, comparisons);
    }
    else
    {
        return search(root->right, targetKey, comparisons);
    }
}

int main()
{
	AVLtree a;
    int n;
    //AVLnode *root;
    //a.root=NULL;
    while(true){
        cout<<"\n1)Add\n2)Update\n3)Delete\n4)Ascending order\n5)Descending order\n6)Search\n7)Level-Order\nEnter choice:-";
        cin>>n;string w,m; 
        switch(n){
            case 1:
                a.create();
                break;
            case 2:
                 cout<<"Enter word whose meaning is to be updated";
                cin>>w;
                 cout<<"Enter the new meaning:"; cin>>m;
                 a.update(a.root,w,m);
                 break;
            case 3:
                
                cout<<"Enter word to be deleted"; 
                cin>>w;
                a.remove(a.root,w);
            case 4:
                a.ascending(a.root);
                break;
            case 5:
                a.descending(a.root);
                break;
            case 6:
            cout<<"Enter the word to search:-"; 
            cin>>w;
            a.search(a.root,w,0);
            break;
            case 7:
                a.printLevelOrder(a.root);
                break;

        }
    }

}
