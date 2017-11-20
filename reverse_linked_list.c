typedef llist llist
struct llist {
    int value;
    llist * next;
}



llist * reverse(llist * head)
{
    prev = NULL;
    curr = head;
    if(!curr) return NULL;

    next = curr.next;
    if(!next) return curr;

    while(next) {
        curr.next = prev;
        prev = curr;
        curr = next;
        next = curr.next;
    }
    curr.next = prev;
    head = curr;
}



{
    prev = NULL;
    curr = head; 
    if(!curr) return NULL;
    next = curr;

    while(curr) {
        next = curr.next;
        curr.next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
