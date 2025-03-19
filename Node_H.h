#ifndef Node_H
#define Node_H

typedef struct Node
{
    //Username
    char username[64];

    //Phone number
    int phoneNumber;

    //Email
    char email[128];

    //Pointer
    struct Node *next;

} Node;

#endif 