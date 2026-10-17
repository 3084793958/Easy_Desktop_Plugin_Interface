#ifndef ARCHIVE_LOADER_INTERFACE_H
#define ARCHIVE_LOADER_INTERFACE_H

#include "interfaces/easy_desktop_class.h"
#include <stddef.h>

struct archive;
struct archive_entry;

#ifndef ARCHIVE_OK
#define ARCHIVE_OK 0
#endif

#ifndef ARCHIVE_EOF
#define ARCHIVE_EOF 1
#endif

class Archive_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual struct archive* archive_read_new() = 0;
    virtual void archive_read_support_filter_all(struct archive *a) = 0;
    virtual void archive_read_support_format_all(struct archive *a) = 0;
    virtual int archive_read_open_filename(struct archive *a, const char *filename, size_t block_size) = 0;
    virtual int archive_read_next_header(struct archive *a, struct archive_entry **entry) = 0;
    virtual const char* archive_entry_pathname(struct archive_entry *entry) = 0;
    virtual int64_t archive_entry_size(struct archive_entry *entry) = 0;
    virtual time_t archive_entry_mtime(struct archive_entry *entry) = 0;
    virtual void archive_read_data_skip(struct archive *a) = 0;
    virtual int archive_read_close(struct archive *a) = 0;
    virtual void archive_read_free(struct archive *a) = 0;

protected:
    virtual ~Archive_Loader_Interface() = default;
};

#endif // ARCHIVE_LOADER_INTERFACE_H
