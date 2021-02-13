#include <iostream>

#include "SocialNetwork.h"

int main() {
    SocialNetwork snetwork;

    snetwork.print();

    snetwork.addProfile("john", "doe", "john@doe.com");

    snetwork.print();

    snetwork.addProfile("meggie", "shawn", "meggie@shawn.com");

    snetwork.addPost("Hello world! My name is John Doe.", "john@doe.com");

    snetwork.addPost("Wassup Bitches!", "meggie@shawn.com");

    snetwork.print();

    snetwork.addPost("Today is my birthday!", "john@doe.com");

    snetwork.likePost(3, "meggie@shawn.com");

    snetwork.print();

    snetwork.addPost("This is the worst valentines day ever!", "meggie@shawn.com");

    snetwork.addProfile("harry", "brownson", "harry@brownson.com");

    snetwork.addPost("Farewell everyone!", "john@doe.com");

    snetwork.print();

    snetwork.deleteProfile("john@doe.com");

    snetwork.makeFriends("meggie@shawn.com", "harry@brownson.com");

    snetwork.addProfile("clara", "oneil", "clara@oneil.com");

    snetwork.addPost("I LOVE TRUMP MFs!!", "clara@oneil.com");

    snetwork.addPost("Screw you Beiden, you'll never get a chance to be elected...", "clara@oneil.com");

    snetwork.print();

    snetwork.addProfile("nial", "broke", "nial@broke.com");

    snetwork.addPost("He cussed me out for crashing his pickup truck.!!", "nial@broke.com");

    snetwork.makeFriends("nial@broke.com", "harry@brownson.com");

    snetwork.likePost(8, "nial@broke.com");

    snetwork.print();

    snetwork.unlikePost(8, "nial@broke.com");

    return 0;
}
