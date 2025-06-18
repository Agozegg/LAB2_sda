#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT_ERROR -1

typedef struct Car {
    int id;
    char brand[50];
    char model[50];
    int year;
    float price;
    struct Car* next;
} Car;

typedef enum {
    INSERT_AT_END = 1,
    INSERT_AT_BEGGING = 2,
    INSERT_AT_POSITION = 3,
    DISPLAYING_LIST = 4,
    SEARCH_BY_ID = 5,
    DELETE_AT_POSITION = 6,
    REVERSING_LIST = 7,
    SORTING_BY_PRICE = 8,
    CLEARING_LIST = 9,
    SEARCHING_BY_BRAND = 10,
    SEARCHING_BY_MODEL = 11,
    SEARCHING_BY_YEAR = 12,
    SEARCHING_BY_PRICE = 13,
} Order;

Car* create_car() {
    Car* new_car = (Car*)malloc(sizeof(Car));
    if (!new_car) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    printf("Enter ID: ");
    scanf("%d", &new_car->id);
    printf("Enter Brand: ");
    scanf(" %[^\n]", new_car->brand);
    printf("Enter Model: ");
    scanf(" %[^\n]", new_car->model);
    printf("Enter Year: ");
    scanf("%d", &new_car->year);
    printf("Enter Price: ");
    scanf("%f", &new_car->price);

    new_car->next = NULL;
    return new_car;
}

Car* insert_at_end(Car* head) {
    Car* new_car = create_car();
    if (!new_car) return head;

    if (head == NULL) {
        return new_car;
    }

    Car* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_car;
    return head;
}

Car* insert_at_beginning(Car* head) {
    Car* new_car = create_car();
    if (!new_car) return head;
    new_car->next = head;
    return new_car;
}

Car* insert_at_position(Car* head, int position) {
    if (position < 1) {
        printf("Invalid position!\n");
        return head;
    }

    if (position == 1) {
        return insert_at_beginning(head);
    }

    Car* new_car = create_car();
    if (!new_car) return head;

    Car* temp = head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position!\n");
        free(new_car);
        return head;
    }

    new_car->next = temp->next;
    temp->next = new_car;
    return head;
}

void display_list(Car* head) {
    if (head == NULL) {
        printf("The list is empty!\n");
        return;
    }
    Car* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Brand: %s, Model: %s, Year: %d, Price: %.3f\n",
               temp->id, temp->brand, temp->model, temp->year, temp->price);
        temp = temp->next;
    }
}

int search_by_id(Car* head, int id) {
    Car* temp = head;
    int position = 1;
    while (temp != NULL) {
        if (temp->id == id) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return OUTPUT_ERROR;
}

void search_by_brand(Car* head, const char* brand) {
    Car* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->brand, brand) == 0) {
            printf("ID: %d, Brand: %s, Model: %s, Year: %d, Price: %.3f\n",
                   temp->id, temp->brand, temp->model, temp->year, temp->price);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No car found with brand: %s\n", brand);
    }
}

void search_by_model(Car* head, const char* model) {
    Car* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->model, model) == 0) {
            printf("ID: %d, Brand: %s, Model: %s, Year: %d, Price: %.3f\n",
                   temp->id, temp->brand, temp->model, temp->year, temp->price);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No car found with model: %s\n", model);
    }
}

void search_by_year(Car* head, int year) {
    Car* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (temp->year == year) {
            printf("ID: %d, Brand: %s, Model: %s, Year: %d, Price: %.3f\n",
                   temp->id, temp->brand, temp->model, temp->year, temp->price);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf( "No car found from year: %d\n", year);
    }
}

void search_by_price(Car* head, float price) {
    Car* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (temp->price == price) {
            printf("ID: %d, Brand: %s, Model: %s, Year: %d, Price: %.3f\n",
                   temp->id, temp->brand, temp->model, temp->year, temp->price);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No car found with price: %.3f\n", price);
    }
}

Car* delete_at_position(Car* head, int position) {
    if (head == NULL || position < 1) {
        printf("Invalid position or empty list!\n");
        return head;
    }

    Car* temp = head;
    if (position == 1) {
        head = head->next;
        free(temp);
        return head;
    }

    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position!\n");
        return head;
    }

    Car* to_delete = temp->next;
    temp->next = to_delete->next;
    free(to_delete);
    return head;
}

Car* reverse_list(Car* head) {
    Car* prev = NULL;
    Car* current = head;
    Car* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    printf("The list has been reversed!\n");
    return prev;
}

Car* sort_by_price(Car* head) {
    if (head == NULL) return NULL;
    int swapped;
    Car* ptr;
    Car* lptr = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != lptr) {
            if (ptr->price > ptr->next->price) {
                int id = ptr->id;
                char brand[50], model[50];
                int year = ptr->year;
                float price = ptr->price;

                strcpy(brand, ptr->brand);
                strcpy(model, ptr->model);

                ptr->id = ptr->next->id;
                strcpy(ptr->brand, ptr->next->brand);
                strcpy(ptr->model, ptr->next->model);
                ptr->year = ptr->next->year;
                ptr->price = ptr->next->price;

                ptr->next->id = id;
                strcpy(ptr->next->brand, brand);
                strcpy(ptr->next->model, model);
                ptr->next->year = year;
                ptr->next->price = price;

                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);

    return head;
}

Car* clear_list(Car* head) {
    Car* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("The list has been cleared!\n");
    return NULL;
}

int main() {
    Car* head = NULL;
    int option, position, id, year;
    float price;
    char brand[50], model[50];

    do {
        printf("\n1. Insert at End\n2. Insert at Beginning\n3. Insert at Position\n4. Display List");
        printf("\n5. Search by ID\n6. Delete at Position\n7. Reverse List\n8. Sort by Price\n9. Clear List");
        printf("\n10. Search by Brand\n11. Search by Model\n12. Search by Year\n13. Search by Price\n0. Exit");
        printf("\nOption: ");
        scanf("%d", &option);

        switch (option) {
            case INSERT_AT_END: head = insert_at_end(head); break;
            case INSERT_AT_BEGGING: head = insert_at_beginning(head); break;
            case INSERT_AT_POSITION:
                printf("Enter position: ");
                scanf("%d", &position);
                head = insert_at_position(head, position);
                break;
            case DISPLAYING_LIST: display_list(head); break;
            case SEARCH_BY_ID:
                printf("Enter Car ID to search: ");
                scanf("%d", &id);
                position = search_by_id(head, id);
                if (position != -1)
                    printf("Found at position %d\n", position);
                else
                    printf("Not found\n");
                break;
            case DELETE_AT_POSITION:
                printf("Enter position to delete: ");
            scanf("%d", &position);
            head = delete_at_position(head, position);
            break;
        case REVERSING_LIST: head = reverse_list(head); break;
        case SORTING_BY_PRICE: head = sort_by_price(head); break;
        case CLEARING_LIST: head = clear_list(head); break;
        case SEARCHING_BY_BRAND:
            printf("Enter brand to search: ");
            scanf(" %[^\n]", brand);
            search_by_brand(head, brand);
            break;
        case SEARCHING_BY_MODEL:
            printf("Enter model to search: ");
            scanf(" %[^\n]", model);
            search_by_model(head, model);
            break;
        case SEARCHING_BY_YEAR:
            printf("Enter year to search: ");
            scanf("%d", &year);
            search_by_year(head, year);
            break;
        case SEARCHING_BY_PRICE:
            printf("Enter price to search: ");
            scanf("%f", &price);
            search_by_price(head, price);
            break;
        }
    } while (option != 0);

    head = clear_list(head);
    return 0;
}