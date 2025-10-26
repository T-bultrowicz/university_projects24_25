#include<cstdio>
#include<random>
#include<ctime>

int main(int argc, char* argv[]) {
    int a = std::stoi(argv[1]);
    int b = std::stoi(argv[2]);
    srand(std::stoi(argv[3]));
    printf("%d %d\n", a, b);
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            if(rand() % 2) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
    return 0;
}