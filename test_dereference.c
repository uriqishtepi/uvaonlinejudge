#include<stdio.h>

/* there is an advantage to get a pointer, because it seems
 * that the compiler generates the references to create more code,
 * however this advantage dissapears in optimized mode */

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


void foo(locker_info *id_array, int offset, int inc)
{
    locker_info * ptr_idarr = &id_array[offset];
    ptr_idarr->count += inc;
    ptr_idarr->killme = inc;
    ptr_idarr->saveme = inc;
    ptr_idarr->readonly = inc;
    ptr_idarr->tracked = inc;
}

void faa(locker_info *id_array, int offset, int inc)
{
    id_array[offset].count += inc;
    id_array[offset].killme = inc;
    id_array[offset].saveme = inc;
    id_array[offset].readonly = inc;
    id_array[offset].tracked = inc;
}

int getval()
{
   return 1;
}

int main()
{
    int count = 0;
    int oldcount = 2;
    int nretries = 2;
    volatile int increment = 0;
    int i;
    #define MAX 1000000

    locker_info id_array[3] = {{0}};
    int (*fptr)(locker_info *id_array, int offset, int inc);
    if(rand() > 1)
        fptr = foo;
    else
        fptr = faa;

    for(i = 0; i < MAX; i++) {
        fptr(id_array, 1, 1);
    }

    /*
    */
    if(fptr == foo)
        fptr = faa;
    else fptr = foo;
    for(i = 0; i < MAX; i++) {
        fptr(id_array, 1, 1);
    }

    printf("count %d\n", id_array[1].count);
}

