#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[50];
    char author[50];
    int quantity;
};

void addBook();
void displayBooks();
void searchBook();
void issueBook();
void returnBook();
void deleteBook();

int main() {
    int choice;

    while (1) {
        printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Delete Book\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: deleteBook(); break;
            case 7: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addBook() {
    struct Book b;
    FILE *fp = fopen("library.dat", "ab");

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Title: ");
    scanf(" %[^\n]", b.title);
    printf("Enter Author: ");
    scanf(" %[^\n]", b.author);
    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("Book Added Successfully!\n");
}

void displayBooks() {
    struct Book b;
    FILE *fp = fopen("library.dat", "rb");

    printf("\n--- Book Records ---\n");

    while (fread(&b, sizeof(b), 1, fp)) {
        printf("\nID: %d", b.id);
        printf("\nTitle: %s", b.title);
        printf("\nAuthor: %s", b.author);
        printf("\nQuantity: %d\n", b.quantity);
    }

    fclose(fp);
}

void searchBook() {
    struct Book b;
    int id, found = 0;
    FILE *fp = fopen("library.dat", "rb");

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\nBook Found!\n");
            printf("Title: %s\nAuthor: %s\nQuantity: %d\n", b.title, b.author, b.quantity);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found!\n");

    fclose(fp);
}

void issueBook() {
    struct Book b;
    int id;
    FILE *fp = fopen("library.dat", "rb+");

    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id && b.quantity > 0) {
            b.quantity--;
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);
            printf("Book Issued Successfully!\n");
            fclose(fp);
            return;
        }
    }

    printf("Book not available!\n");
    fclose(fp);
}

void returnBook() {
    struct Book b;
    int id;
    FILE *fp = fopen("library.dat", "rb+");

    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            b.quantity++;
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);
            printf("Book Returned Successfully!\n");
            fclose(fp);
            return;
        }
    }

    printf("Book not found!\n");
    fclose(fp);
}

void deleteBook() {
    struct Book b;
    int id;
    FILE *fp = fopen("library.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id != id) {
            fwrite(&b, sizeof(b), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("library.dat");
    rename("temp.dat", "library.dat");

    printf("Book Deleted Successfully!\n");
}