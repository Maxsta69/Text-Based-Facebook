/********* definitions.c ********
    Student Name 	= Max Bui
    Student Number	= 101261646
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"


// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
    user_t *new_user = malloc(sizeof(user_t));
    strcpy(new_user -> username, username);
    strcpy(new_user -> password, password);
    new_user -> friends = NULL;
    new_user -> posts = NULL;
    new_user -> next = NULL;

    if (users == NULL || strcmp(users->username, username) > 0)
    {
        new_user->next = users;
        return new_user;
    }

    user_t *current_user = users;
    while (current_user -> next != NULL && strcmp(current_user -> next -> username, username) < 0)
    {
        current_user = current_user -> next;
    }

    new_user -> next = current_user -> next;
    current_user -> next = new_user;

    return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   user_t *current_user = users;

   while (current_user != NULL)
    {
        if (strcmp(current_user -> username, username) == 0)
        {
            return current_user;
        }
        current_user = current_user -> next;
    }

    return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *new_friend = (friend_t *)malloc(sizeof(friend_t));
   strcpy(new_friend -> username, username);
   new_friend -> next = NULL;
   return new_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
    // Create a new friend node
    friend_t *new_friend = create_friend(friend);

    // Insert the new friend into the sorted linked list
    if (user -> friends == NULL || strcmp(user -> friends -> username, friend) > 0)
    {
        new_friend -> next = user -> friends;
        user -> friends = new_friend;
        return;
    }

    friend_t *current_friend = user -> friends;
    while (current_friend->next != NULL && strcmp(current_friend -> next -> username, friend) < 0)
    {
        current_friend = current_friend -> next;
    }

    new_friend -> next = current_friend -> next;
    current_friend -> next = new_friend;
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
    friend_t *current_friend = user->friends;
    friend_t *prev_friend = NULL;

    while (current_friend != NULL && strcmp(current_friend->username, friend_name) != 0)
    {
        prev_friend = current_friend;
        current_friend = current_friend->next;
    }

    if (current_friend == NULL)
    {
        return false;
    }

    if (prev_friend == NULL)
    {
        user->friends = current_friend->next;
    }
    else
    {
        prev_friend->next = current_friend->next;
    }

    free(current_friend);
    return true;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *new_post = malloc(sizeof(post_t));
   
   strcpy(new_post -> content, text);
   new_post -> next = NULL;
   return new_post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
    post_t *new_post = create_post(text);

    new_post -> next = user -> posts;
    user -> posts = new_post; 
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
    post_t *current_post = user->posts;
    post_t *prev_post = NULL;
    int count = 1;

    while (current_post != NULL && count < number)
    {
        prev_post = current_post;
        current_post = current_post->next;
        count++;
    }

    if (current_post == NULL || count > number)
    {
        return false;
    }

    if (prev_post == NULL)
    {
        user->posts = current_post->next;
    }
    else
    {
        prev_post->next = current_post->next;
    }

    free(current_post);
    return true;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
    post_t *current_post = user->posts;

    printf("-----------------------------------------------\n");
    printf("               %s's posts\n", user->username);

    if (current_post == NULL)
    {
        printf("No posts available for %s.\n", user->username);
    }
    else
    {
        int post_number = 1;
        while (current_post != NULL)
        {
            printf("%d- %s: %s\n", post_number, user->username, current_post->content);
            current_post = current_post->next;
            post_number++;
        }
    }

    printf("-----------------------------------------------\n\n");
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
    friend_t *current_friend = user->friends;

    if (current_friend == NULL)
    {
        printf("No friends available for %s.\n", user -> username);
        return;
    }

    printf("-----------------------------------------------\n");
    printf("%s's friends\n", user -> username);

    int friend_number = 1;
    while (current_friend != NULL)
    {
        printf("%d- %s\n", friend_number, current_friend -> username);
        current_friend = current_friend -> next;
        friend_number++;
    }

    printf("-----------------------------------------------\n");
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
    user_t *current_user = users;

    for (int userCount = 0; userCount < 2 && current_user != NULL; userCount++) {
        display_user_posts(current_user);
        current_user = current_user -> next; 
    }
    while (current_user != NULL)
    {
        if (current_user -> next != NULL)
        {
            char choice;
            printf("Do you want to display next 2 users posts? (Y/N): ");
            scanf(" %c", &choice);

            if (choice == 'N' || choice == 'n')
            {
                printf("\n");
                return; 
            }
            else if (choice == 'Y' || choice == 'y') {
                for (int userCount = 0; userCount < 2 && current_user != NULL; userCount++) {
                display_user_posts(current_user);
                current_user = current_user -> next; 
                }
            }
        }
    }
}


/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
    user_t *current_user = users;
    user_t *next_user;

    while (current_user != NULL)
    {
        friend_t *current_friend = current_user -> friends;
        friend_t *next_friend;

        while (current_friend != NULL)
        {
            next_friend = current_friend->next;
            free(current_friend);
            current_friend = next_friend;
        }

        post_t *current_post = current_user -> posts;
        post_t *next_post;

        while (current_post != NULL)
        {
            next_post = current_post->next;
            free(current_post);
            current_post = next_post;
        }

        next_user = current_user->next;
        free(current_user);
        current_user = next_user;
    }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   printf("***********************************************\n");
   printf("               MAIN MENU:                      \n");
   printf("***********************************************\n");
   printf("1. Register a new User\n");
   printf("2. Manage a user's profile (change password)\n");
   printf("3. Manage a user's posts (display/add/remove)\n");
   printf("4. Manage a user's friends (display/add/remove)\n");
   printf("5. Display All Posts\n");
   printf("6. Exit\n\n");
   printf("Enter your choice: ");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
