#include <assert.h>
#include "kernel.h"
#include "../kernel-module/xt_RTPENGINE.h"

int main(void) {
	int ret;

	ret = kernel_setup_table(0);
	assert(ret == 0);

	struct rtpengine_target_info reti;

	reti = (struct rtpengine_target_info) {
		.local = {
			.family = AF_INET,
			.u.ipv4 = htonl(0x7f000001),
			.port = 4444,
		},
		.expected_src = {
			.family = AF_INET,
			.u.ipv4 = htonl(0x7f000001),
			.port = 4446,
		},
		.src_mismatch = MSM_IGNORE,
		.src_addr = {
			.family = AF_INET,
			.u.ipv4 = htonl(0x7f000001),
			.port = 4448,
		},
		.dst_addr = {
			.family = AF_INET,
			.u.ipv4 = htonl(0x7f000001),
			.port = 4450,
		},
		.decrypt = {
			.cipher = REC_NULL,
			.hmac = REH_NULL,
		},
		.encrypt = {
			.cipher = REC_AEAD_AES_GCM_256,
			.hmac = REH_NULL,
			.master_key_len = 32,
			.master_salt_len = 12,
			.session_key_len = 32,
			.session_salt_len = 12,
			.master_key = {
				0x83, 0x23, 0x10, 0xda, 0x20, 0x92, 0x62, 0xea, 0x7b, 0x36, 0x72, 0xe7,
				0xf3, 0x01, 0x16, 0x4b, 0x1f, 0x7d, 0x74, 0x18, 0xd8, 0xa1, 0x42, 0x55,
				0xcf, 0x33, 0xe4, 0x3e, 0x88, 0x2d, 0x6f, 0x52,

			},
			.master_salt = {
				0x87, 0x1b, 0x19, 0x6e,
				0xb5, 0x3c, 0x16, 0x2d, 0xfc, 0xf3, 0xed, 0x0d
			},
		},
		.payload_types = {0, 8, 102},
		.clock_rates = {8000, 8000, 8000},
		.num_payload_types = 3,
		.rtp = 1,
	};

	ret = kernel_add_stream(&reti);
	assert(ret == 0);

	reti = (struct rtpengine_target_info) {
		.local = {
			.family = AF_INET,
			.u.ipv4 = htonl(0x7f000001),
			.port = 6666,
		},
		.expected_src = {
			.family = AF_INET,
			.u.ipv4 = htonl(0x7f000001),
			.port = 6668,
		},
		.src_mismatch = MSM_IGNORE,
		.src_addr = {
			.family = AF_INET,
			.u.ipv4 = htonl(0x7f000001),
			.port = 6670,
		},
		.dst_addr = {
			.family = AF_INET,
			.u.ipv4 = htonl(0x7f000001),
			.port = 6672,
		},
		.decrypt = {
			.cipher = REC_AEAD_AES_GCM_256,
			.hmac = REH_NULL,
			.master_key_len = 32,
			.master_salt_len = 12,
			.session_key_len = 32,
			.session_salt_len = 12,
			.master_key = {
				0x83, 0x23, 0x10, 0xda, 0x20, 0x92, 0x62, 0xea, 0x7b, 0x36, 0x72, 0xe7,
				0xf3, 0x01, 0x16, 0x4b, 0x1f, 0x7d, 0x74, 0x18, 0xd8, 0xa1, 0x42, 0x55,
				0xcf, 0x33, 0xe4, 0x3e, 0x88, 0x2d, 0x6f, 0x52,

			},
			.master_salt = {
				0x87, 0x1b, 0x19, 0x6e,
				0xb5, 0x3c, 0x16, 0x2d, 0xfc, 0xf3, 0xed, 0x0d
			},
		},
		.encrypt = {
			.cipher = REC_NULL,
			.hmac = REH_NULL,
		},
		.payload_types = {0, 8, 102},
		.clock_rates = {8000, 8000, 8000},
		.num_payload_types = 3,
		.rtp = 1,
	};

	ret = kernel_add_stream(&reti);
	assert(ret == 0);

	return 0;
}
