module Formatter
    def self.print_tasks(tasks)
        tasks.each do |task|
            status = task.done? ? "[x]" : "[ ]"
            puts "#{task.id}. #{status} #{task.title}"
        end
    end
end
