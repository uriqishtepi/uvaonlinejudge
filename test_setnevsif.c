#include<stdio.h>
#include<strings.h>
#include<stdint.h>
#define MAX 10000000


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x) 
#define LOC __FILE__":"TOSTRING(__LINE__)

/* testing advantage of setting a = ((b&0x3) > 0) vs using if
 * same number of instructions, so it is possible to not have
 * any gains at all.
 */

typedef struct {
	int		valid;
	int		self_wait;
	int		in_abort;
	int	count;
	int	id;
	int		last_lock;
	int	*last_obj;
	int	last_locker_id;
	int	pgno;
	int 		killme;
	int 		saveme;
	int 		readonly;
	int 		tracked;
    int   tid;
} locker_info;


void foo( locker_info * ptr_idarr, volatile int * flag) 
{
    int i;
    for(i = 0; i < MAX; i++) {
        ptr_idarr->killme = (* flag & 0x3) ; 
        ptr_idarr->saveme = ((* flag & (0x4 | 0x8)) );
        ptr_idarr->readonly = (* flag & 0x5) ; 
        ptr_idarr->tracked = (* flag & 0x6) ; 
        ptr_idarr->in_abort = (* flag & 0x7) ; 
        (*flag)++;
    }
}

void faa( locker_info * ptr_idarr, volatile int * flag) 
{
    int i;
    for(i = 0; i < MAX; i++) {
        if(* flag & 0x3) ptr_idarr->killme = 1;
        else ptr_idarr->killme = 0;
        if(* flag & (0x4 | 0x8)) ptr_idarr->saveme = 1;
        else ptr_idarr->saveme = 0;
        if(* flag & 0x5) ptr_idarr->readonly = 1;
        else ptr_idarr->readonly = 0;
        if(* flag & 0x6) ptr_idarr->tracked = 1;
        else ptr_idarr->tracked = 0;
        if(* flag & 0x7) ptr_idarr->in_abort = 1;
        else ptr_idarr->in_abort = 0;
        (*flag)++;
    }
}

struct st {
    int a;
    int b;
    int c;
};

#include <string.h>
static const char ev_str[][6] = { "unset", "txn", "sql", "sp" };
const char *txn = "txn";

int main()
{
    for (int i = 0; i < sizeof(ev_str)/sizeof(char*); i++)
        printf("%d: ev_str[i] = %s, sizeof(ev_str[i]) = %ld strlen = %d\n",
                i, ev_str[i], sizeof(ev_str[i]), strlen(ev_str[i]));
    printf("sizeof(txn) %ld\n", sizeof(txn));
    printf("LOC %s\n", LOC);
    int ef = 3;
    int *efp = &ef;
    printf("&ef=0x%p efp=0x%p &*efp=0x%p\n", &ef, efp, &(*efp));
    locker_info id_array[3] = {{0}};
    volatile int offset = 2;
    int a = 0xaaaaaaaa;
    int b = 0xbbbbbbbb;
    uint64_t c = (int64_t) a;

    printf("a: 0x%x\n", a);
    printf("b: 0x%x\n", b);
    printf("lx(a): 0x%lx\n", c);

    /*
    char * abc = "abc";
    char * bcd = NULL;
    int rc = strcasecmp(abc, bcd); // this will crash, parameter is NULL
    printf("rc = strcasecmp(abc, bcd); = %d\n", rc);
    */

    struct st s1 = {.b = 1, .c = 3};
    printf("s1: %d %d %d\n", s1.a,s1.b,s1.c);

    /*
     */
    volatile int flag = 0x1234;
    foo(&id_array[offset], &flag); 
    flag = 0x1234;
    /*faa(&id_array[offset], &flag); */

    printf("res %d\n", id_array[offset].tracked);
    return 0;
}
