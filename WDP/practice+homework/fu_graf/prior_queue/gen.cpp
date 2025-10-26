#include<random>
#include<cstdlib>
#include<cstdio>
using namespace std;

int main(int deq, char* argv[]) {
    int a = stoi(argv[1]);
    int b = stoi(argv[2]), c;
    int d = stoi(argv[3]);
    srand(d);
    printf("%d \n", a);
    for(int i = 0; i < a; i++) {
        c = rand() % 4;
        if(c == 3) {
            printf("%d %d\n", 1, rand() % b);
        } else {
            printf("%d ", c);
            if(c == 1) {
                printf("%d\n", rand() % b);
            } else {
                printf("\n");
            }
        }
    }
    return 0;
}