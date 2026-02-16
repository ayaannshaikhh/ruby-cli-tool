# Ruby CLI Project Manager

A simple command-line project manager built in Ruby using Thor and SQLite. 
This tool allows users to create, list, complete, and delete tasks with persistent storage.

This project demonstrates CLI design, database integration, and modular Ruby architecture.

---

## Features

- Add tasks
- List tasks
- Mark tasks as completed
- Delete tasks
- Persistent storage using SQLite
- Automatic database table creation

---

## Tech Stack

- Ruby
- Thor (CLI framework)
- SQLite3

---

## Project Structure

```
ruby-cli-tool/
├── bin/
│   └── pm
├── lib/
│   └── task_manager.rb
├── db/
│   └── tasks.db
├── Gemfile
└── README.md
```

---

## Installation

Clone the repository:

```
git clone <your-repo-url>
cd ruby-cli-tool
```

Install dependencies:

```
bundle install
```

Create the database directory (if needed):

```
mkdir -p db
touch db/tasks.db
```

---

## Usage

Add a task:

```
ruby bin/pm add "Finish assignment"
```

List tasks:

```
ruby bin/pm list
```

Mark a task as done:

```
ruby bin/pm done 1
```

Delete a task:

```
ruby bin/pm delete 1
```

---

## Example Output

```
1. [ ] Finish assignment
2. [x] Study Ruby
```

---

## How It Works

The CLI commands are handled by Thor in `bin/pm`.
Task operations are managed in `TaskManager`, which interacts with a SQLite database.

When the application starts, it automatically ensures the `tasks` table exists:

```
tasks(
  id INTEGER PRIMARY KEY,
  title TEXT,
  done INTEGER
)
```

All task operations use parameterized SQL queries.

---

## Future Improvements

- Task priorities
- Due dates
- Search command
- RSpec tests
- Packaging as a Ruby gem
- Colored terminal output

---