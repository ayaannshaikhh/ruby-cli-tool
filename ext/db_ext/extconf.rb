require "mkmf"

have_library("sqlite3")
create_makefile("db_ext")