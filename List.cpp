//
// Created by 张萍 on 2020/11/21.
//
#include "iostream"
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};
/**
 * 插入排序的动画演示如上。从第一个元素开始，该链表可以被认为已经部分排序（用黑色表示）。
 * 每次迭代时，从输入数据中移除一个元素（用红色表示），并原地将其插入到已排好序的链表中。
 * 插入排序算法：
        插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
        每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
        重复直到所有输入数据插入完为止。
 */
ListNode* insertionSortList(ListNode* head) {
    if (NULL == head || NULL == head->next) {
        return head;
    }
    ListNode *p = new ListNode(0);
    p->next = head;
    ListNode* pre;
    ListNode* current = head->next;
    bool flag;
    while (current != NULL) {
        int curr_val = current->val;
        ListNode *tmp = p->next;
        pre = p;
        flag = false;
        while (tmp != current) {
            if (tmp->val > curr_val) {
                pre->next = current;
                ListNode *curr_after = current->next;
                current->next = tmp;
                while (tmp->next != current) {
                    tmp = tmp->next;
                }
                tmp->next = curr_after;
                current = curr_after;
                flag = true;
                break;
            } else {
                pre = tmp;
                tmp = tmp->next;
            }
        }
        if (!flag) {
            current = current->next;
        }
    }
    return p->next;
}

/**
 * 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
 * 进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
 */
//我写的，逻辑应该没什么问题，但是输入链表太很长且重复数据很多的时候超时了
ListNode* sortList_bubble(ListNode* head) {
    if (nullptr == head || nullptr == head->next) { // <=1个节点直接return
        return head;
    }
    ListNode *dummyHead = new ListNode(-1);
    dummyHead->next = head;
    ListNode *tail = dummyHead, *front, *behind, *pre;
    // 冒泡排序
    while (tail != dummyHead->next) {
        pre = dummyHead;
        front = dummyHead->next;
        behind = front->next;
        while (behind != nullptr && behind != tail) {
            if (front->val > behind->val) { //需要交换
                pre->next = behind;
                front->next = behind->next;
                behind->next = front;
                // 把大的（front）交换到后面，大的继续和他的下一位比
                pre = pre->next;
                behind = front->next;
//                pre = behind;
            } else { //不需要交换
                pre = pre->next;
                front = front->next;
                behind = behind->next;
            }
        }
        //behind == nullptr 一趟结束了，最后的是最大的，以后都不用管了
        tail = front;
    }
    return dummyHead->next;
}

ListNode* separateList(ListNode* head) { //切分链表，返回中点
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* newHead = slow->next;
    slow->next = nullptr;
    return newHead;
}
ListNode* mergeList(ListNode* head1, ListNode* head2) {
    ListNode *dummyHead = new ListNode(-1), *head = dummyHead;
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->val <= head2->val) {
            head->next = head1;
            head1 = head1->next;
        } else {
            head->next = head2;
            head2 = head2->next;
        }
        head = head->next;
    }
    if (head1 != nullptr) head->next = head1;
    if (head2 != nullptr) head->next = head2;
    return dummyHead->next;
}
//归并排序,递归
ListNode* sortList(ListNode* head) {
    if (nullptr == head || nullptr == head->next) {
        return head;
    }
    ListNode *mid = separateList(head);
    ListNode* l1 = sortList(head);
    ListNode* l2 = separateList(mid);
    return mergeList(l1, l2);
}

/**
 * 给你两个链表 list1 和 list2 ，它们包含的元素分别为 n 个和 m 个。
 * 请你将 list1 中第 a 个节点到第 b 个节点删除，并将list2 接在被删除节点的位置。
 */
ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
    int index = 0;
    ListNode* pre, *next, *curr;
    curr = list1;
    while (curr != nullptr) {
        if (index == (a - 1)) pre = curr;
        if (index == (b + 1)) next = curr;
        curr = curr->next;
        index++;
    }
    pre->next = list2;
    ListNode* tail = list2;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    tail->next = next;
    return list1;
}

int main() {
    ListNode *node1 = new ListNode(0);
    ListNode *node2 = new ListNode(1);
    ListNode *node3 = new ListNode(2);
    ListNode *node4 = new ListNode(3);
    ListNode *node5 = new ListNode(4);
    ListNode *node6 = new ListNode(5);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;

    ListNode *node1_1 = new ListNode(100000);
    ListNode *node1_2 = new ListNode(100001);
    ListNode *node1_3 = new ListNode(100002);
    node1_1->next = node1_2;
    node1_2->next = node1_3;
    mergeInBetween(node1, 3, 4,node1_1);
}
