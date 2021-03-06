#ifndef VFS_H_
#define VFS_H_

#include <sqlite3.h>

#include "config.h"

/* Initialize the given SQLite VFS interface with dqlite's in-memory
 * implementation.
 *
 * This function also automatically register the implementation in the global
 * SQLite registry, using the given @name.
 *
 * NOTE: This will make the VFS implement the legacy behavior which depends on
 * patching SQLite. */
int VfsInitV1(struct sqlite3_vfs *vfs, const char *name);

/* Initialize the given SQLite VFS interface with dqlite's custom
 * implementation. */
int VfsInitV2(struct sqlite3_vfs *vfs, const char *name);

/* Release all memory associated with the given dqlite in-memory VFS
 * implementation.
 *
 * This function also automatically unregister the implementation from the
 * SQLite global registry. */
void VfsClose(struct sqlite3_vfs *vfs);

/* Check if the last sqlite3_step() call triggered a write transaction, and
 * return its content if so. */
int VfsPoll(sqlite3_vfs *vfs,
	    const char *database,
	    dqlite_vfs_frame **frames,
	    unsigned *n);

/* Append the given frames to the WAL. */
int VfsApply(sqlite3_vfs *vfs,
	     const char *filename,
	     unsigned n,
	     unsigned long *page_numbers,
	     void *frames);

/* Cancel a pending transaction. */
int VfsAbort(sqlite3_vfs *vfs, const char *filename);

/* Make a full snapshot of a database. */
int VfsSnapshot(sqlite3_vfs *vfs, const char *filename, void **data, size_t *n);

/* Read the content of a file, using the VFS implementation registered under the
 * given name. Used to take database snapshots using the dqlite in-memory
 * VFS. */
int VfsFileRead(const char *vfs_name,
		const char *filename,
		void **buf,
		size_t *len);

/* Write the content of a file, using the VFS implementation registered under
 * the given name. Used to restore database snapshots against the dqlite
 * in-memory VFS. If the file already exists, it's overwritten. */
int VfsFileWrite(const char *vfs_name,
		 const char *filename,
		 const void *buf,
		 size_t len);

#endif /* VFS_H_ */
