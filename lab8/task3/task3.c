#include <stdio.h>

int fib (int lim) {

    int t1 = 0;
    int t2 = 1;
    int hold;
    if (lim <= t1)
        return -1;
    else
        printf("%d ", t1);
    while (lim > t2) {
        printf("%d ", t2);
        hold = t1;
        t1 = t2;
        t2 = t2 + hold;
    }
    return t1;
}


int main() {

    int n;
    // get te limit from the user
    printf("Enter your limit: ");
    scanf("%d", &n);
    fib(n);
    printf("\n");
    return 0;
}