/*
 * mlt_events.h -- event handling 
 * Copyright (C) 2004-2005 Ushodaya Enterprises Limited
 * Author: Charles Yates <charles.yates@pandora.be>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _MLT_EVENTS_H_
#define _MLT_EVENTS_H_

#include "mlt_types.h"

#if GCC_VERSION >= 40000
typedef void ( *mlt_transmitter )( void *, ... );
typedef void ( *mlt_listener )( void *, ... );
#else
typedef void ( *mlt_transmitter )( );
typedef void ( *mlt_listener )( );
#endif

extern void mlt_events_init( mlt_properties self );
extern int mlt_events_register( mlt_properties self, char *id, mlt_transmitter transmitter );
extern void mlt_events_fire( mlt_properties self, char *id, ... );
extern mlt_event mlt_events_listen( mlt_properties self, void *service, char *id, mlt_listener listener );
extern void mlt_events_block( mlt_properties self, void *service );
extern void mlt_events_unblock( mlt_properties self, void *service );
extern void mlt_events_disconnect( mlt_properties self, void *service );

extern mlt_event mlt_events_setup_wait_for( mlt_properties self, char *id );
extern void mlt_events_wait_for( mlt_properties self, mlt_event event );
extern void mlt_events_close_wait_for( mlt_properties self, mlt_event event );

extern void mlt_event_inc_ref( mlt_event self );
extern void mlt_event_block( mlt_event self );
extern void mlt_event_unblock( mlt_event self );
extern void mlt_event_close( mlt_event self );

#endif

