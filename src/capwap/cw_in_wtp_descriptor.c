/*
    This file is part of libcapwap.

    libcapwap is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libcapwap is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "capwap.h"
#include "capwap_items.h"

#include "wtpinfo.h"

#include "cw_util.h"
#include "dbg.h"

#include "sock.h"


static int cw_read_wtp_descriptor_versions(cw_itemstore_t itemstore, uint8_t *data,int len)
{
	int i=0;
	do {
		if (i + 8 > len) {
			cw_dbg(DBG_ELEM_ERR,
			       "WTP descriptor subelement to long, length=%d>%d", i + 8,
			       len);
			return 0;
		}

		uint32_t vendor_id = cw_get_dword(data + i);	
		uint32_t val = cw_get_dword(data + i + 4);

		int subtype = (val >> 16) & 0xffff;
		int sublen = val & 0xffff;
		i += 8;

		if (sublen + i > len) {
			cw_dbg(DBG_ELEM_ERR,
			       "WTP Descriptor subelement too long, length = %d", sublen);
			return 0;
		}

		char *dmp;
		char *dmpmem=NULL;
		if (cw_dbg_is_level(DBG_SUBELEM_DMP)) {
			dmpmem=cw_dbg_mkdmp(data+i,sublen);
			dmp=dmpmem;
		}
		else
			dmp="";
		cw_dbg(DBG_SUBELEM, "WTP Descriptor subtype=%d,len=%d%s", subtype, sublen,dmp);

		if (dmpmem)
			free(dmpmem);
		

		switch (subtype) {
			case CW_SUBELEM_WTP_HARDWARE_VERSION:
				cw_itemstore_set_dword(itemstore,
						       CW_ITEM_WTP_HARDWARE_VENDOR,
						       vendor_id);
				cw_itemstore_set_bstrn(itemstore,
						       CW_ITEM_WTP_HARDWARE_VERSION,
						       data + i, sublen);
				break;
			case CW_SUBELEM_WTP_SOFTWARE_VERSION:
				cw_itemstore_set_dword(itemstore,
						       CW_ITEM_WTP_SOFTWARE_VENDOR,
						       vendor_id);
				cw_itemstore_set_bstrn(itemstore,
						       CW_ITEM_WTP_SOFTWARE_VERSION,
						       data + i, sublen);
				break;
			case CW_SUBELEM_WTP_BOOTLOADER_VERSION:
				cw_itemstore_set_dword(itemstore,
						       CW_ITEM_WTP_BOOTLOADER_VENDOR,
						       vendor_id);
				cw_itemstore_set_bstrn(itemstore,
						       CW_ITEM_WTP_BOOTLOADER_VERSION,
						       data + i, sublen);
				break;
			default:
				cw_dbg(DBG_ELEM_ERR,
				       "Unknown WTP descriptor subelement, type = %d",
				       subtype);
				break;
		}
		i += sublen;

	} while (i < len);

	return 1;

}

static int readelem_wtp_descriptor(struct conn *conn, struct cw_action_in *a,
				   uint8_t * data, int len)
{

	if (len < 6) {
		return 0;
	}

	cw_itemstore_t itemstore = conn->incomming;

	cw_itemstore_set_byte(itemstore, CW_ITEM_WTP_MAX_RADIOS, cw_get_byte(data));
	cw_itemstore_set_byte(itemstore, CW_ITEM_WTP_RADIOS_IN_USE,
			      cw_get_byte(data + 1));


	/* Get number of encryption elements */
	int ncrypt = cw_get_byte(data + 2);
	if (ncrypt == 0) {
		if (conn->strict_capwap){
			cw_dbg(DBG_ELEM_ERR,"Bad WTP Descriptor, number of encryption elements is 0.");
			return 0;
		}
		cw_dbg(DBG_RFC,"Non standard conform WTP Descriptor, number of encryptoin elements is 0.");
	}


	int pos = 3;
	int i;
	for (i=0; i<ncrypt; i++) {
		pos+=3;	
	}

	return cw_read_wtp_descriptor_versions(itemstore,data+pos,len-pos);

}

int cw_in_wtp_descriptor(struct conn *conn, struct cw_action_in *a, uint8_t * data,
			 int len,struct sockaddr *from)
{

/*
	switch (conn->capwap_mode) {
		case CW_MODE_STD:
			{
				int rc =
				    readelem_wtp_descriptor(conn, a, data, len,
							    CW_MODE_STD);
				if (!rc) {
					cw_dbg(DBG_ELEM_ERR, "Bad WTP descriptor from %s",
					       sock_addr2str(from));
					return 0;
				}
				return 1;
			}



	}
*/

	int rc = readelem_wtp_descriptor(conn, a, data, len);

/*
	if (rc == -1) {
		cw_dbg(DBG_RFC, "Bad WTP descriptor, trying cisco hack");
		rc = readelem_wtp_descriptor(conn, a, data, len, 1);
	}
*/
	return rc;
}
