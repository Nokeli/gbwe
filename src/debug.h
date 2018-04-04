/** 
 * Utils
 */

/* Written January 2002 by Hyungsuk JI.  */

/* Nonzero if any of the input files are the standard input. */
//int have_read_stdin;
#define SWAP(a,b) itemp=(a);(a)=(b);(b)=itemp;
#define SWAP_STRING(a,b) strcpy(strtmp,(a));strcpy((a),(b));strcpy((b),strtmp);
#define HERE printf("%d\n",__LINE__);
#define max(A,B) ((A) > (B) ? (A) : (B))
#define dprint(expr) printf(#expr " = %d\n", expr)
#define fprint(expr) printf(#expr " = %f\n", expr)
#define sprint(expr) printf(#expr " = \"%s\"\n", expr)
#define Sprint(expr) printf(#expr " = \"%s\"\n", expr)
#define paste(front,back) front ## back

