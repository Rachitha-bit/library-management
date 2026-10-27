#include <stdio.h>
#include <string.h>

#define MAX 50

struct Request {
    int studentId;
    char studentName[50];
    char bookName[100];
};

struct Queue {
    struct Request requests[MAX];
    int front;
    int rear;
};

struct IssuedBook {
    int studentId;
    char studentName[50];
    char bookName[100];
    int issued;
};

struct IssuedBook issuedBooks[MAX];
int issuedCount = 0;

/* Initialize Queue */
void initializeQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

/* Check whether queue is empty */
int isEmpty(struct Queue *q) {
    return q->front == -1;
}

/* Check whether queue is full */
int isFull(struct Queue *q) {
    return q->rear == MAX - 1;
}

/* Add request to queue */
void enqueue(struct Queue *q) {

    if (isFull(q)) {
        printf("\nQueue is full! Cannot add more requests.\n");
        return;
    }

    struct Request r;

    printf("\nEnter Student ID: ");
    scanf("%d", &r.studentId);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", r.studentName);

    printf("Enter Book Name: ");
    scanf(" %[^\n]", r.bookName);

    if (q->front == -1)
        q->front = 0;

    q->rear++;

    q->requests[q->rear] = r;

    printf("\nBook issue request added successfully!\n");
    printf("Request will be processed in FIFO order.\n");
}

/* Process next request */
void processRequest(struct Queue *q) {

    if (isEmpty(q)) {
        printf("\nNo pending book issue requests.\n");
        return;
    }

    struct Request r = q->requests[q->front];

    printf("\nProcessing Request...\n");
    printf("Student ID   : %d\n", r.studentId);
    printf("Student Name : %s\n", r.studentName);
    printf("Book Name    : %s\n", r.bookName);

    issuedBooks[issuedCount].studentId = r.studentId;
    strcpy(issuedBooks[issuedCount].studentName, r.studentName);
    strcpy(issuedBooks[issuedCount].bookName, r.bookName);
    issuedBooks[issuedCount].issued = 1;

    issuedCount++;

    printf("\nBook issued successfully!\n");

    q->front++;

    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
}

/* Return a book */
void returnBook() {

    if (issuedCount == 0) {
        printf("\nNo books are currently issued.\n");
        return;
    }

    int studentId;
    char bookName[100];

    printf("\nEnter Student ID: ");
    scanf("%d", &studentId);

    printf("Enter Book Name: ");
    scanf(" %[^\n]", bookName);

    int found = 0;

    for (int i = 0; i < issuedCount; i++) {

        if (issuedBooks[i].studentId == studentId &&
            strcmp(issuedBooks[i].bookName, bookName) == 0 &&
            issuedBooks[i].issued == 1) {

            issuedBooks[i].issued = 0;

            printf("\nBook returned successfully!\n");
            printf("Student Name : %s\n", issuedBooks[i].studentName);
            printf("Book Name    : %s\n", issuedBooks[i].bookName);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNo matching issued book found.\n");
    }
}

/* Display pending requests */
void displayQueue(struct Queue *q) {

    if (isEmpty(q)) {
        printf("\nNo pending requests.\n");
        return;
    }

    printf("\n========== PENDING ISSUE REQUESTS ==========\n");

    for (int i = q->front; i <= q->rear; i++) {

        printf("\nStudent ID   : %d", q->requests[i].studentId);
        printf("\nStudent Name : %s", q->requests[i].studentName);
        printf("\nBook Name    : %s\n", q->requests[i].bookName);
    }
}

/* Display issued books */
void displayIssuedBooks() {

    int found = 0;

    printf("\n========== CURRENTLY ISSUED BOOKS ==========\n");

    for (int i = 0; i < issuedCount; i++) {

        if (issuedBooks[i].issued == 1) {

            printf("\nStudent ID   : %d", issuedBooks[i].studentId);
            printf("\nStudent Name : %s", issuedBooks[i].studentName);
            printf("\nBook Name    : %s\n", issuedBooks[i].bookName);

            found = 1;
        }
    }

    if (!found) {
        printf("\nNo books are currently issued.\n");
    }
}

/* Search book */
void searchBook(struct Queue *q) {

    char bookName[100];

    printf("\nEnter Book Name to search: ");
    scanf(" %[^\n]", bookName);

    int found = 0;

    /* Search in issued books */
    for (int i = 0; i < issuedCount; i++) {

        if (issuedBooks[i].issued == 1 &&
            strcmp(issuedBooks[i].bookName, bookName) == 0) {

            printf("\nBook Status: ISSUED\n");
            printf("Issued to: %s\n", issuedBooks[i].studentName);

            found = 1;
        }
    }

    /* Search in pending queue */
    if (!found && !isEmpty(q)) {

        for (int i = q->front; i <= q->rear; i++) {

            if (strcmp(q->requests[i].bookName, bookName) == 0) {

                printf("\nBook Status: REQUEST PENDING\n");
                printf("Requested by: %s\n",
                       q->requests[i].studentName);

                found = 1;
            }
        }
    }

    if (!found) {
        printf("\nBook is currently available.\n");
    }
}

/* Main function */
int main() {

    struct Queue q;

    initializeQueue(&q);

    int choice;

    printf("============================================\n");
    printf(" LIBRARY BOOK ISSUE AND RETURN MANAGEMENT\n");
    printf("============================================\n");

    do {

        printf("\n\n========== LIBRARY MENU ==========\n");
        printf("1. Add Book Issue Request\n");
        printf("2. Process Next Issue Request\n");
        printf("3. Return Book\n");
        printf("4. Display Pending Requests\n");
        printf("5. Display Issued Books\n");
        printf("6. Search Book\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                enqueue(&q);
                break;

            case 2:
                processRequest(&q);
                break;

            case 3:
                returnBook();
                break;

            case 4:
                displayQueue(&q);
                break;

            case 5:
                displayIssuedBooks();
                break;

            case 6:
                searchBook(&q);
                break;

            case 7:
                printf("\nThank you for using the Library Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}

