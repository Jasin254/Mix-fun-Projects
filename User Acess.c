#include "main.h"

// Define the access levels
typedef enum {
    ACCESS_LEVEL_NONE,
    ACCESS_LEVEL_STUDENT,
    ACCESS_LEVEL_TEACHER
} access_level_t;

// Define the users
typedef struct {
    const char *username;
    const char *password;
    access_level_t access_level;
} user_t;

// Define a list of authorized users
user_t authorized_users[] = {
    {"student", "student123", ACCESS_LEVEL_STUDENT},
    {"teacher", "teacher123", ACCESS_LEVEL_TEACHER}
};

// Check if the provided credentials are valid
access_level_t authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(authorized_users) / sizeof(authorized_users[0]); i++) {
        if (strcmp(username, authorized_users[i].username) == 0 &&
            strcmp(password, authorized_users[i].password) == 0) {
            return authorized_users[i].access_level;
        }
    }
    return ACCESS_LEVEL_NONE;
}

// Function to lock user instruction
void lock_instruction() {
    // Lock instruction code
}

// Function to unlock user instruction
void unlock_instruction() {
    // Unlock instruction code
}

int main(void) {
    // Initialize the HAL Library and configure the peripherals
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_I2C1_Init();
    MX_TIM2_Init();

    // Main loop
    while (1) {
        // Get user input for username and password
        char username[32];
        char password[32];
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        // Authenticate user
        access_level_t access_level = authenticate(username, password);

        // Check the access level and execute the corresponding action
        switch (access_level) {
            case ACCESS_LEVEL_NONE:
                printf("Invalid credentials\n");
                break;
            case ACCESS_LEVEL_STUDENT:
                printf("Welcome, student!\n");
                // Perform student-related tasks
                break;
            case ACCESS_LEVEL_TEACHER:
                printf("Welcome, teacher!\n");
                // Perform teacher-related tasks, including locking/unlocking user instructions
                lock_instruction();
                unlock_instruction();
                break;
        }
    }
}
