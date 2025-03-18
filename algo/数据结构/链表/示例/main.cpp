#include <iostream>

struct ListNode {
    struct ListNode *prev, *next;
};

static void ListInit(ListNode *head)
{
    head->next = head;
    head->prev = head;
}

static void ListAdd(ListNode *node, ListNode *head)
{
    head->next = node;
    head->next->prev = node;
    node->prev = head;
    node->next = head->next;
}

static void ListAddTail(ListNode *node, ListNode *head)
{
    ListNode *tail = head->prev;

    head->prev = node;
    tail->next = node;
    node->next = head;
    node->prev = tail->prev;
}

static void ListDel(ListNode *node)
{
    ListNode *prev = node->prev, *next = node->next;
    prev->next = next;
    next->prev = prev;
}

int main(int argc, char *argv[])
{
    return 0;
}