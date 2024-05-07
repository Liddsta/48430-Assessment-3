#include "rsa.h"

#include <stdlib.h>
#include <stdio.h>

int isprime(int num){
  int i=2;
  while (i<=num/2) {
    if(num%i==0){
      return 0;
    }
    i++;
  }
  return 1;
}

int* getpandq(){
  long int p=random();
  while (isprime(p)==0){
    long int p=random();
  }
  long int q=random();
  while (isprime(q)==0){
    long int q=random();
  }
  int out[2]={(int) p,(int) q};
  return out;
}

int getn(int p, int q){
  return p*q;
}

int gcd(int a, int b){
  if(b>0){
    return gcd(b,a%b);
  }else {
    return a;
  }
}

int getlambda(int p, int q){
  int g = gcd(p-1,q-1);
  int out = (p-1*q-1)/g; 
  return out;
}

int gete(int l){
  if(gcd(17,l)!=1){
    printf("o hsid");
    return 0;
  } else {
    return 17;
  }
}

int getd(int e, int l){
  /* get d by solving `de ≡ 1 (mod l)` for d */
  /* TODO */
  return 0;
}
