#include <stdio.h>
#include <stdlib.h>
int main(){


int galois_single_multiply(int a, int b, int w);
int galois_single_divide(int a, int b, int w);
int galois_log(int value, int w);
int galois_ilog(int value, int w);

int galois_create_log_tables(int w);   /* Returns 0 on success, -1 on failure */
int galois_logtable_multiply(int x, int y, int w);
int galois_logtable_divide(int x, int y, int w);

int galois_create_mult_tables(int w);   /* Returns 0 on success, -1 on failure */
int galois_multtable_multiply(int x, int y, int w);
int galois_multtable_divide(int x, int y, int w);

int galois_shift_multiply(int x, int y, int w);
int galois_shift_divide(int x, int y, int w);

int galois_create_split_w8_tables();
int galois_split_w8_multiply(int x, int y);

int galois_inverse(int x, int w);
int galois_shift_inverse(int y, int w);

int *galois_get_mult_table(int w);
int *galois_get_div_table(int w);
int *galois_get_log_table(int w);
int *galois_get_ilog_table(int w);

void galois_region_xor(           char *r1,         /* Region 1 */
                                  char *r2,         /* Region 2 */
                                  char *r3,         /* Sum region (r3 = r1 ^ r2) -- can be r1 or r2 */
                                  int nbytes);      /* Number of bytes in region */

/* These multiply regions in w=8, w=16 and w=32.  They are much faster
   than calling galois_single_multiply.  The regions must be long word aligned. */

void galois_w08_region_multiply(char *region,       /* Region to multiply */
                                  int multby,       /* Number to multiply by */
                                  int nbytes,       /* Number of bytes in region */
                                  char *r2,         /* If r2 != NULL, products go here.  
                                                       Otherwise region is overwritten */
                                  int add);         /* If (r2 != NULL && add) the produce is XOR'd with r2 */

void galois_w16_region_multiply(char *region,       /* Region to multiply */
                                  int multby,       /* Number to multiply by */
                                  int nbytes,       /* Number of bytes in region */
                                  char *r2,         /* If r2 != NULL, products go here.  
                                                       Otherwise region is overwritten */
                                  int add);         /* If (r2 != NULL && add) the produce is XOR'd with r2 */

void galois_w32_region_multiply(char *region,       /* Region to multiply */
                                  int multby,       /* Number to multiply by */
                                  int nbytes,       /* Number of bytes in region */
                                  char *r2,         /* If r2 != NULL, products go here.  
                                                       Otherwise region is overwritten */
                                  int add);         /* If (r2 != NULL && add) the produce is XOR'd with r2 */
                                  
    }
