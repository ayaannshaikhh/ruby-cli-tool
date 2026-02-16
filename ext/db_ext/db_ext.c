#include "ruby.h"
#include <sqlite3.h>

static VALUE add_task(VALUE self, VALUE db_path, VALUE title) {
    sqlite3 *db;
    sqlite3_stmt *stmt;

    sqlite3_open(StringValueCStr(db_path), &db);

    const char *sql = "INSERT INTO tasks (title, done) VALUES (?, 0)";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, StringValueCStr(title), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return Qtrue;
}

void Init_db_ext() {
    VALUE mDBExt = rb_define_module("DBExt");
    rb_define_singleton_method(mDBExt, "add_task", add_task, 2);
}