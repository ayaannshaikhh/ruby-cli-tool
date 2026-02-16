require_relative "../lib/task_manager"

RSpec.describe TaskManager do
    it "adds a task" do
        TaskManager.add_task("Test task")
        rows = DBExt.list_tasks("db/tasks.db")

        titles = rows.map { |r| r[1] }
        expect(titles).to include("Test task")
    end
end
