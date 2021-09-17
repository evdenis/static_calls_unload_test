#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/static_call.h>

extern struct timer_list timer;
extern void fire_a(struct timer_list *data);

DECLARE_STATIC_CALL(fire, fire_a);

static void fire_b(struct timer_list *data)
{
	pr_info("FIRE B\n");
	mod_timer(&timer, jiffies + msecs_to_jiffies(500));
}

static int __init static_calls_init(void)
{
	static_call_update(fire, &fire_b);
	return 0;
}

static void __exit static_calls_exit(void)
{
}

module_init(static_calls_init);
module_exit(static_calls_exit);
MODULE_LICENSE("GPL v2");
