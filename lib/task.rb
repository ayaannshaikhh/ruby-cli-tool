class Task
    attr_reader :id, :title, :done

    def initialize(id, title, done)
        @id = id
        @title = title
        @done = done
    end

    def done?
        @done == 1
    end
end
