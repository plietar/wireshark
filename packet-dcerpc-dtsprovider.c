/* packet-dcerpc-dtsprovider.c
 * Routines for dcerpc Time server dissection
 * Copyright 2002, Jaime Fournier <jafour1@yahoo.com>
 * This information is based off the released idl files from opengroup.
 * ftp://ftp.opengroup.org/pub/dce122/dce/src/time.tar.gz time/service/dtsprovider.idl
 *
 * $Id: packet-dcerpc-dtsprovider.c,v 1.2 2002/09/17 09:38:04 sahlberg Exp $
 *
 * Ethereal - Network traffic analyzer
 * By Gerald Combs <gerald@ethereal.com>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#include <string.h>

#include <glib.h>
#include <epan/packet.h>
#include "packet-dcerpc.h"
#include "packet-dcerpc-dce122.h"

static int proto_dtsprovider = -1;
static int hf_dtsprovider_opnum = -1;


static gint ett_dtsprovider = -1;


static e_uuid_t uuid_dtsprovider = { 0xbfca1238, 0x628a, 0x11c9, { 0xa0, 0x73, 0x08, 0x00, 0x2b, 0x0d, 0xea, 0x7a } };
static guint16  ver_dtsprovider = 1;


static dcerpc_sub_dissector dtsprovider_dissectors[] = {
    { 0, "ContactProvider", NULL, NULL},
    { 1, "ServerRequestProviderTime", NULL, NULL},
    { 0, NULL, NULL, NULL }
};

static const value_string dtsprovider_opnum_vals[] = {
    { 0, "ContactProvider" },
    { 1, "ServerRequestProviderTime" },
    { 0, NULL }
};

void
proto_register_dtsprovider (void)
{
	static hf_register_info hf[] = {
	  { &hf_dtsprovider_opnum,
	    { "Operation", "dtsprovider.opnum", FT_UINT16, BASE_DEC,
	      VALS(dtsprovider_opnum_vals), 0x0, "Operation", HFILL }}
	};

	static gint *ett[] = {
		&ett_dtsprovider,
	};
	proto_dtsprovider = proto_register_protocol ("Time Service Provider Interfacer", "DTSPROVIDER", "dtsprovider");
	proto_register_field_array (proto_dtsprovider, hf, array_length (hf));
	proto_register_subtree_array (ett, array_length (ett));
}

void
proto_reg_handoff_dtsprovider (void)
{
	/* Register the protocol as dcerpc */
	dcerpc_init_uuid (proto_dtsprovider, ett_dtsprovider, &uuid_dtsprovider, ver_dtsprovider, dtsprovider_dissectors, hf_dtsprovider_opnum);
}
