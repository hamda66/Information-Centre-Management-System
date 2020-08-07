#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct student{
    char name[50];
    int id;
};

typedef struct book{
	int ISBN;
	char title[30];
	char author [30];
	char category[20];
        struct book* next;

}book;

struct book *root = NULL;
struct book *books;
struct student *s;



FILE *library;
FILE *students;
FILE *Bbook;



void newBook();
void viewBook();
void deleteBook(book* root, int ISBN);
void borrowBook(book* root, int ISBN);
void admisEN();
void displayborrowed();
void addstudent();
void veiwstudent();
void studentEN();




int main() {	 
	 int choice;

        printf("\n\t\t\t\t--------<<LIBRARY MANAGEMENT SYSTEM>>-----------\n");
	  
	printf("Enter user type: \n");
	printf("\t\t1.administration \t 2.student \n");
	  scanf("%d", &choice);
	  if (choice>3){
              printf("invalid input try again ");
              main();
          }
          else{
	  if (choice == 1){
	  	admisEN();
	  }
	  else if (choice == 2){
                  addstudent();            
	 }
          }
	  	  
}//done

void studentEN(){
    
    int op;
    do{
     printf("options:  \n");
                  printf("\t1.view books in library  \t2.borrow book \t3.main menu \n");
                  scanf("%d", &op);
 	
 	if (op == 1){
             viewBook();
            }
        else if (op == 2){
            int ISBN ;
            printf("enter the ISBN of the book you wanted to borrow:");
            scanf("%d", &ISBN);
            borrowBook(root,ISBN);
        }
        else if (op==3){
           main(); }
        else{
            printf("invalid input try again ");
            studentEN();}
    }while (0<op && 3>op);       
}

void admisEN(){
	
		int choice, i;
                int ISBN;
	
	printf("               \n\t\t\t\t--------<<WELCOME>>-----------\n");
	
	do{
	  	printf("\n");
	  printf("\t\t- - - - - - - - - - - - - - - - - - - - - - - -- - - - - - -- - - --- - - - \n ");
	  printf("choose a number : \t");	  
	  printf("1.add new book\t");
	  printf("2.view books\t");
	  printf("3.delete book\t");
          printf("4.view students \t");
          printf("5.view borrowed book\t");
          printf("6.main menu\t");
	  printf("\t\t - - - - - -- - -- - -  -- - -  - - - - - - -- - - - -- -  -- - - -- - - -- - -\n");
	  scanf("%d", &choice);
	  
          switch(choice){
                  case 1:
                         newBook();
                         break;
                  case 2:       
	  	         viewBook();
                         break;
                  case 3:
                      printf("enter the ISBN of book :");
                      scanf("%d",&ISBN);
                      deleteBook(root,ISBN);
                      break;
                  case 4:
                       veiwstudent();
                       break;
                       
                  case 5:
                      displayborrowed();
                      break;
              case 6 :
                  main();
                  break;
                  
              default : 
                  printf("wrong choice please try again");
                  admisEN();
                  break;
                  
          }
	  

}while (1);

}//done

void newBook(){
     struct book *books = (struct book*)malloc(sizeof(struct book)); 
	

printf("enter book title: \n");
scanf("%s",books->title);


printf("enter author name: \n\t");
scanf("%s",books->author);


printf("enter ISBN : \n\t");
scanf("%d", &books->ISBN);


printf("enter category : \n\t");
scanf("%s", books->category);

books->next = NULL;

if (root == NULL){
    root = books;
}
else{
    struct book *p = root;
    
    while (p->next != NULL){
        p = p->next;
    }
    p->next = books;
}
 	
}//done

void addstudent(){
    
    struct student *s = (struct student*)malloc(sizeof(struct student));
	students =fopen("students.txt","a");
	
        if (students == NULL){
            printf("Could not open file"); 
             exit(0); }
        
      else{
	
	printf ("enter name : \n");
	scanf("%s",s->name);
	fprintf(students, "%s \t",&s->name);
        
	printf("enter ID: \n");
	scanf("%d",&s->id);
	fprintf(students, "%d \t", s->id);}
        
	fclose(students);
        
        studentEN();

} //done

void viewBook(){
struct book *tmp ;
    if(root == NULL){
        printf(" There is no books in the list");
    }
    else{
     tmp = root;
     while(tmp->next != NULL){
         printf("ISBN : %d\t title : %s\t author : %s\t category : %s\t \n",tmp->ISBN,tmp->title,tmp->author,tmp->category); 
         tmp = tmp->next;
        }
     printf("ISBN : %d\t title : %s\t author : %s\t category : %s\t \n",tmp->ISBN,tmp->title,tmp->author,tmp->category); 
    }
} //done

void veiwstudent(){
	
	char str [1000000];
	
	students = fopen("students.txt","r");
                if (students == NULL){
            printf("Could not open file"); 
         exit(0); }
        
      else{
	rewind(students);
	while (fgets(str,1000000,students) != NULL)
	printf("%s",str);}
	
	fclose(students);
} //done

void borrowBook(book* root, int ISBN){
    book *p,*q;
    
    Bbook = fopen("Bbook.txt","w+");
    
    q = root;
    p = root->next;
    
    if (q->ISBN == ISBN){
        root = p;
        fprintf(Bbook, "%d \t",q->ISBN);
        fprintf(Bbook, "%s \t",q->title);
        fprintf(Bbook, "%s \t",q->author);
        fprintf(Bbook, "%s \t",q->category);
        free(q);
    }
    else{
        while (p->ISBN != ISBN){
            p = p->next;
            q = q->next;
        }
        
        if (p->next == NULL){
            q->next = NULL;
             fprintf(Bbook, "%d \t",p->ISBN);
             fprintf(Bbook, "%s \t",p->title);
             fprintf(Bbook, "%s \t",p->author);
             fprintf(Bbook, "%s \t",p->category);
            free(p);
        }
        else {
            q->next = p->next;
            fprintf(Bbook, "%d \t",p->ISBN);
             fprintf(Bbook, "%s \t",p->title);
             fprintf(Bbook, "%s \t",p->author);
             fprintf(Bbook, "%s \t",p->category);
            free(p);
        }
    }
        
    fclose(Bbook);
    printf("<<< you borrowed the book successfully >>> /n");
} //

void deleteBook(book *head,int ISBN){
    book *p,*q;
     
    q = root;
    p = root->next;
    
    if (q->ISBN == ISBN){
        root = p;
        free(q);
    }
    else{
        while (p->ISBN != ISBN){
            p = p->next;
            q = q->next;
        }
        
        if (p->next == NULL){
            q->next = NULL;
            free(p);
        }
        else {
            q->next = p->next;
            free(p);
        }
    }
} //done

void displayborrowed(){
    char str [1000000];
	
	Bbook = fopen("Bbook.txt","r");
                if (Bbook == NULL){
            printf("Could not open file"); 
            exit(0); }
        
      else{
	rewind(Bbook);
	while (fgets(str,1000000,Bbook) != NULL)
	printf("%s",str);}
	
	fclose(Bbook);  
}
