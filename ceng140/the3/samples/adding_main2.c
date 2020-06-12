#include <stdio.h>
#include <stdlib.h>
#include "../the3.h"


int main(int argc, char const *argv[])
{
    Node *meals = NULL;
    Node *philosophers = NULL;

    add_meal(&meals, "Kung Pao", 3);
    add_meal(&meals, "Tofu", 1);
    add_meal(&meals, "Wonton", 2);
    add_meal(&meals, "Fried Rice", 3);

    add_philosopher(&philosophers, "Lao Tzu", "Wonton", 1424);
    add_philosopher(&philosophers, "Confucius", "Tofu", 1145);
    add_philosopher(&philosophers, "Mozi", "Fried Rice", 1976);
    add_philosopher(&philosophers, "Shang Yang", "Fried Rice", 1555);

    print_list(meals, &print_meal_node_mine);
    print_list(philosophers, &print_philosopher_node_mine);
    return 0;
}
