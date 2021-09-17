#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/static_call.h>

void fire_a(struct timer_list *data);
EXPORT_SYMBOL_GPL(fire_a);

struct timer_list timer;
EXPORT_SYMBOL_GPL(timer);

DEFINE_STATIC_CALL(fire, fire_a);
EXPORT_STATIC_CALL_GPL(fire);

void fire_a(struct timer_list *data)
{
	pr_info("FIRE A\n");
	mod_timer(&timer, jiffies + msecs_to_jiffies(500));
}

static void timer_call(struct timer_list *data)
{
	static_call(fire)(data);
}

static int __init static_calls_init(void)
{
	timer_setup(&timer, timer_call, 0);
	mod_timer(&timer, jiffies + msecs_to_jiffies(1000));

	return 0;
}

static void __exit static_calls_exit(void)
{
	del_timer(&timer);
}

module_init(static_calls_init);
module_exit(static_calls_exit);
MODULE_LICENSE("GPL v2");
