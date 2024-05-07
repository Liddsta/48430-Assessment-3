#ifndef RSA_H_
#define RSA_H_

/* the public key consists of n and e, the private key consists of d*/

/* steps for keygen */

/* step 1 */

/* check if an integer num is prime */
int isprime(int num); /* returns 1 if prime, 0 if not */
/* generate two random primes and return them in an array, p then q */
int* getpandq(void);

/* step 2 */

/* get the multiple of p and q, n */ /* i know this one is simple but it's the second step ok */
int getn(int p, int q);

/* step 3 */

/* get the gcd of a and b using the euclidean algorithm */
int gcd(int a, int b);
/* get the lambda function of n, also known as the lcm of p and q */
int getlambda(int p, int q);

/* step 4 */

/* set e. for this implementation we will be using 17 by default, unless 17 is coprime with lambda */
int gete(int l);

/* step 5 */

/* get the private key d from e and l */
int getd(int e, int l);

/* key generation main function, returns an array of the integers [e, n, d] used for encrpytion and decrption */
int getkeys(void);

/* functions for encryption and decreption from / to plaintext */

/* convert the message M into the "padded" integer m */
int pad(char M[]);

/* reverse the padding process, convert an integer m into a message M */ 
char unpad(int c);

/* return the encrypted integer c */
int enc(int n, char M[]); /* call this from outside */

/* return the decrpyed message M */
char dec(int d, int n, int c); /* call this from outside */

#endif
