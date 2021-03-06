/**
 * Setup a sqlite3_wal_replication instance using dqlite's engine.
 */

#ifndef TEST_REPLICATION_H
#define TEST_REPLICATION_H

#include "../../src/replication.h"

#define FIXTURE_REPLICATION sqlite3_wal_replication replication;

#define SETUP_REPLICATION                                                      \
	{                                                                      \
		int rc;                                                        \
		rc = replication__init(&f->replication, &f->config, &f->raft); \
		munit_assert_int(rc, ==, 0);                                   \
	}

#define TEAR_DOWN_REPLICATION replication__close(&f->replication);

#endif /* TEST_REPLICATION_H */
