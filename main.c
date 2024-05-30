#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//macros for defining maximum values that can be achieved for memory allocation
#define MAX_CAPACITY 1000
#define MAX_LOBSTERS 1000

// Function for finding the maximum of 2 numbers, using ternary conditional operator
unsigned long long max(unsigned long long a, unsigned long long b)
{
    return (a > b) ? a : b;
}

// Implement basically the knapsack problem using dynamic programming into lobsters problems
unsigned long long knapsack(unsigned long long sizes[], unsigned long long values[], unsigned long long n, unsigned long long capacity)
{

    //allocation dynamically into memry the dynamic programming matrix
    unsigned long long** dp = (unsigned long long**)malloc((n + 1) * sizeof(unsigned long long*));

    for (unsigned long long i = 0; i <= n; i++)
    {
        dp[i] = (unsigned long long*)malloc((capacity + 1) * sizeof(unsigned long long));
    }

    // Initialize the dp table with 0
    // and using the dynamic programming implementation for the lobsters problem
    for (unsigned long long i = 0; i <= n; i++)
    {
        for (unsigned long long w = 0; w <= capacity; w++)
        {
            // If either the number of items (i) is 0 or the capacity (w) is 0,
            // there is no item to include or no capacity to hold any item.
           // Hence, the maximum value that can be obtained is 0.
          if (i == 0 || w == 0)
          {
           dp[i][w] = 0;
          }
          else if (sizes[i - 1] <= w) // If the size of the current item (sizes[i-1]) is less than or equal to the current capacity (w),
          {
           // We have two choices:
           // 1. Exclude the current item and take the maximum value obtained by the previous items with the same capacity (dp[i-1][w]).
           // 2. Include the current item and add its value to the maximum value obtained by the previous items
           // with the reduced capacity (w - sizes[i-1]) (dp[i-1][w-sizes[i-1]] + values[i-1]).
           // We take the maximum of these two choices.
          dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - sizes[i - 1]] + values[i - 1]);
          }
          else // If the size of the current item (sizes[i-1]) is greater than the current capacity (w),
          {
           // We cannot include the current item in the knapsack.
           // Hence, the maximum value that can be obtained is the same as the maximum value obtained by the previous items with the same capacity (dp[i-1][w]).
           dp[i][w] = dp[i - 1][w];
          }

        }
    }

    //computing the final result
    unsigned long long result = dp[n][capacity];

    // Free allocated memory
    for (unsigned long long i = 0; i <= n; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return result;
}

// Function to generate random data and write to file
void generateRandomData(unsigned long long numLobsters, unsigned long long maxSize, unsigned long long maxValue, FILE *file)
{
    srand(time(0));

    for (unsigned long long i = 0; i < numLobsters; i++)
    {
        unsigned long long size = rand() % maxSize + 1;
        unsigned long long value = rand() % maxValue + 1;
        fprintf(file, "%llu %llu\n", size, value);
    }
}

// Function to print results and measure time complexity
void printResults(FILE *outputFile, unsigned long long testCases, unsigned long long* capacities, unsigned long long* numLobsters, unsigned long long** sizes, unsigned long long** values)
{
    clock_t start, end;
    double cpu_time_used;

    for (unsigned long long t = 0; t < testCases; t++)
    {
        unsigned long long n = numLobsters[t];
        unsigned long long capacity = capacities[t];
        start = clock();
        unsigned long long maxValue = knapsack(sizes[t], values[t], n, capacity);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        fprintf(outputFile, "\n\nTest case %llu: \nMaximum value of lobsters that can be caught: %llu\n", t + 1, maxValue);
        fprintf(outputFile, "Time Complexity: %f", cpu_time_used);

        printf("\n\n");
        printf("\033[1;34mTest case %llu: \nMaximum value of lobsters that can be caught: %llu\033[0m\n", t + 1, maxValue);
        printf("\033[1;34mTime Complexity: %f\033[0m\n", cpu_time_used);
    }
}

// Function to open technical report
void openTechnicalReport()
{
    //system("xdg-open technical_report.pdf");  // Linux
    system("start technical_report.pdf");  // Windows
    // system("open technical_report.pdf");   // macOS
}

// Function to open GitHub repository
void openGithubRepository()
{
    //system("xdg-open https://github.com/example/repository");  // Linux
    system("start https://github.com/Stan-Oana/TEMA_DE_CASA_AD");  // Windows
    // system("open https://github.com/example/repository");   // macOS
}

// Function to display menu options
//Using the ANSI color code for the menu
void displayMenu()
{
    printf("                                  \033[1;33mMenu:\033[0m\n");
    printf("                       \033[1;36m1. Generate Random Data\033[0m\n");
    printf("                       \033[1;36m2. Print Results\033[0m\n");
    printf("                       \033[1;36m3. Open Technical Report\033[0m\n");
    printf("                       \033[1;36m4. Open GitHub Repository\033[0m\n");
    printf("                       \033[1;36m5. Exit\033[0m\n");
}

int main()
{
    //declaring variables
    unsigned long long choice;
    unsigned long long testCases;
    unsigned long long* capacities;
    unsigned long long* numLobsters;
    unsigned long long maxValueRange;
    unsigned long long** sizes;
    unsigned long long** values;

    //implementing a colored menu with a switch case
    while (1)
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%llu", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("Enter the number of test cases: ");
            scanf("%llu", &testCases);

            FILE *inputFile = fopen("homar_in.txt", "w");
            if (inputFile == NULL)
            {
                perror("Error opening file");
                return EXIT_FAILURE;
            }

            fprintf(inputFile, "%llu\n", testCases);

            //alocating dinamically into memory, building the arrays
            capacities = (unsigned long long*)malloc(testCases * sizeof(unsigned long long));
            numLobsters = (unsigned long long*)malloc(testCases * sizeof(unsigned long long));
            sizes = (unsigned long long**)malloc(testCases * sizeof(unsigned long long*));
            values = (unsigned long long**)malloc(testCases * sizeof(unsigned long long*));

            for (unsigned long long t = 0; t < testCases; t++)
            {
                printf("Enter the number of lobsters for test case %llu: ", t + 1);
                scanf("%llu", &numLobsters[t]);
                printf("Enter the maximum value range for test case %llu: ", t + 1);
                scanf("%llu", &maxValueRange);
                printf("Enter the capacity of the net for test case %llu: ", t + 1);
                scanf("%llu", &capacities[t]);

                fprintf(inputFile, "%llu %llu %llu\n", capacities[t], numLobsters[t], maxValueRange);

                sizes[t] = (unsigned long long*)malloc(numLobsters[t] * sizeof(unsigned long long));
                values[t] = (unsigned long long*)malloc(numLobsters[t] * sizeof(unsigned long long));

                for (unsigned long long i = 0; i < numLobsters[t]; i++)
                {
                    sizes[t][i] = rand() % 10 + 1; // Size in range 1-10 cm
                    values[t][i] = rand() % maxValueRange + 1; // Value in the specified range
                    fprintf(inputFile, "%llu %llu\n", sizes[t][i], values[t][i]);
                }
            }

            fclose(inputFile);
            printf("\n");
            printf("\033[1;32mRandom data generated in homar_in.txt\033[0m\n");
            printf("\n\n");
            break;
        }
        case 2:
        {
            FILE *inputFile = fopen("homar_in.txt", "r");
            if (inputFile == NULL)
            {
                perror("Error opening input file");
                return EXIT_FAILURE;
            }

            fscanf(inputFile, "%llu", &testCases);

            capacities = (unsigned long long*)malloc(testCases * sizeof(unsigned long long));
            numLobsters = (unsigned long long*)malloc(testCases * sizeof(unsigned long long));
            sizes = (unsigned long long**)malloc(testCases * sizeof(unsigned long long*));
            values = (unsigned long long**)malloc(testCases * sizeof(unsigned long long*));

            for (unsigned long long t = 0; t < testCases; t++)
            {
                fscanf(inputFile, "%llu %llu %llu", &capacities[t], &numLobsters[t], &maxValueRange);

                sizes[t] = (unsigned long long*)malloc(numLobsters[t] * sizeof(unsigned long long));
                values[t] = (unsigned long long*)malloc(numLobsters[t] * sizeof(unsigned long long));

                for (unsigned long long i = 0; i < numLobsters[t]; i++)
                {
                    fscanf(inputFile, "%llu %llu", &sizes[t][i], &values[t][i]);
                }
            }
            fclose(inputFile);

            FILE *outputFile = fopen("homar_out.txt", "w");
            if (outputFile == NULL)
            {
                perror("Error opening output file");
                return EXIT_FAILURE;
            }

            printResults(outputFile, testCases, capacities, numLobsters, sizes, values);

            fclose(outputFile);
            printf("\n\n");
            printf("\033[1;32mResults written to homar_out.txt\033[0m\n");
            printf("\n");
            break;
        }
        case 3:
            openTechnicalReport();
            break;

        case 4:
            openGithubRepository();
            break;

        case 5:
            printf("\033[1;32mExiting the program.\033[0m\n");
            exit(0);

        default:
            printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
            break;
        }
    }

    return 0;
}
