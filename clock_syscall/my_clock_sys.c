/* Start of mm_sys.c */
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/mm.h>
#include <linux/rmap.h>
#include <linux/list.h>
#include <linux/cpuset.h>
#include <linux/percpu-defs.h>
#include <linux/vm_event_item.h>
#include <linux/memcontrol.h>
#include <linux/swap.h>
#include <linux/timer.h>
#include <linux/page_ref.h>

#define DELAY (3 * HZ)

void func(void);

struct timer_data {
    int value;
    spinlock_t lock;
    struct timer_list timer;
    bool isActive;
};

struct timer_data my_data = {};

void timer_callback(struct timer_list *timer) {
    struct timer_data *data = from_timer(data, timer, timer);

    data->value++;
    spin_lock(&data->lock);
    if (data->isActive){
        mod_timer(timer, jiffies + DELAY);
        func();
    }
    spin_unlock(&data->lock);
}

void func(void){
    struct pglist_data *current_pglist = NULL;
    struct lruvec *lruvec = NULL;
    struct mem_cgroup *memcg = NULL;
    struct list_head *src;
    int ref_count = 0;
    int i;
    struct page *p = NULL;
    unsigned long vm_flags;

    for (i = 0; i < MAX_NUMNODES; i++) {
        if (NODE_DATA(i) == NULL) 
            continue;
        
        current_pglist = NODE_DATA(i);

        if (current_pglist->node_present_pages == 0) {
            printk(KERN_ALERT "Node-%d does not have any pages.\n", i);
            continue;
        }

        pgdat_resize_lock(current_pglist, 0);

        memcg = get_mem_cgroup_from_mm(NULL);
        lruvec = mem_cgroup_lruvec(memcg, current_pglist);

        /* 모든 page 순회 */

        // 1. LRU_ACTIVE_FILE
        src = &lruvec->lists[LRU_ACTIVE_FILE];

        if (list_empty(src)) return;
        list_for_each_entry(p, src, lru) {
            /* counter에 reference bit 더하기 */

            ref_count = page_referenced(p, 1, memcg, &vm_flags);
            if (ref_count > 0) {
                p->counter += ref_count;  
                /* reference bit 초기화 */
                ClearPageReferenced(p); 
            }

            /* counter 값 최댓값 초과 확인 */
            if(p->counter>100) p->counter = 100;
        }

        // 2. LRU_INACTIVE_FILE
        src = &lruvec->lists[LRU_INACTIVE_FILE];
    
        if (list_empty(src)) return;
        list_for_each_entry(p, src, lru) {
            ref_count = page_referenced(p, 1, memcg, &vm_flags);
            if (ref_count > 0) {
                p->counter += ref_count;  
                /* reference bit 초기화 */
                ClearPageReferenced(p);
            }

            /* counter 값 최댓값 초과 확인 */
            if(p->counter>100) p->counter = 100;
        }

        // 3. LRU_ACTIVE_ANON
        src = &lruvec->lists[LRU_ACTIVE_ANON];
        j = 0;

        if (list_empty(src)) return;
        list_for_each_entry(p, src, lru) {
            ref_count = page_referenced(p, 1, memcg, &vm_flags);
            if (ref_count > 0) {
                p->counter += ref_count;  

                /* reference bit 초기화 */
                ClearPageReferenced(p); 
            }

            /* counter 값 최댓값 초과 확인 */
            if(p->counter>100) p->counter = 100;
        }

        // 4. LRU_INACTIVE_ANON
        src = &lruvec->lists[LRU_INACTIVE_ANON];

        if (list_empty(src)) return;
        list_for_each_entry(p, src, lru) {
            ref_count = page_referenced(p, 1, memcg, &vm_flags);
            if (ref_count > 0) {
                p->counter += ref_count; 
                /* reference bit 초기화 */
                ClearPageReferenced(p); 
            }

            /* counter 값 최댓값 초과 확인 */
            if(p->counter>100) p->counter = 100;
        }
        pgdat_resize_unlock(current_pglist, 0);
    }
}

SYSCALL_DEFINE0(clock_syscall)
{

   printk("[%s] creating timer...\n", __func__);

   /* initialization */
   my_data.isActive = true;
   spin_lock_init(&my_data.lock);
   timer_setup(&my_data.timer, timer_callback, 0);
   mod_timer(&my_data.timer, jiffies + DELAY);

   return 0;
}