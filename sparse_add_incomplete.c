#include<stdio.h>
#include<stdlib.h>
struct node
{
	int row;
	int column;
	int val;
	struct node* next;
};
struct node* start= NULL;
struct node* start1= NULL;
struct node* start2= NULL;
struct node* start3= NULL;
struct node* create_sll(struct node* start, int row, int column, int val );
struct node* add_mat(struct node* start1, struct node* start2, struct node* start3);
struct node* add_val(struct node* start3, int, int, int);
void display(struct node* start);
void display_mat(struct node*, int , int );

void main()
{
	int i,j,m,n,option;
	printf("enter the row size and column size: ");
	scanf("%d %d",&m,&n);
	int a[m][n], b[m][n];
	do
    {
    	printf("\n\n***MAIN MENU***");
    	printf("\nenter 1 : To enter matrix 1 elements.");
    	printf(" \nenter 2 : To display matrix 1 linkedlist.");
    	printf("\nenter  3: To enter matrix 2 elements.");
    	printf(" \nenter 4 : To display matrix 2 linkedlist.");
    	printf("\n enter 5 : To add the sparse matrices.");
    	printf("\nenter 6 : To display Addition Matrix.");
    	printf("\nenter 7 : EXIT.");
    	printf("\nenter the option :");
    	scanf("%d",&option);
    	switch(option)
    	{
    		case 1:
    			printf("enter the matrix 1 elements: ");
				for(i=0;i<m;i++)
					for(j=0;j<n;j++)
						scanf("%d",&a[i][j]);
    			for(i=0;i<m;i++)
					for(j=0;j<n;j++)
						if(a[i][j]!=0)
							start1= create_sll(start1, i, j, a[i][j]);
    			printf("\n linked list is created");
    			break;
    	    case 2:
			    display(start1);
			    break;
			case 3:
    			printf("enter the matrix 2 elements: ");
				for(i=0;i<m;i++)
					for(j=0;j<n;j++)
						scanf("%d",&b[i][j]);
    			for(i=0;i<m;i++)
					for(j=0;j<n;j++)
						if(b[i][j]!=0)
							start2= create_sll(start2, i, j, b[i][j]);
    			printf("\n linked list is created");
    			break;
			case 4:
			    display(start2);
			    break;	
			case 5: 
					start3=add_mat(start1, start2, start3);
					printf("\nLinkedlist is created");
					break;
			case 6:
					printf("\nAddition Matrix in Linked List\n");
					display(start3);
					printf("\nAddition Matrix in Matrix Form\n");
					display_mat(start3, m, n);
					break;			 
		}
	}while(option != 7);
}

struct node* create_sll(struct node* start, int r, int c, int v)
{
	struct node* new_node, *ptr;
	new_node=(struct node*)malloc(sizeof(struct node));
	new_node->row=r;
	new_node->column=c;
	new_node->val=v;
	if(start==NULL)
	{
		new_node->next=NULL;
		start=new_node;
	}
	else
	{
		ptr=start;
		while(ptr->next != NULL)
			ptr=ptr->next;
		ptr->next=new_node;
		new_node->next=NULL;	
	}
	return start;
}

void display(struct node* start)
{
	struct node* ptr=start;
	printf("\nRow   : ");
	while(ptr!=NULL)
	{
		printf("%d ",ptr->row);
		ptr=ptr->next;
	}
	ptr=start;
	printf("\nColumn: ");
	while(ptr!=NULL)
	{
		printf("%d ",ptr->column);
		ptr = ptr->next;
	}
	ptr = start;
	printf("\nValues: ");
	while(ptr != NULL)
	{
		printf("%d ",ptr->val);
		ptr = ptr->next;
	}
}

struct node* add_mat(struct node* start1, struct node* start2, struct node* start3)
{
	struct node *a, *b;
	int sum;
	a=start1, b=start2;
	while(a!=NULL && b!=NULL)
	{
		if(a->row == b->row && a->column == b->column )
		{
			sum = a->val + b->val;
			start3 = add_val(start3, sum, a->row, a->column );
			a = a->next;
			b = b->next;
		}
		else if(a->row == b->row && a->column < b->column )
		{
			start3 = add_val(start3, a->val, a->row, a->column );
			a = a->next;
		}
		else if(a->row == b->row && b->column < a->column )
		{
			start3 = add_val(start3 , b->val, b->row , b->column );
			b = b->next;
		}
		else if(a->row < b->row)
		{
			start3 = add_val(start3, a->val, a->row, a->column );
			a = a->next;
		}
		else 
		{
			start3 = add_val(start3, b->val, b->row, b->column );
			b = b->next;
		}
	}
	if(a == NULL)
	{
		while(b != NULL)
		{
			start3 = add_val(start3, b->val, b->row, b->column );
			b = b->next;
		}
	}
	if(b == NULL)
	{
		while(a != NULL)
		{
			start3= add_val(start3, a->val, a->row, a->column );
			a=a->next;
		}
	}
	return start3;
}

struct node* add_val(struct node* start3, int sum, int r, int c)
{
	struct node *ptr, *newnode;
	newnode=(struct node*)malloc(sizeof(struct node));
	newnode->row = r;
	newnode->column = c;
	newnode->val = sum;
	if(start3 == NULL)
	{
		newnode->next = NULL;
		start3=newnode;
	}
	else
	{
		ptr=start3;
		while(ptr->next != NULL)
			ptr = ptr->next;
		newnode->next = NULL;
		ptr->next= newnode;	
	}
	return start3;
}

void display_mat(struct node* start3, int m, int n)
{
	struct node* ptr=start3;
	int i, j, c[m][n];
	for(i=0 ; i<m ; i++)
	{
		for(j=0 ; j<n ; j++)
		{
			if(ptr!=NULL)
			{
				if(i==ptr->row && j==ptr->column )
				{
					c[i][j]=ptr->val;
				}
				else 
				c[i][j]=0;
			}
		}
		ptr=ptr->next;
	}
	for(i=0 ; i<m ; i++)
	{
		for(j=0 ; j<n ; j++)
			printf("%d ",c[i][j]);
		printf("\n");	
	}
}
