// SPDX-License-Identifier: GPL-2.0-only
/*
 *  linux/init/version.c
 *
 *  Copyright (C) 1992  Theodore Ts'o
 *
 *  May be freely distributed as part of Linux.
 */

#include <generated/compile.h>
#include <linux/build-salt.h>
#include <linux/export.h>
#include <linux/uts.h>
#include <linux/utsname.h>
#include <generated/utsrelease.h>
#include <linux/version.h>
#include <linux/proc_ns.h>

#if defined(CONFIG_FAKE_UNAME_4_19)
#undef UTS_RELEASE
#define UTS_RELEASE "4.19.325—WearyStars⭐"
#elif defined(CONFIG_FAKE_UNAME_5_4)
#undef UTS_RELEASE
#define UTS_RELEASE "5.4.298—WearyStars⭐"
#elif defined(CONFIG_FAKE_UNAME_5_10)
#undef UTS_RELEASE
#define UTS_RELEASE "5.10.247—WearyStars⭐"
#elif defined(CONFIG_FAKE_UNAME_5_15)
#undef UTS_RELEASE
#define UTS_RELEASE "5.15.200—WearyStars⭐"
#elif defined(CONFIG_FAKE_UNAME_6_1)
#undef UTS_RELEASE
#define UTS_RELEASE "6.1.200—WearyStars⭐"
#elif defined(CONFIG_FAKE_UNAME_6_6)
#undef UTS_RELEASE
#define UTS_RELEASE "6.6.200—WearyStars⭐"
#elif defined(CONFIG_FAKE_UNAME_6_12)
#undef UTS_RELEASE
#define UTS_RELEASE "6.12.200—WearyStars⭐"
#endif

#ifndef CONFIG_KALLSYMS
#define version(a) Version_ ## a
#define version_string(a) version(a)

extern int version_string(LINUX_VERSION_CODE);
int version_string(LINUX_VERSION_CODE);
#endif

struct uts_namespace init_uts_ns = {
	.kref = KREF_INIT(2),
	.name = {
		.sysname	= UTS_SYSNAME,
		.nodename	= UTS_NODENAME,
		.release	= UTS_RELEASE,
		.version	= UTS_VERSION,
		.machine	= UTS_MACHINE,
		.domainname	= UTS_DOMAINNAME,
	},
	.user_ns = &init_user_ns,
	.ns.inum = PROC_UTS_INIT_INO,
#ifdef CONFIG_UTS_NS
	.ns.ops = &utsns_operations,
#endif
};
EXPORT_SYMBOL_GPL(init_uts_ns);

/* FIXED STRINGS! Don't touch! */
const char linux_banner[] =
	"Linux version " UTS_RELEASE " (" LINUX_COMPILE_BY "@"
	LINUX_COMPILE_HOST ") (" LINUX_COMPILER ") " UTS_VERSION "\n";

const char linux_proc_banner[] =
	"%s version %s"
	" (" LINUX_COMPILE_BY "@" LINUX_COMPILE_HOST ")"
	" (" LINUX_COMPILER ") %s\n";

BUILD_SALT;
