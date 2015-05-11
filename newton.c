#include <stdio.h>
#include <math.h>


/* 与えらえれるx,y座標 */
double x[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
double y[] = {0.91735, 0.8608, 0.81925, 0.7792, 0.71875, 0.6016, 0.37105, -0.056, -0.79505};

/* y配列の要素数 */
#define N (sizeof(y) / sizeof(double))

/* 階差の各0番目の値を入れる配列 0で初期化 */
double a[N - 1] = {};

/*--------------------------------
 * 階上計算
 *------------------------------*/
int factorial(int n)
{
    if(n > 0){
        return n * factorial(n - 1);
    } else {
        return 1;
    }
}

/*--------------------------------
 * 階差計算
 *------------------------------*/
void difference(void)
{
    double buf[N];      //Nはy配列の要素数
    int i, j, k;        //ループ用変数
    
    /* y座標をbuf配列にコピーする */
    for(i = 0; i < N; i++){
        buf[i] = y[i];
    }
    
    /* 階差計算を行う */
    for(j = 0; j < N - 1; j++){
        for(k = 0; k < (N - (1 + j)); k++){
            buf[k] = buf[k + 1] - buf[k];
        }
        a[j] = buf[0];  //階差のそれぞれ1番目の要素を使用するのでa[]配列に置いていく
    }
}

/*--------------------------------
 * ニュートン補間
 *------------------------------*/
double newton(double X)
{
    double sum, temp;
    double p;
    
    p = (X - x[0]) / (x[1] - x[0]);
    
    difference();
    
    sum = y[0];
    for(int i = 0; i < N; i++){
        temp = 1;
        for(int j = 0; j < (i + 1); j++){
            temp *= (p - j);
        }
        temp = temp * a[i] / factorial(i + 1);
        sum += temp;
    }
    return sum;
}

/*******************************
 * main関数
 ******************************/
int main(void)
{
    printf("y = %f\n", newton(0.43));    
    
    return 0;
}