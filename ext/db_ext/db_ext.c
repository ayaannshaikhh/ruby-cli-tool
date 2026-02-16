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

static VALUE list_tasks(VALUE self, VALUE db_path) {
    sqlite3 *db;
    sqlite3_stmt *stmt;

    sqlite3_open(StringValueCStr(db_path), &db);

    const char *sql = "SELECT id, title, done FROM tasks";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    VALUE results = rb_ary_new();

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *title = sqlite3_column_text(stmt, 1);
        int done = sqlite3_column_int(stmt, 2);

        VALUE row = rb_ary_new();
        rb_ary_push(row, INT2NUM(id));
        rb_ary_push(row, rb_str_new_cstr((const char *)title));
        rb_ary_push(row, INT2NUM(done));

        rb_ary_push(results, row);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return results;
}

static VALUE mark_done(VALUE self, VALUE db_path, VALUE id_val) {
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int id = NUM2INT(id_val);

    sqlite3_open(StringValueCStr(db_path), &db);

    const char *sql = "UPDATE tasks SET done = 1 WHERE id = ?";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return Qtrue;
}

static VALUE delete_task(VALUE self, VALUE db_path, VALUE id_val) {
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int id = NUM2INT(id_val);

    sqlite3_open(StringValueCStr(db_path), &db);

    const char *sql = "DELETE FROM tasks WHERE id = ?";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return Qtrue;
}

void Init_db_ext() {
    VALUE mDBExt = rb_define_module("DBExt");
    rb_define_singleton_method(mDBExt, "add_task", add_task, 2);
    rb_define_singleton_method(mDBExt, "list_tasks", list_tasks, 1);
    rb_define_singleton_method(mDBExt, "mark_done", mark_done, 2);
    rb_define_singleton_method(mDBExt, "delete_task", delete_task, 2);
}