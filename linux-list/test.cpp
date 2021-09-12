#include <iostream>
#include "list.h"

#define SZ 32
#define CNT 10

struct ourstu {
	char name[SZ];
	int num;
	struct list_head list;
};
//#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
//
//#define container_of(ptr, type, member) ({            \
//    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
//    (type *)( (char *)__mptr - offsetof(type,member) );})



/*����˫��ѭ������*/
LIST_HEAD(head);

static int demo_init(void)
{
	int i;
	struct ourstu* stu;

	struct list_head* pos, * n;

	for (i = 0; i < CNT; i++) {
		stu = (ourstu*)malloc(sizeof(struct ourstu));
		if (nullptr == stu) {
			goto error0;
		}
		printf("size:%d\n", sizeof(struct ourstu));
		printf("before init list:%p\n", &stu->list);
		printf("before init list:%p\n", stu->list);
		INIT_LIST_HEAD(&stu->list);
		printf("after init list:%p\n", &stu->list);
		printf("after init list:%p\n", stu->list);
		stu->num = 100 + i;
		sprintf_s(stu->name, "name%d", i);

		list_add_tail(&stu->list, &head);//�Ƚ��ȳ���β������
	    //list_add(&stu->list, &head);//ջ��ͷ������
	}

	list_for_each(pos, &head) {
		stu = container_of(pos, struct ourstu, list);
		printf("%s's number %d\n", stu->name, stu->num);
		//std::cout << stu->name << "s number " << stu->num << std::endl;
	}
	return 0;

error0:
	list_for_each_safe(pos, n, &head) {
		stu = container_of(pos, struct ourstu, list);//��ѭ���У�����ÿ�����ݣ�����ɾ���ڵ�Ҫ��list_for_each_safe����ɾ��list_for_each����
		printf("%s see bye...\n", stu->name);
		free(stu);
	}

	return -1;
}



static void demo_exit(void)
{
	struct list_head* n, * pos;
	struct ourstu* stu;

	list_for_each_safe(pos, n, &head) {
		stu = container_of(pos, struct ourstu, list);
		printf("%s say bye...\n", stu->name);
		free(stu);//�ͷ�head
	}

	printf("see you, kernel...\n");
}

int main()
{
	demo_init();
	demo_exit();

	while (1);
	return 0;
}