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

#define LIST_NODE_NUM 5

/*
链表节点
*/
struct node
{
    void *data;
    struct node *next;
};

struct data_human 
{
    int age;
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
销毁节点。
参数
    node:节点。
返回值
    NA
*/
void destroy_node(struct node **node)
{
    struct node *temp = *node;

    if (temp->next != NULL)
    {
        LIST_DBG("next not null\n");
    }
    else
    {
        free(temp->data);
        temp->data = NULL;
        free(temp);
        temp = NULL;
    }

    
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
        free(temp);
        temp = NULL;
    }
    
}

void show_list_value(struct node **head)
{
    int i = 0;
    struct node *temp = *head;
    
    while (temp != NULL )
    {
        struct data_human* data = temp->data;
        LIST_DBG("node %d, data=%d\n", ++i, data->age);
        temp = temp->next;
    }
}

int main()
{
    struct node* head = NULL;
    int i = 0;
    struct node* temp = NULL;

    LIST_DBG("create list:\n");
    head = create_list(LIST_NODE_NUM);
    show_list_value(&head);//打印创建的链表
    LIST_DBG("init list:\n");
    temp = head;
    while (temp != NULL)
    {
        struct data_human* data = NULL;
        data = malloc(sizeof(struct data_human));
        data->age = i + 20;
        temp->data = data;
        temp = temp->next;
        i++;
    }
    show_list_value(&head);//打印赋初值的链表
    LIST_DBG("change list:\n");
    temp = head;
    {
        struct data_human* data1 = NULL;
        struct data_human* data2 = NULL;
        struct data_human* data3 = NULL;
        data1 = malloc(sizeof(struct data_human));
        data2 = malloc(sizeof(struct data_human));
        data3 = malloc(sizeof(struct data_human));
        data1->age = 221;
        data2->age = 222;
        data3->age = 223;

        add_node_tail(&head,data1);
        add_node_any(&head,2,data2);
        add_node_head(&head,data3);
        show_list_value(&head);//打印改变后的链表
        LIST_DBG("change list:\n");
        data1 = NULL;
        data2 = NULL;
        data3 = NULL;
        temp = popup_node_frome_head(&head);
        data3 = temp->data;
        LIST_DBG("popup head node age = %d\n", data3->age);
        destroy_node(&temp);

        temp = popup_node_frome_tail(&head);
        data1 = temp->data;
        LIST_DBG("popup tail node age = %d\n", data1->age);
        destroy_node(&temp);
    }
    show_list_value(&head);//打印改变后的链表
    temp = head;

    // i = 0;
    // while (head != NULL )
    // {
    //     struct data_human* data = head->data;
    //     LIST_DBG("count %d, d=%d\n", ++i, data->age);
    //     head = head->next;
    // }
    

    destroy_list(&temp);
    return 0;
}