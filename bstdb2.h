//==== NOTE ==================================================================
// You do not need to change anything in this file, but feel free to read it
// if it is of interest.
//
// You only need to update bstdb.c
//============================================================================

#ifndef BSTDB2_H
#define BSTDB2_H

int   bstdb_init_2				(void);
int   bstdb_add_2				(char* name, int word_count, char* author);
int   bstdb_get_word_count_2	(int doc_id);
char* bstdb_get_name_2			(int doc_id);
void  bstdb_stat_2				(void);
void  bstdb_quit_2				(void);

#endif