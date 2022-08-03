///////////////////////////////////////////////////////////////////////////////
// include headers
#include <iostream>
#include <pthread.h>
#include <queue>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <vector>
// prevent linking error
extern "C" {
#include "hw2_output.h"
}
// namespace describe
using namespace std;
// macro definitions
// 2d array values
#define G(x, y) grid[x][y]
#define F(x, y) gridFilter[x][y]
// controlled mechanish of gather'ing and throw'ing cigbutts
#define GATHER(a) (--a)
#define THROW(a) (++a)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//____________METU__CENG__OPERATING_SYSTEMS__HOMEWORK_2________________________
//____________Name:Mustafa_Alperen_Bitirgen____________________________________
//____________Id:2231496_______________________________________________________
//____________Date:May-25______________________________________________________
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//___________________________Global_Variables_________________________________
// grid size AND 2d array representing the corresponding area
int gridSize_x, gridSize_y;
int** grid;
int** gridFilter;
// number of proper privates AND sneaky smokers
int count_pp = 0;
int count_ss = 0;
int count_orders = 0;
// mutex
pthread_mutex_t grid_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t filter_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t order_mutex = PTHREAD_MUTEX_INITIALIZER;
// conditionals
pthread_cond_t gather_sleep = PTHREAD_COND_INITIALIZER;
pthread_cond_t gather_time = PTHREAD_COND_INITIALIZER;
pthread_cond_t smoke_sleep = PTHREAD_COND_INITIALIZER;
pthread_cond_t smoke_time = PTHREAD_COND_INITIALIZER;
pthread_cond_t order_sleep = PTHREAD_COND_INITIALIZER;
pthread_cond_t order_rec = PTHREAD_COND_INITIALIZER;
// semaphores
sem_t sem_gather;
sem_t sem_throw;
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////____START____
//____________Size Object Class________________________________________________
/*
        holds 2 integer value => representing the length in both dimensions
*/
class Size {
private:
    int x, y;

public:
    Size() {
        this->x = -1;
        this->y = -1;
    }
    Size(int x1, int y1) {
        this->x = x1;
        this->y = y1;
    }
    int getX() { return this->x; }
    int getY() { return this->y; }
};
///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
//____________Proper Private Object Class_____________________________________
/*
        proper private gathers the cigbutts in the given area
        has:
                - gid :: each proper private has a unique ID
                - gather_interval :: start gathering one cigbutt every
   gather_interval ms
                - gather_area :: size of the area private can gather cigbutts
   from
                - area_count :: number of gather_areas to gather cigbutts
                - private_areas :: all the areas to gather cigbutts
*/
class ProperPrivate {
private:
    int gid = -1;
    int gather_interval = -1;
    int area_count = -1;

    Size gather_area = Size();

    queue<Size> privates_area;
public:
    ProperPrivate() {}
    ProperPrivate(int gid, int gather_size_x, int gather_size_y,
                  int gather_interval, int area_count) {
        this->gid = gid;
        this->gather_area = Size(gather_size_x, gather_size_y);
        this->gather_interval = gather_interval;
        this->area_count = area_count;
    }
    Size getAreaSize() { return this->gather_area; }
    int getAreaCount() { return this->area_count; }
    Size getArea() { 
        cout << "PP-" << this->gid<< ": " << this->privates_area.front().getX() << " " << this->privates_area.front().getY() << endl;
        return this->privates_area.front(); }
    void addArea(Size newArea) { this->privates_area.push(newArea); }
    void removeArea() {
        this->privates_area.pop();
        this->area_count -= 1;
    }
    int getGid() { return this->gid; }
    int getGatherInterval() { return this->gather_interval; }
};
///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
//____________Order Enumarator & Object Class_________________________________
/*
        orders will be issued by the commander
        has:
                - order_time :: when should the order apply
                - order_statement :: which order to apply at given time
*/
enum OrderStatement {
    PRIVATE_BREAK = -1,
    PRIVATE_CONTINUE = 1,
    PRIVATE_STOP = 0
};

class Order {
private:
    int time;
    OrderStatement statement;
public:
    Order(int order_time, char char_statement) {
        this->time = order_time;
        if (char_statement == 'b') {
            this->statement = PRIVATE_BREAK;
        } else if (char_statement == 'c') {
            this->statement = PRIVATE_CONTINUE;
        } else {
            this->statement = PRIVATE_STOP;
        }
    }
    int getTime() { return this->time; }
    OrderStatement getStatement() { return this->statement; }
};
// global order initialization
OrderStatement givenOrder = PRIVATE_CONTINUE;
///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
//____________Sneaky Smoker Object Class______________________________________
/*
        smoking cigarets and generating cigbutts around where they smoke
        while the proper privates are working
        has:
                - sid :: each sneaky smoker has a unique ID
                - smoke_interval :: start smoking one cigaret every
   smokde_interval ms
                - env_count :: number of smoker_env to gather cigarets
                - smoker_env :: all the environments to smoke cigarets
*/
class SneakySmoker {
private:
    int sid = -1;
    int smoke_interval = -1;
    int env_count = -1;

    queue<pair<Size, int> > smoker_env;
public:
    SneakySmoker() {}
    SneakySmoker(int sid, int smoke_interval, int env_count) {
        this->sid = sid;
        this->smoke_interval = smoke_interval;
        this->env_count = env_count;
    }
    int getEnvCount() { return this->env_count; }
    Size getEnv() {
        cout <<"SS-" << this->sid<< ": " << this->smoker_env.front().first.getX() << " " <<  this->smoker_env.front().first.getY()  << endl;
        return this->smoker_env.front().first; }
    int getCigbuttCount() { return this->smoker_env.front().second; }
    void addEnv(Size newEnv, int cig_count) {
        this->smoker_env.push(pair<Size, int>(newEnv, cig_count));
    }
    void removeEnv() {
        this->smoker_env.pop();
        this->env_count -= 1;
    }
    int getSid() { return this->sid; }
    int getSmokeInterval() { return this->smoke_interval; }
};
///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
/*
    read the inputs and save as req. objects
*/
// list of pp AND list of ss
vector<ProperPrivate> allPP;
vector<SneakySmoker> allSS;
// number of orders AND initial order AND orders queue
queue<Order> allOrders;
void inputHandler() {
    // cout << "get input" << endl;
    // GRID STRUCTURE
    // get grid size
    fscanf(stdin, "%d %d", &(gridSize_x), &(gridSize_y));
    // allocate memory for grid
    grid = new int*[gridSize_x];
    gridFilter = new int*[gridSize_x];
    for (int i = 0; i < gridSize_x; i++) {
        grid[i] = new int[gridSize_y];
        gridFilter[i] = new int[gridSize_y];
    }
    // insert cigbutt counts into grid
    for (int i = 0; i < gridSize_x; i++) {
        for (int j = 0; j < gridSize_y; j++) {
            fscanf(stdin, "%d", &(G(i, j)));
            F(i, j) = 0;
        }
    }
    // cout << "get pp" << endl;
    // PROPER PRIVATES
    // get the number of proper privates
    fscanf(stdin, "%d", &count_pp);
    // get each of the proper private
    int id = -1, size_x = -1, size_y = -1, t = -1, c = -1;
    int area_x = -1, area_y = -1;
    for (int i = 0; i < count_pp; i++) {
        fscanf(stdin, "%d %d %d %d %d", &id, &size_x, &size_y, &t, &c);
        ProperPrivate newPP = ProperPrivate(id, size_x, size_y, t, c);
        // gather from
        for (int j = 0; j < c; j++) {
            fscanf(stdin, "%d %d", &area_x, &area_y);
            Size newArea = Size(area_x, area_y);
            newPP.addArea(newArea);
        }
        allPP.push_back(newPP);
    }
    // ORDER STRUCTURE
    // if no orders, simply return to main
    // cout << "get order" << endl;
    if (fscanf(stdin, "%d", &count_orders) == EOF) {
        return;
    }
    // add the given orders to orders queue
    char orderDesc;
    for (int i = 0; i < count_orders; i++) {
        // cout << "order loop" << endl;
        fscanf(stdin, "%d %s", &t, &orderDesc);
        // cout << "order loop-end" << endl;
        // cout << *orderDesc << endl;
        Order newOrder = Order(t, orderDesc);
        allOrders.push(newOrder);
    }
    // SNEAKY SMOKERS
    // if no sneaky smokers, simply return to main
    // cout << "get ss" << endl;
    if (fscanf(stdin, "%d", &count_ss) == EOF) {
        return;
    }
    // get each of the sneaky smoker
    for (int i = 0; i < count_ss; i++) {
        fscanf(stdin, "%d %d %d", &id, &t, &c);
        SneakySmoker newSS = SneakySmoker(id, t, c);
        // get each of the env ss will smoke
        int cig_count = 0;
        for (int j = 0; j < c; j++) {
            fscanf(stdin, "%d %d %d", &area_x, &area_y, &cig_count);
            Size newEnvCenter = Size(area_x, area_y);
            newSS.addEnv(newEnvCenter, cig_count);
        }
        allSS.push_back(newSS);
    }
}
///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
/*
    locks/unlocks the corresponding area
*/

void lockArea(Size center, Size step = Size(-1, -1)) {
    // get step coords
    int step_x = step.getX();
    int step_y = step.getY();
    // get center coords
    int center_x = center.getX();
    int center_y = center.getY();
    // place 'gatherer'
    if (step_x != -1) {
        for (int i = 0; i < step_x; i++) {
            for (int j = 0; j < step_y; j++) {
                F(center_x + i, center_y + j) = 1;
            }
        }

    }
    // place smoker
    else {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                F(center_x + i, center_y + j) = -1;
            }
        }
        F(center_x, center_y) = -2;
    }
}

void unlockArea(Size center, Size step = Size(-1, -1)) {
    // get step coords
    int step_x = step.getX();
    int step_y = step.getY();
    // get center coords
    int center_x = center.getX();
    int center_y = center.getY();
    // remove smoker
    if (step_x == -1) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                F(center_x + i, center_y + j) = 0;
            }
        }
    }
    // remove gatherer
    else {
        for (int i = 0; i < step_x; i++) {
            for (int j = 0; j < step_y; j++) {
                F(center_x + i, center_y + j) = 0;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
/*
    assign int values to type of intersection for smoker/gatherer placement
*/
enum IntersectType {
    NOT_OCC = 0,
    OCC_ANY = 1,
};
/*
    check if the given area is already occupied by another gatherer/smoker
        - if 2 smokers' centers' overlap => return -3
        - if occupied by smoker(adj to each other) => return -2
        - if occupied by smoker(next to each other) => return -1
        - if  overlap with gatherer => return 2
        - overlap of any kind(more general) => return 1
        - o.w. => return 0
*/
int checkIntersection(Size center, Size traverseArea = Size(-1, -1)) {
    // get center coords
    int x = center.getX();
    int y = center.getY();
    // get traverse area coords
    int step_x = traverseArea.getX();
    int step_y = traverseArea.getY();
    // if no traverse area given => check around for smoker placement
    if (step_x == -1) {
        // occupied by another smoker
        if (F(x, y) == -2) {
            return OCC_ANY;
        }
        // overlap with gatherer
        else if ((F(x - 1, y - 1) == 1) or (F(x, y - 1) == 1) or
                 (F(x + 1, y - 1) == 1) or (F(x - 1, y) == 1) or
                 (F(x + 1, y) == 1) or (F(x - 1, y + 1) == 1) or
                 (F(x, y + 1) == 1) or (F(x + 1, y + 1) == 1)) {
            return OCC_ANY;
        }

        // adj to another smoker
        else if ((F(x - 1, y - 1) == -2) or (F(x, y - 1) == -2) or
                 (F(x + 1, y - 1) == -2) or (F(x - 1, y) == -2) or
                 (F(x + 1, y) == -2) or (F(x - 1, y + 1) == -2) or
                 (F(x, y + 1) == -2) or (F(x + 1, y + 1) == -2)) {
            return NOT_OCC;
        }
        // next to another smoker
        else if ((F(x - 1, y - 1) == -1) or (F(x, y - 1) == -1) or
                 (F(x + 1, y - 1) == -1) or (F(x - 1, y) == -1) or
                 (F(x + 1, y) == -1) or (F(x - 1, y + 1) == -1) or
                 (F(x, y + 1) == -1) or (F(x + 1, y + 1) == -1)) {
            return NOT_OCC;
        }
        // not occupied
        else {
            return NOT_OCC;
        }
    }
    // if traverse area given => check around for gatherer placement
    // if there is at least one grid with value other than 0, its occupied
    else {
        for (int i = 0; i < step_x; i++) {
            for (int j = 0; j < step_y; j++) {
                if (F(x + i, y + j)) {
                    return OCC_ANY;
                }
            }
        }
        return NOT_OCC;
    }
}
///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
/*
    calculate the expected time using clock initializer and time in ms
*/
// sec ms mikros ns
struct timespec timeFactory(struct timespec a, int b) {
    int p = (b % 1000) * 1000000;
    int d = b / 1000;
    if ((a.tv_nsec + p) >= 1000000000) {
        d += 1;
        a.tv_nsec = a.tv_nsec + p - 1000000000;
    } else {
        a.tv_nsec += p;
    }
    a.tv_sec += d;
    return a;
}

///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
/*
    checks the order issues for proper private
*/
void pp_order_check(Size center, Size traverse, int gid) {
    pthread_mutex_t temp_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&temp_mutex);
    pthread_mutex_lock(&filter_mutex);
    if (givenOrder == PRIVATE_BREAK) {
        hw2_notify(PROPER_PRIVATE_TOOK_BREAK, gid, 0, 0);
        while (true) {
            pthread_cond_wait(&order_rec, &temp_mutex);
            if (givenOrder == PRIVATE_CONTINUE) {
                hw2_notify(PROPER_PRIVATE_CONTINUED, gid, 0, 0);
                break;
            } else if (givenOrder == PRIVATE_STOP) {
                hw2_notify(PROPER_PRIVATE_STOPPED, gid, 0, 0);
                pthread_exit((void*)0);
            }
        }
    } else if (givenOrder == PRIVATE_STOP) {
        hw2_notify(PROPER_PRIVATE_STOPPED, gid, 0, 0);
        pthread_exit((void*)0);
    }
    // its occupied => cannot proceed
    while (checkIntersection(center, traverse)) {
        pthread_cond_wait(&gather_sleep, &filter_mutex);
        // check order
        if (givenOrder == PRIVATE_BREAK) {
            hw2_notify(PROPER_PRIVATE_TOOK_BREAK, gid, 0, 0);
            while (true) {
                pthread_cond_wait(&order_rec, &temp_mutex);
                if (givenOrder == PRIVATE_CONTINUE) {
                    hw2_notify(PROPER_PRIVATE_CONTINUED, gid, 0, 0);
                    break;
                } else if (givenOrder == PRIVATE_STOP) {
                    hw2_notify(PROPER_PRIVATE_STOPPED, gid, 0, 0);
                    pthread_exit((void*)0);
                }
            }
        } else if (givenOrder == PRIVATE_STOP) {
            hw2_notify(PROPER_PRIVATE_STOPPED, gid, 0, 0);
            pthread_exit((void*)0);
        }
    }
    // lock the corresponding area on filter
    lockArea(center, traverse);
    pthread_mutex_unlock(&filter_mutex);
    pthread_mutex_unlock(&temp_mutex);
}
///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
/*
    Thread routine function for Proper Private
*/
void* gatherRoutine(void* void_value) {
    pthread_mutex_t temp_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&temp_mutex);
    // cast void* to proper private
    ProperPrivate cur_pp = *(ProperPrivate*)void_value;
    // notify with thread creation
    hw2_notify(PROPER_PRIVATE_CREATED, cur_pp.getGid(), 0, 0);
    // get the area count to clean
    int areaCount = cur_pp.getAreaCount();
    for (int i = 0; i < areaCount; i++) {
        pp_order_check(cur_pp.getArea(), cur_pp.getAreaSize(), cur_pp.getGid());
        int origin_x = cur_pp.getArea().getX();
        int origin_y = cur_pp.getArea().getY();
        int area_x = cur_pp.getAreaSize().getX();
        int area_y = cur_pp.getAreaSize().getY();
        // notfiy after locking-down an area
        hw2_notify(PROPER_PRIVATE_ARRIVED, cur_pp.getGid(), origin_x, origin_y);
        // gather cigbutts
        for (int j = 0; j < area_x; j++) {
            for (int k = 0; k < area_y; k++) {
                int cig_count = G(origin_x + j, origin_y + k);
                for (int p = 0; p < cig_count; p++) {
                    struct timespec cur_time;
                    clock_gettime(CLOCK_REALTIME, &cur_time);
                    struct timespec next_time =
                        timeFactory(cur_time, cur_pp.getGatherInterval());

                    pthread_cond_timedwait(&gather_time, &temp_mutex,
                                           &next_time);

                    if (givenOrder == PRIVATE_BREAK) {
                        unlockArea(cur_pp.getArea(), cur_pp.getAreaSize());
                        hw2_notify(PROPER_PRIVATE_TOOK_BREAK, cur_pp.getGid(),
                                   0, 0);
                        while (true) {
                            pthread_cond_wait(&order_rec, &temp_mutex);
                            if (givenOrder == PRIVATE_CONTINUE) {
                                hw2_notify(PROPER_PRIVATE_CONTINUED,
                                           cur_pp.getGid(), 0, 0);
                                break;
                            } else if (givenOrder == PRIVATE_STOP) {
                                hw2_notify(PROPER_PRIVATE_STOPPED,
                                           cur_pp.getGid(), 0, 0);
                                pthread_exit((void*)0);
                            }
                        }
                        pp_order_check(cur_pp.getArea(), cur_pp.getAreaSize(),
                                       cur_pp.getGid());
                        j = 0;
                        k = -1;
                        break;
                    } else if (givenOrder == PRIVATE_STOP) {
                        unlockArea(cur_pp.getArea(), cur_pp.getAreaSize());
                        hw2_notify(PROPER_PRIVATE_STOPPED, cur_pp.getGid(), 0,
                                   0);
                        pthread_exit((void*)0);
                    }

                    GATHER(G(origin_x + j, origin_y + k));
                    hw2_notify(PROPER_PRIVATE_GATHERED, cur_pp.getGid(),
                               origin_x + j, origin_y + k);
                }
            }
        }
        // area unlock and remove from queue
        pthread_mutex_lock(&filter_mutex);
        unlockArea(cur_pp.getArea(), cur_pp.getAreaSize());
        pthread_cond_broadcast(&gather_sleep);
        pthread_mutex_unlock(&filter_mutex);
        cur_pp.removeArea();
        // notify after cleaning
        hw2_notify(PROPER_PRIVATE_CLEARED, cur_pp.getGid(), 0, 0);
    }
    hw2_notify(PROPER_PRIVATE_EXITED, cur_pp.getGid(), 0, 0);
    pthread_mutex_unlock(&temp_mutex);
    pthread_exit((void*)0);
}

///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
/*
    checks the order issues for proper private
*/
void ss_order_check(Size center, int sid) {
    // cout << "order check" << endl;
    pthread_mutex_t temp_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&temp_mutex);
    pthread_mutex_lock(&filter_mutex);
    if (givenOrder == PRIVATE_STOP) {
        hw2_notify(SNEAKY_SMOKER_STOPPED, sid, 0, 0);
        pthread_exit((void*)0);
    }
    // cout << "while loop" << endl;
    // its occupied => cannot proceed
    while (checkIntersection(center)) {
        // cout << "here" << endl;
        pthread_cond_wait(&smoke_sleep, &filter_mutex);
        if (givenOrder == PRIVATE_STOP) {
            hw2_notify(SNEAKY_SMOKER_STOPPED, sid, 0, 0);
            pthread_exit((void*)0);
        }
    }
    // cout << "lock area" << endl;
    // lock the corresponding area on filter
    lockArea(center);
    pthread_mutex_unlock(&filter_mutex);
    pthread_mutex_unlock(&temp_mutex);
}
///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
/*
    Thread routine function for Sneaky Smoker
*/
void* smokerRoutine(void* void_value) {
    pthread_mutex_t temp_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&temp_mutex);
    // cast void* to sneaky smoker
    SneakySmoker cur_ss = *(SneakySmoker*)void_value;
    // cout << "ec0: "<<cur_ss.getEnvCount() << endl;
    // notify with thread creation
    hw2_notify(SNEAKY_SMOKER_CREATED, cur_ss.getSid(), 0, 0);
    // get the area count to clean
    int envCount = cur_ss.getEnvCount();
    // cout << "ec1: " << envCount << endl;
    for (int i = 0; i < envCount; i++) {
        // cout << "loop: " << i << endl;
        ss_order_check(cur_ss.getEnv(), cur_ss.getSid());
        int origin_x = cur_ss.getEnv().getX();
        int origin_y = cur_ss.getEnv().getY();
        // notfiy after locking-down an area
        hw2_notify(SNEAKY_SMOKER_ARRIVED, cur_ss.getSid(), origin_x, origin_y);
        // throw cigbutts
        int cig_count = cur_ss.getCigbuttCount();
        for (int j = -1; j < 2, 0 < cig_count; j++) {
            for (int k = -1; k < 2, 0 < cig_count; k++) {
                if (k or j){
                    struct timespec cur_time;
                    clock_gettime(CLOCK_REALTIME, &cur_time);
                    struct timespec next_time =
                        timeFactory(cur_time, cur_ss.getSmokeInterval());
                    pthread_cond_timedwait(&smoke_time, &temp_mutex,
                                           &next_time);

                    if (givenOrder == PRIVATE_STOP) {
                        hw2_notify(SNEAKY_SMOKER_STOPPED, cur_ss.getSid(), 0,
                                   0);
                        pthread_exit((void*)0);
                    }

                    THROW(G(origin_x + j, origin_y + k));
                    hw2_notify(SNEAKY_SMOKER_FLICKED, cur_ss.getSid(),
                               origin_x + j, origin_y + k);
                    cig_count--;
                }
            }
        }
        // area unlock and remove from queue
        pthread_mutex_lock(&filter_mutex);
        unlockArea(cur_ss.getEnv());
        pthread_cond_broadcast(&smoke_sleep);
        pthread_mutex_unlock(&filter_mutex);
        cur_ss.removeEnv();
        // notify after cleaning
        hw2_notify(SNEAKY_SMOKER_LEFT, cur_ss.getSid(), 0, 0);
    }

    hw2_notify(SNEAKY_SMOKER_EXITED, cur_ss.getSid(), 0, 0);
    pthread_mutex_unlock(&temp_mutex);
    pthread_exit((void*)0);
}

///////////////////////////////////////////////////////////////////////____END____

/////////////////////////////////////////////////////////////////____START____
/*
    Thread routine function for Commander's orders
*/
void* orderRoutine(void* void_value) {
    // cast the void value
    // cout << "give order" << endl;
    struct timespec* start_time = (struct timespec*)void_value;
    struct timespec cur_time = *start_time;
    pthread_mutex_t orderMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&orderMutex);
    pthread_cond_t orderTimed = PTHREAD_COND_INITIALIZER;
    // traverse over the orders
    for (int i = 0; i < count_orders; i++) {
        // get the order
        Order cur_order = allOrders.front();
        struct timespec next_order_time =
            timeFactory(cur_time, cur_order.getTime());

        pthread_cond_timedwait(&orderTimed, &orderMutex, &next_order_time);

        // broadcast
        givenOrder = cur_order.getStatement();
        pthread_cond_broadcast(&gather_sleep);
        pthread_cond_broadcast(&gather_time);
        pthread_cond_broadcast(&order_rec);
        allOrders.pop();
    }
    pthread_mutex_unlock(&orderMutex);
    pthread_exit((void*)0);
}

///////////////////////////////////////////////////////////////////////____END____

int main(int argc, char const* argv[]) {
    hw2_init_notifier();

    inputHandler();
    // init clock
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    // thread variables
    pthread_t* thread_ss = nullptr;
    pthread_t* thread_pp = nullptr;
    pthread_t thread_order;

    // cout << count_orders << " :: " << count_pp << " :: " << count_ss << endl;

    // create thread for commander's orders
    if ((count_orders > 0) and
        (pthread_create(&thread_order, NULL, &orderRoutine, &ts) != 0)) {
        perror("CANNOT CREATE THREAD");
    }

    if (count_pp > 0) {
        // create threads for proper privates
        thread_pp = new pthread_t[count_pp];
        for (int i = 0; i < count_pp; i++) {
            ProperPrivate* cur_pp = &(allPP[i]);
            if (pthread_create(thread_pp + i, NULL, &gatherRoutine, cur_pp) !=
                0) {
                perror("CANNOT CREATE THREAD");
            }
        }
    }
    if (count_ss > 0) {
        // create threads for sneaky smokers
        thread_ss = new pthread_t[count_ss];
        for (int i = 0; i < count_ss; i++) {
            SneakySmoker* cur_ss = &(allSS[i]);
            // cout << cur_ss->getEnvCount() << endl;
            if (pthread_create(thread_ss + i, NULL, &smokerRoutine, cur_ss) !=
                0) {
                perror("CANNOT CREATE THREAD");
            }
        }
    }

    // terminate thread for commander's orders
    if ((count_orders > 0) and (pthread_join(thread_order, NULL) != 0)) {
        perror("CANNOT TERMINATE THREAD");
    }

    if (count_pp > 0) {
        // terminate the threads for proper privates
        for (int i = 0; i < count_pp; i++) {
            if (pthread_join(thread_pp[i], NULL) != 0) {
                perror("CANNOT TERMINATE THREAD");
            }
        }
    }

    if (count_ss > 0) {
        // terminate the threads for sneaky smokers
        for (int i = 0; i < count_ss; i++) {
            if (pthread_join(thread_ss[i], NULL) != 0) {
                perror("CANNOT TERMINATE THREAD");
            }
        }
    }

    return 0;
}
