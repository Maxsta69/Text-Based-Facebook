/********* main.c ********
    Student Name 	= Max Bui
    Student Number	= 10261646
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE 
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    
    /* IMPORTANT: You must use the users linked list created in the code above. 
                  Any new users should be added to that linked list.
    */

    // Your solution goes here

    int user_choice, post_number;
    char username[30];
    char password[15];
    char friend_name[30];

    printf("***********************************************\n");
    printf("        Welcome to Text-Based Facebook         \n");
    printf("***********************************************\n\n");

    do 
    {
        print_menu();
        scanf(" %d", &user_choice);

        if (user_choice == 1) {
            printf("Enter a username: ");
            scanf(" %s", username);

            printf("Enter an upto 15 characters password: ");
            scanf(" %s", password);

            users = add_user(users, username, password);

            printf("**** User Added! ****\n\n");
        }
        else if (user_choice == 2) {
            printf("Enter username to update their password: ");
            scanf(" %s", username);

            if (find_user(users, username) == NULL) {
                printf("\n-----------------------------------------------\n");
                printf("               User not found.                 \n");
                printf("-----------------------------------------------\n\n");
            }
            else 
            {
                printf("Enter a new password that is upto 15 characters: ");
                scanf("%s", password);
                printf("**** Password changed! ****\n\n");
            }
        }
        else if (user_choice == 3) {
            int post_choice;
            printf("\nEnter username to manage their posts: ");
            scanf(" %s", username);
            user_t *userToManagePost = find_user(users, username);
            if (userToManagePost != NULL) {
                do {
                display_user_posts(userToManagePost);
                printf("1. Add a new user post\n");
                printf("2. Remove a users post\n");
                printf("3. Return to main menu\n");
                printf("\nYour choice: ");
                scanf("%d", &post_choice);

                switch (post_choice) {
                case 1:
                    char post_content[250];
                        printf("Enter your post content: ");
                        scanf(" %[^\n]s", post_content);
                        add_post(userToManagePost, post_content);
                        printf("Post added to your profile.\n");
                        break;

                    case 2:
                        printf("Which post do you want to delete? ");
                        scanf("%d", &post_number);
                        if (delete_post(userToManagePost, post_number)) {
                            printf("Post %d was deleted successfully!\n", post_number);
                        }
                        else {
                            printf("Invalid post number!\n");
                        }
                        break;

                    case 3:
                        break;

                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                    }
                } while (post_choice != 3);
            }
            else
            {
                printf("-----------------------------------------------\n");
                printf("               User not found.                 \n");
                printf("-----------------------------------------------\n\n");
            }
            }
            else if (user_choice == 4) {
                printf("Enter username to manage their friends: ");
                scanf(" %s", username);
                user_t *userToManageFriends = find_user(users, username);

                if (userToManageFriends != NULL) {
                    int friend_choice;
                    do {
                        printf("-----------------------------------------------\n");
                        printf("                 %s's friends                  \n", username);
                        printf("-----------------------------------------------\n\n");
                        printf("1: Display all user's friends\n");
                        printf("2. Add a new friend\n");
                        printf("3. Delete a friend\n");
                        printf("4. Return to main menu\n\n");
                        printf("Your choice: ");
                        scanf("%d", &friend_choice);

                        switch (friend_choice) {
                            case 1:
                                display_user_friends(userToManageFriends);
                                break;

                            case 2:
                                printf("Enter a new friends' name: ");
                                scanf("%s", friend_name);
                                add_friend(userToManageFriends, friend_name);
                                printf("Friend added to the list.\n");
                                break;

                            case 3:
                                printf("List of %s's friends:\n", userToManageFriends -> username);
                                display_user_friends(userToManageFriends);
                                printf("Enter a friend's name to delete: ");
                                scanf("%s", friend_name);

                                if (delete_friend(userToManageFriends, friend_name)) {
                                    printf("Friend %s deleted successfully!\n", friend_name);
                                }
                                else
                                {
                                    printf("Invalid friend's name\n");
                                }
                                break;
                            case 4:
                                break;

                            default:
                                printf("Invalid choice. Please try again\n");
                                break;
                        }
                    } while (friend_choice != 4);
                }
                else
                {
                    printf("-----------------------------------------------\n");
                    printf("               User not found.                 \n");
                    printf("-----------------------------------------------\n\n");
                }
            }
            else if (user_choice == 5) {
                display_all_posts(users);
            }
            else if (user_choice == 6) {
                printf("***********************************************\n");
                printf("   Thank you for using Text-Based Facebook     \n");
                printf("              GoodBye!                         \n");
                printf("***********************************************");
            }
            else if (user_choice < 0 || user_choice > 6)
            {
            printf("Invalid choice. Please try again.\n\n");
            }
        } while (user_choice != 6);
}