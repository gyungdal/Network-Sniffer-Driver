#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <net/ip.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/in.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static const uint16_t port = 25;

static unsigned int hook_func(unsigned int hooknum,
	struct sk_buff **pskb, const struct net_device *in,
		const struct net_device *out, int (*okfn)(struct sk_buff *)){
		
	struct iphdr *iph = ip_hdr(*pskb);
	struct tcphdr *tcph, tcpbuf;
	tcph = skb_header_pointer(*pskb, ip_hdrlen(*pskb), sizeof(*tcph), &tcpbuf);
	printk(KERN_INFO "IP Header Length : %d byte\n", ((int)(iph->ihl))*4);
	printk(KERN_INFO "Type Of Service : %d\n", (int)iph->tos);
	printk(KERN_INFO "Identification : %d\n", (int)ntohs(iph->id));
	printk(KERN_INFO "TTL : %d\n", (int)iph->ttl);
	printk(KERN_INFO "Protocol : %d\n", (int)iph->protocol);
	printk(KERN_INFO "Checkuum : %d\n", (int)ntohs(iph->check));
	printk(KERN_INFO "Source IP : %s\n", inet_ntoa(iph->saddr));
	printk(KERN_INFO "Dest IP : %s\n", inet_ntoa(iph->daddr));
	return NF_ACCEPT;
}


static struct nf_hook_ops hook_info_struct = {
	.hook     = hook_func,
	.hooknum  = NF_INET_PRE_ROUTING,
	.pf       = NFPROTO_IPV4,
	.priority = NF_IP_PRI_FIRST,
};

static __init int init_process(void){
	return nf_register_hook(&hook_info_struct);
}

static __exit void exit_process(void){
	nf_unregister_hook(&hook_info_struct);
}

module_init(init_process);
module_exit(exit_process);