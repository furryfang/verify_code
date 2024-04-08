/* 
编译器：MinGW
语言：c
系统：windows11
作用：验证单向链表的创建，插入，弹出操作
结论：NA
 */
#include<stdio.h>
#include<stdlib.h>

#define LIST_DBG(fmt, ...)      {printf("func:%s ", __func__); \
                                printf("line:%d ",__LINE__); \
                                printf(fmt,##__VA_ARGS__); \
                                }while(0)
/*
链表节点
*/
struct node
{
    void *data;
    struct node *next;
};

/*
创建链表
参数
    node_num:链表节点个数。
返回值
    链表头节点
*/
struct node* create_list(int node_num)
{
    struct node* head = NULL;
    struct node* tail = NULL;
    int count = 0;
    
    tail = malloc(sizeof(struct node));
    head = tail;

    for (count = 0; count<node_num - 1; count++)
    {
        tail->next = malloc(sizeof(struct node));
        if (!tail)
        {
            LIST_DBG("malloc node fail\n");
            goto EXIT;
        }
        tail = tail->next;
    }
    tail->next = NULL;    

    return head;

EXIT:
    while (head!=NULL)
    {
        free(head);
        head = NULL;
    }
    return NULL;
}


/*
创建链表
参数
    node_num:链表节点个数。
返回值
    链表头节点
*/
void add_node_any(struct node** list, int station,void *data)
{
    struct node *new_node = NULL;
    int current_station = 0;
    struct node *head_node = *list;

    new_node = malloc(sizeof(struct node));
    if (!new_node)
    {
        new_node = NULL;
        LIST_DBG("malloc node fail\n");
    }
    new_node->data = data;

    if (station == 0 || list == NULL)
    {
        new_node->next = head_node;
        head_node = new_node;
        return ;
    }
    while (!head_node->next && current_station < station)
    {
        current_station++;
        head_node = head_node->next;
    }

    new_node->next = head_node->next;
    head_node->next = new_node;
    return ;
}

/*
从链表头插入节点(头插)
参数
    list:链表。
    data:插入的节点数据。
返回值
    NA
*/
void add_node_head(struct node** list,void *data)
{
    struct node *new_node = NULL;

    new_node = malloc(sizeof(struct node));
    if (!new_node)
    {
        new_node = NULL;
        LIST_DBG("malloc node fail\n");
    }
    new_node->data = data;

    new_node->next = *list;
    *list = new_node;

    return ;
}

/*
从链表尾插入节点(尾插)
参数
    list:链表。
    data:插入的节点数据。
返回值
    NA
*/
void add_node_tail(struct node** list,void *data)
{
    struct node *head = *list;
    struct node *new_node = NULL;

    new_node = malloc(sizeof(struct node));
    if (!new_node)
    {
        new_node = NULL;
        LIST_DBG("malloc node fail\n");
    }

    new_node->data = data;
    new_node->next = NULL;
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = new_node;
    return ;
}

/*
从链表头弹出一个节点
参数
    list:链表。
返回值
    弹出的节点本身，注意弹出节点中的数据需要手动释放。
*/
struct node* popup_node_frome_head(struct node **list)
{
    struct node *temp = NULL;

    temp = *list;
    *list = (*list)->next;

    temp->next = NULL;

    return temp;
}

/*
从链表尾弹出一个节点
参数
    list:链表。
返回值
    弹出的节点本身，注意弹出节点中的数据需要手动释放。
*/
struct node* popup_node_frome_tail(struct node **list)
{
    struct node *temp = NULL;
    struct node *head = *list;
    struct node *pre_node = NULL;

    while (head->next != NULL)
    {
        pre_node = head;
        head = head->next;
    }
    
    pre_node->next = NULL;

    return head;
}

/*
销毁节点。有些问题，暂未修复
参数
    node:节点。
返回值
    NA
*/
void destroy_node(struct node **node)
{
    struct node *temp = *node;

    free(temp->data);
    temp->data = NULL;
    node = NULL;
}
/*
销毁链表
参数
    list:链表。
返回值
    NA
*/
void destroy_list(struct node **list)
{
    struct node *head = *list;
    struct node *temp = NULL;

    while (head != NULL)
    {
        temp = head;
        free(head->data);
        head->data = NULL;
        head = head->next;
        temp = NULL;
    }
    
}

struct data_human 
{
    int age;
};

int main()
{
    struct node* head = NULL;
    int i = 0;
    struct node* temp = NULL;

    head = create_list(5);
    i = 20;
    temp = head;
    LIST_DBG("init list:\n");
    while (temp != NULL)
    {
        struct data_human* data = NULL;
        data = malloc(sizeof(struct data_human));
        data->age = i;
        temp->data = data;
        LIST_DBG("node[%d] age=[%d]\n", i-19, data->age);
        temp = temp->next;
        i++;
    }
    LIST_DBG("change list:\n");
    temp = head;
    {
        struct data_human* data = NULL;
        data = malloc(sizeof(struct data_human));
        data->age = 222;

        add_node_tail(&head,data);
        add_node_any(&head,2,data);
        add_node_head(&head,data);

        temp = popup_node_frome_head(&head);
        data = temp->data;
        LIST_DBG("popup head node age = %d\n", data->age);
        // destroy_node(&temp);

        temp = popup_node_frome_tail(&head);
        temp = temp->data;
        LIST_DBG("popup tail node age = %d\n", data->age);
        // destroy_node(&temp);
    }
    


    i = 0;
    while (head != NULL )
    {
        struct data_human* data = head->data;
        LIST_DBG("count %d, d=%d\n", ++i, data->age);
        head = head->next;
    }


    return 0;
}