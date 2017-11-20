#include<stdio.h>
#define MAX 10000000

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

int main()
{
    int count = 0;
    int oldcount = 2;
    volatile int res = 0;
    volatile int res2 = 0;
    int i;
    locker_info id_array[3] = {{0}};
    volatile int offset = 2;


    /*
     */
    volatile int flag = 0x1234;
    foo(&id_array[offset], &flag); 
    flag = 0x1234;
    /*faa(&id_array[offset], &flag); */

    printf("res %d\n", id_array[offset].tracked);
    return 0;
}
