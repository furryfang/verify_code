/* 
编译器：MinGW
语言：c
系统：windows11
作用：验证双向链表的创建，插入，弹出操作.(此链表不包含不存数据的头节点).
    与此库中单向链表不同，这里将链表单独成一个结构体，里面包含头节点尾节点和长度。相交单链表的实现这样方便访问，不需要一直存头节点。
结论：NA
 */
#include<stdio.h>
#include<stdlib.h>

#define LOG_I(fmt, ...) {printf("line:%d {%s} ", __LINE__, __func__);printf(fmt, ##__VA_ARGS__);}

typedef enum ENUM_ERR
{
    TWOWAY_OK,
    TWOWAY_ERR,
}enum_err;

struct data
{
    int age;
    int weigth;
};

struct node
{
    struct node *next;
    struct node *pre;
    struct data *date;
};

struct list
{
    struct node* head;
    struct node* tail;
    int list_num;
};

struct list *create_list(void);
struct node *create_node(void);
enum_err destory_list(struct list *list);
enum_err destory_node(struct node *node);
enum_err add_node_any(struct list *list, int location, struct node *node);
enum_err add_node_head(struct list *list, struct node *node);
enum_err add_node_tail(struct list *list, struct node *node);
struct node *popup_node_any(struct list *list, int loaction);
struct node *popup_node_head(struct list *list);
struct node *popup_node_tail(struct list *list);


struct list *create_list(void)
{
    struct list *list = NULL;

    list = malloc(sizeof(struct list));
    if (list == NULL)
    {
        LOG_I("malloc list head fail!\n");
        goto ERR_LIST;
    }
    list->list_num = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
ERR_LIST:
    list = NULL;
    return list;
}

struct node *create_node(void)
{
    struct node *new_node = NULL;
    new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        LOG_I("malloc new node fail!\n");
        goto ERR_NODE;
    }
    new_node->date = NULL;
    new_node->next = NULL;
    new_node->pre = NULL;
    return new_node;
ERR_NODE:
    new_node = NULL;
    return new_node;
}

enum_err destory_list(struct list *list)
{
    struct node *head = list->head;
    struct node *temp = NULL;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        destory_node(temp);
        list->list_num--;
    }
    if (list->list_num != 0 )
    {
        LOG_I("destory list fail! free count != real count.\n");
        return TWOWAY_ERR;
    }
    if (list != NULL)
    {
        free(list);
        list = NULL;
    }
    return TWOWAY_OK;
}

enum_err destory_node(struct node *node)
{
    if (node != NULL)
    {
        if (node->date != NULL)
        {
            free(node->date);
            node->date = NULL;
        }
        free(node);
        node = NULL;
    }
    return TWOWAY_ERR;
}

enum_err add_node_any(struct list *list, int location, struct node *node)
{
    struct node *temp = list->head;

    if (list->list_num < location || location == 0)
    {
        LOG_I("location is more than list_num\n");
        return TWOWAY_ERR;
    }
    for (int i = 1; i < location; i++)
    {
        temp = temp->next;
    }
    node->next = temp;
    node->pre = temp->pre;
    temp->pre = node;
    if (list->list_num == location)
    {
        list->tail = node;
    }
    list->list_num++;

    return TWOWAY_OK;
}

enum_err add_node_head(struct list *list, struct node *node)
{
    if (list == NULL || node == NULL)
    {
        LOG_I("list or node is null\n");
        return TWOWAY_ERR;
    }
    if (list->list_num == 0)
    {
        list->head = node;
        list->head->next = NULL;
        list->head->pre = NULL;
        list->tail = list->head;
    }
    else
    {
        node->next = list->head;
        list->head->pre = node;
        node->pre = NULL;
        list->head = node;
    }
    list->list_num++;

    return TWOWAY_OK;
}

enum_err add_node_tail(struct list *list, struct node *node)
{
    if (list == NULL || node == NULL)
    {
        LOG_I("list or node is null\n");
        return TWOWAY_ERR;
    }

    if (list->list_num == 0)
    {
        list->tail = node;
        list->tail->pre = NULL;
        list->tail->next = NULL;
        list->head = list->tail;   
    }
    else
    {
        node->next = NULL;
        node->pre = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->list_num++;

    return TWOWAY_OK;
}

struct node *popup_node_any(struct list *list, int loaction)
{

}
struct node *popup_node_head(struct list *list)
{
    struct node *node_head = NULL;

    if (list == NULL )
    {
        LOG_I("list is null\n");
        return node_head;
    }
    if (list->list_num == 0)
    {
        LOG_I("list not have node\n");
        return node_head;
    }
    else if(list->list_num == 1)
    {
        node_head = list->head;
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        node_head = list->head;
        list->head = list->head->next;
        list->head->pre = NULL;
        node_head->next = NULL;
    }

    list->list_num--;

    return node_head;
}
struct node *popup_node_tail(struct list *list)
{
    struct node *node_tail = NULL;
    if (list == NULL )
    {
        LOG_I("list is null\n");
        return node_tail;
    }
    if (list->list_num == 0)
    {
        LOG_I("list not have node\n");
        return node_tail;
    }
    else if(list->list_num == 1)
    {
        node_tail = list->tail;
        list->tail = NULL;
        list->head = NULL;
    }
    else
    {
        node_tail = list->tail;
        list->tail = list->tail->pre;
        list->tail->next = NULL;
        node_tail->pre = NULL;
    }
    list->list_num--;

    return node_tail;
}

void show_list(struct list* list)
{
    int count = 0;
    struct node *node_temp = list->head;

    while (node_temp != NULL)
    {
        LOG_I("age=%d, weigth=%d, count=%d\n",node_temp->date->age,node_temp->date->weigth, count);
        node_temp = node_temp->next;
        count++;
    }
}
int main(int argc, void *argv)
{
    struct list *my_list = NULL;

    my_list = create_list();
    for (int i = 0; i < 10; i++)
    {
        struct node *temp_node = NULL;
        temp_node = create_node();
        temp_node->date = malloc(sizeof(struct data));
        temp_node->date->age = rand() % 110;
        temp_node->date->weigth = rand() & 300;
        // add_node_tail(my_list,temp_node);
        add_node_head(my_list,temp_node);
    }
    show_list(my_list);
    LOG_I("list_num=%d\n", my_list->list_num);
    for (int i = 0; i < 10; i++)
    {
        struct node *temp_node = NULL;
        // temp_node = popup_node_tail(my_list);
        temp_node = popup_node_head(my_list);
        LOG_I("age = %d, weight = %d\n", temp_node->date->age, temp_node->date->weigth);
        destory_node(temp_node);
    }
    LOG_I("list_num=%d\n", my_list->list_num);
    for (int i = 0; i < 10; i++)
    {
        struct node *temp_node = NULL;
        temp_node = create_node();
        temp_node->date = malloc(sizeof(struct data));
        temp_node->date->age = rand() % 110;
        temp_node->date->weigth = rand() & 300;
        add_node_tail(my_list,temp_node);
    }
    {
        struct node *temp_node = NULL;
        temp_node = create_node();
        temp_node->date = malloc(sizeof(struct data));
        temp_node->date->age = 1;
        temp_node->date->weigth = 1;
        add_node_any(my_list, 1, temp_node);
    }
    show_list(my_list);
    LOG_I("list_num=%d\n", my_list->list_num);
    destory_list(my_list);

    return 0;
}