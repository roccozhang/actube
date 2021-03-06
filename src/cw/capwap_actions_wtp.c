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
#include "action.h"
#include "capwap_items.h"
#include "capwap_actions.h"
#include "strheap.h"
#include "radio.h"



cw_action_in_t capwap_actions_wtp_in[] = {


	/* ------------------------------------------------------------------------------- */

	/* Message Discovery Response */
	{0, 0, CW_STATE_DISCOVERY, CW_MSG_DISCOVERY_RESPONSE, 0,
	 0, cw_in_check_disc_resp}
	,
	/* AC Descriptor */
	{0, 0, CW_STATE_DISCOVERY, CW_MSG_DISCOVERY_RESPONSE,
	 CW_ACTION_IN_AC_DESCRIPTOR, 1}
	,

	/* AC Name */
	{0, 0, CW_STATE_DISCOVERY, CW_MSG_DISCOVERY_RESPONSE,
	 CW_ACTION_IN_AC_NAME, 1}
	,

	/* CAPWAP Control IPv4 Address */
	{0, 0, CW_STATE_DISCOVERY, CW_MSG_DISCOVERY_RESPONSE,
	 CW_ACTION_IN_CAPWAP_CONTROL_IPV4_ADDRESS, 1}
	,

	/* CAPWAP Control IPv6 Address */
	{0, 0, CW_STATE_DISCOVERY, CW_MSG_DISCOVERY_RESPONSE,
	 CW_ACTION_IN_CAPWAP_CONTROL_IPV6_ADDRESS, 1}
	,

	/* Vendor Specific Payload*/
	{0, 0, CW_STATE_DISCOVERY, CW_MSG_DISCOVERY_RESPONSE,
	 CW_ACTION_IN_VENDOR_SPECIFIC_PAYLOAD, 0}
	,



	/* ------------------------------------------------------------------------------- */

	/* Message Join  Response */
	{0, 0, CW_STATE_JOIN, CW_MSG_JOIN_RESPONSE, 0,
	 0, cw_in_check_join_resp }
	,

	/* Result Code */
	{0, 0, CW_STATE_JOIN, CW_MSG_JOIN_RESPONSE,
	 CW_ACTION_IN_RESULT_CODE, 1}
	,

	/* AC Descriptor */
	{0, 0, CW_STATE_JOIN, CW_MSG_JOIN_RESPONSE,
	 CW_ACTION_IN_AC_DESCRIPTOR, 1}
	,

	/* AC Name */
	{0, 0, CW_STATE_JOIN, CW_MSG_JOIN_RESPONSE,
	 CW_ACTION_IN_AC_NAME, 1}
	,

	
	/* CAPWAP Control IPv4 Address */
	{0, 0, CW_STATE_JOIN, CW_MSG_JOIN_RESPONSE,
	 CW_ACTION_IN_CAPWAP_CONTROL_IPV4_ADDRESS, 1}
	,


	


	/* ------------------------------------------------------------------------------- */

	/* Message Image Data Response */
	{0, 0, CW_STATE_CONFIGURE, CW_MSG_IMAGE_DATA_RESPONSE, 0,
	 0, cw_in_check_img_data_resp }
	,

	/* Element: Result Code */
	{0, 0, CW_STATE_CONFIGURE, CW_MSG_IMAGE_DATA_RESPONSE,
	 CW_ACTION_IN_RESULT_CODE, 1}

	,

	/* ------------------------------------------------------------------------------- */

	/* Message Image Data Request IN */
	{0, 0, CW_STATE_IMAGE_DATA, CW_MSG_IMAGE_DATA_REQUEST, 0,
	 0, cw_in_check_img_data_req_wtp }
	,

		


	/* ------------------------------------------------------------------------------- */

	/* Message Config Status Response IN */
	{0, 0, CW_STATE_CONFIGURE, CW_MSG_CONFIGURATION_STATUS_RESPONSE, 0,
	 0,0  }
	,


	{0, 0, CW_STATE_CONFIGURE, CW_MSG_CONFIGURATION_STATUS_RESPONSE,
	 CW_ACTION_IN_CAPWAP_TIMERS, 1}
	,
	
	{0, 0, CW_STATE_CONFIGURE, CW_MSG_CONFIGURATION_STATUS_RESPONSE,
	 CW_ACTION_IN_IDLE_TIMEOUT, 1}
	,

//	{0, 0, CW_STATE_CONFIGURE, CW_MSG_CONFIGURATION_STATUS_RESPONSE,
//	 CW_ACTION_IN_DECRYPTION_ERROR_REPORT_PERIOD, 1}
//	,

	
	{0, 0, CW_STATE_CONFIGURE, CW_MSG_CONFIGURATION_STATUS_RESPONSE,
	 CW_ACTION_IN_VENDOR_SPECIFIC_PAYLOAD, 0}
	,



	/* ------------------------------------------------------------------------------- */
	/* Message Change State Response IN */
	{0, 0, CW_STATE_CONFIGURE, CW_MSG_CHANGE_STATE_EVENT_RESPONSE, 0,
	 0, cw_in_check_cfg_update_req  }
	,

	/* ------------------------------------------------------------------------------- */
	/* Message Configuration Update Request IN */
	{0, 0, CW_STATE_RUN, CW_MSG_CONFIGURATION_UPDATE_REQUEST, 
	0, 0,0  }
	,

	{0, 0, CW_STATE_RUN, CW_MSG_CONFIGURATION_UPDATE_REQUEST,
	 CW_ACTION_IN_CAPWAP_TIMERS, 0}
	,


	{0, 0, CW_STATE_RUN, CW_MSG_CONFIGURATION_UPDATE_REQUEST,
	 CW_ACTION_IN_RADIO_ADMINISTRATIVE_STATE_WTP, 0}
	,

	{0, 0, CW_STATE_RUN, CW_MSG_CONFIGURATION_UPDATE_REQUEST,
	 CW_ACTION_IN_WTP_NAME, 0}
	,

	/* Location Data */
	{0, 0, CW_STATE_RUN, CW_MSG_CONFIGURATION_UPDATE_REQUEST, 
	CW_ACTION_IN_LOCATION_DATA, 0}
	,


	/* Element: Vendor Specific */
	{0, 0, CW_STATE_RUN, CW_MSG_CONFIGURATION_UPDATE_REQUEST,
	 CW_ACTION_IN_VENDOR_SPECIFIC_PAYLOAD, 0}
	,



	/* ------------------------------------------------------------------------------- */
	/* Echo Response Response IN */
	{0, 0, CW_STATE_RUN, CW_MSG_ECHO_RESPONSE, 0,
	 0,0  }
	,




	/* Element: Vendor Specific */
	{0, 0, CW_STATE_RUN, CW_MSG_ECHO_RESPONSE,
	 CW_ACTION_IN_VENDOR_SPECIFIC_PAYLOAD, 0}
	,




	{0, 0, 0}
};




cw_action_out_t capwap_actions_wtp_out[] = {

	/* -------------------------------------------------------------------------------
	 * Discovery Request OUT
	 */


	{CW_MSG_DISCOVERY_REQUEST, CW_ITEM_NONE}
	,

	/* AC Name */
	{CW_MSG_DISCOVERY_REQUEST, CW_ITEM_DISCOVERY_TYPE, 0,
	 CW_ELEM_DISCOVERY_TYPE, NULL,cw_out_generic, cw_out_get_outgoing}
	,
	{CW_MSG_DISCOVERY_REQUEST, CW_ITEM_WTP_FRAME_TUNNEL_MODE, 0,
	 CW_ELEM_WTP_FRAME_TUNNEL_MODE, NULL,cw_out_generic, cw_out_get_local,1}
	,

	{CW_MSG_DISCOVERY_REQUEST, CW_ITEM_WTP_MAC_TYPE, 0,
	 CW_ELEM_WTP_MAC_TYPE, NULL,cw_out_generic, cw_out_get_local,1}
	,

	/* WTP Board Data */
	{CW_MSG_DISCOVERY_REQUEST, CW_ITEM_WTP_BOARD_DATA, 0,
	 CW_ELEM_WTP_BOARD_DATA, NULL,cw_out_wtp_board_data, cw_out_get_outgoing,1}
	,
	/* WTP Descriptor */
	{CW_MSG_DISCOVERY_REQUEST, CW_ITEM_WTP_DESCRIPTOR, 0, 
	 CW_ELEM_WTP_DESCRIPTOR, NULL,cw_out_wtp_descriptor, NULL,1}
	,
	

	/* -------------------------------------------------------------------------------
	 * Join Request OUT
	 */

	{CW_MSG_JOIN_REQUEST, CW_ITEM_NONE}
	,

	/* Location Data */
	{CW_MSG_JOIN_REQUEST, CW_ITEM_LOCATION_DATA, 0,
	 CW_ELEM_LOCATION_DATA, NULL,cw_out_generic, cw_out_get_config,1}
	,

	/* WTP Board Data */
	{CW_MSG_JOIN_REQUEST, CW_ITEM_WTP_BOARD_DATA, 0,
	 CW_ELEM_WTP_BOARD_DATA, NULL,cw_out_wtp_board_data, cw_out_get_outgoing,1}
	,

	/* WTP Descriptor */
	{CW_MSG_JOIN_REQUEST, CW_ITEM_WTP_DESCRIPTOR, 0, 
	 CW_ELEM_WTP_DESCRIPTOR, NULL,cw_out_wtp_descriptor, NULL,1}
	,
	
	/* WTP Name */
	{CW_MSG_JOIN_REQUEST, CW_ITEM_WTP_NAME, 0,
	 CW_ELEM_WTP_NAME, NULL,cw_out_generic, cw_out_get_config,1}
	,

	/* WTP MAC Type */
	{CW_MSG_JOIN_REQUEST, CW_ITEM_WTP_MAC_TYPE, 0,
	 CW_ELEM_WTP_MAC_TYPE, NULL,cw_out_generic, cw_out_get_config,1}
	,

	/* WTP MAC Type */
	{CW_MSG_JOIN_REQUEST, CW_ITEM_WTP_FRAME_TUNNEL_MODE, 0,
	 CW_ELEM_WTP_FRAME_TUNNEL_MODE, NULL,cw_out_generic, cw_out_get_config,1}
	,

	/* Session ID */
	{CW_MSG_JOIN_REQUEST, CW_ITEM_SESSION_ID, 0,
	 CW_ELEM_SESSION_ID, NULL,cw_out_generic, cw_out_get_session_id,1}
	,


	/* -------------------------------------------------------------------------------
	 * Image Data Request OUT
	 */

	{CW_MSG_IMAGE_DATA_REQUEST, CW_ITEM_NONE}
	,
	/* Image Identifier */
	{CW_MSG_IMAGE_DATA_REQUEST, CW_ITEM_IMAGE_IDENTIFIER, 0,
	 CW_ELEM_IMAGE_IDENTIFIER, NULL,cw_out_generic, cw_out_get_outgoing,0}
	,

	
	/* -------------------------------------------------------------------------------
	 * Image Data Response OUT
	 */
	{CW_MSG_IMAGE_DATA_RESPONSE, CW_ITEM_NONE}
	,

	/* Result Code */
	{CW_MSG_IMAGE_DATA_RESPONSE, CW_ITEM_RESULT_CODE, 0,
	 CW_ELEM_RESULT_CODE, NULL,cw_out_generic, cw_out_get_outgoing, 1}
	,



	/* -------------------------------------------------------------------------------
	 * Configuration Status Request OUT
	 */
	{CW_MSG_CONFIGURATION_STATUS_REQUEST, CW_ITEM_NONE}
	,
	/* AC Name */
	{CW_MSG_CONFIGURATION_STATUS_REQUEST, CW_ITEM_AC_NAME, 0,
	CW_ELEM_AC_NAME, NULL, cw_out_generic, cw_out_get_local,1}
	,

	/* AC Name with Priority */
	{CW_MSG_CONFIGURATION_STATUS_REQUEST, CW_ITEM_AC_NAME_WITH_PRIORITY, 0,
	CW_ELEM_AC_NAME_WITH_PRIORITY, NULL, cw_out_ac_name_with_priority, cw_out_get_config,1}
	,

	/* Radio Admin State */
	{CW_MSG_CONFIGURATION_STATUS_REQUEST, CW_ITEM_RADIO_ADMINISTRATIVE_STATE, 0,
	CW_ELEM_RADIO_ADMINISTRATIVE_STATE, NULL, cw_out_radio_administrative_states, cw_out_get_config,1}
	,


	
		


	/* -------------------------------------------------------------------------------
	 * Configuration Status Request OUT
	 */
	{CW_MSG_CHANGE_STATE_EVENT_REQUEST, CW_ITEM_NONE}
	,

	/* Radio Ooerational State */
	{CW_MSG_CHANGE_STATE_EVENT_REQUEST, CW_ITEM_RADIO_OPER_STATE, 0,
	0, NULL, cw_out_radio_operational_states, cw_out_get_config,1}
	,



	/* -------------------------------------------------------------------------------
	 * Echo Request Request OUT
	 */
	{CW_MSG_ECHO_REQUEST, CW_ITEM_NONE}
	,

	/* -------------------------------------------------------------------------------
	 * Configuration Update Response
	 */
	{CW_MSG_CONFIGURATION_UPDATE_RESPONSE, CW_ITEM_NONE}
	,
	
	/* Radio Oper State */
	{CW_MSG_CONFIGURATION_UPDATE_RESPONSE, CW_ITEM_RADIO_OPER_STATE, 0,
	0, NULL, cw_out_radio_operational_states, cw_out_get_config,1}
	,


	{0, 0}

};





int cw_register_actions_capwap_wtp(struct cw_actiondef *def)
{
	def->in = cw_actionlist_in_create();
	def->out = cw_actionlist_out_create();
	def->strmsg = cw_strheap_create();
	def->strelem = cw_strheap_create();
	def->items = cw_itemdefheap_create();
	def->radioitems = cw_itemdefheap_create();



	int rc;

	rc = cw_actionlist_in_register_actions(def->in, capwap_actions_wtp_in);
	rc += cw_actionlist_out_register_actions(def->out, capwap_actions_wtp_out);

	rc += cw_strheap_register_strings(def->strmsg, capwap_strings_msg);
	rc += cw_strheap_register_strings(def->strelem, capwap_strings_elem);

	rc += cw_itemdefheap_register(def->items,capwap_itemdefs);
	rc += cw_itemdefheap_register(def->radioitems,capwap_radioitemdefs);

	return rc;
}
