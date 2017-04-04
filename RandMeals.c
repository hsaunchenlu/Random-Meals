#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct node{
	char food[30];
	struct node *next;
};

typedef struct node node;
node *getnode(){
	node *p;
	p = (node*)malloc(sizeof(node));
	
	if (p == NULL){
		puts("Memory is not enough");
		exit(1);
	}
	return(p);
}

void freenode(node *p){
	free(p);
}


node *insert_node(node *head,node* ptr,node data){
	node *new_node;
	new_node = getnode();
	*new_node = data;
	new_node->next = NULL;
	if (ptr == NULL){
		new_node->next = head;
		head = new_node;
		
	}else{
		if (ptr->next == NULL){
			ptr->next = new_node;
		}else{
			new_node->next = ptr->next;
			ptr->next = new_node;
		}
	}
	return(head);
}

node *find_node(node *head,char people[30]){
	node *ptr;
	ptr = head;
	char *a[30],*b[30];
	int c;
	*b = people;
	while(ptr != NULL){
		*a = ptr->food; 
		c = strcmp(*a,*b);
		if (c == 0){
			return(ptr);
		}	
		ptr=ptr->next;
	}
	return(ptr);
}

node *delete_node(node *head,node *ptr){
	node *previous;
	if (ptr == head){
		head = head->next;
	}else{
		previous = head;
		while(previous->next != ptr){
			previous = previous->next;
		}
		if (ptr->next == NULL){
			previous->next = NULL;
		}else{
			previous->next = ptr->next;
		}
	}
	freenode(ptr);
	
	return(head);
}

int main(int argc, char *argv[]) {
	node *head, *ptr;
	node data;
	char op;
	int pos,randnum,i;
	int count = 0;
	char choose[30];
	head = NULL;
	ptr = head;
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
	FILE *fin, *fout;
	
	fout = fopen("food","a+t");
	fin = fopen("food","rt");
	
	while(1){
		fscanf(fin,"%s",data.food);
		if(!feof(fin)){
			count += 1;
			if(head == NULL){
				head = insert_node(head,NULL,data);
			}else{
				ptr = head;
				while(ptr->next!=NULL && ptr->next)
				ptr = ptr->next;
				head = insert_node(head,ptr,data);
			}
			
		}else{
			break;
		}
			
		//if() break;
	}
	
	
	
	while(1){
		puts("e: Today's food");
		puts("i: Insert a new food name");
		puts("d: Delete a food name");
		puts("f: Find a food name");
		puts("l: List all food");
		puts("q: Quit");
			
		scanf(" %c", &op);
		
		switch(op){
			case 'i':
				puts("Food's name");
				scanf("%s",&data.food);
		
				if(head == NULL){
					head = insert_node(head,NULL,data);
				}else{
					ptr = head;
					while(ptr->next!=NULL && ptr->next)
					ptr = ptr->next;
					head = insert_node(head,ptr,data);
				}		
				fprintf(fout,"%s\n",&data.food);
				count += 1;
				break;
				
			case 'l':
				ptr = head;
				while(ptr != NULL){
					printf("food: %s\n",ptr->food);
					puts("=============");
					ptr = ptr->next;
				}
				break;
				
			case 'd':
				
				puts("Food's name");
				scanf("%s",&choose);
				ptr = find_node(head,choose);
				
				if (ptr == NULL){
					puts("Not found the food");
				}else{
					puts("Delete ok!");
					head = delete_node(head,ptr);
			   }
				break;
			case 'f':
				puts("Food's name");
				scanf("%s",&choose);
				ptr = find_node(head,choose);
				
				if(ptr == NULL)
					puts("Not found");
				else{
					printf("Found the member! \nFood's name : %s", ptr->food);
				}
				break;
			case 'q':
				ptr = head;
				while(ptr!=NULL){
					freenode(ptr);
					ptr=ptr->next;
				}
				return 0;
				break;
			case 'e':
				randnum = rand()%count;
				ptr = head;
				for (i=0;i<count;i++){
					if (i == randnum){
						printf("Today's food is: %s\n",ptr->food);
					}
					ptr = ptr->next;
				}
				break;
			default:
				puts("Wrong commend! Input again.");
				break;
		}
		system("pause");
		system("cls");
	}
	
	
	return 0;
}
