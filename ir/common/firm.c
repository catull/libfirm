/*
 * This file is part of libFirm.
 * Copyright (C) 2012 University of Karlsruhe.
 */

/**
 * @file
 * @brief     Central firm functionality.
 * @author    Martin Trapp, Christian Schaefer, Goetz Lindenmaier
 */
#include <stdio.h>

#ifdef HAVE_FIRM_REVISION_H
# include "firm_revision.h"
#endif
#include "version.h"
#include <stdio.h>
#include "lc_opts.h"
#include "ident_t.h"
#include "firm.h"
#include "irflag_t.h"
#include "tv_t.h"
#include "irprog_t.h"
#include "irnode_t.h"
#include "irmode_t.h"
#include "ircons_t.h"
#include "irgraph_t.h"
#include "type_t.h"
#include "entity_t.h"
#include "irarch.h"
#include "irhooks.h"
#include "iredges_t.h"
#include "irmemory_t.h"
#include "opt_init.h"
#include "debugger.h"
#include "be_t.h"
#include "irtools.h"
#include "execfreq_t.h"

/* returns the firm root */
lc_opt_entry_t *firm_opt_get_root(void)
{
	static lc_opt_entry_t *grp = NULL;
	if (!grp)
		grp = lc_opt_get_grp(lc_opt_root_grp(), "firm");
	return grp;
}

void ir_init(void)
{
	firm_init_flags();
	init_ident();
	init_edges();
	init_tarval_1();
	/* Builds a basic program representation, so modes can be added. */
	init_irprog_1();
	init_mode();
	init_tarval_2();
	firm_init_op();
	firm_init_reassociation();
	firm_init_funccalls();
	firm_init_inline();
	firm_init_scalar_replace();
	/* Builds a construct allowing to access all information to be constructed
	   later. */
	init_irprog_2();
	firm_init_memory_disambiguator();
	firm_init_loop_opt();

	arch_dep_set_opts(arch_dep_none);

	init_execfreq();
	firm_be_init();

#ifdef DEBUG_libfirm
	firm_init_debugger();
#endif
}

void ir_finish(void)
{
#ifdef DEBUG_libfirm
	firm_finish_debugger();
#endif
	exit_execfreq();
	firm_be_finish();

	free_ir_prog();
	firm_finish_op();
	finish_tarval();
	finish_mode();
	finish_ident();
}

unsigned ir_get_version_major(void)
{
	return libfirm_VERSION_MAJOR;
}

unsigned ir_get_version_minor(void)
{
	return libfirm_VERSION_MINOR;
}

const char *ir_get_version_revision(void)
{
#ifdef libfirm_VERSION_REVISION
	return libfirm_VERSION_REVISION;
#else
	return "";
#endif
}

const char *ir_get_version_build(void)
{
	return "";
}
