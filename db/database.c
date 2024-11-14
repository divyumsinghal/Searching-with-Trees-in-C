//==== NOTE ==================================================================
// You do not need to change anything in this file, but feel free to read it
// if it is of interest.
//
// You only need to update bstdb.c
//============================================================================

#include "database.h"

#include <memory.h>

#include "../bstdb.h"
#include "../bstdb2.h"
#include "listdb.h"

//=== FUNCTION ================================================================
//         Name: database_bind_listdb
//  Description: Point the abstraction layer at the functions for listdb
//=============================================================================
void database_bind_listdb (struct database* db)
{
	if (db)
	{
		memset (db, 0, sizeof (struct database));
		db->init           = listdb_init;
		db->add            = listdb_add;
		db->get_word_count = listdb_get_word_count;
		db->get_name       = listdb_get_name;
		db->stat           = listdb_stat;
		db->quit           = listdb_quit;
	}
}

//=== FUNCTION ================================================================
//         Name: database_bind_listdb
//  Description: Point the abstraction layer at the functions for bstdb
//=============================================================================
void database_bind_bstdb (struct database* db)
{
	if (db)
	{
		memset (db, 0, sizeof (struct database));
		db->init           = bstdb_init;
		db->add            = bstdb_add;
		db->get_word_count = bstdb_get_word_count;
		db->get_name       = bstdb_get_name;
		db->stat           = bstdb_stat;
		db->quit           = bstdb_quit;
	}
}

void database_bind_bstdb_2 (struct database* db)
{
	if (db)
	{
		memset (db, 0, sizeof (struct database));
		db->init           = bstdb_init_2;
		db->add            = bstdb_add_2;
		db->get_word_count = bstdb_get_word_count_2;
		db->get_name       = bstdb_get_name_2;
		db->stat           = bstdb_stat_2;
		db->quit           = bstdb_quit_2;
	}
}