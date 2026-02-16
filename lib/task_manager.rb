require "sqlite3"

class TaskManager
    DB = SQLite3::Database.new("db/tasks.db")

    DB.execute <<-SQL
        CREATE TABLE IF NOT EXISTS tasks(
            id INTEGER PRIMARY KEY,
            title TEXT,
            done INTEGER
        );
    SQL

    def self.add_task(title)
        DB.execute("INSERT INTO tasks (title, done) VALUES (?, ?)", [title, 0])
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