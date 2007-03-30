/*
 * mlt_deque.c -- double ended queue
 * Copyright (C) 2003-2004 Ushodaya Enterprises Limited
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

// Local header files
#include "mlt_deque.h"

// System header files
#include <stdlib.h>
#include <string.h>

typedef union
{
	void *addr;
	int value;
	double floating;
}
deque_entry;

/** Private structure.
*/

struct mlt_deque_s
{
	deque_entry *list;
	int size;
	int count;
};

/** Create a deque.
*/

mlt_deque mlt_deque_init( )
{
	mlt_deque this = malloc( sizeof( struct mlt_deque_s ) );
	if ( this != NULL )
	{
		this->list = NULL;
		this->size = 0;
		this->count = 0;
	}
	return this;
}

/** Return the number of items in the deque.
*/

int mlt_deque_count( mlt_deque this )
{
	return this->count;
}

/** Allocate space on the deque.
*/

static int mlt_deque_allocate( mlt_deque this )
{
	if ( this->count == this->size )
	{
		this->list = realloc( this->list, sizeof( deque_entry ) * ( this->size + 20 ) );
		this->size += 20;
	}
	return this->list == NULL;
}

/** Push an item to the end.
*/

int mlt_deque_push_back( mlt_deque this, void *item )
{
	int error = mlt_deque_allocate( this );

	if ( error == 0 )
		this->list[ this->count ++ ].addr = item;

	return error;
}

/** Pop an item.
*/

void *mlt_deque_pop_back( mlt_deque this )
{
	return this->count > 0 ? this->list[ -- this->count ].addr : NULL;
}

/** Queue an item at the start.
*/

int mlt_deque_push_front( mlt_deque this, void *item )
{
	int error = mlt_deque_allocate( this );

	if ( error == 0 )
	{
		memmove( &this->list[ 1 ], this->list, ( this->count ++ ) * sizeof( deque_entry ) );
		this->list[ 0 ].addr = item;
	}

	return error;
}

/** Remove an item from the start.
*/

void *mlt_deque_pop_front( mlt_deque this )
{
	void *item = NULL;

	if ( this->count > 0 )
	{
		item = this->list[ 0 ].addr;
		memmove( this->list, &this->list[ 1 ], ( -- this->count ) * sizeof( deque_entry ) );
	}

	return item;
}

/** Inquire on item at back of deque but don't remove.
*/

void *mlt_deque_peek_back( mlt_deque this )
{
	return this->count > 0 ? this->list[ this->count - 1 ].addr : NULL;
}

/** Inquire on item at front of deque but don't remove.
*/

void *mlt_deque_peek_front( mlt_deque this )
{
	return this->count > 0 ? this->list[ 0 ].addr : NULL;
}

/** Push an item to the end.
*/

int mlt_deque_push_back_int( mlt_deque this, int item )
{
	int error = mlt_deque_allocate( this );

	if ( error == 0 )
		this->list[ this->count ++ ].value = item;

	return error;
}

/** Pop an item.
*/

int mlt_deque_pop_back_int( mlt_deque this )
{
	return this->count > 0 ? this->list[ -- this->count ].value : 0;
}

/** Queue an item at the start.
*/

int mlt_deque_push_front_int( mlt_deque this, int item )
{
	int error = mlt_deque_allocate( this );

	if ( error == 0 )
	{
		memmove( &this->list[ 1 ], this->list, ( this->count ++ ) * sizeof( deque_entry ) );
		this->list[ 0 ].value = item;
	}

	return error;
}

/** Remove an item from the start.
*/

int mlt_deque_pop_front_int( mlt_deque this )
{
	int item = 0;

	if ( this->count > 0 )
	{
		item = this->list[ 0 ].value;
		memmove( this->list, &this->list[ 1 ], ( -- this->count ) * sizeof( deque_entry ) );
	}

	return item;
}

/** Inquire on item at back of deque but don't remove.
*/

int mlt_deque_peek_back_int( mlt_deque this )
{
	return this->count > 0 ? this->list[ this->count - 1 ].value : 0;
}

/** Inquire on item at front of deque but don't remove.
*/

int mlt_deque_peek_front_int( mlt_deque this )
{
	return this->count > 0 ? this->list[ 0 ].value : 0;
}

/** Push an item to the end.
*/

int mlt_deque_push_back_double( mlt_deque this, double item )
{
	int error = mlt_deque_allocate( this );

	if ( error == 0 )
		this->list[ this->count ++ ].floating = item;

	return error;
}

/** Pop an item.
*/

double mlt_deque_pop_back_double( mlt_deque this )
{
	return this->count > 0 ? this->list[ -- this->count ].floating : 0;
}

/** Queue an item at the start.
*/

int mlt_deque_push_front_double( mlt_deque this, double item )
{
	int error = mlt_deque_allocate( this );

	if ( error == 0 )
	{
		memmove( &this->list[ 1 ], this->list, ( this->count ++ ) * sizeof( deque_entry ) );
		this->list[ 0 ].floating = item;
	}

	return error;
}

/** Remove an item from the start.
*/

double mlt_deque_pop_front_double( mlt_deque this )
{
	double item = 0;

	if ( this->count > 0 )
	{
		item = this->list[ 0 ].floating;
		memmove( this->list, &this->list[ 1 ], ( -- this->count ) * sizeof( deque_entry ) );
	}

	return item;
}

/** Inquire on item at back of deque but don't remove.
*/

double mlt_deque_peek_back_double( mlt_deque this )
{
	return this->count > 0 ? this->list[ this->count - 1 ].floating : 0;
}

/** Inquire on item at front of deque but don't remove.
*/

double mlt_deque_peek_front_double( mlt_deque this )
{
	return this->count > 0 ? this->list[ 0 ].floating : 0;
}

/** Close the queue.
*/

void mlt_deque_close( mlt_deque this )
{
	free( this->list );
	free( this );
}

