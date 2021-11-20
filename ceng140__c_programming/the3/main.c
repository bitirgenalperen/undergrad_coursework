/* IT WILL NOT BE USED IN GRADING! YOU CAN USE IT FOR TESTING PURPOSES.*/
#include <stdio.h>
#include <stdlib.h>
#include "the3.h"


int main() {
    /* initialize linked lists and table as NULL pointer */
    Node *meals = NULL;
    Node *philosophers = NULL;
    Node *table = NULL;

    /* add meals */
    add_meal(&meals, "Kung Pao", 3);
    add_meal(&meals, "Tofu", 1);
    add_meal(&meals, "Wonton", 2);
    add_meal(&meals, "Fried Rice", 3);

    /* add philosophers */
    add_philosopher(&philosophers, "Lao Tzu", "Wonton", 1424);
    add_philosopher(&philosophers, "Confucius", "Tofu", 1145);
    add_philosopher(&philosophers, "Mozi", "Fried Rice", 1976);
    add_philosopher(&philosophers, "Shang Yang", "Fried Rice", 1555);

    /* print meals */
    print_list(meals, &print_meal_node);
    /* print philosophers */
    print_list(philosophers, &print_philosopher_node);

    /* place philosophers around table */
    place_philosophers(&table, philosophers);
    /* print table in its own format */
    print_table(table);

    /* serve meals and update meal counts */
    serve_meals(table, meals);
    /* print new meals list */
    print_list(meals, &print_meal_node);

    /* remove philosopher in index 2 from the table */
    remove_philosopher(&table, 2, 4);
    /* print updated table */
    print_table(table);
    return 0;
}