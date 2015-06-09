#ifndef __RDPDK_ACL_H
#define __RDPDK_ACL_H

#define OPTION_RULE_IPV4	"rule_ipv4"
#define OPTION_RULE_IPV6	"rule_ipv6"
#define OPTION_SCALAR		"scalar"
#define DEFAULT_MAX_CATEGORIES	1

#define OFF_ETHHEAD	(sizeof(struct ether_hdr))
#define OFF_IPV42PROTO (offsetof(struct ipv4_hdr, next_proto_id))
#define OFF_IPV62PROTO (offsetof(struct ipv6_hdr, proto))
#define MBUF_IPV4_2PROTO(m)	\
	(rte_pktmbuf_mtod((m), uint8_t *) + OFF_ETHHEAD + OFF_IPV42PROTO)
#define MBUF_IPV6_2PROTO(m)	\
	(rte_pktmbuf_mtod((m), uint8_t *) + OFF_ETHHEAD + OFF_IPV62PROTO)

int acl_init(void);

struct rte_acl_ctx *setup_acl(struct rte_acl_rule *acl_base,
							  unsigned int acl_num, int ipv6,
							  int socketid);
struct acl_search_t {
	const uint8_t *data_ipv4[MAX_PKT_BURST];
	struct rte_mbuf *m_ipv4[MAX_PKT_BURST];
	uint32_t res_ipv4[MAX_PKT_BURST];
	int num_ipv4;

	const uint8_t *data_ipv6[MAX_PKT_BURST];
	struct rte_mbuf *m_ipv6[MAX_PKT_BURST];
	uint32_t res_ipv6[MAX_PKT_BURST];
	int num_ipv6;
};

struct acl_parm {
	const char *rule_ipv4_name;
	const char *rule_ipv6_name;
	int scalar;
};

extern struct acl_parm acl_parm_config;

extern struct rte_acl_ctx *ipv4_acx[NB_SOCKETS];
extern struct rte_acl_ctx *ipv6_acx[NB_SOCKETS];

#endif
