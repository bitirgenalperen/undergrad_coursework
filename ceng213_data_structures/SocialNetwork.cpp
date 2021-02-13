#include "SocialNetwork.h"

#include <iostream>

SocialNetwork::SocialNetwork() {

}

void SocialNetwork::addProfile(const std::string &firstname, const std::string &lastname, const std::string &email) {/* TODO */
    Profile element = {firstname, lastname, email};
    profiles.insertSorted(element);
}

void SocialNetwork::addPost(const std::string &message, const std::string &email){/* TODO */
    Post element = {message};
    posts.insertAtTheTail(element);
    Node<Profile> *current = profiles.getFirstNode();
    while (current != nullptr){
        if (current->data.getEmail() == email){
            current->data.addPost(&(posts.getLastNode()->data));
            return;
        }
        current = current->next;
    } 
}

void SocialNetwork::deleteProfile(const std::string &email) {/* TODO */
    Node<Profile> *current = profiles.getFirstNode();                          
    Profile *del_node;
    while (current != nullptr){
        if(current->data.getEmail() == email){
            del_node = &(current->data);
            LinkedList<Profile *> *ara = &(del_node->getFriends());
            Node<Profile *> *sub = ara->getFirstNode(); 
            Profile *del_friend = nullptr;
            while (sub != nullptr){
                del_friend = (sub->data);
                del_friend->dropFriend(del_node);
                sub = sub->next;
            }
            ara->removeAllNodes();
            
            LinkedList<Post *> *bul = &(del_node->getPosts());
            Node<Post *> *holder = bul->getFirstNode();
            while (holder!= nullptr){
                Post *del_post = (holder->data);
                Node<Profile> *current2 = profiles.getFirstNode();
                while (current2 != nullptr){
                    current2->data.dropLike(del_post);
                    current2 = current2->next;
                }
                holder = holder->next;
                posts.removeNode(*del_post);
            }
            bul->removeAllNodes();
            
            bul = &(del_node->getLikes()); //likelari siler, dikkat
            bul->removeAllNodes();

            profiles.removeNode(*del_node);
        }
        current = current->next;
    }
    
}

void SocialNetwork::makeFriends(const std::string &email1, const std::string &email2) {/* TODO */
    Node<Profile> *current1 = profiles.getFirstNode(), *current2 = profiles.getFirstNode();

    while (current1 != nullptr){
        if(current1->data.getEmail() == email1){
            while (current2 != nullptr){
                if (current2->data.getEmail() == email2){
                    current1->data.addFriend(&(current2->data));
                    current2->data.addFriend(&(current1->data));
                    return;
                }
                current2 = current2->next;
            }
        }
        current1 = current1->next;
    }
}

void SocialNetwork::likePost(int postId, const std::string &email) {/* TODO */
    Node<Profile> *current = profiles.getFirstNode();
    Node<Post> *cur_post = posts.getFirstNode();
    while (current != nullptr){
        if (current->data.getEmail() == email){
            while(cur_post != nullptr){
                if (cur_post->data.getPostId() == postId){
                    current->data.addLike(&(cur_post->data));
                    return;
                }
                cur_post = cur_post->next;
            }
        }
        current = current->next;
    }
}

void SocialNetwork::unlikePost(int postId, const std::string &email) {/* TODO */
    Node<Profile> *current = profiles.getFirstNode();
    Node<Post> *cur_post = posts.getFirstNode();
    while (current != nullptr){
        if (current->data.getEmail() == email){
            while(cur_post != nullptr){
                if (cur_post->data.getPostId() == postId){
                    current->data.dropLike(&(cur_post->data));
                    return;
                }
                cur_post = cur_post->next;
            }
        }
        current = current->next;
    }
}

LinkedList<Profile *> SocialNetwork::getMutualFriends(const std::string &email1, const std::string &email2) {/* TODO */
    Node<Profile> *current = profiles.getFirstNode();
    Node<Profile> *compare = profiles.getFirstNode();
    LinkedList<Profile *> holder;
    while (current != nullptr){
        while (compare != nullptr){
            if ((current->data.getEmail() == email1) && (compare->data.getEmail() == email2)){
                LinkedList<Profile *> *cur_friend = &(current->data.getFriends());
                LinkedList<Profile *> *com_friend = &(compare->data.getFriends());               
                Node<Profile *> *ara = cur_friend->getFirstNode();
                Node<Profile *> *bul = com_friend->getFirstNode();
                while (ara != nullptr){
                    while (bul != nullptr){
                        if(bul->data == ara->data){
                            holder.insertAtTheTail(ara->data);
                        }
                        bul = bul->next;
                    }
                    bul = com_friend->getFirstNode();
                    ara = ara->next;
                }
            }
            compare=compare->next;
        }
        compare = profiles.getFirstNode();
        current = current->next;
    }
    return holder;
}

LinkedList<Post *> SocialNetwork::getListOfMostRecentPosts(const std::string &email, int k) {/* TODO */
    LinkedList<Post *> holder;
    Node<Profile> *current = profiles.getFirstNode();

    while (current != nullptr){
        if (current->data.getEmail() == email){
            Node<Post *> *cur_post = (current->data.getPosts()).getLastNode();
            for (int i = 0; i < k, cur_post != nullptr; i++, cur_post=cur_post->prev){
                holder.insertAtTheTail(cur_post->data);
            }
            return holder;
        }
        current = current->next;
    }
}

void SocialNetwork::print() const {
    std::cout << "# Printing the social network ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getNumberOfNodes() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of posts is " << posts.getNumberOfNodes() << ":" << std::endl;
    posts.print();

    std::cout << "# Printing is done." << std::endl;
}
