require_relative "../ext/db_ext/db_ext"
require "sqlite3"

require_relative "task"
require_relative "formatter"
require_relative "config"

class TaskManager
    DB_PATH = Config::DB_PATH
    DB = SQLite3::Database.new(DB_PATH)
    schema = File.read("db/schema.sql")
    DB.execute_batch(schema)

    def self.add_task(title)
        DBExt.add_task(DB_PATH, title)
    end

    def self.list_tasks
        rows = DBExt.list_tasks(DB_PATH)
        tasks = rows.map { |r| Task.new(*r) }
        Formatter.print_tasks(tasks)
    end

    def self.mark_done(id)
        DBExt.mark_done(DB_PATH, id + 1)
    end

    def self.delete_task(id)
        DBExt.delete_task(DB_PATH, id + 1)
    end
end