require_relative "../ext/db_ext/db_ext"
require "sqlite3"

class TaskManager
    DB_PATH = "db/tasks.db"
    DB = SQLite3::Database.new(DB_PATH)
    schema = File.read("db/schema.sql")
    DB.execute_batch(schema)

    def self.add_task(title)
        DBExt.add_task(DB_PATH, title)
    end

    def self.list_tasks
        rows = DB.execute("SELECT id, title, done FROM tasks")

        rows.each do |id, title, done|
            # Use ternary operator -> if done, mark as [x], if not completed, use [ ]
            status = done == 1 ? "[x]" : "[ ]"
            puts "#{id}. #{status} #{title}"
        end
    end

    def self.mark_done(id)
        DB.execute("UPDATE tasks SET done = 1 WHERE id = ?", [id + 1])
    end

    def self.delete_task(id)
        DB.execute("DELETE FROM tasks WHERE id = ?", [id + 1])
    end
end