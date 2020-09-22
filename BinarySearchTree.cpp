#include<stdio.h>
#include<stdlib.h>

struct Node{
	int key;
	char nama[100];
	struct Node* left;
	struct Node* right;
};

int hash(char nama[]){
	
}

struct Node * root = NULL;

struct Node* createNode(int key){
	struct Node * newNode = (struct Node*) malloc(sizeof(struct Node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;
	return newNode;
}
//Insert Recursive
struct Node * insert(struct Node * curr, int key){
	if(!curr){
		return createNode(key);
	}
	else if(curr->key > key){ // Ke kiri
		curr->left = insert(curr->left, key);
		return curr;
	}
	else if(curr->key < key){ // Ke kanan
		curr->right = insert(curr->right, key);
		return curr;
	}
	else{ //Kalo datanya sama
		printf("Data Exist in the tree\n");
		return curr;
	}
}

//Search
// Recur
void search_recur(struct Node *curr, int target){
	if(!curr){ // kalo g ketemu
		printf("Data %d not found\n", target);
	}
	else if(curr->key == target){ // Kalo Ketemu
		printf("Data %d found inside tree\n", curr->key);
	}
	else if (curr->key < target){// Cek kanan
		search_recur(curr->right, target);
	}
	else if (curr->key > target){ // Cek Kiri
		search_recur(curr->left, target);
	}
}
// Search Loop
void search_iter(int target){
	struct Node * curr = root;
	while(curr){
		if(curr->key == target){// Ketemu
			printf("Data %d found inside tree\n", curr->key);
			return;
		}
		else if(curr->key < target){ //CEK Kanan
			curr = curr->right;
		}
		else if(curr->key > target){
			curr = curr->left;
		}
	}
	printf("Data %d not found\n", target);
	return;
}


// Print / View
/*
	1. In-order
	2. Pre-Order
	3. Post-Order
*/
// Inorder
void inorder(struct Node* curr){
	if(curr != NULL){
		inorder(curr->left);
		//Akses data
		printf("%d ", curr->key);
		
		inorder(curr->right);
	}
}
// PreOrder
void preorder(struct Node* curr){
	if(curr != NULL){
		//Akses data
		printf("%d ", curr->key);
		
		preorder(curr->left);
		preorder(curr->right);
	}
}

//Post Order
void postorder(struct Node* curr){
	if(curr != NULL){
		postorder(curr->left);
		postorder(curr->right);
		
		//Akses data
		printf("%d ", curr->key);
	}
}

//Remove
/*
	1. G punya anak
	2. 1 anak
	3. 2 anak
*/
struct Node * remove(struct Node *curr, int target){
	if(!curr){// Kalo data g ada
		printf("Data %d not exist in tree\n",target);
		return NULL;
	}
	else if(curr->key < target){ //Kanan
		curr->right = remove(curr->right, target);
		return curr;
	}
	else if(curr->key > target){ //Kiri
		curr->left = remove(curr->left, target);
		return curr;
	}
	else{ // Sama  | Ketemu
		//Case 1 (G punya anak)
		if(curr->left == NULL && curr->right == NULL){
			free(curr);
			return NULL;
		}
		//Case 2 (Punya 1 anak)
		if(curr->left == NULL || curr->right == NULL){
			struct Node *subtitue;
			if(curr->left != NULL){
				subtitue = curr->left;
			}
			else{
				subtitue = curr->right;
			}
			free(curr);
			return subtitue;
		}
		//Case 3 (Punya 2 anak)
		if(curr->left != NULL && curr->right != NULL){
			// Cari Penggantinya
			struct Node *subtitue;
			/*
				1. Successor ( setelahnya )
					Paling kecil di anak kanan
					Ke kanan 1x
						ke kiri sampe mentok
				2. Predeccessor ( sebelumnya)
					Paling gede di anak kiri
					Ke kiri 1x
						ke kanan sampe mentok
			*/
//			//Predecessor
//			subtitue = curr->left;
//			while(subtitue->right){
//				subtitue = subtitue->right;
//			}
			//Sucssesor
			subtitue = curr->right;
			while(subtitue->left){
				subtitue = subtitue->left;
			}
			
			// Tuker Nilai
			// curr <- subtitue
			// Kecuali right dan left
			curr->key = subtitue->key;
			
			// Buang si subtitue yang di bawah;
			curr->right = remove(curr->right, subtitue->key);
			return curr;
		}
	}
}

int main(){
	root = NULL;
	root = insert(root, 50);
	root = insert(root, 20);
	root = insert(root, 60);
	root = insert(root, 30);
	root = insert(root, 70);
	
	printf("Inorder   : "); inorder(root); puts("");
	printf("PreOrder  : "); preorder(root); puts("");
	printf("PostOrder : "); postorder(root); puts("");
	
	root = remove(root, 50);
	
	printf("Inorder   : "); inorder(root); puts("");
	printf("PreOrder  : "); preorder(root); puts("");
	printf("PostOrder : "); postorder(root); puts("");
	
//	search_iter(50);
//	search_iter(20);
//	search_iter(10);
	
}
