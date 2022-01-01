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

int get_pfn(struct list_head *src)
{
	int page_count = 0;
	struct page *p = NULL;

	if (list_empty(src)) return 0;
	list_for_each_entry(p, src, lru) {
		page_count++;
	}
	return page_count;
}

int get_ref_count(struct list_head *src, struct mem_cgroup *memcg)
{
	int ref_count = 0;
	struct page *p = NULL;
	unsigned long vm_flags;

	if (list_empty(src)) return 0;
	list_for_each_entry(p, src, lru) {
		if (page_referenced(p, 1, memcg, &vm_flags) > 0) {
			ref_count++;
		}
	}
	return ref_count;
}

int get_demo_promo_count(int category)
{
	if (category == 0)
		return this_cpu_read(vm_event_states.event[PGACTIVATE]);
	else if (category == 1)
		return this_cpu_read(vm_event_states.event[PGDEACTIVATE]);
	else
		return -1;
}

int get_evicted_page_count(int category)
{
	if (category == 0)
		return this_cpu_read(vm_event_states.event[PGSTEAL_ANON]);
	else if (category == 1)
		return this_cpu_read(vm_event_states.event[PGSTEAL_FILE]);
	else
		return -1;
}

SYSCALL_DEFINE0(mm_syscall)
{
	struct pglist_data *current_pglist = NULL;
	struct lruvec *lruvec = NULL;
	struct mem_cgroup *memcg = NULL;
	struct mem_cgroup_per_node *mz;
	int i;

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

		printk(KERN_INFO "The current number of pages in the current LRU page lists\n"); 
		printk(KERN_INFO "LRU_ACTIVE_FILE: %d\n", get_pfn(&lruvec->lists[LRU_ACTIVE_FILE])); 
		printk(KERN_INFO "LRU_INACTIVE_FILE: %d\n", get_pfn(&lruvec->lists[LRU_INACTIVE_FILE])); 
		printk(KERN_INFO "LRU_ACTIVE_ANON: %d\n", get_pfn(&lruvec->lists[LRU_ACTIVE_ANON])); 
		printk(KERN_INFO "LRU_INACTIVE_ANON: %d\n", get_pfn(&lruvec->lists[LRU_INACTIVE_ANON])); 

		pgdat_resize_unlock(current_pglist, 0);

		printk(KERN_INFO "===================================================================================\n"); 

		pgdat_resize_lock(current_pglist, 0);

		memcg = get_mem_cgroup_from_mm(NULL);
		lruvec = mem_cgroup_lruvec(memcg, current_pglist);

		printk(KERN_INFO "The current number of pages those reference bits are set in active/inactive list\n"); 
		printk(KERN_INFO "LRU_ACTIVE_FILE: %d\n", get_ref_count(&lruvec->lists[LRU_ACTIVE_FILE], memcg)); 
		printk(KERN_INFO "LRU_INACTIVE_FILE: %d\n", get_ref_count(&lruvec->lists[LRU_INACTIVE_FILE], memcg)); 
		printk(KERN_INFO "LRU_ACTIVE_ANON: %d\n", get_ref_count(&lruvec->lists[LRU_ACTIVE_ANON], memcg)); 
		printk(KERN_INFO "LRU_INACTIVE_ANON: %d\n", get_ref_count(&lruvec->lists[LRU_INACTIVE_ANON], memcg)); 

		pgdat_resize_unlock(current_pglist, 0);

		printk(KERN_INFO "===================================================================================\n"); 

		pgdat_resize_lock(current_pglist, 0);

		memcg = get_mem_cgroup_from_mm(NULL);
		lruvec = mem_cgroup_lruvec(memcg, current_pglist);

		printk(KERN_INFO "The cumulative number of pages moved from active list to inactive list and vice versa\n"); 
		printk(KERN_INFO "Active to inactive: %d\n", get_demo_promo_count(1)); 
		printk(KERN_INFO "Inactive to active: %d\n", get_demo_promo_count(0)); 

		pgdat_resize_unlock(current_pglist, 0);

		printk(KERN_INFO "===================================================================================\n"); 

		pgdat_resize_lock(current_pglist, 0);

		memcg = get_mem_cgroup_from_mm(NULL);
		lruvec = mem_cgroup_lruvec(memcg, current_pglist);

		printk(KERN_INFO "The cumulative number of pages evicted from inactive list\n"); 
		printk(KERN_INFO "Evicted pages(ANON): %d\n", get_evicted_page_count(0)); 
		printk(KERN_INFO "Evicted pages(FILE): %d\n", get_evicted_page_count(1)); 

		pgdat_resize_unlock(current_pglist, 0);
	}

	return 0;
}