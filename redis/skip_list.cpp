#include <iostream>

float randFloat() {
    return (float)rand() / RAND_MAX;
}

int randomLevel(int max_level) {
    // 注意：设置为0.5时，1到n-1层之间i+1层数量=i层数量/2，但n层数量=n-1层数量。例如有5层，第4层和第5层的概率相同。因为在>=4的前提内，50%=4，50%>=5。而由于最大为5所以最终50%=4，50%=5
    // 但设置为0.25时(redis)，1到n-1层之间i+1层数量=i层数量/4，n层数量=n-1层数量/3。例如有5层，第4层概率是逼近与第5层的1/3的。因为在>=4的前提内，25%=4，75%>=5。而由于最大为5所以最终25%=4，75%=5
    static float SKIP = 0.25;
    int level = 1;
    while (randFloat() < SKIP && level < max_level) {
        level++;
    }
    return level;
}

int main () {
    int max_level = 5;
    int sum[max_level + 1];
    for (int i = 0; i <= max_level; ++i) sum[i] = 0;
    for (int i = 0; i < 100000; ++i) {
        sum[randomLevel(max_level)]++;
    }
    for (int i = 1; i <= max_level; ++i) printf("level %d : %d\n", i, sum[i]);
    return 0;
}