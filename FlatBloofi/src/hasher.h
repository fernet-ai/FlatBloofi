#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "time.h"


 struct hasher{
	int seed;
	int maxval;
	int *randomkeys;
	int numdichiavi;

 };

struct hasher* init_hasher();
struct hasher* init_hasher2(int seed);
int hash(struct hasher* h,const void*o,int whichhash);
int java_hashCode(const char *str);
void setMaxValue(struct hasher*h,int bitSetSize);
void setNumberOfRandomKeys(struct hasher* h,int K);
int int_rand(int min,int max);
